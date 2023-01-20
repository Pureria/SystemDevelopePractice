#include	"Player.h"

// ����ȌĂяo��������鏈��
#pragma region ����֐�

CPlayer::CPlayer() :
m_Texture() ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_bMove(false) ,
m_MoveX(0.0f) ,
m_MoveY(0.0f) ,
m_bJump(false) ,
m_bDead(false),
m_bReverse(false) ,
m_SrcRect(),
m_pEffectManager(),
m_pEndEffect(),
m_DamageWait(0),
m_ShotWait(0),
m_bTop(false),
m_bBottom(false),
m_ShotType(NORMAL),
m_NatuType(FIRE),
m_DrcType(RIGHT),
m_HP(0),
m_SP(0),
m_PlShotAry(),
m_bNextBossScene(false),
m_SpWait(0),
m_SEManager(),
m_bShow(false),
m_UiWait(0),
m_UIAnimationTimer(0),
m_bUIAnimation(false),
m_bUIAnimationEnd(false)
{}

#pragma endregion


//�ǂݍ��ݏ���
#pragma region Load�֐�

bool CPlayer::Load(){
	//�e�N�X�`���̓ǂݍ���
	if (!m_Texture.Load("Player/chara_ren.png"))					{		return false;		}

	if (!m_FrameTexture.Load("Player/Frame.png"))					{		return false;		}

	if (!m_HPBarTexture.Load("Player/Hp.png"))						{		return false;		}	

	if (!m_SPBarTexture.Load("Player/Sp.png"))						{		return false;		}

	if (!m_ShotHealTex.Load("Player/healammo.png"))					{		return false;		}

	if (!m_ShotHeavyTex.Load("Player/heavyammo.png"))				{		return false;		}

	if (!m_HealTex.Load("Player/heal.png"))							{		return false;		}

	if (!m_HeavyTex.Load("Player/heavy.png"))						{		return false;		}

	if (!m_FireTex.Load("Player/fire.png"))							{		return false;		}

	if (!m_FrostTex.Load("Player/frost.png"))						{		return false;		}

	if (!m_FireLazerTexture.Load("Player/laser2.png"))				{		return false;		}

	if (!m_FrostLazerTexture.Load("Player/bluelaser2.png"))			{		return false;		}		

	if (!m_Heavy2Tex.Load("Player/heavy2.png"))						{		return false;		}

	if (!m_Frost2Tex.Load("Player/frost2.png"))						{		return false;		}
	
	if (!m_Heal2Tex.Load("Player/heal2.png"))						{		return false;		}
	
	if (!m_Fire2Tex.Load("Player/blaze2.png"))						{		return false;		}

	if (!m_H2Tex.Load("Player/heavyic.png"))						{		return false;		}

	if (!m_HeTex.Load("Player/healic.png"))							{		return false;		}	

	if (!m_Fr2Tex.Load("Player/frostic.png"))						{		return false;		}

	if (!m_Fi2Tex.Load("Player/blazeic.png"))						{		return false;		}

	if (!m_FireLaserUpDownTexture.Load("Player/laser3.png"))		{		return false;		}

	if (!m_FrostLaserUpDownTexture.Load("Player/bluelaser3.png"))	{		return false;		}


	for (int i = 0; i < PLAYERSHOT_COUNT; i++)	
	{
		m_PlShotAry[i].SetHealTexture(&m_ShotHealTex); 
		m_PlShotAry[i].SetHeavyTexture(&m_ShotHeavyTex);
	}

	m_Laser.SetFireTexture(&m_FireLazerTexture);
	m_Laser.SetFrostTexture(&m_FrostLazerTexture);
	m_Laser.SetFireLaserUpDownTexture(&m_FireLaserUpDownTexture);
	m_Laser.SetFrostLaserUpDownTexture(&m_FrostLaserUpDownTexture);

	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim[] = {
		{
			"�ҋ@",
			0,640,
			128,128,
			TRUE,
			{		
					{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},
					{5,6,0},{5,7,0},{5,8,0},{5,9,0},{5,10,0},{5,11,0},
					{5,12,0},{5,13,0},{5,14,0},{5,15,0},{5,16,0},{5,17,0},
					{5,18,0},{5,19,0},{5,20,0},{5,21,0},{5,22,0},{5,23,0},
					{5,24,0},{5,25,0},{5,26,0},{5,27,0},{5,28,0},{5,29,0}
			}
		},
		{
			"�ړ�",
			0,0,
			128,128,
			TRUE,
			{		
					{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},
					{5,6,0},{5,7,0},{5,8,0},{5,9,0},{5,10,0},{5,11,0},
					{5,12,0},{5,13,0},{5,14,0},{5,15,0},{5,16,0},{5,17,0},
					{5,18,0},{5,19,0},{5,20,0},{5,21,0},{5,22,0},{5,23,0},
					{5,24,0},{5,25,0},{5,26,0},{5,27,0},{5,28,0},{5,29,0}
			}
		},
		{
			"�W�����v�ړ�",
			0,1408,
			128,128,
			FALSE,
			{
					{5,0,0},{5,1,0},{5,2,0},
			}
		},
		{
			"�W�����v�I��",
			256,1408,
			128,128,
			FALSE,
			{
					{2,0,0},{2,1,0},{2,2,0},{2,3,0},
			}
		},
		{
			"�U��",
			0,640,
			128,128,
			FALSE,
			{
					{5,24,0}
			}
		},
		{
			"�ʏ�e�̏e���グ��",
			0,1024,
			128,128,
			FALSE,
			{
					{5,0,0}
			}
		},
		{
			"�ʏ�e�̏e��������",
			0,1152,
			128,128,
			FALSE,
			{
					{5,0,0}
			}
		},
		{
			"�ʏ�e�̏e���グ���܂܈ړ�",
			0,1024,
			128,128,
			TRUE,
			{
					{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},
					{5,6,0},{5,7,0},{5,8,0},{5,9,0},{5,10,0},{5,11,0},
					{5,12,0},{5,13,0},{5,14,0},{5,15,0},{5,16,0},{5,17,0},
					{5,18,0},{5,19,0},{5,20,0},{5,21,0},{5,22,0},{5,23,0},
					{5,24,0},{5,25,0},{5,26,0},{5,27,0},{5,28,0},{5,29,0}
			}
		},
		{
			"�ʏ�e�̏e���������܂܈ړ�",
			0,1152,
			128,128,
			TRUE,
			{
					{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},
					{5,6,0},{5,7,0},{5,8,0},{5,9,0},{5,10,0},{5,11,0},
					{5,12,0},{5,13,0},{5,14,0},{5,15,0},{5,16,0},{5,17,0},
					{5,18,0},{5,19,0},{5,20,0},{5,21,0},{5,22,0},{5,23,0},
					{5,24,0},{5,25,0},{5,26,0},{5,27,0},{5,28,0},{5,29,0}
			}
		},
		{
			"���[�U�[�̏e���グ��",
			0,896,
			128,128,
			FALSE,
			{
					{5,0,0}
			}
		},
		{
			"���[�U�[�̏e��������",
			0,1280,
			128,128,
			FALSE,
			{
					{5,0,0}
			}
		},
		{
			"���[�U�[�̏e���グ���܂܈ړ�",
			0,896,
			128,128,
			TRUE,
			{
					{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},
					{5,6,0},{5,7,0},{5,8,0},{5,9,0},{5,10,0},{5,11,0},
					{5,12,0},{5,13,0},{5,14,0},{5,15,0},{5,16,0},{5,17,0},
					{5,18,0},{5,19,0},{5,20,0},{5,21,0},{5,22,0},{5,23,0},
					{5,24,0},{5,25,0},{5,26,0},{5,27,0},{5,28,0},{5,29,0}
			}
		},
		{
			"���[�U�[�̏e���������܂܈ړ�",
			0,1280,
			128,128,
			TRUE,
			{
					{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},
					{5,6,0},{5,7,0},{5,8,0},{5,9,0},{5,10,0},{5,11,0},
					{5,12,0},{5,13,0},{5,14,0},{5,15,0},{5,16,0},{5,17,0},
					{5,18,0},{5,19,0},{5,20,0},{5,21,0},{5,22,0},{5,23,0},
					{5,24,0},{5,25,0},{5,26,0},{5,27,0},{5,28,0},{5,29,0}
			}
		},
		{
			"�e����߂�",
			0,640,
			128,128,
			FALSE,
			{
					{5,0,0}
			}
		},
		{
			"�_���[�W",
			0,1280,
			128,128,
			FALSE,
			{
					{5,29,0}
			}
		},
	};

	m_Motion.Create(anim, MOTION_COUNT);

	return true;
}

