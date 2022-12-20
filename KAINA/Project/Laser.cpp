#include "Laser.h"

Laser::Laser() :
	//m_FmTime(0)		,
	m_LaserHitPos(0, 0),
	m_LaserRange(0){};


void Laser::Initialize() {
	m_ShotPos = Vector2(0, 0);
	m_bShow = false;
	m_DrcType = RIGHT;
	//m_FmTime = 0.0f;
	m_bHitWall = false;
}

void Laser::Update() {
	if (!m_bShow) { return; }

	ShotLaser();
}

void Laser::Fire(Vector2& pos, int tb, int natuyype) {
	m_ShotPos.x = pos.x;
	m_ShotPos.y = pos.y;
	m_bShow = true;
	m_DrcType = tb;
	m_NatuType = natuyype;
	m_bHitWall = false;
	m_LaserRange = 0;
}

/*float Laser::FpsSpd() {
	return m_FmTime = CUtilities::GetFrameSecond();
}*/

void Laser::ShotLaser() {

	if (!m_bHitWall) {
		m_LaserRange += LASER_ATTACKWIDTH;
		return;
	}
	else {

		DirecPosSet();
		OutRange();
	}
}

CRectangle Laser::GetRect() {
	CRectangle Rec = CRectangle(m_ShotPos.x,
		m_ShotPos.y,
		m_ShotPos.x + m_LaserRange,
		m_ShotPos.y + 50);
	switch (GetDirec())
	{
	case RIGHT:
		Rec = CRectangle(m_ShotPos.x,
			m_ShotPos.y,
			m_ShotPos.x + m_LaserRange,
			m_ShotPos.y + 50);
		break;
	case LEFT:
		Rec = CRectangle(m_ShotPos.x - m_LaserRange,
			m_ShotPos.y,
			m_ShotPos.x,
			m_ShotPos.y + 50);
		break;
	case RIGHTTOP:
		Rec = CRectangle(m_ShotPos.x,
			m_ShotPos.y - m_LaserRange,
			m_ShotPos.x + 50,
			m_ShotPos.y);
		break;
	case LEFTTOP:
		Rec = CRectangle(m_ShotPos.x,
			m_ShotPos.y - m_LaserRange,
			m_ShotPos.x + 50,
			m_ShotPos.y);
	case RIGHTBOTTOM:
		Rec = CRectangle(m_ShotPos.x,
			m_ShotPos.y,
			m_ShotPos.x + 50,
			m_ShotPos.y + m_LaserRange);
		break;
	case LEFTBOTTOM:
		Rec = CRectangle(m_ShotPos.x,
			m_ShotPos.y,
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
	 
	for (int i = 0; i < 3; i++)
	{

		/*m_FireRec[i] = FireRec[i];


		MofU32 Color[3] = {
			MOF_COLOR_RED,
			MOF_COLOR_GREEN,
			MOF_COLOR_BLUE,
		};

		CGraphicsUtilities::RenderRect(m_FireRec[i], Color[i]);*/
	    return &m_FireRec[i];
	}
	
}

/*CRectangle Laser::GetSlopeRect() {
	return;
}*/


void Laser::OutRange() {
	//Á‚¦‚éˆ—
	CRectangle lzrec = GetRect();

	lzrec.Left += m_LaserRange;
	if (lzrec.Left > lzrec.Right) {
		m_bShow = false;
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
	CGraphicsUtilities::RenderFillRect(lzrec, Color,MOF_COLOR_BLACK,MOF_COLOR_BLUE,MOF_COLOR_RED);


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