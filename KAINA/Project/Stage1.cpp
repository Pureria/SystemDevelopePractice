#include	"GameDefine.h"
#include	"Stage1.h"

/**
 * デストラクタ
 *
 */
CStage1::~CStage1(){
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CStage1::Load(){
	//プレイヤーの素材読み込み
	m_Player.Load();
	//ステージの素材読み込み
	m_BaseStage.Load("ChipData/1-1MAP_noWall.txt",m_NowSceneNo);
	//m_BaseStage.Load("ChipData/New1-1_α.txt", m_NowSceneNo);
	//敵メモリ確保
	m_EnemyArray	= new CEnemy[m_BaseStage.GetEnemy1Count()];
	m_Enemy2Array	= new CEnemy_2[m_BaseStage.GetEnemy2Count()];
	//アイテムメモリ確保
	m_ItemArray		= new CItem[m_BaseStage.GetItemCount()];
	//エフェクトの素材読み込み
	m_EffectManager.Load();	

	//BGMの読み込み
	m_BGMManager.Load();
	
	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * 状態を初期化したいときに実行する。
 */
void CStage1::Initialize(){
	
	Load();
	//プレイヤーの状態初期化
	m_Player.Initialize();
	m_Player.SetSEManager(&m_pSEManager);
	m_Player.SetPlayerPos(m_BaseStage.GetIniPlayerPos().x, m_BaseStage.GetIniPlayerPos().y);
	//ステージの状態初期化
	m_BaseStage.Initialize(m_EnemyArray, m_Enemy2Array, m_ItemArray);
	//エフェクトの状態初期化
	m_EffectManager.Initialize();
	//プレイヤーと敵にエフェクトクラスの設定
	m_Player.SetEffectManager(&m_EffectManager);
	for (int i = 0; i < m_BaseStage.GetEnemy1Count(); i++)
	{
		m_EnemyArray[i].SetEffectManager(&m_EffectManager);
	}
	char* m_pTitle = "ポーズ";
	char* m_pMenuString[TEXTCOUNT_MAX] = {
						"ゲームに戻る",
						"ステージ選択画面へ",
	};

	m_Menu.Create(m_pTitle, m_pMenuString, TEXTCOUNT_MAX);

	m_intervalFire = FIREBAR_INTERVAL;
	m_bFire = false;

	//Enemy2にエフェクトクラスの設定
	for (int i = 0; i < m_BaseStage.GetEnemy2Count(); i++)
	{
		m_Enemy2Array[i].SetEffectManager(&m_EffectManager);
		m_Enemy2Array[i].SetSEManager(&m_pSEManager);
	}

	//ステージにエフェクトクラスの設定
	m_BaseStage.SetEffectManager(&m_EffectManager);
	//ステージにSEマネージャーの設定
	m_BaseStage.SetSEManager(&m_pSEManager);

	//BGMの初期化
	m_BGMManager.Initialize();
	m_BGMManager.BGMPlayer(BGM_STAGE1);
}

/**
 * 更新
 *
 */
void CStage1::Update(void){
#pragma region Fade
	if (m_bFadeIn)
	{
		m_NowTime += CUtilities::GetFrameSecond();
		m_Alpha = (int)m_Function.Animation(0, FADE_TIME, 255, 0, m_NowTime);
		if (m_Alpha <= 0)
			m_bFadeIn = false;
	}

	if (m_bFadeOut)
	{
		m_NowTime += CUtilities::GetFrameSecond();
		m_Alpha = (int)m_Function.Animation(0, FADE_TIME, 0, 255, m_NowTime);
		if (m_Alpha >= 255)
		{
			m_bEnd = true;
			m_SceneNo = SCENENO_GAMECLEAR;
		}
		return;
	}
#pragma endregion

	UpdateExitkey();

	if (m_Menu.IsShow()) {
		m_Menu.Update();
		if (m_Menu.IsEnter()) {
			if (m_Menu.GetSelect() == 1) {
				m_bEnd = true;
				m_SceneNo = SCENENO_SELECT;
			}
			m_Menu.Hide();
		}
		return;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
		m_Menu.Show(Vector2(g_pGraphics->GetTargetWidth() * 0.5f, g_pGraphics->GetTargetHeight() * 0.5f));
	}

	//ボス部屋ドアアニメーション
	if (m_Player.GetNextBossScene())
	{
		for (int i = 0; i < m_BaseStage.GetItemCount(); i++)
		{
			if (m_ItemArray[i].GetType() != BOSS_DOOR)
				continue;

			m_ItemArray[i].StartDoorAnimation();

			if (m_ItemArray[i].IsEndDoorAnimation())
			{
				m_bFadeOut = true;
				m_Alpha = 0;
				m_NowTime = 0;
				m_PlayerHp = m_Player.GetHp();
				SetSaveToFile();
				break;
			}
		}
		return;
	}

	//プレイヤーの更新
	m_Player.Update();
	//ステージとプレイヤーの当たり判定
	StgCollPlayer();

	float wx = m_BaseStage.GetScrollX();
	float wy = m_BaseStage.GetScrollY();

	StgCollBullet();

	//敵の更新
	StgCollEne();

	//アイテムの更新
	StgCollItm();

	//ステージの更新
	m_BaseStage.Update(m_Player);

	//エフェクトの更新
	m_EffectManager.Update();

	//F2キーでリザルト画面へ
	if (g_pInput->IsKeyPush(MOFKEY_F2))
	{
		m_bEnd = true;
		m_SceneNo = SCENENO_GAMECLEAR;
	}

	//プレイヤーの終了フラグでリザルト画面へ
	if (m_Player.IsEnd())
	{
		m_bEnd = true;
		m_SceneNo = SCENENO_GAMEOVER;
	}

	//F3キーでリザルト画面へ
	if (g_pInput->IsKeyPush(MOFKEY_F3))
	{
		m_bEnd = true;
		m_SceneNo = SCENENO_GAMEOVER;
	}
}

void CStage1::StgCollPlayer() {
	float ox = 0, oy = 0;
	if (m_BaseStage.Collision(m_Player.GetRect(), ox, oy))
	{
		m_Player.CollisionStage(ox, oy);
	}

	if (!m_Player.IsJump())
	{
		if (m_BaseStage.CollisionLift(m_Player.GetRect(), ox, oy))
		{
			m_Player.CollisionStage(ox, oy);
		}
	}

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_Player.GetLaserShotShow(i)) { continue; }

		ox = 0, oy = 0;
		if (m_BaseStage.Collision(m_Player.GetLaserRect(i), ox, oy))
		{
			m_Player.SetWallLaser(i,true);
		}

		if (m_Player.IsLaser(i)) {
			m_BaseStage.CollisionCrack(m_Player.GetLaserRect(i));
		}

		//TODO: 水と弾の判定
		if (m_Player.GetNatuLaser(i) == FROST)
		{
			m_BaseStage.CollisionFreezeWater(m_Player.GetLaserRect(i),m_Player.GetRect());
		}

		//TODO: 氷と弾の判定
		if (m_Player.GetNatuLaser(i) == FIRE)
		{
			m_BaseStage.CollisionIceFroe(m_Player.GetLaserRect(i));
		}
	}

	//TODO: 砲台とプレイヤーの当たり判定
	for (int i = 0; i < m_BaseStage.GetEnemy1Count(); i++)
	{
		ox = 0; oy = 0;
		if (EnemyOnPlayer(m_EnemyArray[i].GetRect(), m_Player.GetRect(), ox, oy))
		{
			m_Player.CollisionStage(ox, oy);
		}

	}

	//炎の判定
	if (m_bFire)
	{
		bool	bFireEffect;
		if (m_intervalFire == FIREBAR_INTERVAL)
			bFireEffect = true;
		else
			bFireEffect = false;

		if (m_BaseStage.FireBar(CRectangle(-m_BaseStage.GetScrollX() + m_Player.GetRect().Left, -m_BaseStage.GetScrollY() + m_Player.GetRect().Top, -m_BaseStage.GetScrollX() + m_Player.GetRect().GetCenter().x - 10, -m_BaseStage.GetScrollY() + m_Player.GetRect().Bottom), bFireEffect))
		{
			m_Player.PlayerDamage(false, 5);
		}
		if (m_BaseStage.FireBar(CRectangle(-m_BaseStage.GetScrollX() + m_Player.GetRect().GetCenter().x + 10, -m_BaseStage.GetScrollY() + m_Player.GetRect().Top, -m_BaseStage.GetScrollX() + m_Player.GetRect().Right, -m_BaseStage.GetScrollY() + m_Player.GetRect().Bottom), bFireEffect))
		{
			m_Player.PlayerDamage(true, 5);
		}

		if (m_intervalFire <= 0)
		{
			m_bFire = false;
			m_intervalFire = FIREBAR_INTERVAL;
		}
		else
			m_intervalFire -= 1;
	}
	else
	{
		for (int i = 0; i < SE_COUNT; i++)
		{
			if (m_pSEManager.GetNowSetSE() == SE_BURNER &&m_pSEManager.IsPlaySE())
				m_pSEManager.StopSE();
		}

		m_EffectManager.Stop(EFC_FIREBAR_TOP);
		m_EffectManager.Stop(EFC_FIREBAR_BOTTOM);

		if (m_intervalFire <= 0)
		{
			m_bFire = true;
			m_intervalFire = FIREBAR_INTERVAL;
		}
		else
			m_intervalFire -= 1;
	}


	if (m_BaseStage.CollisionWater(m_Player.GetRect()))
	{
		m_Player.PlayerDamage(1);
	}

}