#pragma endregion


//����������
#pragma region Initialize�֐�


void CPlayer::Initialize(){

	Load();
	m_Laser.Initialize();
	m_SEManager.PlayerLoad();
	m_PosX = 200;
	m_PosY = 0;
	m_bMove = false;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bReverse = false;
	m_bJump = false;
	m_HP = 100;
	m_SP = 100;
	m_DamageWait = 0;
	m_Motion.ChangeMotion(MOTION_WAIT);
	m_bDead = false;
	m_pEndEffect = NULL;
	m_bTop = false;
	m_bBottom = false;
	m_ShotType = NORMAL;
	m_NatuType = NULL;
	m_DrcType = NULL;
	m_bNextBossScene = false;
	m_SpWait = 0;
	m_bFall = false;
	m_bShow = true;
}


#pragma endregion


//�X�V
#pragma region Update�֐�

void CPlayer::Update() {

	UpdateShot();
	UIAnimationUpdate();

	//HP�������Ȃ�Ɣ����̏I����ҋ@���ďI��
	if (PlayerEnd())	{			return;				}
	if (!m_bShow)
		return;

	//�ړ��t���O�A���̃t���[���ł̈ړ�������������ۑ�
	m_bMove = false;

	//�U�����A���n�̏ꍇ�̓���
	if (m_Motion.GetMotionNo() == MOTION_ATTACK || m_Motion.GetMotionNo() == MOTION_JUMPEND)
	{
		//�I���őҋ@�ɖ߂�
		if (m_Motion.IsEndMotion())
		{
			if (m_bTop) {
				m_Motion.ChangeMotion(IsLaser() ? MOTION_LASER_MUZZLETOP : MOTION_NORMAL_MUZZLETOP);
			}
			else if (m_bBottom) {
				m_Motion.ChangeMotion(IsLaser() ? MOTION_LASER_MUZZLEBOTTOM : MOTION_NORMAL_MUZZLEBOTTOM);
			}
			else {
				m_Motion.ChangeMotion(MOTION_WAIT);
			}
		}
	}
	else if(m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		//�I���őҋ@�ɖ߂�
		if (m_Motion.IsEndMotion())
		{
			if (m_bTop) {
				m_Motion.ChangeMotion(IsLaser() ? MOTION_LASER_MUZZLETOP : MOTION_NORMAL_MUZZLETOP);
			}
			else if (m_bBottom) {
				m_Motion.ChangeMotion(IsLaser() ? MOTION_LASER_MUZZLEBOTTOM : MOTION_NORMAL_MUZZLEBOTTOM);
			}
			else {
				m_Motion.ChangeMotion(MOTION_WAIT);
			}
		}
	}
	else if (m_Motion.GetMotionNo() == MOTION_RETURN_MUZZLE) {

		if (m_Motion.IsEndMotion()) 
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}
	else
	{
		//�L�[���͂ɂ�铮��
		UpdateKey();	
	}

	//�ړ��X�V
	UpdateMove();
	//���ۂɍ��W���ړ�������
	m_PosX += m_MoveX;
	m_PosY += m_MoveY;

	Fall();
	
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();

	if (m_HP >= 100) {
		m_HP = 100;
	}
	
	if (m_SP >= 100) {
		m_SP = 100;
	}
	else {
		if (m_SPInterval <= 0)
		{
			if (m_SpWait > 0) {
				m_SpWait--;
				if (m_SpWait <= 0) {
					m_SP += SP_POWER;
					m_SpWait = PLAYER_SPWAIT;
				}
			}
		}
		else
		{
			m_SPInterval--;
		}
	}

	if (m_SP <= 0) {
		m_SP = 0;
	}

	//�_���[�W�̃C���^�[�o�������炷
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}
	if (m_UiWait > 0) {
		m_UiWait--;
	}
	
}

