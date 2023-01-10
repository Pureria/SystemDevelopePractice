#include	"GameDefine.h"
#include	"Title.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
//extern int						gChangeScene;

/**
 * デストラクタ
 *
 */
CTitle::~CTitle(){}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CTitle::Load(void){
	//テクスチャの読み込み
	if (!m_BackImage.Load("BackGround/Title.png"))
		return false;
	
	if (!m_SelectArrow.Load("SelectArrow.png"))
		return false;

	m_BGMManager.Load();

	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * 状態を初期化したいときに実行する。
 */
void CTitle::Initialize(void){

	this->Load();

	m_bSelectArrow = true;

	m_Alpha = 0;

	char* m_pTitle = "ゲームを終了しますか？";

	char* m_pMenuString[TEXTCOUNT_MAX] = {
						"いいえ",
						"はい",
	};
	// ポーズ機能に必要な値を渡す。	
	m_Menu.Create(m_pTitle, m_pMenuString, TEXTCOUNT_MAX);

	m_BGMManager.Initialize();
	m_BGMManager.BGMPlayer(BGM_TITLE);
}

/**
 * 更新
 *
 */
void CTitle::Update(void){
	UpdateExitkey();
	UpdateMenu();

	if (m_Menu.IsShow()) {
		return;
	}
	UpdateSelect();
	//Enterキーでゲーム画面へ
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && m_bSelectArrow && !m_bEnd) {
		m_bEnd = true;
		m_SceneNo = SCENENO_SELECT;
	}
}

/*
* 画面選択
*
*/
void CTitle::UpdateSelect() {

	if (g_pInput->IsKeyPush(MOFKEY_UP) || g_pInput->IsKeyPush(MOFKEY_DOWN))
	{
		if (!m_bSelectArrow)
			m_bSelectArrow = true;
		else
			m_bSelectArrow = false;
	}
}
/*
* ゲーム終了確認のメニュー表示
*
*/
void CTitle::UpdateMenu() {

	if (m_Menu.IsShow()) {
		m_Menu.Update();
		if (m_Menu.IsEnter()) {
			if (m_Menu.GetSelect() == 0) {
				m_Menu.Hide();
			}
			else {
				exit(0);
			}
		}
	}
	else if (!m_bSelectArrow) {
		if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
			m_Menu.Show(Vector2(g_pGraphics->GetTargetWidth() * 0.5f, g_pGraphics->GetTargetHeight() * 0.5f));
		}
	}
}
/**
 * 描画
 *
 */
void CTitle::Render(void){
	CGraphicsUtilities::RenderFillRect(0, 0, 1024, 768, MOF_COLOR_WHITE);
	m_BackImage.Render(0, 0);

	CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() / 2.5, g_pGraphics->GetTargetHeight() / 1.3, MOF_XRGB( 0, 0, 0), "ゲームスタート");
	CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() / 2.2, g_pGraphics->GetTargetHeight() / 1.2, MOF_XRGB(0, 0, 0), "終了");

	(m_bSelectArrow) ?	m_SelectArrow.Render(g_pGraphics->GetTargetWidth() / 3.5, g_pGraphics->GetTargetHeight() / 1.35, MOF_XRGB(255, 255, 255)) :
		m_SelectArrow.Render(g_pGraphics->GetTargetWidth() / 3.5, g_pGraphics->GetTargetHeight() / 1.25, MOF_XRGB(255, 255, 255));

	if (m_Menu.IsShow()) {
		m_Menu.Render();
	}
	
}

/**
 * デバッグ描画
 *
 */
void CTitle::RenderDebug(void){

}

/**
 * 解放
 *
 */
void CTitle::Release(void){
	m_BackImage.Release();
	m_SelectArrow.Release();
	m_Menu.Release();
	m_BGMManager.Release();
}