void CStage1::StgCollBullet() {

	float x, y;
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (m_BaseStage.GetMapChipPos(m_Player.GetLaserRect(i), x, y, false)) {
			m_Player.SetMapChipPos(Vector2(x, y), i);
		}
		if (m_Player.GetLaserShotShow(i)) {
			m_BaseStage.StageAttackCollision(m_Player.GetLaserRect(i));
		}
	}

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		float ox = 0, oy = 0;
		if (!m_Player.GetNormalShow(i))
		{
			continue;
		}

		CRectangle psrec = m_Player.GetNormalRect(i);
		if (m_BaseStage.StageAttackCollision(psrec))
		{
			m_Player.SetNormalShotShow(false, i);
			continue;
		}

		//上の判定
		psrec.Bottom = psrec.Top + 1;
		psrec.Expansion(-15, 0);
		if (m_BaseStage.Collision(psrec))
		{
			m_Player.ShotRefTop(i);
			for (int j = 0; j < SE_COUNT; j++)
			{
				if (m_pSEManager.IsPlaySE())
					continue;
				m_pSEManager.SEPlayer(SE_WALL_CONTACT);
				break;
			}
		}

		//下の判定
		psrec = m_Player.GetNormalRect(i);
		psrec.Top = psrec.Bottom - 1;
		psrec.Expansion(-15, 0);
		if (m_BaseStage.Collision(psrec))
		{
			m_Player.ShotRefBottom(i);
			for (int j = 0; j < SE_COUNT; j++)
			{
				if (m_pSEManager.IsPlaySE())
					continue;
				m_pSEManager.SEPlayer(SE_WALL_CONTACT);
				break;
			}
		}

		//左の判定
		psrec = m_Player.GetNormalRect(i);
		psrec.Right = psrec.Left + 1;
		psrec.Expansion(0, -15);
		if (m_BaseStage.Collision(psrec))
		{
			m_Player.ShotRefLeft(i);
			for (int j = 0; j < SE_COUNT; j++)
			{
				if (m_pSEManager.IsPlaySE())
					continue;
				m_pSEManager.SEPlayer(SE_WALL_CONTACT);
				break;
			}
		}

		//右の判定
		psrec = m_Player.GetNormalRect(i);
		psrec.Left = psrec.Right - 1;
		psrec.Expansion(0, -15);
		if (m_BaseStage.Collision(psrec))
		{
			m_Player.ShotRefRight(i);
			for (int j = 0; j < SE_COUNT; j++)
			{
				if (m_pSEManager.IsPlaySE())
					continue;
				m_pSEManager.SEPlayer(SE_WALL_CONTACT);
				break;
			}
		}
	}
}

