#include	"GameDefine.h"
#include	"Stage1.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
//extern int						gChangeScene;

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
	m_Stage.Load("ChipData/1-1MAP_noWall.txt",m_NowSceneNo);
	//敵メモリ確保
	int a = m_Stage.GetEnemy1Count();
	m_EnemyArray = new CEnemy[m_Stage.GetEnemy1Count()];
	a = m_Stage.GetEnemy2Count();
	m_Enemy2Array = new CEnemy_2[m_Stage.GetEnemy2Count()];
	//アイテムメモリ確保
	m_ItemArray = new CItem[m_Stage.GetItemCount()];
	//エフェクトの素材読み込み
	m_EffectManager.Load();		
	
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
	m_Player.SetPlayerPos(m_Stage.GetIniPlayerPos().x, m_Stage.GetIniPlayerPos().y);
	//ステージの状態初期化
	m_Stage.Initialize(m_EnemyArray, m_Enemy2Array, m_ItemArray);
	//エフェクトの状態初期化
	m_EffectManager.Initialize();
	//プレイヤーと敵にエフェクトクラスの設定
	m_Player.SetEffectManager(&m_EffectManager);
	for (int i = 0; i < m_Stage.GetEnemy1Count(); i++)
	{
		m_EnemyArray[i].SetEffectManager(&m_EffectManager);
	}
	char* m_pTitle = "ポーズ";
	char* m_pMenuString[TEXTCOUNT_MAX] = {
						"ゲームに戻る",
						"ステージ選択画面へ",
	};
	// ポーズ機能に必要な値を渡す。	
	m_Menu.Create(m_pTitle, m_pMenuString, TEXTCOUNT_MAX);
	m_Alpha = 0;

	m_intervalFire = FIREBAR_INTERVAL;
	m_bFire = false;

	//ステージにエフェクトクラスの設定
	m_Stage.SetEffectManager(&m_EffectManager);
}

/**
 * 更新
 *
 */
