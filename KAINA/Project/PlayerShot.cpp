#include "PlayerShot.h"

PlayerShot::~PlayerShot() {

}

void PlayerShot::Update(bool rev) {
	if (!m_bShow) { return; }
	if (!rev)     { m_ShotPos.x += PLAYERSHOT_SPEED; }
	else          { m_ShotPos.x -= PLAYERSHOT_SPEED; }

	if (m_ShotPos.x < 0 || m_ShotPos.x + m_pShotTex->GetWidth() > g_pGraphics->GetTargetWidth() || 
		m_ShotPos.y < 0 || m_ShotPos.y + m_pShotTex->GetHeight() > g_pGraphics->GetTargetHeight()) {
		m_bShow = false;
	}
}

void PlayerShot::Render() {
	if (!m_bShow) { return; }

	m_pShotTex->Render(m_ShotPos.x,m_ShotPos.y);
}

void PlayerShot::RenderDebug() {
	if (!m_bShow) { return; }

	CGraphicsUtilities::RenderRect(m_ShotPos.x, 
								   m_ShotPos.y,
								   m_ShotPos.x + m_pShotTex->GetWidth(),
								   m_ShotPos.y + m_pShotTex->GetHeight(), 
								   MOF_XRGB(0, 255, 0));
}


