#include "Laser.h"

Laser::Laser() :
	m_LaserHitPos(0, 0),
	m_LaserRange(0),
	m_LaserDecrealse(0),
	m_StopCount(0)
{};


void Laser::Initialize() {
	m_ShotPos = Vector2(0, 0);
	m_bShow = false;
	m_DrcType = RIGHT;
	m_bHitWall = false;
}

void Laser::Update() {
	if (!m_bShow) { return; }

	ShotLaser();
}

void Laser::Fire(Vector2& pos, int tb, int natuyype,int type) {
	m_ShotPos.x = pos.x - 16;
	m_ShotPos.y = pos.y - 32;
	m_bShow = true;
	m_DrcType = tb;
	m_NatuType = natuyype;
	m_ShotType = type;
	m_bHitWall = false;
	m_LaserRange = 0;
	m_LaserDecrealse = 0;
	m_StopCount = LASER_DELAY;
}

void Laser::ShotLaser() {

	if (!m_bHitWall) {
		if (m_LaserRange < 1000)
			m_LaserRange += LASER_ATTACKWIDTH;

		return;
	}
	else {
		DirecPosSet();
		OutRange();
	}
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

void Laser::DirecPosSet() {
	CRectangle rec = GetRect();

	switch (GetDirec())
	{
	case RIGHT:
		m_LaserHitPos.x = rec.Right;
		m_LaserHitPos.y = rec.Top;
		break;
	case LEFT:
		m_LaserHitPos.x = rec.Left;
		m_LaserHitPos.y = rec.Bottom;
		break;
	}
}

CRectangle* Laser::GetFireRect() {
	CRectangle rec = GetRect();

	CRectangle FireRec[3] =	{ CRectangle(rec.Left, m_LaserHitPos.y - 50, m_LaserHitPos.x, rec.Bottom - 50),
							  CRectangle(rec.Left, m_LaserHitPos.y - 5, m_LaserHitPos.x, rec.Bottom + 5),
							  CRectangle(rec.Left, m_LaserHitPos.y + 60, m_LaserHitPos.x, rec.Bottom + 60),
	};
	 
	return m_FireRec;
	
}

void Laser::OutRange() {
	//Á‚¦‚éˆ—

	if (m_StopCount <= 0)
	{
		m_LaserDecrealse += LASER_ATTACKWIDTH * 0.5;
		if (GetRect().Left > GetRect().Right || GetRect().Top > GetRect().Bottom) {
			m_bShow = false;
			m_bHitWall = false;
		}
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
	
	/*
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
	*/

	if(GetNatu() == FIRE)
		m_pShotTex->Render(lzrec.Left, lzrec.Top, lzrec);
	else
		m_phShotTex->Render(lzrec.Left, lzrec.Top, lzrec);


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


}