#include "Laser.h"

Laser::Laser() :
	m_LaserHitPos(0, 0),
	m_LaserRange(0),
	m_LaserDecrealse(0),
	m_StopCount(0),
	m_HitRange(0),
	m_bRev(false)
{};


void Laser::Initialize() {
	m_ShotPos = Vector2(0, 0);
	m_bShow = false;
	m_DrcType = RIGHT;
	m_bHitWall = false;
}

void Laser::SetUp() {
	
}

void Laser::Update() {
	/*while (m_HitRange < g_pGraphics->GetTargetWidth())
	{
		m_HitRange++;
		m_bShow = false;
	}*/
	if (!m_bHitWall) {
		m_LaserRange += LASER_ATTACKWIDTH;
		return;
	}
	ShotLaser();
}


bool Laser::GetRev() {
	bool flg = false;
	switch (GetDirec())
	{
	case RIGHT:
		flg = false;
		break;
	case LEFT:
		flg = true;
		break;
	case RIGHTTOP:
		flg = false;
		break;
	case LEFTTOP:
		flg = true;
		break;
	case RIGHTBOTTOM:
		flg = false;
		break;
	case LEFTBOTTOM:
		flg = true;
		break;
	}
	return flg;
}

void Laser::ShotLaser() {
	
	m_bShow = true;
	
	OutRange();
}

CRectangle Laser::GetRect() {
	CRectangle Rec;

	switch (GetDirec())
	{
	case RIGHT:
		Rec = CRectangle(m_ShotPos.x + m_LaserDecrealse,
			m_ShotPos.y,
			m_ShotPos.x + m_LaserRange,
			m_ShotPos.y + 50);
		break;
	case LEFT:
		Rec = CRectangle(m_ShotPos.x - m_LaserRange,
			m_ShotPos.y,
			m_ShotPos.x - m_LaserDecrealse,
			m_ShotPos.y + 50);
		break;
	case RIGHTTOP:
		Rec = CRectangle(m_ShotPos.x,
			m_ShotPos.y - m_LaserRange,
			m_ShotPos.x + 50,
			m_ShotPos.y - m_LaserDecrealse);
		break;
	case LEFTTOP:
		Rec = CRectangle(m_ShotPos.x,
			m_ShotPos.y - m_LaserRange,
			m_ShotPos.x + 50,
			m_ShotPos.y - m_LaserDecrealse);
		break;
	case RIGHTBOTTOM:
		Rec = CRectangle(m_ShotPos.x,
			m_ShotPos.y + m_LaserDecrealse,
			m_ShotPos.x + 50,
			m_ShotPos.y + m_LaserRange);
		break;
	case LEFTBOTTOM:
		Rec = CRectangle(m_ShotPos.x,
			m_ShotPos.y + m_LaserDecrealse,
			m_ShotPos.x + 50,
			m_ShotPos.y + m_LaserRange);
		break;
	}
	return Rec;
}

CRectangle Laser::GetSearchRect() {
	return CRectangle(m_ShotPos.x,
		m_ShotPos.y,
		m_ShotPos.x + m_LaserRange * (GetRev()) ? -1 : 1,
		m_ShotPos.y + 10);
}

void Laser::Fire(Vector2& pos, int tb, int natuyype,int type) {
	m_ShotPos.x = pos.x - 16;
	m_ShotPos.y = pos.y - 32;
	m_DrcType = tb;
	m_NatuType = natuyype;
	m_ShotType = type;
	m_LaserDecrealse = 0;
	m_StopCount = LASER_DELAY;
	m_bShow = true;
	m_bHitWall = false;
	/*m_bRev = GetRev();
	m_HitRange = m_LaserHitPos.x;
	m_LaserRange = m_HitRange;*/
}

void Laser::OutRange() {
	//消える処理

	if (m_StopCount <= 0)
	{
		m_LaserDecrealse += LASER_ATTACKWIDTH;
		m_bShow = false;
	}
	else
	{
		m_StopCount -= CUtilities::GetFrameSecond();
	}

}

void Laser::Render(float wx, float wy) {
	if (!m_bShow) { return; }

	CRectangle lzrec = GetRect();
	lzrec.Left -= wx;
	lzrec.Top -= wy;
	lzrec.Right -= wx;
	lzrec.Bottom -= wy;

	MofU32 Color = 0;

	switch (GetNatu())
	{
	case FIRE:
		Color = MOF_COLOR_RED;
		break;
	case FROST:
		Color = MOF_XRGB(0, 255, 255);
		break;
	}
	CGraphicsUtilities::RenderFillRect(lzrec, Color,MOF_COLOR_WHITE, MOF_COLOR_WHITE,Color);
	

	/*if (GetNatu() == FIRE)
		m_pShotTex->Render(lzrec.Left, lzrec.Top, lzrec);
	else
		m_phShotTex->Render(lzrec.Left, lzrec.Top, lzrec);*/


	return;

}

void Laser::RenderDebug(float wx, float wy) {
	if (!m_bShow) { return; }

	CRectangle lzrec = GetRect();
	lzrec.Left -= wx;
	lzrec.Top -= wy;
	lzrec.Right -= wx;
	lzrec.Bottom -= wy;

	CGraphicsUtilities::RenderRect(lzrec, MOF_XRGB(255, 0, 0));

	CGraphicsUtilities::RenderString(1500,100, "%.0f",m_HitRange);

	CRectangle lrec = GetSearchRect();
	lrec.Left -= wx;
	lrec.Top -= wy;
	lrec.Right -= wx;
	lrec.Bottom -= wy;

	CGraphicsUtilities::RenderRect(lrec, MOF_XRGB(0, 255, 0));
}