void CPlayer::UIAnimationUpdate()
{
	if (!m_bUIAnimation)
		return;

	m_UIAnimationTimer += CUtilities::GetFrameSecond();

	if (!m_bUIAnimationEnd)
	{
		if (m_UIAnimationAlpha < 255)
		{
			m_UIAnimationAlpha = m_PublicFunction.Animation(0, PLAYER_UI_UP, 0, 255, m_UIAnimationTimer);
		}
		else if (m_UIAnimationTimer > PLAYER_UI_UP + PLAYER_UI_STOP)
		{
			m_bUIAnimationEnd = true;
			m_UIAnimationTimer = 0;
		}
	}
	else
	{
		if (m_UIAnimationAlpha > 0)
		{
			m_UIAnimationAlpha = m_PublicFunction.Animation(0, PLAYER_UI_DOWN, 255, 0, m_UIAnimationTimer);
		}
		else
		{
			m_bUIAnimation = false;
		}
	}
}

void CPlayer::UpdateShot() {
	m_Laser.Update();
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_PlShotAry[i].Update();
	}
}


void CPlayer::UpdateMove(){
	//���̃t���[���ł̈ړ����͂��Ȃ���Ό������������s����
	if (!m_bMove)
	{
		if (m_MoveX > 0)
		{
			m_MoveX -= PLAYER_SPEED;
			if (m_MoveX <= 0)
			{
				m_MoveX = 0;
				MoveStopAnim();
			}
		}
		else if (m_MoveX < 0)
		{
			m_MoveX += PLAYER_SPEED;
			if (m_MoveX >= 0)
			{
				m_MoveX = 0;
				MoveStopAnim();
			}
		}
		else if (m_Motion.GetMotionNo() == MOTION_MOVE)
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	//�d�͂ɂ�菭����������
	if (IsJump())
	{
		m_MoveY += GRAVITY;
	}
	else
	{
		m_MoveY += GRAVITY + 0.2f;
	}

	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
}


void CPlayer::UpdateKey() {

	MoveKey();

	BulletChange();

	DirecTpBtmChange();

	NatuChange();

	ShotManager();

}


#pragma endregion


//�L�[���͂ɂ�铮��X�V/
#pragma region Move�֐�

void CPlayer::MoveKey() {
	//���͂Œ��ڍ��W�𓮂����̂ł͂Ȃ��A���x��ω�������
	//�U�����͈ړ��ł��Ȃ��悤�ɂ���
	if (g_pInput->IsKeyHold(MOFKEY_A))
	{
		m_MoveX -= PLAYER_SPEED;
		m_bReverse = true;
		m_bMove = true;
		if (m_MoveX < -PLAYER_MAXSPEED)
		{
			m_MoveX = -PLAYER_MAXSPEED;
		}
		MoveTpBtmAnim();
		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}

	else if (g_pInput->IsKeyHold(MOFKEY_D))
	{
		m_MoveX += PLAYER_SPEED;
		m_bReverse = false;
		m_bMove = true;
		if (m_MoveX > PLAYER_MAXSPEED)
		{
			m_MoveX = PLAYER_MAXSPEED;
		}
		MoveTpBtmAnim();
		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}

	//E�L�[�ŃW�����v
	if (g_pInput->IsKeyHold(MOFKEY_SPACE) && !m_bJump && !m_bFall)
	{
		m_bJump = true;
		m_MoveY = PLAYER_JUMP;
		m_Motion.ChangeMotion(MOTION_JUMPSTART);
		m_SEManager.SEPlayer(SE_JUMP);		
	}

	if (m_MoveY > 0.0f)
		m_bFall = true;
	else
		m_bFall = false;
}

void CPlayer::MoveTpBtmAnim() {
	if (IsLaser()) {
		if (m_Motion.GetMotionNo() == MOTION_LASER_MUZZLETOP) {
			m_Motion.ChangeMotion(MOTION_LASER_MOVETOP);
		}
		else if(m_Motion.GetMotionNo() == MOTION_LASER_MUZZLEBOTTOM){
			m_Motion.ChangeMotion(MOTION_LASER_MOVEBOTTOM);
		}
	}
	else {
		if (m_Motion.GetMotionNo() == MOTION_NORMAL_MUZZLETOP) {
			m_Motion.ChangeMotion(MOTION_NORMAL_MOVETOP);
		}
		else if (m_Motion.GetMotionNo() == MOTION_NORMAL_MUZZLEBOTTOM) {
			m_Motion.ChangeMotion(MOTION_NORMAL_MOVEBOTTOM);
		}
	}
}

void CPlayer::MoveStopAnim() {
	if (m_bTop) {
		m_Motion.ChangeMotion((IsLaser()) ? MOTION_LASER_MUZZLETOP : MOTION_NORMAL_MUZZLETOP);
	}
	else if (m_bBottom) {
		m_Motion.ChangeMotion((IsLaser()) ? MOTION_LASER_MUZZLEBOTTOM : MOTION_NORMAL_MUZZLEBOTTOM);
	}
	else {
		m_Motion.ChangeMotion(MOTION_RETURN_MUZZLE);
	}
}

void CPlayer::BltChangeTpBtmAnim() {
	if (m_bTop) {
		m_Motion.ChangeMotion(IsLaser() ? MOTION_NORMAL_MUZZLETOP : MOTION_LASER_MUZZLETOP);
	}
	else if(m_bBottom){
		m_Motion.ChangeMotion(IsLaser() ? MOTION_NORMAL_MUZZLEBOTTOM : MOTION_LASER_MUZZLEBOTTOM);
	}
}
#pragma endregion


//�ς��鏈��
#pragma region Change�֐�

void CPlayer::BulletChange() {
	if (g_pInput->IsKeyPush(MOFKEY_I)) {
		TypeChange();
		BltChangeTpBtmAnim();
	}
}

void CPlayer::TypeChange() {
	if (m_ShotType == NORMAL) {
		m_ShotType = LASER;
		m_NatuType = FIRE;
	}
	else {
		m_ShotType = NORMAL;
		m_NatuType = HEAL;
	}
}

void CPlayer::NatuChange() {
	if (g_pInput->IsKeyPush(MOFKEY_O)) {
		SEBltChange();
		//m_UiWait = UI_WAIT;
		m_bUIAnimation = true;
		m_UIAnimationAlpha = 0;
		m_UIAnimationTimer = 0;
		m_bUIAnimationEnd = false;

		switch (m_NatuType)
		{
		case HEAL:
			m_NatuType = HEAVY;
			
			break;
		case HEAVY:
			m_NatuType = HEAL;
			break;
		case FIRE:
			m_NatuType = FROST;
			break;
		case FROST:
			m_NatuType = FIRE;
			break;
		}
	}
}

void CPlayer::DirecTpBtmChange() {

	if (g_pInput->IsKeyPush(MOFKEY_W) && !m_bTop) {
		m_bTop = true;
		m_bBottom = false;
		m_Motion.ChangeMotion((IsLaser()) ? MOTION_LASER_MUZZLETOP : MOTION_NORMAL_MUZZLETOP);
	}
	else if (g_pInput->IsKeyPush(MOFKEY_W) && m_bTop) {
		m_bTop = false;
		m_bBottom = false;
		m_Motion.ChangeMotion(MOTION_RETURN_MUZZLE);		
	}
	if (g_pInput->IsKeyPush(MOFKEY_S) && !m_bBottom) {
		m_bBottom = true;
		m_bTop = false;
		m_Motion.ChangeMotion((IsLaser()) ? MOTION_LASER_MUZZLEBOTTOM : MOTION_NORMAL_MUZZLEBOTTOM);
	}
	else if (g_pInput->IsKeyPush(MOFKEY_S) && m_bBottom) {
		m_bBottom = false;
		m_bTop = false;
		m_Motion.ChangeMotion(MOTION_RETURN_MUZZLE);
	}
}

void CPlayer::DirecMotionChange() {
	if (IsLaser()) {
		if (m_bTop) {
			m_Motion.ChangeMotion((m_bMove) ? MOTION_LASER_MOVETOP : MOTION_LASER_MUZZLETOP);
		}
		else if (m_bBottom) {
			m_Motion.ChangeMotion((m_bMove) ? MOTION_LASER_MOVEBOTTOM : MOTION_LASER_MUZZLEBOTTOM);
		}
		else {
			m_Motion.ChangeMotion(MOTION_ATTACK);
		}
	}
	else {
		if (m_bTop) {
			m_Motion.ChangeMotion((m_bMove) ? MOTION_NORMAL_MOVETOP : MOTION_NORMAL_MUZZLETOP);
		}
		else if (m_bBottom) {
			m_Motion.ChangeMotion((m_bMove) ? MOTION_NORMAL_MOVEBOTTOM : MOTION_NORMAL_MUZZLEBOTTOM);
		}
		else {
			m_Motion.ChangeMotion(MOTION_ATTACK);
		}
	}
}

void CPlayer::SEBltChange() {
	
	switch (GetNatu())
	{
	case HEAL:
		m_SEManager.SEPlayer(SE_HEAVY);
		break;
	case HEAVY:
		m_SEManager.SEPlayer(SE_HEAL);
		break;
	case FIRE:
		m_SEManager.SEPlayer(SE_ICE);
		break;
	case FROST:
		m_SEManager.SEPlayer(SE_FIRE);
		break;
	}
}

#pragma endregion


//�����̊Ǘ�
#pragma region Manager����

void CPlayer::ShotManager() {
	if (IsLaser()) {
		FireShotLaser();
	}
	else {
		FireShot();
	}
}

#pragma endregion


//���˒e�̏���
#pragma region Shot�֐�


//�e��������
void CPlayer::FireShot() {
	//�e�̔���

	if (m_ShotWait <= 0)
	{
		if (g_pInput->IsKeyPush(MOFKEY_P))
		{
			DirecMotionChange();
			for (int i = 0; i < PLAYERSHOT_COUNT; i++) {

				if (m_PlShotAry[i].GetShow())	{		continue;		}
				m_SPInterval = PLAYERSHOT_INTERVAL;
				
				m_SEManager.SEPlayer((m_PlShotAry[i].GetNatu() == HEAL) ? SE_ATTACK_REFLECTION : SE_ATTACK_HEAVY);

				m_ShotWait = (m_PlShotAry[i].GetNatu() == HEAL) ? PLAYERSHOT_HEALWAIT : PLAYERSHOT_HEAVYWAIT;
				ShotRev(i);
				break;
			}
		}
	}
	else
	{
		m_ShotWait--;
	}
}


//�e�̌��������u�ԂɃZ�b�g
void CPlayer::ShotRev(int i) {
	if (m_SP <= 0) {		
		return;
	}

	if (!m_bReverse) {
		if (m_bTop) {
			m_PlShotAry[i].Fire(SetStartPos(), RIGHTTOP, m_NatuType,NORMAL);
			m_SpWait = PLAYER_SPWAIT;
			m_SP -= (m_PlShotAry[i].GetNatu() == HEAL) ? HEAL_DECREASE : HEAVY_DECREASE;
			return;
		}
		else if (m_bBottom) {
			m_PlShotAry[i].Fire(SetStartPos(), RIGHTBOTTOM, m_NatuType,NORMAL);
			m_SpWait = PLAYER_SPWAIT;
			m_SP -= (m_PlShotAry[i].GetNatu() == HEAL) ? HEAL_DECREASE : HEAVY_DECREASE;
			return;
		}
		else {
			m_PlShotAry[i].Fire(SetStartPos(), RIGHT, m_NatuType,NORMAL);
			m_SpWait = PLAYER_SPWAIT;
			m_SP -= (m_PlShotAry[i].GetNatu() == HEAL) ? HEAL_DECREASE : HEAVY_DECREASE;
			return;
		}
	}
	else {
		if (m_bTop) {
			m_PlShotAry[i].Fire(SetStartPos(), LEFTTOP, m_NatuType,NORMAL);
			m_SpWait = PLAYER_SPWAIT;
			m_SP -= (m_PlShotAry[i].GetNatu() == HEAL) ? HEAL_DECREASE : HEAVY_DECREASE;
			return;
		}
		else if (m_bBottom) {
			m_PlShotAry[i].Fire(SetStartPos(), LEFTBOTTOM, m_NatuType,NORMAL);
			m_SpWait = PLAYER_SPWAIT;
			m_SP -= (m_PlShotAry[i].GetNatu() == HEAL) ? HEAL_DECREASE : HEAVY_DECREASE;
			return;
		}
		else {
			m_PlShotAry[i].Fire(SetStartPos(), LEFT, m_NatuType,NORMAL);
			m_SpWait = PLAYER_SPWAIT;
			m_SP -= (m_PlShotAry[i].GetNatu() == HEAL) ? HEAL_DECREASE : HEAVY_DECREASE;
			return;
		}
	}
}

void  CPlayer::ShotRender(float wx,float wy) {
	//�e�̕`��
	m_Laser.Render(wx, wy);
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_PlShotAry[i].Render(wx, wy);
	}
}


