#include "CSelect.h"
#include "Mof.h"
#include "GameDefine.h"


CSelect::~CSelect() { Release(); }

bool CSelect::Load() {

	if(!m_Stage1Str.Load("BackGround/stage1ui.png"))			{			return false;			}

	if(!m_Stage2Str.Load("BackGround/stage2ui.png"))			{			return false;			}

	m_BGMManager.Load();

	m_SEManager.SelectLoad();

	return true;
}

void CSelect::Initialize() {
	Load();
	m_NowSelect = 0;
	m_Alpha = 0;
	m_BGMManager.Initialize();
	m_BGMManager.BGMPlayer(BGM_TITLE);
	m_Alpha = 255;
	m_FlashCount = 0;
}
void CSelect::Update() {

	if (m_FlashCount > 0) {
		m_FlashCount--;
	}
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
			switch (m_NowSelect)
			{
			case 0:
				m_bEnd = true;
				m_SceneNo = SCENENO_GAME_STAGE1;
				SetOldScene(SCENENO_SELECT);
				break;
			case 1:
				m_bEnd = true;
				m_SceneNo = SCENENO_GAME_STAGE2;
				SetOldScene(SCENENO_SELECT);
				break;
			}
		}
		return;
	}
#pragma endregion

	if (g_pInput->IsKeyPush(MOFKEY_D)) {
		if (m_NowSelect < COUNT_NO - 1) {
			m_SEManager.SEPlayer(SE_SELECT_CHANGE);

			++m_NowSelect;
		}
	}
	if (g_pInput->IsKeyPush(MOFKEY_A)) {
		if (m_NowSelect > 0) {
			m_SEManager.SEPlayer(SE_SELECT_CHANGE);
				
			--m_NowSelect;
		}
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_bEnd) {
		m_bFadeOut = true;
		m_Alpha = 0;
		m_NowTime = 0;
		m_FlashCount = FLASH_COUNT;
		m_SEManager.SEPlayer(SE_SELECT_OK);
	}
}

void CSelect::Render() {
	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_COLOR_BLACK);

	switch (m_NowSelect)
	{
	case 0:
		m_Stage2Str.Render(1150, 500, MOF_XRGB(128, 128, 128));
		if (m_FlashCount % 4 >= 2)
		{
			break;
		}
		m_Stage1Str.Render(350, 500);
		break;
	case 1:
		m_Stage1Str.Render(350, 500, MOF_XRGB(128, 128, 128));
		if (m_FlashCount % 4 >= 2)
		{
			break;
		}
		m_Stage2Str.Render(1150, 500);
		break;
	}

	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_ARGB(m_Alpha, 0, 0, 0));
}

void CSelect::RenderDebug() {

}

void CSelect::Release()
{
	m_Stage1Str.Release();
	m_Stage2Str.Release();
	m_BGMManager.Release();
	m_SEManager.SelectRelease();
}