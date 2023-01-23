#include	"GameDefine.h"
#include	"GameOver.h"

/**
 * デストラクタ
 *
 */
CGameOver::~CGameOver(){
	Release();
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CGameOver::Load(void){
	//テクスチャの読み込み
	if (!m_BackImage.Load("BackGround/game over.png"))
	{
		return false;
	}

	m_BGMManager.Load();
	m_SEManager.SelectLoad();


	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * 状態を初期化したいときに実行する。
 */
void CGameOver::Initialize(void){
	Load();

	char* m_pTitle = "リトライしますか？";

	char* m_pMenuString[TEXTCOUNT_MAX] = {
						"リトライする",
						"タイトルへ",
	};
	// ポーズ機能に必要な値を渡す。	
	m_Menu.Create(m_pTitle, m_pMenuString, TEXTCOUNT_MAX);

	m_BGMManager.Initialize();
	m_BGMManager.BGMPlayer(BGM_GAMEOVER);

}

void CGameOver::UpdateMenu() {
	if (m_Menu.IsShow()) {
		m_Menu.Update();
		if (m_Menu.IsEnter()) {
			if (m_Menu.GetSelect() == 0) {
				m_bEnd = true;
				m_SceneNo = (GetOldScene() == SCENENO_GAME_STAGE1) ? SCENENO_GAME_STAGE1 : SCENENO_GAME_STAGE2;
				SetOldScene(SCENENO_GAMEOVER);
			}
			else {
				m_bEnd = true;
				m_SceneNo = SCENENO_TITLE;
				SetOldScene(SCENENO_GAMEOVER);
			}
		}
	}
	else if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {

		m_SEManager.SEPlayer(SE_SELECT_OK);
		m_Menu.Show(Vector2(g_pGraphics->GetTargetWidth() * 0.5f, g_pGraphics->GetTargetHeight() * 0.5f + 150));
	}
}

/**
 * 更新
 *
 */
void CGameOver::Update(void){
	UpdateMenu();
	if (m_Menu.IsShow()) {
		return;
	}

	if (m_FlashCount > 0) {
		m_FlashCount--;
	}
	//Enterキーでタイトル画面へ
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_bEnd)
	{
		m_bEnd = true;
		m_SceneNo = SCENENO_SELECT;
		m_FlashCount = START_FLASH_COUNT;
		m_SEManager.SEPlayer(SE_SELECT_OK);
	}
}

/**
 * 描画
 *
 */
void CGameOver::Render(void){
	m_BackImage.Render(0, 0);

	if (m_Menu.IsShow()) {
		m_Menu.Render();
		return;
	}

	if (m_FlashCount % 4 >= 2)
	{
		return;
	}
	CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() * 0.5 - 100, g_pGraphics->GetTargetHeight() * 0.5 + 200, MOF_COLOR_WHITE, "Press Enter Key");
}

/**
 * デバッグ描画
 *
 */
void CGameOver::RenderDebug(void){
}

/**
 * 解放
 *
 */
void CGameOver::Release(void){
	m_BackImage.Release();
	m_BGMManager.Release();
	m_Menu.Release();
	m_SEManager.SelectRelease();
}