#pragma endregion

//���[�U�[�̏���
#pragma region Laser�֐�

void CPlayer::FireShotLaser() {
	//�e�̔���

	if (m_ShotWait <= 0)
	{
		if (g_pInput->IsKeyPush(MOFKEY_P))
		{
			DirecMotionChange();

			m_SPInterval = PLAYERSHOT_INTERVAL;
			m_SEManager.SEPlayer(SE_ATTACK_THROUGH);
			m_ShotWait = LASER_WAIT;
			ShotRevLaser();
		}
	}
	else
	{
		m_ShotWait--;
	}
}

//�e�̌��������u�ԂɃZ�b�g
void CPlayer::ShotRevLaser() {
	if (m_SP <= 0) {
		return;
	}
	//TODO LASER
	m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_LASER_HAND);
	if (!m_bReverse) {
		if (m_bTop) {
			m_Laser.Fire(SetStartPos(), RIGHTTOP, m_NatuType,LASER);
			m_SpWait = PLAYER_SPWAIT;
			m_SP -= (m_Laser.GetNatu() == FIRE) ? FIRE_DECREASE : FROST_DECREASE;

		}
		else if (m_bBottom) {
			m_Laser.Fire(SetStartPos(), RIGHTBOTTOM, m_NatuType, LASER);
			m_SpWait = PLAYER_SPWAIT;
			m_SP -= (m_Laser.GetNatu() == FIRE) ? FIRE_DECREASE : FROST_DECREASE;
		}
		else {
			m_Laser.Fire(SetStartPos(), RIGHT, m_NatuType, LASER);
			m_SpWait = PLAYER_SPWAIT;
			m_SP -= (m_Laser.GetNatu() == FIRE) ? FIRE_DECREASE : FROST_DECREASE;
		}
	}
	else {
		if (m_bTop) {
			m_Laser.Fire(SetStartPos(), LEFTTOP, m_NatuType, LASER);
			m_SpWait = PLAYER_SPWAIT;
			m_SP -= (m_Laser.GetNatu() == FIRE) ? FIRE_DECREASE : FROST_DECREASE;
		}
		else if (m_bBottom) {
			m_Laser.Fire(SetStartPos(), LEFTBOTTOM, m_NatuType, LASER);
			m_SpWait = PLAYER_SPWAIT;
			m_SP -= (m_Laser.GetNatu() == FIRE) ? FIRE_DECREASE : FROST_DECREASE;
		}
		else {
			m_Laser.Fire(SetStartPos(), LEFT, m_NatuType, LASER);
			m_SpWait = PLAYER_SPWAIT;
			m_SP -= (m_Laser.GetNatu() == FIRE) ? FIRE_DECREASE : FROST_DECREASE;
		}
	}
}

