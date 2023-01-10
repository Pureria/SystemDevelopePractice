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
m_bGoal(false),
m_PlShotAry(),
m_NextBossScene(false){}

#pragma endregion


//�ǂݍ��ݏ���
#pragma region Load�֐�

bool CPlayer::Load(){
	//�e�N�X�`���̓ǂݍ���
	if (!m_Texture.Load("Player/chara_ren.png"))				{		return false;		}

	if (!m_FrameTexture.Load("Player/Frame.png"))				{		return false;		}

	if (!m_HPTexture.Load("Player/HP.png"))						{		return false;		}

	if (!m_HPBarTexture.Load("Player/HPBAR.png"))				{		return false;		}	
	
	if (!m_SPTexture.Load("Player/SP.png"))						{		return false;		}

	if (!m_SPBarTexture.Load("Player/SPBAR.png"))				{		return false;		}

	if (!m_ShotHealTex.Load("Player/healammo.png"))				{		return false;		}

	if (!m_ShotHeavyTex.Load("Player/heavyammo.png"))			{		return false;		}

	//TODO: Fire�֐��Ɉړ�
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)	
	{
		m_PlShotAry[i].SetHealTexture(&m_ShotHealTex); 
		m_PlShotAry[i].SetHeavyTexture(&m_ShotHeavyTex);
	}

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
					{5,24,0},{5,24,1},{5,24,2},{5,24,3}
			}
		},
		{
			"�ʏ�e�̏e���グ��",
			0,0,
			128,128,
			FALSE,
			{
					{2,0,0},{2,1,0},{2,2,0},{2,3,0},
			}
		},
		{
			"�ʏ�e�̏e��������",
			0,0,
			128,128,
			FALSE,
			{
					{2,0,0},{2,1,0},{2,2,0},{2,3,0},
			}
		},
		{
			"���[�U�[�̏e���グ��",
			0,0,
			128,128,
			FALSE,
			{
					{2,0,0},{2,1,0},{2,2,0},{2,3,0},
			}
		},
		{
			"���[�U�[�̏e��������",
			0,0,
			128,128,
			FALSE,
			{
					{2,0,0},{2,1,0},{2,2,0},{2,3,0},
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
	m_bGoal = false;
	m_bTop = false;
	m_bBottom = false;
	m_ShotType = NORMAL;
	m_NatuType = NULL;
	m_DrcType = NULL;
	m_NextBossScene = false;
	//�v���C���[�̑f�ޓǂݍ���
	Load();
}


#pragma endregion


//�X�V
#pragma region Update�֐�

void CPlayer::Update() {
	UpdateShot();
	//TODO: �Q�[���p�b�h�g�p��
	//g_pInput->GetGamePad(m_GamePadCnt);

	//HP�������Ȃ�Ɣ����̏I����ҋ@���ďI��
	if (PlayerEnd()) {	return;	}

	//�ړ��t���O�A���̃t���[���ł̈ړ�������������ۑ�
	m_bMove = false;
	//�U�����A���n�̏ꍇ�̓���
	if (m_Motion.GetMotionNo() == MOTION_ATTACK || m_Motion.GetMotionNo() == MOTION_JUMPEND)
	{
		//�I���őҋ@�ɖ߂�
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	else if(m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		//�I���őҋ@�ɖ߂�
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	/*else if (m_Motion.GetMotionNo() == MOTION_NORMAL_MUZZLETOP || m_Motion.GetMotionNo() == MOTION_NORMAL_MUZZLEBOTTOM
			|| m_Motion.GetMotionNo() == MOTION_LASER_MUZZLETOP || m_Motion.GetMotionNo() == MOTION_LASER_MUZZLEBOTTOM) {

		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}//*/
	else
	{
		//�L�[���͂ɂ�铮��
		UpdateKey();
		//TODO: �Q�[���p�b�h�̐ڑ��m�F
		/*if (m_pGamePad != nullptr) {
			UpdatePadKey(m_pGamePad);//�Q�[���p�b�h�ɂ�铮��
		}//*/
	
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

	//�_���[�W�̃C���^�[�o�������炷
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}

}


void CPlayer::UpdateShot() {
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_Laser[i].Update();
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
			}
		}
		else if (m_MoveX < 0)
		{
			m_MoveX += PLAYER_SPEED;
			if (m_MoveX >= 0)
			{
				m_MoveX = 0;
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
		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}

	//E�L�[�ŃW�����v
	if (g_pInput->IsKeyHold(MOFKEY_SPACE) && !m_bJump)
	{
		m_bJump = true;
		m_MoveY = PLAYER_JUMP;
		m_Motion.ChangeMotion(MOTION_JUMPSTART);
	}
}


#pragma endregion


//�ς��鏈��
#pragma region Change�֐�

void CPlayer::BulletChange() {
	if (g_pInput->IsKeyPush(MOFKEY_I)) {
		TypeChange();
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
		if (IsLaser()) {
			m_Motion.ChangeMotion(MOTION_LASER_MUZZLETOP);
		}
		else {
			m_Motion.ChangeMotion(MOTION_NORMAL_MUZZLETOP);
		}
	}
	else if (g_pInput->IsKeyPush(MOFKEY_W) && (m_bTop || m_bBottom)) {
		m_bTop = false;
		m_bBottom = false;
		m_Motion.ChangeMotion(MOTION_WAIT);
	}
	if (g_pInput->IsKeyPush(MOFKEY_S) && !m_bBottom) {
		m_bBottom = true;
		m_bTop = false;
		if (IsLaser()) {
			m_Motion.ChangeMotion(MOTION_LASER_MUZZLEBOTTOM);
		}
		else {
			m_Motion.ChangeMotion(MOTION_NORMAL_MUZZLEBOTTOM);
		}
	}
	else if (g_pInput->IsKeyPush(MOFKEY_S) && (m_bTop || m_bBottom)) {
		m_bBottom = false;
		m_bTop = false;
		m_Motion.ChangeMotion(MOTION_WAIT);
	}
}

void CPlayer::DirecMotionChange() {
	if (GetDirec() == RIGHTTOP || GetDirec() == LEFTTOP) {
		if (IsLaser()) {
			m_Motion.ChangeMotion(MOTION_LASER_MUZZLETOP);
		}
		else {
			m_Motion.ChangeMotion(MOTION_NORMAL_MUZZLETOP);
		}
	}
	else if (GetDirec() == RIGHTBOTTOM || GetDirec() == LEFTBOTTOM) {
		if (IsLaser()) {
			m_Motion.ChangeMotion(MOTION_LASER_MUZZLEBOTTOM);
		}
		else {
			m_Motion.ChangeMotion(MOTION_NORMAL_MUZZLEBOTTOM);
		}
	}
	else {
		m_Motion.ChangeMotion(MOTION_ATTACK);
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
				m_ShotWait = PLAYERSHOT_WAIT;
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
	if (!m_bReverse) {
		if (m_bTop) {
			m_PlShotAry[i].Fire(SetStartPos(), RIGHTTOP, m_NatuType);
			return;
		}
		else if (m_bBottom) {
			m_PlShotAry[i].Fire(SetStartPos(), RIGHTBOTTOM, m_NatuType);
			return;
		}
		else {
			m_PlShotAry[i].Fire(SetStartPos(), RIGHT, m_NatuType);
			return;
		}
	}
	else {
		if (m_bTop) {
			m_PlShotAry[i].Fire(SetStartPos(), LEFTTOP, m_NatuType);
			return;
		}
		else if (m_bBottom) {
			m_PlShotAry[i].Fire(SetStartPos(), LEFTBOTTOM, m_NatuType);
			return;
		}
		else {
			m_PlShotAry[i].Fire(SetStartPos(), LEFT, m_NatuType);
			return;
		}
	}
	/*switch (GetDirec())
	{
		case RIGHT:
			m_PlShotAry[i].Fire(SetStartPos(), RIGHT, m_NatuType);
			break;
		case RIGHTTOP:
			m_PlShotAry[i].Fire(SetStartPos(), RIGHTTOP, m_NatuType);
			break;
		case RIGHTBOTTOM:
			m_PlShotAry[i].Fire(SetStartPos(), RIGHTBOTTOM, m_NatuType);
			break;

		case LEFT:
			m_PlShotAry[i].Fire(SetStartPos(), LEFT, m_NatuType);
			break;
		case LEFTTOP:
			m_PlShotAry[i].Fire(SetStartPos(), LEFTTOP, m_NatuType);
			break;
		case LEFTBOTTOM:
			m_PlShotAry[i].Fire(SetStartPos(), LEFTBOTTOM, m_NatuType);
			break;
	}//*/
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

			for (int i = 0; i < PLAYERSHOT_COUNT; i++) {
				if (m_Laser[i].GetShow()) { continue; }
				m_ShotWait = PLAYERSHOT_WAIT;
				ShotRevLaser(i);
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
void CPlayer::ShotRevLaser(int i) {
	if (!m_bReverse) {
		if (m_bTop) {
			m_Laser[i].Fire(SetStartPos(), RIGHTTOP, m_NatuType);
		}
		else if (m_bBottom) {
			m_Laser[i].Fire(SetStartPos(), RIGHTBOTTOM, m_NatuType);
		}
		else {
			m_Laser[i].Fire(SetStartPos(), RIGHT, m_NatuType);
		}
	}
	else {
		if (m_bTop) {
			m_Laser[i].Fire(SetStartPos(), LEFTTOP, m_NatuType);
		}
		else if (m_bBottom) {
			m_Laser[i].Fire(SetStartPos(), LEFTBOTTOM, m_NatuType);
		}
		else {
			m_Laser[i].Fire(SetStartPos(), LEFT, m_NatuType);
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
	m_DamageWait = 60;
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
		//�����G�t�F�N�g�𔭐�������
		m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
	}
	else
	{
		//�_���[�W�G�t�F�N�g�𔭐�������
		m_pEffectManager->Start(SetStartPos(), EFC_DAMAGE);
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
		if (!m_PlShotAry[i].GetShow()) { continue; }
		CRectangle srec = m_PlShotAry[i].GetRect();
		if (srec.CollisionRect(erec))
		{
			if (eneType != Turret)
			{
				if (m_PlShotAry[i].GetNatu() == HEAL)
				{
					//TODO::�񕜒e�̉񕜗�
					m_HP += HEAL_POWER;
					//TODO::�_���[�W��
					ene.Damage(10);
				}
				else if (m_PlShotAry[i].GetNatu() == HEAVY)
				{
					//TODO::�_���[�W��
					ene.Damage(12);
				}
			}
			m_PlShotAry[i].SetShow(false);
		}

	}

	//�G�ƃ��[�U�[�̓����蔻��
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_Laser[i].GetShow()) { continue; }

		CRectangle srec = m_Laser[i].GetRect();
		if (srec.CollisionRect(erec))
		{
			if (eneType == Turret)
				continue;

			//TODO::���[�U�[�̃_���[�W
			if (m_Laser[i].GetNatu() == FIRE) {
				ene.Damage(10);
			}
			else if (m_Laser[i].GetNatu() == FROST) {
				ene.Damage(12);
			}
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
				//�����G�t�F�N�g�𔭐�������
				m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
			}
			else
			{
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
				//�����G�t�F�N�g�𔭐�������
				m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
			}
			else
			{
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
			if (!ene.ShotArrayBool(i))
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
					break;
				}
				break;
			}
		}
	}


	return flg;

}

bool CPlayer::Collision_Stage1_Boss(CEnemy_Stage1_Boss& boss) {
	if (!boss.GetShow())
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
			//�����G�t�F�N�g�𔭐�������
			m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
		}
		else
		{
			//�_���[�W�G�t�F�N�g�𔭐�������
			m_pEffectManager->Start(SetStartPos(), EFC_DAMAGE);
		}
		return true;
	}

	if (boss.isCollisionBossAttack(prec))
	{
		m_HP -= 30;
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
			//�����G�t�F�N�g�𔭐�������
			m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
		}
		else
		{
			//�_���[�W�G�t�F�N�g�𔭐�������
			m_pEffectManager->Start(SetStartPos(), EFC_DAMAGE);
		}
		return true;
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
		itm.Effect(m_HP, m_bGoal,IsJump(),m_NextBossScene,m_MoveX,m_MoveY);
		return true;
	}
	return false;
}

