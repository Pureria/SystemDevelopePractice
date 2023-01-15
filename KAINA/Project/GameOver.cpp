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
	if (!m_BackImage.Load("BackGround/game over.png"))
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
	UpdateExitkey();
	if (m_FlashCount > 0) {
		m_FlashCount--;
	}
	//Enterキーでタイトル画面へ
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_bEnd)
	{
		m_bEnd = true;
		m_SceneNo = SCENENO_SELECT;
		m_FlashCount = START_FLASH_COUNT;
		for (int i = 0; i < SE_COUNT; i++)
		{
			if (m_SEManager[i].IsPlaySE())
				continue;
			m_SEManager[i].SEPlayer(SE_SELECT_OK);
			break;
		}
	}
}

/**
 * 描画
 *
 */
void CGameOver::Render(void){
	m_BackImage.Render(0, 0);
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

	for (int i = 0; i < SE_COUNT; i++)
	{
		m_SEManager[i].Release();
	}
}