#pragma endregion


//Player�ɉe����^����֐�
#pragma region Player�֐�

void CPlayer::PlayerDamage(bool flg,float damage)
{
	//HP�������Ȃ�Ɠ����蔻�肵�Ȃ�
	if (m_HP <= 0)
		return;


	//�_���[�W���̂��ߓ����蔻����s��Ȃ�
	if (m_DamageWait > 0)
		return;

	m_HP -= damage;
	m_DamageWait = DAMAGE_WAIT;
	if (flg)
	{
		m_MoveX = -5.0f;
		m_bReverse = false;
	}
	else
	{
		m_MoveX = 5.0f;
		m_bReverse = true;
	}

	if (m_HP <= 0)
	{
		m_SEManager.SEPlayer(SE_PLAYER_DIE);
		
		//�����G�t�F�N�g�𔭐�������
		m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
		m_bShow = false;
	}
	else
	{
		m_SEManager.SEPlayer(SE_PLAYER_DAMAGE);
		
		//�_���[�W�G�t�F�N�g�𔭐�������
		m_pEffectManager->Start(SetStartPos(), EFC_DAMAGE);
	}

}

void CPlayer::PlayerDamage(float damage)
{
	if (m_HP <= 0)
		return;

	if (m_DamageWait > 0)
		return;

	m_HP -= damage;
	m_DamageWait = 5;
	if (m_HP <= 0)
	{
		m_SEManager.SEPlayer(SE_PLAYER_DIE);
	
		m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
		m_bShow = false;
	}
	else {
		
		m_SEManager.SEPlayer(SE_PLAYER_DAMAGE);
		
	}

}

bool CPlayer::PlayerEnd() {
	if (m_HP <= 0)
	{
		if (!m_pEndEffect || !m_pEndEffect->GetShow())
		{
			m_bDead = true;
			return true;
		}
	}
	return false;
}

#pragma endregion


//�����蔻��̊֐�
#pragma region Collision�֐�

