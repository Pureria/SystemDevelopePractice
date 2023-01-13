#include "CSelect.h"
#include "Mof.h"
#include "GameDefine.h"

//extern int gChangeScene;

CSelect::~CSelect() {}

bool CSelect::Load() {
	if (!m_SelectTex.Load("BackGround/stage select kari.png")) { return false; }

	m_BGMManager.Load();

	return true;
}

void CSelect::Initialize() {
	Load();
	m_NowSelect = 0;
	m_Alpha = 0;
	m_BGMManager.Initialize();
	m_BGMManager.BGMPlayer(BGM_TITLE);
	m_Alpha = 255;
}
void CSelect::Update() {

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
				break;
			case 1:
				m_bEnd = true;
				m_SceneNo = SCENENO_GAME_STAGE1;
				break;
			case 2:
				m_bEnd = true;
				m_SceneNo = SCENENO_GAME_STAGE1;
				break;
			case 3:
				m_bEnd = true;
				m_SceneNo = SCENENO_GAME_STAGE1;
				break;
			}
		}

		return;
	}
#pragma endregion

	if (g_pInput->IsKeyPush(MOFKEY_D)) {
		if (m_NowSelect < COUNT_NO - 1) {
			for (int i = 0; i < SE_COUNT; i++)
			{
				if (m_SEManager[i].IsPlaySE())
					continue;
				m_SEManager[i].SEPlayer(SE_SELECT_CHANGE);
				break;
			}

			++m_NowSelect;
		}
	}
	if (g_pInput->IsKeyPush(MOFKEY_A)) {
		if (m_NowSelect > 0) {
			for (int i = 0; i < SE_COUNT; i++)
			{
				if (m_SEManager[i].IsPlaySE())
					continue;
				m_SEManager[i].SEPlayer(SE_SELECT_CHANGE);
				break;
			}
			--m_NowSelect;
		}
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_bEnd) {
		m_bFadeOut = true;
		m_Alpha = 0;
		m_NowTime = 0;

		for (int i = 0; i < SE_COUNT; i++)
		{
			if (m_SEManager[i].IsPlaySE())
				continue;
			m_SEManager[i].SEPlayer(SE_SELECT_OK);
			break;
		}
	}
}

void CSelect::Render() {

	m_SelectTex.Render(0,0);

	const char* MenuString[COUNT_NO] = {
		"ステージ1",
		"ステージ2",
		"ステージ3",
	    "ステージ4",
	};
	MofU32	color[COUNT_NO];

	for (int i = 0; i < COUNT_NO; ++i) {
		color[i] = MOF_XRGB( 128, 128, 128);
	}

	color[m_NowSelect] = MOF_XRGB(255, 0, 0);


	for (int i = 0; i < COUNT_NO; ++i) {
		CGraphicsUtilities::RenderString(100 + 450 * i,(i == 1) ? 100 + 600 * i : (i == 3) ? 700 : 300, color[i], MenuString[i]);
	}

	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_ARGB(m_Alpha, 0, 0, 0));
}

void CSelect::RenderDebug() {

}

void CSelect::Release()
{
	m_SelectTex.Release(); 
	m_BGMManager.Release();

	for (int i = 0; i < SE_COUNT; i++)
	{
		m_SEManager[i].Release();
	}
}