void CStage1::Update(void){
	UpdateExitkey();
	//メニュー画面の表示
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
		for (int i = 0; i < m_Stage.GetItemCount(); i++)
		{
			if (m_ItemArray[i].GetType() != BOSS_DOOR)
				continue;

			m_ItemArray[i].StartDoorAnimation();

			if (m_ItemArray[i].IsEndDoorAnimation())
			{
				m_bEnd = true;
				m_SceneNo = SCENENO_GAME_STAGE1_BOSS;
			}
		}
		return;
	}

	//プレイヤーの更新
	m_Player.Update();
	//ステージとプレイヤーの当たり判定
	StgCollPlayer();

	float wx = m_Stage.GetScrollX();
	float wy = m_Stage.GetScrollY();

	StgCollBullet();

	//敵の更新
	StgCollEne();

	//アイテムの更新
	StgCollItm();


	//当たり判定の実行・プレイヤーの座標をセット
	for (int i = 0; i < m_Stage.GetEnemy1Count(); i++)
	{
		m_Player.CollisionEnemy_1(m_EnemyArray[i]);
		m_EnemyArray[i].SetPlayerPos(Vector2(m_Player.GetPosX(), m_Player.GetPosY()));
	}

	//当たり判定の実行・Enemy2にプレイヤーの座標をセット
	for (int i = 0; i < m_Stage.GetEnemy2Count(); i++)
	{
		//TODO::PlayerにCollisionEnemy2の追加
		if (!m_Enemy2Array[i].GetShow())
			continue;

		if (m_Enemy2Array[i].GetRect().CollisionRect(m_Player.GetRect()))
		{
			if (m_Enemy2Array[i].GetPos().x > m_Player.GetPosX())
			{
				//TODO::ダメージ量はあとからEnemyDefineに持たせる
				m_Player.PlayerDamage(true,10);
			}
			else
			{
				m_Player.PlayerDamage(false, 10);
			}
		}

		//弾との判定
		for (int j = 0; j < ENEMY_SHOT_COUNT; j++)
		{
			if (!m_Enemy2Array[i].GetShotShow(j))
				continue;

			if (m_Enemy2Array[i].GetShotRect(j).CollisionRect(m_Player.GetRect()))
			{
				m_Enemy2Array[i].SetShotShow(false, j);
				if (m_Enemy2Array[i].GetShotPos(j).x > m_Player.GetPosX())
				{
					//TODO::上と同様にダメージ量はEnemyDefineに持たせる
					m_Player.PlayerDamage(true, 10);
				}
				else
				{
					m_Player.PlayerDamage(false, 10);
				}
			}
		}

		//TODO::敵とプレイヤーの弾の当たり判定
		//TODO::プレイヤーの弾と敵の弾の当たり判定


		m_Enemy2Array[i].SetTargetPos(m_Player.GetPosX(), m_Player.GetPosY());
	}

	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_Player.ColisionItem(m_ItemArray[i]);
		m_Player.CollisionAttackItem(m_ItemArray[i]);
	}

	//ステージの更新
	m_Stage.Update(m_Player);
	if (m_Player.IsAttack())
	{
		for (int i = 0;i < PLAYERSHOT_COUNT; i++)
		{
			m_Stage.StageAttackCollision(m_Player.GetLaserRect(i));
		}
	}

	//エフェクトの更新
	m_EffectManager.Update();

	//デバッグ用

	//プレイヤーのゴールフラグでリザルト画面へ
	if (m_Player.IsGoal())
	{
		m_bEnd = true;
		m_SceneNo = SCENENO_RESULT;
	}

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
		m_SceneNo = SCENENO_RESULT;
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
	if (m_Stage.Collision(m_Player.GetRect(), ox, oy))
	{
		m_Player.CollisionStage(ox, oy);
	}

	if (!m_Player.IsJump())
	{
		if (m_Stage.CollisionLift(m_Player.GetRect(), ox, oy))
		{
			m_Player.CollisionStage(ox, oy);
		}
	}

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_Player.GetLaserShotShow(i)) { continue; }

		ox = 0, oy = 0;
		if (m_Stage.Collision(m_Player.GetLaserRect(i), ox, oy))
		{
			m_Player.SetWallLaser(i);
		}

		//水と弾の判定
		if (m_Player.GetNatuLaser(i) == FROST)
		{
			m_Stage.CollisionFreezeWater(m_Player.GetLaserRect(i));
		}

		//氷と弾の判定
		if (m_Player.GetNatuLaser(i) == FIRE)
		{
			m_Stage.CollisionIceFroe(m_Player.GetLaserRect(i));
		}
	}

	//砲台とプレイヤーの当たり判定
	for (int i = 0; i < m_Stage.GetEnemy1Count(); i++)
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

		if (m_Stage.FireBar(CRectangle(-m_Stage.GetScrollX() + m_Player.GetRect().Left, -m_Stage.GetScrollY() + m_Player.GetRect().Top, -m_Stage.GetScrollX() + m_Player.GetRect().GetCenter().x - 10, -m_Stage.GetScrollY() + m_Player.GetRect().Bottom), bFireEffect))
		{
			m_Player.PlayerDamage(false, 5);
		}
		if (m_Stage.FireBar(CRectangle(-m_Stage.GetScrollX() + m_Player.GetRect().GetCenter().x + 10, -m_Stage.GetScrollY() + m_Player.GetRect().Top, -m_Stage.GetScrollX() + m_Player.GetRect().Right, -m_Stage.GetScrollY() + m_Player.GetRect().Bottom), bFireEffect))
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
		//m_Stage.FireBar(CRectangle(-m_Stage.GetScrollX() + m_Player.GetRect().Left, -m_Stage.GetScrollY() + m_Player.GetRect().Top, -m_Stage.GetScrollX() + m_Player.GetRect().Left + 1, -m_Stage.GetScrollY() + m_Player.GetRect().Bottom));
		//m_Stage.FireBar(CRectangle(-m_Stage.GetScrollX() + m_Player.GetRect().Right - 1, -m_Stage.GetScrollY() + m_Player.GetRect().Top, -m_Stage.GetScrollX() + m_Player.GetRect().Right, -m_Stage.GetScrollY() + m_Player.GetRect().Bottom));

		if (m_intervalFire <= 0)
		{
			m_bFire = true;
			m_intervalFire = FIREBAR_INTERVAL;
		}
		else
			m_intervalFire -= 1;
	}

}

void CStage1::StgCollBullet() {
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		float ox = 0, oy = 0;
		if (!m_Player.IsLaser()) {
			if (!m_Player.GetNormalShow(i))
			{
				continue;
			}

			CRectangle psrec = m_Player.GetNormalRect(i);
			if (m_Stage.StageAttackCollision(psrec))
			{
				m_Player.SetNormalShotShow(false, i);
				continue;
			}

			//上の判定
			psrec.Bottom = psrec.Top + 1;
			psrec.Expansion(-15, 0);
			if (m_Stage.Collision(psrec))
			{
				m_Player.ShotRefTop(i);
			}

			//下の判定
			psrec = m_Player.GetNormalRect(i);
			psrec.Top = psrec.Bottom - 1;
			psrec.Expansion(-15, 0);
			if (m_Stage.Collision(psrec))
			{
				m_Player.ShotRefBottom(i);
			}

			//左の判定
			psrec = m_Player.GetNormalRect(i);
			psrec.Right = psrec.Left + 1;
			psrec.Expansion(0, -15);
			if (m_Stage.Collision(psrec))
			{
				m_Player.ShotRefLeft(i);
			}

			//右の判定
			psrec = m_Player.GetNormalRect(i);
			psrec.Left = psrec.Right - 1;
			psrec.Expansion(0, -15);
			if (m_Stage.Collision(psrec))
			{
				m_Player.ShotRefRight(i);
			}
		}
		else if (m_Stage.Collision(m_Player.GetLaserRect(i)))
		{
			m_Player.SetWallLaser(i);
		}

		//TODO: 火柱の矩形は完成してる
	}
}