bool CPlayer::CollisionEnemy(CEnemyBase_Shot& ene, int eneType) {

	bool flg = false;

	if (!ene.GetShow()) 
		return flg;
	
	//HP�������Ȃ�Ɠ����蔻�肵�Ȃ�
	if (m_HP <= 0)
		return flg;
	
	//�G�̒Z�a�Ǝ����̒Z�a�Ń_���[�W
	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();

	//�G�ƒe�̓����蔻��
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_Laser.GetShow()) { continue; }

		CRectangle srec = m_Laser.GetRect();
		if (srec.CollisionRect(erec))
		{
			if (eneType == Turret)
				continue;

			if (m_Laser.GetNatu() == FIRE) {
				ene.Damage(FIRE_DAMAGE);
			}
			else if (m_Laser.GetNatu() == FROST) {
				ene.Damage(FROST_DAMAGE);
				ene.SetAbState(STATE_FROST);
				ene.SetAbStateWait(FROST_WAIT);
			}
			m_SEManager.SEPlayer((m_Laser.GetNatu() == FIRE) ? SE_FIRE : SE_ICE);
			
		}
	}

	for (int i = 0; i < PLAYERSHOT_COUNT; i++) {

		if (!m_PlShotAry[i].GetShow()) { continue; }
		CRectangle srec = m_PlShotAry[i].GetRect();
		if (srec.CollisionRect(erec))
		{
			if (eneType != Turret)
			{
				if (m_PlShotAry[i].GetNatu() == HEAL)
				{
					m_HP += HEAL_POWER;
					m_pEffectManager->Start(SetStartPos(), EFC_HEAL);
					ene.Damage(HEAL_DAMAGE);
				}
				else if (m_PlShotAry[i].GetNatu() == HEAVY)
				{
					ene.Damage(HEAVY_DAMAGE);
				}
				m_SEManager.SEPlayer((m_PlShotAry[i].GetNatu() == HEAL) ? SE_HEAL : SE_HEAVY);
			}
			m_PlShotAry[i].SetShow(false);
		}
	}
	//�_���[�W���̂��ߓ����蔻����s��Ȃ�
	if (m_DamageWait > 0) 
		return flg;

	//�G�Ƃ̓����蔻��
	if (eneType != Turret)
	{
		if (prec.CollisionRect(erec))
		{
			m_HP -= ENEMY_ATTAK_POWER;
			m_DamageWait = DAMAGE_WAIT;
			if (prec.Left < erec.Left)
			{
				m_MoveX = -5.0f;
				m_bReverse = false;
			}
			else
			{
				m_MoveX = 5.0f;
				m_bReverse = true;
			}
			m_Motion.ChangeMotion(MOTION_DAMAGE);

			if (m_HP <= 0)
			{
				m_SEManager.SEPlayer(SE_PLAYER_DIE);
				//�����G�t�F�N�g�𔭐�������
				m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
				m_bShow = false;
			}
			else
			{
				m_SEManager.SEPlayer(SE_PLAYER_DAMAGE);
				//�_���[�W�G�t�F�N�g�𔭐�������
				m_pEffectManager->Start(SetStartPos(), EFC_DAMAGE);
			}
			flg = true;
		}
	}

	//�G�̒e�Ƃ̓����蔻��
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
	{
		if (!ene.ShotArrayBool(i))
			continue;
		CRectangle esrec = ene.ShotArrayRect(i);
		if (prec.CollisionRect(esrec))
		{
			m_HP -= 5;
			m_DamageWait = DAMAGE_WAIT;
			if (prec.Left < erec.Left)
			{
				m_MoveX = -5.0f;
				m_bReverse = false;
			}
			else
			{
				m_MoveX = 5.0f;
				m_bReverse = true;
			}
			m_Motion.ChangeMotion(MOTION_DAMAGE);

			if (m_HP <= 0)
			{
				
				m_SEManager.SEPlayer(SE_PLAYER_DIE);
				
				//�����G�t�F�N�g�𔭐�������
				m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
				m_bShow = false;
			}
			else
			{
				m_SEManager.SEPlayer(SE_PLAYER_DAMAGE);
				//�_���[�W�G�t�F�N�g�𔭐�������
				m_pEffectManager->Start(SetStartPos(), EFC_DAMAGE);
			}
		}
	}

	//�v���C���[�ƓG�̒e���m�̓����蔻��
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_PlShotAry[i].GetShow()) { continue; }

		CRectangle srec = m_PlShotAry[i].GetRect();
		for (int j = 0; j < ENEMY_SHOT_COUNT; j++) {
			if (!ene.ShotArrayBool(j))
				continue;
			CRectangle esrec = ene.ShotArrayRect(j);
			if (srec.CollisionRect(esrec))
			{
				switch (m_PlShotAry[i].GetNatu())
				{
				case HEAL:
					m_PlShotAry[i].SetShow(false);
					ene.SetShotShow(false, j);
					break;

				case HEAVY:
					ene.SetShotShow(false, j);
					m_PlShotAry[i].SetRectCount();
					m_PlShotAry[i].SetThroughCount();
					break;
				}
				break;
			}
		}
	}

	return flg;

}

