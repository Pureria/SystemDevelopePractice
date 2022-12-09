#include	"GameDefine.h"
#include	"Stage1.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
//extern int						gChangeScene;

/**
 * デストラクタ
 *
 */
CGame::~CGame(){
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CGame::Load(){
	//プレイヤーの素材読み込み
	m_Player.Load();
	//ステージの素材読み込み
	m_Stage.Load("1-1MAP_noWall.txt",m_NowSceneNo);
	//敵メモリ確保
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
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
void CGame::Initialize(){
	
	Load();
	//プレイヤーの状態初期化
	m_Player.Initialize();
	m_Player.SetPlayerPos(m_Stage.GetIniPlayerPos().x, m_Stage.GetIniPlayerPos().y);
	//ステージの状態初期化
	m_Stage.Initialize(m_EnemyArray,m_ItemArray);
	//エフェクトの状態初期化
	m_EffectManager.Initialize();
	//プレイヤーと敵にエフェクトクラスの設定
	m_Player.SetEffectManager(&m_EffectManager);
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
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
void CGame::Update(void){
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


	//当たり判定の実行
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_Player.CollisionEnemy_1(m_EnemyArray[i]);
	}

	//Enemy1にプレイヤーの座標をセット
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].SetPlayerPos(Vector2(m_Player.GetPosX(), m_Player.GetPosY()));
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

void CGame::StgCollPlayer() {
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
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_Player.GetLaserRect(i), ox, oy))
		{
			if (m_Player.IsLaser()) {
				m_Player.SetWallLaser(i);
			}
		}

		//水と弾の判定
		if (m_Player.GetNatuLaser(i) == FROST)
		{
			for (int i = 0; i < PLAYERSHOT_COUNT; i++)
			{
				m_Stage.CollisionFreezeWater(m_Player.GetLaserRect(i));
			}
		}
		//氷と弾の判定
		if (m_Player.GetNatuLaser(i) == FIRE)
		{
			for (int i = 0; i < PLAYERSHOT_COUNT; i++)
			{
				m_Stage.CollisionIceFroe(m_Player.GetLaserRect(i));
			}
		}
	}

	
	//TODO::elseの判定でスクロール値が動いた分当たり判定も変化する
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
			m_Player.PlayerDamage(false);
		}
		if (m_Stage.FireBar(CRectangle(-m_Stage.GetScrollX() + m_Player.GetRect().GetCenter().x + 10, -m_Stage.GetScrollY() + m_Player.GetRect().Top, -m_Stage.GetScrollX() + m_Player.GetRect().Right, -m_Stage.GetScrollY() + m_Player.GetRect().Bottom), bFireEffect))
		{
			m_Player.PlayerDamage(true);
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

void CGame::StgCollBullet() {
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		float ox = 0, oy = 0;
		if (!m_Player.IsLaser()) {
			if (!m_Player.GetNormalShow(i))
			{
				continue;
			}

			CRectangle psrec = m_Player.GetNormalRect(i);
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

void CGame::StgCollEne() {
	float PPosX = m_Player.GetPosX() + 30;
	float PPosY = m_Player.GetPosY() + 30;

	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
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
				ox = 0, oy = 0;
				if (m_Stage.Collision(m_EnemyArray[i].ShotArrayRect(j), ox, oy))
				{
					m_EnemyArray[i].SetShotShow(false, j);
				}
			}
		}
	}
}

void CGame::StgCollItm() {
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
/**
 * 描画
 *
 */
void CGame::Render(void){
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
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
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
			//TODO: 火柱の処理
			CRectangle rec = m_Player.GetLaserRect(i);

			CRectangle FireRec[3] = { CRectangle(rec.Left -= LASER_ATTACKWIDTH, rec.Top - 50, rec.Right, rec.Bottom - 60),
									  CRectangle(rec.Left, rec.Top - 5, rec.Right, rec.Bottom + 5),
									  CRectangle(rec.Left, rec.Top + 60, rec.Right, rec.Bottom + 70),
			};
			for (int j = 0; j < 3; j++)
			{
				MofU32 Color[3] = {
					MOF_COLOR_RED,
					MOF_COLOR_GREEN,
					MOF_COLOR_BLUE,
				};

				CGraphicsUtilities::RenderFillRect(FireRec[j], Color[j]);
			}
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
void CGame::RenderDebug(void){
	//ステージデバッグ描画
	m_Stage.RenderDebug();
	//プレイヤーデバッグ描画
	m_Player.RenderDebug(m_Stage.GetScrollX(),m_Stage.GetScrollY());
	//敵のデバッグ描画
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
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
void CGame::Release(void){
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