#include	"GameDefine.h"
#include	"GameOver.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
//extern int						gChangeScene;


/**
 * デストラクタ
 *
 */
CGameOver::~CGameOver(){
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CGameOver::Load(void){
	//テクスチャの読み込み
	if (!m_BackImage.Load("game over.png"))
	{
		return false;
	}

	m_BGMManager.Load();

	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * 状態を初期化したいときに実行する。
 */
void CGameOver::Initialize(void){
	Load();

	m_BGMManager.Initialize();
	m_BGMManager.BGMPlayer(BGM_GAMEOVER);
}

/**
 * 更新
 *
 */
void CGameOver::Update(void){
	//Enterキーでタイトル画面へ
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_bEnd && m_NowScene == m_SceneNo)
	{
		m_bEnd = true;
		m_SceneNo = SCENENO_RESULT;
	}
}

/**
 * 描画
 *
 */
void CGameOver::Render(void){
	m_BackImage.Render(0, 0);
	CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() * 0.5, g_pGraphics->GetTargetHeight() * 0.5, MOF_COLOR_WHITE, "Press Enter Key");
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
}