bool CPlayer::Collision_Stage1_Boss(CEnemy_Stage1_Boss& boss) {
	if (boss.GetNowBossHP() <= 0)
		return false;

	//HP�������Ȃ�Ɠ����蔻�肵�Ȃ�
	if (m_HP <= 0)
		return false;


	//�_���[�W���̂��ߓ����蔻����s��Ȃ�
	if (m_DamageWait > 0)
		return false;

	//�G�̒Z�a�Ǝ����̒Z�a�Ń_���[�W
	CRectangle prec = GetRect();
	CRectangle erec = boss.GetRect();

	for (int i = 0; i < ENEMY_BOSS_SLASH_COUNT; i++)
	{
		if (!boss.ShotArrayBool(i))
			continue;

		if (prec.CollisionRect(boss.ShotArrayRect(i)))
		{
			m_HP -= ENEMY_ATTAK_POWER;
			m_DamageWait = DAMAGE_WAIT;
			if (prec.Left < boss.ShotArrayRect(i).Left)
			{
				m_MoveX = -5.0f;
			}
			else
			{
				m_MoveX = 5.0f;
			}
			m_Motion.ChangeMotion(MOTION_DAMAGE);

			if (m_HP <= 0)
			{
				
				m_SEManager.SEPlayer(SE_PLAYER_DIE);
				//�����G�t�F�N�g�𔭐�������
				m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
				m_bShow = false;
			}
			else
			{
				
				m_SEManager.SEPlayer(SE_PLAYER_DAMAGE);
				//�_���[�W�G�t�F�N�g�𔭐�������
				m_pEffectManager->Start(SetStartPos(), EFC_DAMAGE);
			}
			return true;
		}
	}

	if (prec.CollisionRect(erec))
	{
		m_HP -=  ENEMY_ATTAK_POWER;
		m_DamageWait = DAMAGE_WAIT;
		if (prec.Left < erec.Left)
		{
			m_MoveX = -5.0f;
		}
		else
		{
			m_MoveX = 5.0f;
		}
		m_Motion.ChangeMotion(MOTION_DAMAGE);

		if (m_HP <= 0)
		{
			m_SEManager.SEPlayer(SE_PLAYER_DIE);
			
			//�����G�t�F�N�g�𔭐�������
			m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
			m_bShow = false;
		}
		else
		{
			m_SEManager.SEPlayer(SE_PLAYER_DAMAGE);
			
			//�_���[�W�G�t�F�N�g�𔭐�������
			m_pEffectManager->Start(SetStartPos(), EFC_DAMAGE);
		}
		return true;
	}

	if (boss.isCollisionBossAttack(prec))
	{
		m_HP -= STAGE1_BOSS_SLASH_DAMAGE;
		m_DamageWait = DAMAGE_WAIT;
		if (prec.Left < erec.Left)
		{
			m_MoveX = -5.0f;
		}
		else
		{
			m_MoveX = 5.0f;
		}
		m_Motion.ChangeMotion(MOTION_DAMAGE);

		if (m_HP <= 0)
		{
			m_SEManager.SEPlayer(SE_PLAYER_DIE);
			
			//�����G�t�F�N�g�𔭐�������
			m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
			m_bShow = false;
		}
		else
		{

			m_SEManager.SEPlayer(SE_PLAYER_DAMAGE);
			//�_���[�W�G�t�F�N�g�𔭐�������
			m_pEffectManager->Start(SetStartPos(), EFC_WEAK);
		}
		return true;
	}

	//�G�ƒe�̓����蔻��
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_Laser.GetShow()) { continue; }

		CRectangle srec = m_Laser.GetRect();
		erec = boss.GetBossFrontRect();

		if (srec.CollisionRect(erec))
		{
			if (m_Laser.GetNatu() == FIRE) {
				boss.Damage(FIRE_DAMAGE, true);
				m_Laser.SetWallHitLaser(true);

			}
			else if (m_Laser.GetNatu() == FROST) {
				boss.Damage(FROST_DAMAGE, true);
				m_Laser.SetWallHitLaser(true);

			}
			m_SEManager.SEPlayer((m_Laser.GetNatu() == FIRE) ? SE_FIRE : SE_ICE);
			continue;
		}

		erec = boss.GetRect();
		if (srec.CollisionRect(erec))
		{
			if (m_Laser.GetNatu() == FIRE) {
				boss.Damage(FIRE_DAMAGE, false);
			}
			else if (m_Laser.GetNatu() == FROST) {
				boss.Damage(FROST_DAMAGE, false);
				boss.SetAbState(STATE_FROST);
				boss.SetAbStateWait(FROST_WAIT);
			}
			m_SEManager.SEPlayer((m_Laser.GetNatu() == FIRE) ? SE_FIRE : SE_ICE);
			
			continue;
		}
	}
	//�G�ƒe�̓����蔻��
	for (int i = 0; i < PLAYERSHOT_COUNT; i++) {
		if (!m_PlShotAry[i].GetShow()) { continue; }
		CRectangle srec = m_PlShotAry[i].GetRect();
		erec = boss.GetBossFrontRect();

		if (srec.CollisionRect(erec))
		{
			if (m_PlShotAry[i].GetNatu() == HEAL)
			{
				m_HP += HEAL_POWER;
				m_pEffectManager->Start(SetStartPos(), EFC_HEAL);
				boss.Damage(HEAL_DAMAGE, true);
			}
			else if (m_PlShotAry[i].GetNatu() == HEAVY)
			{
				boss.Damage(HEAVY_DAMAGE, true);

			}
			
			m_SEManager.SEPlayer((m_PlShotAry[i].GetNatu() == HEAL) ? SE_HEAL : SE_HEAVY);
			
			m_PlShotAry[i].SetShow(false);
			continue;
		}

		erec = boss.GetRect();
		if (srec.CollisionRect(erec))
		{
			if (m_PlShotAry[i].GetNatu() == HEAL)
			{
				m_HP += HEAL_POWER;
				m_pEffectManager->Start(SetStartPos(), EFC_HEAL);
				boss.Damage(HEAL_DAMAGE, false);
			}
			else if (m_PlShotAry[i].GetNatu() == HEAVY)
			{
				boss.Damage(HEAVY_DAMAGE, false);
			}
			
			m_SEManager.SEPlayer((m_PlShotAry[i].GetNatu() == HEAL) ? SE_HEAL : SE_HEAVY);
			
			m_PlShotAry[i].SetShow(false);
			continue;
		}
	}

	return false;

}

bool CPlayer::ColisionItem(CItem& itm)
{
	if (!itm.GetShow())
	{
		return false;
	}

	//�A�C�e���̒Z�a�Ǝ����̒Z�a�œ����蔻��
	CRectangle prec = GetRect();
	CRectangle irec = itm.GetRect();
	if (prec.CollisionRect(irec))
	{
		itm.Effect(IsJump(),m_bNextBossScene,m_MoveX,m_MoveY);
		return true;
	}
	return false;
}

bool CPlayer::CollisionAttackItem(CItem& itm)
{

	CRectangle irec = itm.GetRect();
	//�w偂̑��폜����

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_Laser.GetShow())
			return false;

		CRectangle srec = m_Laser.GetRect();
		if (irec.CollisionRect(srec))
		{
			switch (itm.GetType())
			{
			case ITEM_SPIDERWEB:
				if (m_Laser.GetNatu() == FIRE) {
					itm.SetShow(false);
					m_SEManager.SEPlayer(SE_FIRE_SPIDERWEB);
					
				}
				break;
			default:
				break;
			}
			return true;
		}
	}
	return false;
}

void CPlayer::CollisionStage(float ox, float oy)
{
	m_PosX += ox;
	m_PosY += oy;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������
	if (oy < 0 && m_MoveY >0)
	{
		m_MoveY = 0;
		if (m_bJump)
		{
			m_bJump = false;
			m_Motion.ChangeMotion(MOTION_JUMPEND);
		}
	}
	
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������
	if (ox < 0 && m_MoveX > 0)
	{
		m_MoveX = 0;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX = 0;
	}
}


#pragma endregion


//���Ғl��Ԃ��֐�
#pragma region Is�֐�

bool CPlayer::IsJump()
{
	if (m_MoveY < 0)
		return true;
	else
		return false;
}

#pragma endregion


//�`��
#pragma region Render�֐�

void CPlayer::Render(float wx,float wy){
	if (!m_bShow)
		return;

	//�C���^�[�o��2�t���[�����Ƃɕ`������Ȃ�
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}

	//�`��Z�a
	CRectangle dr = m_SrcRect;
	//�`��ʒu
	float px = m_PosX - wx;
	float py = m_PosY - wy;
	//���]�t���O��ON�̏ꍇ�`��Z�a�𔽓]������
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//�e�N�X�`���̕`��
	m_Texture.Render(px, py, dr);
}

