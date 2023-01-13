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
	if (!m_BackImage.Load("BackGround/stage clear.png"))
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

	m_Alpha = 255;
}

/**
 * 更新
 *
 */
void CGameClear::Update(void){
#pragma region Fade
	if (m_bFadeIn)
	{
		m_NowTime += CUtilities::GetFrameSecond();
		m_Alpha = (int)m_Function.Animation(0, FADE_TIME, 255, 0, m_NowTime);
		if (m_Alpha <= 0)
			m_bFadeIn = false;
		return;
	}

	if (m_bFadeOut)
	{
		m_NowTime += CUtilities::GetFrameSecond();
		m_Alpha = (int)m_Function.Animation(0, FADE_TIME, 0, 255, m_NowTime);
		if (m_Alpha >= 255)
		{
			m_bEnd = true;
			m_SceneNo = SCENENO_SELECT;
		}

		return;
	}
#pragma endregion

	//Enterキーでタイトル画面へ
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_bEnd)
	{
		m_bFadeOut = true;
		m_Alpha = 0;
		m_NowTime = 0;
	}
}

/**
 * 描画
 *
 */
void CGameClear::Render(void){
	m_BackImage.Render(0, 0);
	CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() * 0.5 - 100, g_pGraphics->GetTargetHeight() * 0.5 + 200, MOF_COLOR_WHITE, "Press Enter Key");

	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_ARGB(m_Alpha, 0, 0, 0));
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