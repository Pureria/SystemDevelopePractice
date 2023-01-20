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
	
	return;
}

void Laser::SetUp() {
	return;
}

void Laser::Update() {
	/*while (m_HitRange < g_pGraphics->GetTargetWidth())
	{
		m_HitRange++;
		m_bShow = false;
	}*/

	if (!m_bShow) { return; }

	
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
	if (!m_bHitWall) {
		m_LaserRange += LASER_ATTACKWIDTH;
		return;
	}
	
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
	m_LaserRange = 0;
}

void Laser::Fire(float x,float y, int tb, int natuyype, int type) {
	m_ShotPos.x = x - 16;
	m_ShotPos.y = y - 32;
	m_DrcType = tb;
	m_NatuType = natuyype;
	m_ShotType = type;
	m_LaserDecrealse = 0;
	m_StopCount = LASER_DELAY;
	m_bShow = true;
	m_bHitWall = false;
	m_LaserRange = 0;
}

void Laser::OutRange() {
	//è¡Ç¶ÇÈèàóù

	if (m_StopCount <= 0)
	{
		m_LaserDecrealse += LASER_ATTACKWIDTH * 2;
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

	/*/MofU32 Color = 0;

	switch (GetNatu())
	{
	case FIRE:
		Color = MOF_COLOR_RED;
		break;
	case FROST:
		Color = MOF_XRGB(0, 255, 255);
		break;
	}
	//CGraphicsUtilities::RenderFillRect(lzrec, Color,MOF_COLOR_WHITE, MOF_COLOR_WHITE,Color);*/
	

	if (GetNatu() == FIRE)
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