void CStage1::StgCollEne() {
	float PPosX = m_Player.GetPosX() + 30;
	float PPosY = m_Player.GetPosY() + 30;

	for (int i = 0; i < m_Stage.GetEnemy1Count(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		m_EnemyArray[i].SetTargetPos(PPosX, PPosY);
		m_EnemyArray[i].Update(m_Stage.GetScrollX());
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy))
		{
			m_EnemyArray[i].CollisionStage(ox, oy);

			//敵の弾とステージの当たり判定
			for (int j = 0; j < ENEMY_SHOT_COUNT; j++)
			{
				if (m_Stage.Collision(m_EnemyArray[i].ShotArrayRect(j)))
				{
					m_EnemyArray[i].SetShotShow(false, j);
				}
			}
		}
	}

	for (int i = 0; i < m_Stage.GetEnemy2Count(); i++)
	{
		if (!m_Enemy2Array[i].GetShow())
		{
			continue;
		}
		m_Enemy2Array[i].SetTargetPos(PPosX, PPosY);
		m_Enemy2Array[i].Update(m_Stage.GetScrollX());
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_Enemy2Array[i].GetRect(), ox, oy))
		{
			m_Enemy2Array[i].CollisionStage(ox, oy);

			//敵の弾とステージの当たり判定
			for (int j = 0; j < ENEMY_SHOT_COUNT; j++)
			{
				if (m_Stage.Collision(m_Enemy2Array[i].ShotArrayRect(j)))
				{
					m_Enemy2Array[i].SetShotShow(false, j);
				}
			}
		}

		if (m_Enemy2Array[i].GetFallFlg())
		{
			continue;
		}
		if (!m_Stage.Collision(m_Enemy2Array[i].GetLedgeCheckRect()))
		{
			m_Enemy2Array[i].Flip();
		}
	}
}

void CStage1::StgCollItm() {
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_ItemArray[i].Update();
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_ItemArray[i].GetRect(), ox, oy))
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
	//下と当たり判定
	if (eneRect.CollisionRect(brec))
	{
		re = true;
		oy += eneRect.Top - playerRect.Bottom;
		playerRect.Top += eneRect.Top - brec.Bottom;
		playerRect.Bottom += eneRect.Top - brec.Bottom;
	}

	//上の当たり判定
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

	//左右の当たり判定
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
	//ステージの描画
	m_Stage.Render();

	//ドアの描画
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		if (m_ItemArray[i].GetType() == BOSS_DOOR)
		{
			m_ItemArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
		}
	}

	//プレイヤーの描画
	m_Player.Render(m_Stage.GetScrollX(),m_Stage.GetScrollY());

	//敵の描画
	for (int i = 0; i < m_Stage.GetEnemy1Count(); i++)
	{
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}

	//敵2の描画
	for (int i = 0; i < m_Stage.GetEnemy2Count(); i++)
	{
		m_Enemy2Array[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}

	//アイテムの描画
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		if (m_ItemArray[i].GetType() != BOSS_DOOR)
		{
			m_ItemArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
		}
	}

	//エフェクトの描画
	m_EffectManager.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());

	CGraphicsUtilities::RenderString(500 - m_Stage.GetScrollX(), 300 - m_Stage.GetScrollY(), "W,A,S,Dで移動");

	//プレイヤーの状態描画
	m_Player.RenderStatus();

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (m_Stage.Collision(m_Player.GetLaserRect(i)))
		{
			
		}
	}

	CGraphicsUtilities::RenderString(10,10,"ゲーム画面");
	CGraphicsUtilities::RenderString(10,40,"F2キーでゲームクリア、F3キーでゲームオーバー");
	if (m_Menu.IsShow()) {
		m_Menu.Render();
	}
}

/**
 * デバッグ描画
 *
 */
void CStage1::RenderDebug(void){
	//ステージデバッグ描画
	m_Stage.RenderDebug();
	//プレイヤーデバッグ描画
	m_Player.RenderDebug(m_Stage.GetScrollX(),m_Stage.GetScrollY());
	//敵のデバッグ描画
	for (int i = 0; i < m_Stage.GetEnemy1Count(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//敵2のデバッグ描画
	for (int i = 0; i < m_Stage.GetEnemy2Count(); i++)
	{
		m_Enemy2Array[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//アイテムのデバッグ描画
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}

	//エフェクトのデバッグ描画
	m_EffectManager.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
}

/**
 * 解放
 *
 */
void CStage1::Release(void){
	//ステージの開放
	m_Stage.Release(m_NowSceneNo);
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
}