#include "CSelect.h"
#include "Mof.h"
#include "GameDefine.h"

//extern int gChangeScene;

CSelect::~CSelect() {}

void CSelect::Initialize() {
	m_NowSelect = 0;
	m_Alpha = 0;
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
		CGraphicsUtilities::RenderString((i >= 2) ? ((i == 2) ? 100 : 100 * i) : 100 + 200 * i, (i >= 2) ? 400 : 350, color[i], MenuString[i]);
	}
}

void CSelect::RenderDebug() {

}