void CPlayer::RenderStatus() {
	//HP�ɉ����ĒZ�a�̕���ω�������
	/*CRectangle hprec(0, 0, 795 * (m_HP * 0.01f), 31);
	m_HPBarTexture.Render(100,23, hprec);*/
	CRectangle rec(0, 0, 795, 31);
	m_HPBarTexture.RenderScale(100, 23, m_HP * 0.01f, 1.0f, rec, MOF_COLOR_WHITE);//�摜�����k����\��*/
	/*CRectangle sprec(0, 0, 702 * (m_SP * 0.01f), 27);
	m_SPBarTexture.Render(80,51, sprec);*/
	CRectangle sprec(0, 0, 702, 27);
	m_SPBarTexture.RenderScale(80, 51, m_SP * 0.01f, 1.0f, sprec, MOF_COLOR_WHITE);//�摜�����k����\��*/
	//�t���[�����㕔�ɕ`��
	m_FrameTexture.Render(0, 0);

	switch (GetNatu())
	{
	case HEAL:
		m_HealTex.Render(0, 0);
		m_Heal2Tex.RenderScale(100, 75, 0.7f);
		m_Heavy2Tex.RenderScale(250, 75, 0.7f, MOF_XRGB(125, 125, 125));
		m_Fire2Tex.RenderScale(400, 75, 0.7f, MOF_XRGB(125, 125, 125));
		m_Frost2Tex.RenderScale(550, 75, 0.7f, MOF_XRGB(125, 125, 125));
		break;
	case HEAVY:
		m_HeavyTex.Render(0, 0);
		m_Heal2Tex.RenderScale(100, 75, 0.7f, MOF_XRGB(125, 125, 125));
		m_Heavy2Tex.RenderScale(250, 75, 0.7f);
		m_Fire2Tex.RenderScale(400, 75, 0.7f, MOF_XRGB(125, 125, 125));
		m_Frost2Tex.RenderScale(550, 75, 0.7f, MOF_XRGB(125, 125, 125));

		break;
	case FIRE:
		m_FireTex.Render(0, 0);
		m_Heal2Tex.RenderScale(100, 75, 0.7f, MOF_XRGB(125, 125, 125));
		m_Heavy2Tex.RenderScale(250, 75, 0.7f, MOF_XRGB(125, 125, 125));
		m_Fire2Tex.RenderScale(400, 75, 0.7f);
		m_Frost2Tex.RenderScale(550, 75, 0.7f, MOF_XRGB(125, 125, 125));

		break;
	case FROST:
		m_FrostTex.Render(0, 0);
		m_Heal2Tex.RenderScale(100, 75, 0.7f, MOF_XRGB(125, 125, 125));
		m_Heavy2Tex.RenderScale(250, 75, 0.7f, MOF_XRGB(125, 125, 125));
		m_Fire2Tex.RenderScale(400, 75,0.7f,MOF_XRGB(125, 125, 125));
		m_Frost2Tex.RenderScale(550, 75, 0.7f);

		break;
	}
	
}

void  CPlayer::UIRender(float wx, float wy) {
	switch (GetNatu())
	{
		case HEAL:
		{
			if (m_bUIAnimation) {
				m_HeTex.RenderScale(SetStartPos().x - 85 + m_HeTex.GetWidth() * 0.5f - wx, SetStartPos().y - 100 - wy, 0.5, MOF_ARGB(m_UIAnimationAlpha,255,255,255), TEXALIGN_CENTERCENTER);
			}
			break;

		}

		case HEAVY:
		{
			if (m_bUIAnimation) {
				m_H2Tex.RenderScale(SetStartPos().x - 85 + m_HeTex.GetWidth() * 0.5f - wx, SetStartPos().y - 100 - wy, 0.5, MOF_ARGB(m_UIAnimationAlpha, 255, 255, 255), TEXALIGN_CENTERCENTER);
			}
			break;
		}

		case FIRE:
		{
			if (m_bUIAnimation) {
				m_Fi2Tex.RenderScale(SetStartPos().x - 85 + m_HeTex.GetWidth() * 0.5f - wx, SetStartPos().y - 100 - wy, 0.5, MOF_ARGB(m_UIAnimationAlpha, 255, 255, 255), TEXALIGN_CENTERCENTER);
				break;
			}
		}
		case FROST:
		{
			if (m_bUIAnimation) {
				m_Fr2Tex.RenderScale(SetStartPos().x - 85 + m_HeTex.GetWidth() * 0.5f - wx, SetStartPos().y - 100 - wy, 0.5, MOF_ARGB(m_UIAnimationAlpha, 255, 255, 255), TEXALIGN_CENTERCENTER);

			}
			break;
		}
	}
}

void CPlayer::RenderDebug(float wx, float wy){
	//�ʒu�̕`��
	CGraphicsUtilities::RenderString(10,70,"�v���C���[�ʒu X : %.0f , Y : %.0f , Move_Y : %.0f",m_PosX,m_PosY,m_MoveY);
	if(m_bNextBossScene)
		CGraphicsUtilities::RenderString(10,130, "�{�X�����t���O : TRUE");
	else
		CGraphicsUtilities::RenderString(10, 130, "�{�X�����t���O : FALSE");
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));

	CRectangle wr = GetWaterRect();
	CGraphicsUtilities::RenderRect(wr.Left - wx, wr.Top - wy, wr.Right - wx, wr.Bottom - wy, MOF_XRGB(0, 0, 255));

	CGraphicsUtilities::RenderCircle(m_PosX - wx + 30,m_PosY - wy + 30, 2, MOF_XRGB(255, 0, 0));
	for (int i = 0; i < PLAYERSHOT_COUNT; i++) {
		m_PlShotAry[i].RenderDebug(wx, wy);
	}
	m_Laser.RenderDebug(wx,wy);
}

#pragma endregion


//���
#pragma region Release�֐�

void CPlayer::Release(){
	m_Texture.Release();
	m_Motion.Release();
	m_FrameTexture.Release();
	m_HPBarTexture.Release();
	m_SPBarTexture.Release();
	m_ShotHealTex.Release();
	m_ShotHeavyTex.Release();
	m_HealTex.Release();
	m_HeavyTex.Release();
	m_FireTex.Release();
	m_FrostTex.Release();
	m_FireLazerTexture.Release();
	m_FrostLazerTexture.Release();
	m_SEManager.Release();
	m_Heal2Tex.Release();
	m_Heavy2Tex.Release();
	m_Fire2Tex.Release();
	m_Frost2Tex.Release();
	m_FireLaserUpDownTexture.Release();
	m_FrostLaserUpDownTexture.Release();
	m_Laser.Release();

	m_H2Tex.Release();

	m_HeTex.Release();

	m_Fr2Tex.Release();

	m_Fi2Tex.Release();
}

#pragma endregion


//���̑��̊֐�
#pragma region Other�֐�


void CPlayer::Fall() {
	//��ʊO�ŗ����Ƃ���HP��0�ɂ���
	if (m_PosY >= g_pGraphics->GetTargetHeight() && m_HP > 0)
	{
		m_HP = 0;
		//�����G�t�F�N�g�𔭐�������
		m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
		m_bShow = false;
	}
}


#pragma endregion