bool CPlayer::CollisionAttackItem(CItem& itm)
{
	//TODO::�e�̎�ނɂ���ď����̎��s

	CRectangle irec = itm.GetRect();
	//�w偂̑��폜����

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_Laser[i].GetShow())
			return false;

		CRectangle srec = m_Laser[i].GetRect();
		if (irec.CollisionRect(srec))
		{
			switch (itm.GetType())
			{
			case ITEM_SPIDERWEB:
				if(m_Laser[i].GetNatu() == FIRE)
					itm.SetShow(false);
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
	//�e�̕`��
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_Laser[i].Render(wx, wy);
		m_PlShotAry[i].Render(wx, wy);
	}

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
		if (m_Motion.GetMotionNo() == MOTION_ATTACK)
		{
			px -= PLAYER_ATTACKWIDTH;
		}
	}
	//�e�N�X�`���̕`��
	m_Texture.Render(px, py, dr);
}

void CPlayer::RenderStatus() {
	m_HPTexture.Render(0,0);
	m_SPTexture.Render(0,0);
	//HP�ɉ����ĒZ�a�̕���ω�������
	CRectangle hprec(0, 0, 728 * (m_HP * 0.01f), 128);
	m_HPBarTexture.Render(180, -20, hprec);
	CRectangle sprec(0, 0, 728 * (m_SP * 0.01f), 128);
	m_SPBarTexture.Render(180, 20, sprec);
	//�t���[�����㕔�ɕ`��
	m_FrameTexture.Render(0, 0);
}

