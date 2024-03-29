#include "Laser.h"

Laser::Laser() :
	m_LaserHitPos(0, 0),
	m_LaserRange(0),
	m_LaserDecrealse(0),
	m_StopCount(0),
	m_HitRange(0),
	m_bRev(false),
	m_SrcRect(),
	m_pFireLaserUpDownTexture(),
	m_pFrostLaserUpDownTexture(),
	m_ScrollX(0.0f),
	m_ScrollY(0.0f)
{}


void Laser::Initialize() {
	SpriteAnimationCreate anim[] = {
		{
			"LaserSide",
			0,0,
			1920,128,
			TRUE,
			{
				{3,0,7}, {3,0,8}, {3,0,9}, {3,0,10},{3,0,11},
				{3,0,12},{3,0,13},{3,0,14},{3,0,15},{3,0,16},
				{3,0,17},{3,0,18},{3,0,19},{3,0,20},{3,0,21},
				{3,0,22},{3,0,23},{3,0,24}

			}
		},
		{
			"LaserHeight",
			0,0,
			128,1920,
			TRUE,
			{
				{3,7 ,0},{3, 8,0},{3, 9,0},{3,10,0},{3,11,0},
				{3,12,0},{3,13,0},{3,14,0},{3,15,0},{3,16,0},
				{3,17,0},{3,18,0},{3,19,0},{3,20,0},{3,21,0},
				{3,22,0},{3,23,0},{3,24,0}
			}
		}
	};

	m_Motion.Create(anim, LASER_ANIMATION_COUNT);
	return;
}

void Laser::Update() {

	if (!m_bShow) { return; }

	
	ShotLaser();
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
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
		if (GetRect().Bottom > g_pGraphics->GetTargetHeight() + 200) {
			m_bHitWall = true;
		}
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

	if (m_DrcType == LEFT || m_DrcType == RIGHT)
		m_Motion.ChangeMotion(LASER_SIDE);
	else
		m_Motion.ChangeMotion(LASER_UPDOWN);

	m_Motion.SetTime(0.0f);
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

	if (m_DrcType == LEFT || m_DrcType == RIGHT)
		m_Motion.ChangeMotion(LASER_SIDE);
	else
		m_Motion.ChangeMotion(LASER_UPDOWN);

	m_Motion.SetTime(0.0f);
}

void Laser::OutRange() {

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
	lzrec.Right -=wx;
	lzrec.Bottom -= wy;

	switch (GetDirec())
	{
		case RIGHT:
			m_SrcRect.Right = m_SrcRect.Left + (lzrec.Right - lzrec.Left);
			if (GetNatu() == FIRE)
				m_pShotTex->Render(lzrec.Left, lzrec.Top - 45.0f, m_SrcRect);
			else
				m_phShotTex->Render(lzrec.Left, lzrec.Top - 45.0f, m_SrcRect);

		case LEFT:
			m_SrcRect.Right = m_SrcRect.Left + (lzrec.Right - lzrec.Left);
			if (GetNatu() == FIRE)
				m_pShotTex->Render(lzrec.Left, lzrec.Top - 45.0f, m_SrcRect);
			else
				m_phShotTex->Render(lzrec.Left, lzrec.Top - 45.0f, m_SrcRect);
		break;

		default:
			m_SrcRect.Bottom = m_SrcRect.Top + (lzrec.Bottom - lzrec.Top);
			if (GetNatu() == FIRE)
				m_pFireLaserUpDownTexture->Render(lzrec.Left - 15.0f, lzrec.Top, m_SrcRect);
			else
				m_pFrostLaserUpDownTexture->Render(lzrec.Left - 40.0f, lzrec.Top, m_SrcRect);
			break;
	}


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

void Laser::Release()
{
	m_Motion.Release();
}