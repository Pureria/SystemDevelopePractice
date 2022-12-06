#include "CResult.h"

CResult::~CResult() {}


bool CResult::Load() {
	return false;
}

void CResult::Initialize() {
	this->Load();
	m_String = nullptr;
	m_StrPos = Vector2(0.0f, 0.0f);
}

void CResult::Update() {
	m_String = "Press Enter Key";
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_bEnd && m_NowScene == m_SceneNo) {
		m_bEnd = true;
		m_SceneNo = SCENENO_SELECT;
	}
}

void CResult::RenderDebug() {

}

void CResult::Release() {
	
}