void CPlayer::RenderDebug(float wx, float wy){
	//�ʒu�̕`��
	CGraphicsUtilities::RenderString(10,70,"�v���C���[�ʒu X : %.0f , Y : %.0f , Move_Y : %.0f",m_PosX,m_PosY,m_MoveY);
	if(m_NextBossScene)
		CGraphicsUtilities::RenderString(10,130, "�{�X�����t���O : TRUE");
	else
		CGraphicsUtilities::RenderString(10, 130, "�{�X�����t���O : FALSE");
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));

	CGraphicsUtilities::RenderCircle(m_PosX - wx + 30,m_PosY - wy + 30, 2, MOF_XRGB(255, 0, 0));
	for (int i = 0; i < PLAYERSHOT_COUNT; i++) {
		m_PlShotAry[i].RenderDebug(wx, wy);
		m_Laser[i].RenderDebug(wx,wy);
	}
}

#pragma endregion


//���
#pragma region Release�֐�

void CPlayer::Release(){
	m_Texture.Release();
	m_Motion.Release();
	m_FrameTexture.Release();
	m_HPTexture.Release();
	m_HPBarTexture.Release();
	m_SPTexture.Release();
	m_SPBarTexture.Release();
	m_ShotHealTex.Release();
	m_ShotHeavyTex.Release();
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
	}
}


#pragma endregion