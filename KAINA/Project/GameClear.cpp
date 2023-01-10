#include	"GameDefine.h"
#include	"GameClear.h"

//変更するシーン(外部参照、実体はGameApp.cpp)
//extern int						gChangeScene;

/**
 * コンストラクタ
 *
 */

/**
 * デストラクタ
 *
 */
CGameClear::~CGameClear(){
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CGameClear::Load(void){
	//テクスチャの読み込み
	if (!m_BackImage.Load("stage clear.png"))
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
void CGameClear::Initialize(void){
	this->Load();
	m_Alpha = 0;

	m_BGMManager.Initialize();
	m_BGMManager.BGMPlayer(BGM_GAMECLEAR);
}

/**
 * 更新
 *
 */
void CGameClear::Update(void){
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
void CGameClear::Render(void){
	m_BackImage.Render(0, 0);
	CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_WHITE, "Press Enter Key");
}

/**
 * デバッグ描画
 *
 */
void CGameClear::RenderDebug(void){
}

/**
 * 解放
 *
 */
void CGameClear::Release(void){
	m_BackImage.Release();
	m_BGMManager.Release();
}