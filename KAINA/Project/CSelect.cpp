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
}
void CSelect::Update() {
	if (g_pInput->IsKeyPush(MOFKEY_D)) {
		if (m_NowSelect < COUNT_NO - 1) {
			++m_NowSelect;
		}
	}
	if (g_pInput->IsKeyPush(MOFKEY_A)) {
		if (m_NowSelect > 0) {
			--m_NowSelect;
		}
	}

	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_bEnd) {
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
}

void CSelect::RenderDebug() {

}