void CStage1::StgCollEne() {
	float PPosX = m_Player.GetPosX() + 30;
	float PPosY = m_Player.GetPosY() + 30;

	for (int i = 0; i < m_BaseStage.GetEnemy1Count(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		m_EnemyArray[i].SetTime(Time());
		m_Player.CollisionEnemy(m_EnemyArray[i], m_EnemyArray[i].GetEnemyType());
		m_EnemyArray[i].Update(m_BaseStage.GetScrollX());
		float ox = 0, oy = 0;
		if (m_BaseStage.Collision(m_EnemyArray[i].GetRect(), ox, oy))
		{
			m_EnemyArray[i].CollisionStage(ox, oy);

			//TODO: 敵の弾とステージの当たり判定
			for (int j = 0; j < ENEMY_SHOT_COUNT; j++)
			{
				if (m_BaseStage.Collision(m_EnemyArray[i].ShotArrayRect(j)))
				{
					m_EnemyArray[i].SetShotShow(false, j);
				}
			}
		}
	}

	for (int i = 0; i < m_BaseStage.GetEnemy2Count(); i++)
	{
		if (!m_Enemy2Array[i].GetShow())
		{
			continue;
		}
		if (!m_BaseStage.Collision(m_Enemy2Array[i].GetLedgeCheckRect()) && !m_Enemy2Array[i].GetKnockback())
		{
			m_Enemy2Array[i].Flip();
		}
		m_Player.CollisionEnemy(m_Enemy2Array[i], m_Enemy2Array[i].GetEnemyType());
		m_Enemy2Array[i].SetTime(Time());
		m_Enemy2Array[i].SetTargetPos(PPosX, PPosY);
		m_Enemy2Array[i].Update(m_BaseStage.GetScrollX());
		float ox = 0, oy = 0;
		if (m_BaseStage.Collision(m_Enemy2Array[i].GetRect(), ox, oy))
		{
			m_Enemy2Array[i].CollisionStage(ox, oy);

			//TODO: 敵の弾とステージの当たり判定
			for (int j = 0; j < ENEMY_SHOT_COUNT; j++)
			{
				if (m_BaseStage.Collision(m_Enemy2Array[i].ShotArrayRect(j)))
				{
					m_Enemy2Array[i].SetShotShow(false, j);
				}
			}
		}

		if (m_Enemy2Array[i].GetFallFlg())
			continue;
	}
}

void CStage1::StgCollItm() {
	for (int i = 0; i < m_BaseStage.GetItemCount(); i++)
	{
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_Player.ColisionItem(m_ItemArray[i]);
		m_Player.CollisionAttackItem(m_ItemArray[i]);
		m_ItemArray[i].SetBossEliminated(true);
		m_ItemArray[i].Update();
		float ox = 0, oy = 0;
		if (m_BaseStage.Collision(m_ItemArray[i].GetRect(), ox, oy))
		{
			m_ItemArray[i].CollisionStage(ox, oy);
		}
	}
}

bool CStage1::EnemyOnPlayer(CRectangle eneRect, CRectangle playerRect, float& ox, float& oy)
{
	bool re = false;

	CRectangle brec = playerRect;
	brec.Top = brec.Bottom - 1;
	brec.Expansion(-6, -0);
	//TODO: 下と当たり判定
	if (eneRect.CollisionRect(brec))
	{
		re = true;
		oy += eneRect.Top - playerRect.Bottom;
		playerRect.Top += eneRect.Top - brec.Bottom;
		playerRect.Bottom += eneRect.Top - brec.Bottom;
	}

	//TODO: 上の当たり判定
	CRectangle trec = playerRect;
	trec.Bottom = trec.Top + 1;
	trec.Expansion(-12, 0);
	if (eneRect.CollisionRect(trec))
	{
		re = true;
		oy += eneRect.Bottom - trec.Top;
		playerRect.Top += eneRect.Bottom - trec.Top;
		playerRect.Bottom += eneRect.Bottom - trec.Top;
	}

	//TODO: 左右の当たり判定
	CRectangle lrec = playerRect;
	lrec.Right = lrec.Left + 1;
	lrec.Expansion(0, -12);
	CRectangle rrec = playerRect;
	rrec.Left = rrec.Right - 1;
	rrec.Expansion(0, -12);

	if (eneRect.CollisionRect(lrec))
	{
		re = true;
		ox += eneRect.Right - lrec.Left;
		playerRect.Left += eneRect.Right - lrec.Left;
		playerRect.Right += eneRect.Right - lrec.Left;
	}
	else if (eneRect.CollisionRect(rrec))
	{
		re = true;
		ox += eneRect.Left - rrec.Right;
		playerRect.Left += eneRect.Left - rrec.Right;
		playerRect.Right += eneRect.Left - rrec.Right;
	}

	return re;
}

/**
 * 描画
 *
 */
void CStage1::Render(void){
	m_BaseStage.BackTexRender();
	m_Player.ShotRender(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
	m_BaseStage.Render();


	//ドアの描画
	for (int i = 0; i < m_BaseStage.GetItemCount(); i++)
	{
		if (m_ItemArray[i].GetType() == BOSS_DOOR)
		{
			m_ItemArray[i].Render(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
		}
	}

	//プレイヤーの描画
	m_Player.Render(m_BaseStage.GetScrollX(),m_BaseStage.GetScrollY());

	//敵の描画
	for (int i = 0; i < m_BaseStage.GetEnemy1Count(); i++)
	{
		m_EnemyArray[i].Render(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
	}

	//敵2の描画
	for (int i = 0; i < m_BaseStage.GetEnemy2Count(); i++)
	{
		m_Enemy2Array[i].Render(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
	}

	//アイテムの描画
	for (int i = 0; i < m_BaseStage.GetItemCount(); i++)
	{
		if (m_ItemArray[i].GetType() != BOSS_DOOR)
		{
			m_ItemArray[i].Render(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
		}
	}

	//エフェクトの描画
	m_EffectManager.Render(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());

	//プレイヤーの状態描画
	m_Player.RenderStatus();

	if (m_Menu.IsShow()) {
		m_Menu.Render();
	}

	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_ARGB(m_Alpha, 0, 0, 0));
}

/**
 * デバッグ描画
 *
 */
void CStage1::RenderDebug(void){
	//ステージデバッグ描画
	m_BaseStage.RenderDebug();
	//プレイヤーデバッグ描画
	m_Player.RenderDebug(m_BaseStage.GetScrollX(),m_BaseStage.GetScrollY());
	//敵のデバッグ描画
	for (int i = 0; i < m_BaseStage.GetEnemy1Count(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
	}
	//敵2のデバッグ描画
	for (int i = 0; i < m_BaseStage.GetEnemy2Count(); i++)
	{
		m_Enemy2Array[i].RenderDebug(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
	}
	//アイテムのデバッグ描画
	for (int i = 0; i < m_BaseStage.GetItemCount(); i++)
	{
		m_ItemArray[i].RenderDebug(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
	}

	//エフェクトのデバッグ描画
	m_EffectManager.RenderDebug(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
}

/**
 * 解放
 *
 */
void CStage1::Release(void){
	//ステージの開放
	m_BaseStage.Release(m_NowSceneNo);
	//プレイヤーの開放
	m_Player.Release();
	//敵の解放
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//敵2の開放
	if (m_Enemy2Array)
	{
		delete[] m_Enemy2Array;
		m_Enemy2Array = NULL;
	}
	//アイテムの解放
	if (m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	
	//エフェクトの解放
	m_EffectManager.Release();
	m_Menu.Release();
	m_BGMManager.Release();
}