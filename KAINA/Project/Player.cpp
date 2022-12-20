#include	"Player.h"

/**
 * �R���X�g���N�^
 *
 */
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
m_NextBossScene(false){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CPlayer::Load(void){
	//�e�N�X�`���̓ǂݍ���
	if (!m_Texture.Load("player.png"))				{		return false;	}

	if (!m_FrameTexture.Load("Frame.png"))			{		return false;	}

	if (!m_HPTexture.Load("HP.png"))				{		return false;	}

	if (!m_HPBarTexture.Load("HPBAR.png"))			{		return false;	}	
	
	if (!m_SPTexture.Load("SP.png"))				{		return false;	}

	if (!m_SPBarTexture.Load("SPBAR.png"))			{		return false;	}

	if (!m_ShotHealTex.Load("P_missile.png"))		{		return false;	}

	if (!m_ShotHeavyTex.Load("HeavyAmmo.png"))		{		return false;	}

	//if (!m_LaserTex.Load("Shot.png")) { return false; }

	//TODO: Fire�֐��Ɉړ�
	for (int i = 0; i < PLAYERSHOT_COUNT; i++) {
		m_PlShotAry[i].SetHealTexture(&m_ShotHealTex); 
	}

	//for (int i = 0; i < PLAYERSHOT_COUNT; i++) { m_Laser[i].SetTexture(&m_LaserTex); }

	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim[] = {
		{
			"�ҋ@",
			0,0,
			120,128,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
		},
		{
			"�ړ�",
			0,70,
			120,128,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0}}
		},
		{
			"�W�����v�ړ�",
			0,140,
			120,128,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
		},
		{
			"�W�����v�I��",
			240,140,
			120,128,
			FALSE,{{2,0,0},{2,1,0}}
		},
		{
			"�U��",
			0,350,
			120,128,
			FALSE,{{2,0,0},{2,1,0},{2,2,0},{2,3,0},{2,4,0},{2,5,0},{2,6,0}}
		},
		{
			"�_���[�W",
			480,0,
			120,128,
			FALSE,{{20,0,0}}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);
	
	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * �v���C���[�̈ʒu�ȂǏ�Ԃ��������������Ƃ��Ɏ��s����B
 */
void CPlayer::Initialize(void){
	m_PosX = 200;
	m_PosY = 0;
	m_bMove = false;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bReverse = false;
	m_bJump = false;
	m_HP = 100;
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
	//�v���C���[�̑f�ޓǂݍ���
	Load();
	m_NextBossScene = false;
}

/**
 * �X�V
 *
 */
void CPlayer::Update() {
	UpdateShot();
	//TODO: �Q�[���p�b�h�g�p��
	//g_pInput->GetGamePad(m_GamePadCnt);

	//HP�������Ȃ�Ɣ����̏I����ҋ@���ďI��
	PlayerEnd();

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

	//�_���[�W�̃C���^�[�o�������炷
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}

}

/**
 * �L�[���͂ɂ�铮��X�V
 *
 */
void CPlayer::UpdateKey( void ) {
	//�L�[�{�[�h�ł̈ړ�����
	MoveKey();

	//�e�̓����؂�ւ�
	BulletChange();

	//�e���̌�������
	DirecTpBtm();

	//�e�̓����ω��̏���
	NatuChange();

	//SPACE�L�[�ōU��
	ShotManager();

}

//�v���C���[�̓����̐���
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

//�e�̎�ނ�ς��鏈��
void CPlayer::BulletChange() {
	if (g_pInput->IsKeyPush(MOFKEY_I)) {
		Change();
	}
}

void CPlayer::Change() {
	if (m_ShotType == NORMAL) {
		m_ShotType = LASER;
		m_NatuType = FIRE;
	}
	else {
		m_ShotType = NORMAL;
		m_NatuType = HEAL;
	}
}

//�e�̓�����ς��鏈��
void CPlayer::NatuChange() {
	if (g_pInput->IsKeyPush(MOFKEY_O)) {
		switch (m_NatuType)
		{
		case FIRE:
			m_NatuType = FROST;
			break;
		case FROST:
			m_NatuType = FIRE;
			break;
		case HEAL:
			m_NatuType = HEAVY;
			break;
		case HEAVY:
			m_NatuType = HEAL;
			break;
		}
	}
}

void CPlayer::ShotManager() {
	if (IsLaser()) {
		FireShotLaser();
	}
	else {
		FireShot();
	}
}

//�e�̕�����ς��鏈��
void CPlayer::DirecTpBtm() {
	if (g_pInput->IsKeyPush(MOFKEY_W) && !m_bTop) {
		m_bTop = true;
		m_bBottom = false;

	}
	else if (g_pInput->IsKeyPush(MOFKEY_W) && m_bTop) {
		m_bTop = false;//�e�������ɖ߂�
	}
	if (g_pInput->IsKeyPush(MOFKEY_S) && !m_bBottom) {
		m_bBottom = true;
		m_bTop = false;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_S) && m_bBottom) {
		m_bBottom = false;
	}
}

