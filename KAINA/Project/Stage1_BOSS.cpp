#include	"GameDefine.h"
#include	"Stage1_BOSS.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
//extern int						gChangeScene;

/**
 * デストラクタ
 *
 */
CStage1_Boss::~CStage1_Boss() {
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CStage1_Boss::Load() {
	//ステージの素材読み込み
	m_Stage.Load("ChipData/1-1bossmap.txt",m_NowSceneNo);
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
void CStage1_Boss::Initialize() {

	Load();
	//プレイヤーの状態初期化
	m_Player.Initialize();
	m_Player.SetPlayerPos(m_Stage.GetIniPlayerPos().x, m_Stage.GetIniPlayerPos().y);
	GetSaveToFile();
	m_Player.SetHp(m_PlayerHp);
	//ボスの状態初期化
	m_Boss.Initialize();

	//ステージの状態初期化
	m_Stage.Initialize(m_ItemArray);
	//エフェクトの状態初期化
	m_EffectManager.Initialize();
	//プレイヤーと敵にエフェクトクラスの設定
	m_Player.SetEffectManager(&m_EffectManager);
	m_Boss.SetEffectManager(&m_EffectManager);

	char* m_pTitle = "ポーズ";
	char* m_pMenuString[TEXTCOUNT_MAX] = {
						"ゲームに戻る",
						"ステージ選択画面へ",
	};
	// ポーズ機能に必要な値を渡す。	
	m_Menu.Create(m_pTitle, m_pMenuString, TEXTCOUNT_MAX);
	m_Alpha = 0;

	m_BGMManager.Initialize();
	m_BGMManager.BGMPlayer(BGM_BOSS1);
}

/**
 * 更新
 *
 */
void CStage1_Boss::Update(void) {
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
				m_SceneNo = SCENENO_RESULT;
			}
		}
		return;
	}

	//プレイヤーの更新
	m_Player.Update();
	StgCollPlayer();
	StgCollBullet();

	//ステージとプレイヤーの当たり判定
	float ox = 0, oy = 0;

	//敵の更新
	StgCollEne();

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_Player.IsLaser()) {
			if (!m_Player.GetNormalShow(i)) { continue; }
			
			CRectangle prec = m_Player.GetNormalRect(i);
			CRectangle erec = m_Boss.GetBossFrontRect();
			if (prec.CollisionRect(erec)) {
				if (m_Player.GetNatuShot(i) == HEAL) {
					m_Boss.Damage(10,true);
					m_Player.SetNormalShotShow(false,i);
				}
				else if (m_Player.GetNatuShot(i) == HEAVY) {
					m_Boss.Damage(12,true);
					m_Player.SetNormalShotShow(false,i);
				}
				continue;
			}
			else {
				erec = m_Boss.GetRect();
				if (prec.CollisionRect(erec)) {
					if (m_Player.GetNatuShot(i) == HEAL) {
						m_Boss.Damage(10, false);
						m_Player.SetNormalShotShow(false, i);
					}
					else if (m_Player.GetNatuShot(i) == HEAVY) {
						m_Boss.Damage(12, false);
						m_Player.SetNormalShotShow(false, i);
					}
					continue;
				}
			}
		}
		else {
			if (!m_Player.GetLaserShotShow(i)) { continue; }
			CRectangle prec = m_Player.GetLaserRect(i);
			CRectangle erec = m_Boss.GetBossFrontRect();
			if (prec.CollisionRect(erec)) {
				if (m_Player.GetNatuLaser(i) == FIRE) {
					m_Boss.Damage(10, true);
					m_Player.SetWallLaser(i);
				}
				else if (m_Player.GetNatuLaser(i) == FROST) {
					m_Boss.Damage(12, true);
					m_Player.SetWallLaser(i);
				}
				continue;
			}
			else {
				erec = m_Boss.GetRect();
				if (prec.CollisionRect(erec)) {
					if (m_Player.GetNatuLaser(i) == FIRE) {
						m_Boss.Damage(10, false);
					}
					else if (m_Player.GetNatuLaser(i) == FROST) {
						m_Boss.Damage(12, false);
					}
					continue;
				}
			}
		}



	}

	//アイテムの更新
	StgCollItm();

	//当たり判定の実行
	m_Player.Collision_Stage1_Boss(m_Boss);

	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_Player.ColisionItem(m_ItemArray[i]);
		m_Player.CollisionAttackItem(m_ItemArray[i]);
	}

	//ステージの更新
	m_Stage.Update(m_Player);

	//エフェクトの更新
	m_EffectManager.Update();

	//スクロール値の固定
	m_Stage.SetScroll(STAGE1_BOSS_FIXSCROLL_WIDTH, STAGE1_BOSS_FIXSCROLL_HEIGHT);

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

void CStage1_Boss::StgCollPlayer()
{
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
}

void CStage1_Boss::StgCollBullet()
{
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

void CStage1_Boss::StgCollEne()
{
	float PPosX = m_Player.GetPosX() + 30;
	float PPosY = m_Player.GetPosY() + 30;

	//ボスの更新
	m_Boss.SetTargetPos(PPosX, PPosY);
	//3 = ダッシュ攻撃中
	/*
	if (m_Boss.GetBossMotionNo() == 3)
	{
		if (m_Stage.Collision(m_Boss.GetBossSideRect()))
		{
			if (m_Boss.GetReverse())
				m_Boss.SetReverse(false);
			else
				m_Boss.SetReverse(true);
			m_Boss.SetMotionMove();
		}
	}
	*/
	m_Boss.Update();
	float ox = 0; float oy = 0;
	if (m_Stage.Collision(m_Boss.GetRect(), ox, oy))
	{
		m_Boss.SetTouchGround(true);
		m_Boss.CollisionStage(ox, oy);
	}

	if (m_Stage.Collision(m_Boss.GetBossSideRect()))
	{
		m_Boss.CollisionWall();
	}

	//4 = ジャンプ攻撃
	if (m_Boss.GetBossMotionNo() == 4)
	{
		if (m_Stage.CollisionBoss1(CRectangle(m_Boss.GetRect().Left, m_Boss.GetRect().Bottom - 1, m_Boss.GetRect().Right, m_Boss.GetRect().Bottom)))
		{
			m_Boss.SetJumpAttackEnd();
		}
	}

	if (!m_Boss.IsJump())
	{
		if (m_Boss.GetBossMotionNo() != 4)
		{
			if (m_Stage.CollisionLift(m_Boss.GetRect(), ox, oy))
			{
				m_Boss.SetTouchGround(true);
				m_Boss.CollisionStage(ox, oy);
			}
		}
	}
}

void CStage1_Boss::StgCollItm()
{
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_ItemArray[i].SetBossEliminated(m_Boss.isBossEliminated());
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
void CStage1_Boss::Render(void) {
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
	m_Player.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());

	//敵の描画
	m_Boss.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());

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

	CGraphicsUtilities::RenderString(10, 10, "ゲーム画面");
	CGraphicsUtilities::RenderString(10, 40, "F2キーでゲームクリア、F3キーでゲームオーバー");
	if (m_Menu.IsShow()) {
		m_Menu.Render();
	}
}

/**
 * デバッグ描画
 *
 */
void CStage1_Boss::RenderDebug(void) {
	//ステージデバッグ描画
	m_Stage.RenderDebug();
	//プレイヤーデバッグ描画
	m_Player.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//敵のデバッグ描画
	m_Boss.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());

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
void CStage1_Boss::Release(void) {
	//ステージの開放
	m_Stage.Release(m_NowSceneNo);
	//プレイヤーの開放
	m_Player.Release();

	//ボスの開放
	m_Boss.Release();

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