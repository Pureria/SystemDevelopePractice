#include "EnemyShot.h"

CEnemyShot::CEnemyShot():
m_pTexture(NULL),
m_Pos(0.0f,0.0f),
m_Spd(0.0f,0.0f),
m_bShow(false),
m_bReverse(false){
}

CEnemyShot::~CEnemyShot(){
}

void CEnemyShot::Initialize()
{
	m_Pos.x = 0;
	m_Pos.y = 0;
	m_Spd.x = 0;
	m_Spd.y = 0;
	m_bShow = false;
	m_bReverse = false;
}

void CEnemyShot::Fire(float px, float py, float sx, float sy)
{
	m_Pos.x = px - m_pTexture->GetWidth() * 0.5f;
	m_Pos.y = py;
	m_Spd.x = sx;
	m_Spd.y = sy;
	m_bShow = true;
}

void CEnemyShot::Update(float wx)
{
	if (!m_bShow)
		return;

	m_Pos.x += m_Spd.x;
	m_Pos.y += m_Spd.y;

	//‰æ–ÊŠO‚ÅÁ‹Ž
	if (m_Pos.x - wx + m_pTexture->GetWidth() < 0 || m_Pos.x - wx > g_pGraphics->GetTargetWidth() ||
		m_Pos.y + m_pTexture->GetHeight() < 0 || m_Pos.y > g_pGraphics->GetTargetHeight())
		m_bShow = false;
}

void CEnemyShot::Update()
{
	if (!m_bShow)
		return;

	m_Pos.x += m_Spd.x;
	m_Pos.y += m_Spd.y;

	//‰æ–ÊŠO‚ÅÁ‹Ž
	if (m_Pos.x + m_pTexture->GetWidth() < 0 || m_Pos.x > g_pGraphics->GetTargetWidth() ||
		m_Pos.y + m_pTexture->GetHeight() < 0 || m_Pos.y > g_pGraphics->GetTargetHeight())
		m_bShow = false;
}


void CEnemyShot::Render(float wx, float wy)
{
	if (!m_bShow)
		return;
	
	CRectangle dr = CRectangle(0, 0, m_pTexture->GetWidth(), m_pTexture->GetHeight());
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
		m_pTexture->Render(m_Pos.x - wx, m_Pos.y - wy, dr);
}

void CEnemyShot::RenderDebug(float wx, float wy)
{
	if (!m_bShow)
		return;

	CGraphicsUtilities::RenderRect(m_Pos.x - wx, m_Pos.y - wy, m_Pos.x - wx + m_pTexture->GetWidth(), m_Pos.y - wy + m_pTexture->GetHeight(), MOF_XRGB(255, 0, 0));
}