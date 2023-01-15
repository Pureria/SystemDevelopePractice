#include "CPlayerShot.h"

/*********コンストラクタ*********/
CPlayerShot::CPlayerShot() :
	m_RefCount(0),
	m_MoveX(0.0),
	m_MoveY(0.0),
	m_ThroughCount(0){};

void CPlayerShot::Initialize() {
	m_ShotPos = Vector2(0, 0);
	m_bShow = false;
	m_DrcType = RIGHT;
	m_RefCount = 0;
	m_ThroughCount = 0;
	m_Time = 0;
}

void CPlayerShot::Update() {
	if (!m_bShow) { return; }


	Direction();
	SpeedSave();
	ShotTime();
	m_ShotPos.x += m_MoveX;
	m_ShotPos.y += m_MoveY;


	
}

//発射する情報をセット
void CPlayerShot::Fire(Vector2& pos, int tb, int natuyype, int type) {
	m_ShotPos.x = pos.x - m_pShotTex->GetWidth() * 0.5f;
	m_ShotPos.y = pos.y - m_pShotTex->GetHeight() * 0.5f;
	m_bShow = true;
	m_DrcType = tb;
	m_bHitWall = false;
	m_NatuType = natuyype;
	m_ShotType = type;
	m_RefCount = 0;
	m_ThroughCount = 0;
	m_Time = 0;
}

void CPlayerShot::ShotTime()
{
	m_Time += CUtilities::GetFrameSecond();

	if (m_Time >= PLAYERSHOT_LIFETIME)
		m_bShow = false;
}

void CPlayerShot::Direction() {
	switch (GetDirec())
	{
	case RIGHT:
		m_MoveX += PLAYERSHOT_SPEED;
		m_MoveY = 0;
		break;
	case RIGHTTOP:
		m_MoveX += PLAYERSHOT_SPEED;
		m_MoveY -= PLAYERSHOT_SPEED;
		break;
	case RIGHTBOTTOM:
		m_MoveX += PLAYERSHOT_SPEED;
		m_MoveY += PLAYERSHOT_SPEED;
		break;
	case LEFT:
		m_MoveX -= PLAYERSHOT_SPEED;
		m_MoveY = 0;
		break;
	case LEFTTOP:
		m_MoveX -= PLAYERSHOT_SPEED;
		m_MoveY -= PLAYERSHOT_SPEED;
		break;
	case LEFTBOTTOM:
		m_MoveX -= PLAYERSHOT_SPEED;
		m_MoveY += PLAYERSHOT_SPEED;
		break;
	}
}

void CPlayerShot::SpeedSave() {
	//X軸の制限
	if (m_MoveX < -PLAYERSHOT_SPEED) {
		m_MoveX = -PLAYERSHOT_SPEED;
	}
	else if (m_MoveX > PLAYERSHOT_SPEED) {
		m_MoveX = PLAYERSHOT_SPEED;
	}
	//Y軸の制限
	if (m_MoveY < -PLAYERSHOT_SPEED) {
		m_MoveY = -PLAYERSHOT_SPEED;
	}
	else if (m_MoveY > PLAYERSHOT_SPEED) {
		m_MoveY = PLAYERSHOT_SPEED;
	}
}

void CPlayerShot::SetPowerLeft() {
	switch (GetDirec())
	{
	case LEFT:
		SetDirection(RIGHT);
		break;
	case LEFTTOP:
		SetDirection(RIGHTTOP);
		break;
	case LEFTBOTTOM:
		SetDirection(RIGHTBOTTOM);
		break;
	}
}

void CPlayerShot::SetPowerTop() {
	switch (GetDirec())
	{
	case LEFTTOP:
		SetDirection(LEFTBOTTOM);
		break;
	case RIGHTTOP:
		SetDirection(RIGHTBOTTOM);
		break;
	}
}

void CPlayerShot::SetPowerRight() {
	switch (GetDirec())
	{
	case RIGHT:
		SetDirection(LEFT);
		break;
	case RIGHTTOP:
		SetDirection(LEFTTOP);
		break;
	case RIGHTBOTTOM:
		SetDirection(LEFTBOTTOM);
		break;
	}
}

void CPlayerShot::SetPowerBottom() {
	switch (GetDirec())
	{
	case LEFTBOTTOM:
		SetDirection(LEFTTOP);
		break;
	case RIGHTBOTTOM:
		SetDirection(RIGHTTOP);
		break;
	}
}

void CPlayerShot::SetDirection(int dic)
{
	m_DrcType = dic;
	Direction();
	m_RefCount++;
	ShotRemove();
}

void CPlayerShot::ShotRemove() {
	if (m_RefCount >= REFLECTION_COUNT)
	{
		m_bShow = false;
	}
}

void CPlayerShot::SetThroughCount() {
	if (m_ThroughCount >= THROUGH_COUNT) {
		m_bShow = false;
	}
}

void CPlayerShot::Render(float wx, float wy) {
	if (!m_bShow) { return; }

	CRectangle rec = GetRect();
	rec.Left -= wx;
	rec.Top -= wy;
	rec.Right -= wx;
	rec.Bottom -= wy;

	switch (GetNatu())
	{
	case HEAL:
		m_pShotTex->Render(m_ShotPos.x - wx, m_ShotPos.y - wy);
		break;
	case HEAVY:
		m_phShotTex->Render(m_ShotPos.x - wx, m_ShotPos.y - wy);
		break;
	}
}

void CPlayerShot::RenderDebug(float wx, float wy) {
	if (!m_bShow) { return; }

	CRectangle rec = GetRect();
	rec.Left -= wx;
	rec.Top -= wy;
	rec.Right -= wx;
	rec.Bottom -= wy;

	CGraphicsUtilities::RenderRect(rec, MOF_XRGB(0, 255, 0));
}