//�e��������
void CPlayer::FireShot() {
	//�e�̔���

	if (m_ShotWait <= 0)
	{
		if (g_pInput->IsKeyPush(MOFKEY_P))
		{
			m_Motion.ChangeMotion(MOTION_ATTACK);

			for (int i = 0; i < PLAYERSHOT_COUNT; i++) {
				if (m_PlShotAry[i].GetShow())
				{
					continue;
				}
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
		}
		else if (m_bBottom) {
			m_PlShotAry[i].Fire(SetStartPos(), RIGHTBOTTOM, m_NatuType);
		}
		else {
			m_PlShotAry[i].Fire(SetStartPos(), RIGHT, m_NatuType);
		}
	}
	else {
		if (m_bTop) {
			m_PlShotAry[i].Fire(SetStartPos(), LEFTTOP, m_NatuType);
		}
		else if (m_bBottom) {
			m_PlShotAry[i].Fire(SetStartPos(), LEFTBOTTOM, m_NatuType);
		}
		else {
			m_PlShotAry[i].Fire(SetStartPos(), LEFT, m_NatuType);
		}
	}
}

void CPlayer::FireShotLaser() {
	//�e�̔���

	if (m_ShotWait <= 0)
	{
		if (g_pInput->IsKeyPush(MOFKEY_P))
		{
			m_Motion.ChangeMotion(MOTION_ATTACK);

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


//�e�̍X�V
void CPlayer::UpdateShot() {
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_Laser[i].Update();
		m_PlShotAry[i].Update();
	}
}

/**
 * �ړ��X�V
 *
 */
void CPlayer::UpdateMove(void){
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

bool CPlayer::CollisionEnemy_1(CEnemy& ene) {
	if (!ene.GetShow()) 
		return false;
	
	//HP�������Ȃ�Ɠ����蔻�肵�Ȃ�
	if (m_HP <= 0)
		return false;


	//�_���[�W���̂��ߓ����蔻����s��Ȃ�
	if (m_DamageWait > 0) 
		return false;

	//�G�̒Z�a�Ǝ����̒Z�a�Ń_���[�W
	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();

	//�C��Ƃ̓����蔻��
	/*
	if (prec.CollisionRect(erec))
	{
		m_HP -= 5;
		m_DamageWait = 60;
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
		return true;
	}
	*/

	//�G�̒e�Ƃ̓����蔻��
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
	{
		if (!ene.ShotArrayBool(i))
			continue;
		CRectangle esrec = ene.ShotArrayRect(i);
		if (prec.CollisionRect(esrec))
		{
			m_HP -= 5;
			m_DamageWait = 60;
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


	//�G�ƒe�̓����蔻��
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!IsLaser()) {
			if (!m_PlShotAry[i].GetShow()) { continue; }
			CRectangle srec = m_PlShotAry[i].GetRect();
			if (srec.CollisionRect(erec))
			{
				switch (m_PlShotAry[i].GetNatu())
				{
				case HEAL:
					m_HP += HEAL_POWER;
					break;

				case HEAVY:
					ene.SetShotShow(false, i);
					break;
				}
				m_PlShotAry[i].SetShow(false);
				break;
			}
		}
		else {
			if (!m_Laser[i].GetShow()) { continue; }
			CRectangle lrec = m_Laser[i].GetRect();
			
			if (lrec.CollisionRect(erec))
			{
				break;
			}
		}
	}

	//�v���C���[�ƓG�̒e���m�̓����蔻��
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_PlShotAry[i].GetShow()) { continue; }

		CRectangle srec = m_PlShotAry[i].GetRect();
		for (int j = 0; j < ENEMY_SHOT_COUNT; j++) {
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


	return false;

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
		DeffenceProc(5);
		m_DamageWait = 60;
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
		return true;
	}

	//�U�����̏ꍇ�̂ݍU���Ƃ̓����蔻������s
	if (m_Motion.GetMotionNo() != MOTION_ATTACK)
		return false;

	return false;

}
/**�����蔻��
* �����̃A�C�e���ɑ΂��ĒZ�a���m�̓����蔻������s����
* �������Ă����ꍇ�̓v���C���[�̏�Ԃ�ύX����
* 
* ����
* [in]			itm			������s���A�C�e��
* 
* �߂�l
* �������Ă���ꍇ��true�A�������Ă��Ȃ����false��Ԃ�
* */
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

/**
 * �v���C���[���S���̏���
 *
 */
void CPlayer::PlayerEnd() {
	if (m_HP <= 0)
	{
		if (!m_pEndEffect || !m_pEndEffect->GetShow())
		{
			m_bDead = true;
		}
		return;
	}
}

//�v���C���[�̗�������
void CPlayer::Fall() {
	//��ʊO�ŗ����Ƃ���HP��0�ɂ���
	if (m_PosY >= g_pGraphics->GetTargetHeight() && m_HP > 0)
	{
		m_HP = 0;
		//�����G�t�F�N�g�𔭐�������
		m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
	}
}

//�X�e�[�W�Ƃ̓����蔻��
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

bool CPlayer::IsJump()
{
	if (m_MoveY < 0)
		return true;
	else
		return false;
}

/**
 * �`��
 *
 */
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

void CPlayer::RenderStatus(void) {
	m_HPTexture.Render(0,0);
	m_SPTexture.Render(0,0);
	//HP�ɉ����ĒZ�a�̕���ω�������
	CRectangle hprec(0, 0, 1064 * (m_HP * 0.01f), 64);
	m_HPBarTexture.Render(10, 0, hprec);
	CRectangle sprec(0, 0, 1064 * (m_SP * 0.01f), 64);
	m_SPBarTexture.Render(248, 20, sprec);
	//�t���[�����㕔�ɕ`��
	m_FrameTexture.Render(0, 0);
}

/**
 * �f�o�b�O�`��
 *
 */
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

/**
 * ���
 *
 */
void CPlayer::Release(void){
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
