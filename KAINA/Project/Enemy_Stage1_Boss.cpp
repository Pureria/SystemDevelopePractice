#include "Enemy_Stage1_Boss.h"
#include	"Enemy_Stage1_Boss.h"


/**
 * �R���X�g���N�^
 *
 */
CEnemy_Stage1_Boss::CEnemy_Stage1_Boss() :
	m_Texture(),
	m_ShotTexture(),
	m_AttackSlash(),
	m_bEliminated(false),
	m_pEndEffect(),
	m_HPTex(),
	m_FrameTex()
{};

/**
 * �f�X�g���N�^
 *
 */
CEnemy_Stage1_Boss::~CEnemy_Stage1_Boss() {
	Release();
}

bool CEnemy_Stage1_Boss::Load()
{
	if (!m_Texture.Load("Enemy/Stage1Boss/BossAnimation/Boss1_Animation.png"))
		return false;

	if (!m_HPTex.Load("Enemy/Stage1Boss/bosshp.png"))
		return false;

	if (!m_FrameTex.Load("Enemy/Stage1Boss/bossframe.png"))
		return false;

	if (!m_ShotTexture.Load("Enemy/Stage1Boss/boss_zangeki.png"))
		return false;

	for (int i = 0; i < ENEMY_BOSS_SLASH_COUNT; i++)
	{
		m_ShotArray[i].SetTexture(&m_ShotTexture);
	}

	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim[] = {
		{
			"�A�C�h��",
			0,0,320,320,TRUE,
			{{5,0,0}}
		},
		{
			"�ړ�",
			0,0,320,320,TRUE,
			{ { 5,0,0 },{ 5,1,0 },{ 5,2,0 },{ 5,3,0 }, { 5,4,0 },{ 5,5,0 },
			  { 5,6,0 },{ 5,7,0 },{ 5,8,0 },{ 5,9,0 },{ 5,10,0 },{ 5,11,0 }, 
			  { 5,12,0 },{ 5,13,0 },{ 5,14,0 },{ 5,15,0 },{ 5,16,0 },{ 5,17,0 },
			  { 5,18,0 },{ 5,19,0 }, { 5,20,0 },{ 5,21,0 },{ 5,22,0 },{ 5,23,0 },
			  { 5,24,0 },{ 5,25,0 },{ 5,26,0 },{ 5,27,0 }, { 5,28,0 },{ 5,29,0 } }
		},
		{
			"�W�����v",
			0,0,320,320,TRUE,
			{{5,0,3}}
		},
		{
			"�_�b�V���U��",
			0,0,320,320,FALSE,
			{{5,6,4}, {5,7,4}, {5,8,4}, {5,9,4}, {5,10,4}}
		},
		{
			"�W�����v�U��",
			0,0,320,320,FALSE,
			{{5,0,3}}
		},
		{
			"�a���U��",
			0,0,320,320,FALSE,
			{{2,13,2}, {2,14,2}, {2,15,2}, {2,16,2}, {2,17,2}, {2,18,2}}
		},
		{
			"�a���U�����[�V�����I��",
			0,0,320,320,FALSE,
			{{5,19,2}, {5,20,2}, {5,21,2}, {5,22,2}, {5,23,2}, {5,24,2}, {5,25,2}, {5,26,2}, {5,27,2}, {5,28,2}, {5,29,2}, {5,30,2}}
		},
		{
			"���n",
			0,0,320,320,FALSE,
			{{2,1,3}, {2,2,3}, {2,3,3}, {2,4,3}, {2,5,3}, {2,6,3}, {2,7,3}}
		},
		{
			"�a���O���[�V����",
			0,0,320,320,FALSE,
			{{5,0,2}, {5,1,2}, {5,2,2}, {5,3,2}, {5,4,2}, {5,5,2}, {5,6,2}, {5,7,2}, {5,8,2}, {5,9,2}, {5,10,2}, {5,11,2}, {5,12,2}}
		},
		{
			"�_�b�V���U���O���[�V����",
			0,0,320,320,FALSE,
			{{20,0,4},{5,1,4}, {5,2,4}, {5,3,4}, {5,4,4}, {35,5,4}}
		},
		{
			"�_�b�V���U���ヂ�[�V����",
			0,0,320,320,FALSE,
			{{5,11,4}, {5,12,4}, {5,13,4}, {5,14,4}, {5,15,4}, {5,16,4}, {5,17,4}, {5,18,4}, {5,19,4}, {5,20,4}, {5,21,4}}
		},
		{
			"���j�����[�V����",
			0,0,320,320,FALSE,
			{{5,0,5},{5,1,5},{5,2,5},{5,3,5},{5,4,5},{5,5,5},
			{5,6,5},{5,7,5},{5,8,5},{5,9,5},{5,10,5},{5,11,5},
			{5,12,5},{5,13,5},{5,14,5},{5,15,5},{5,16,5},{5,17,5},
			{5,18,5},{5,19,5},{5,20,5},{5,21,5},{5,22,5},{5,23,5},
			{5,24,5},{5,25,5},{5,26,5},{5,27,5},{5,28,5},{5,29,5}}
		}
	};
	m_Motion.Create(anim, MOTION_COUNT);

	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 *
 * ����
 * [in]			px					X���W
 * [in]			py					Y���W
 * [in]			type				�G�^�C�v
 */
void CEnemy_Stage1_Boss::Initialize() {
	this->Load();
	m_Pos.x = ENEMY_DEFAULT_RIGHTPOS;
	m_Pos.y = 896.0f - m_Motion.GetSrcRect().GetHeight();
	m_Move.x = 0.0f;
	m_Move.y = 0.0f;
	m_bReverse = false;
	m_bShow = true;
	m_HP = 100;
	m_MotionWait = ENEMY_MOTION_WAIT;
	m_bIsEnemyPosLeft = false;
	m_bIsOnLift = false;
	m_bJump = false;
	m_bTouchGround = true;
	m_AttackSlash = false;
	m_OldMotionNo = MOTION_Idle;
	m_bDead = false;
	m_bEliminated = false;
	m_DamageWait = 0;

	for (int i = 0; i < ENEMY_BOSS_SLASH_COUNT; i++)
	{
		m_ShotArray[i].Initialize();
	}
	
}

/**
 * �X�V
 *
 */
void CEnemy_Stage1_Boss::Update() {
	for (int i = 0; i < ENEMY_BOSS_SLASH_COUNT; i++)
	{
		m_ShotArray[i].Update();
	}

	if (m_bDead) {
		m_bEliminated = true;
	}

	ReturnWaitStates();

	if (m_DamageWait > 0)
		m_DamageWait--;


	if (m_HP <= 0) {
		m_bDead = true;
	}

	switch (m_Motion.GetMotionNo())
	{
		//�ҋ@���
	case MOTION_Idle:
		if (m_MotionWait <= 0)
		{
			if (m_bIsOnLift)
			{
				//���t�g��ɂ���Ƃ��̏���
				if (!m_bReverse)
				{
					m_Move.x = -ENEMY_ATTACKDASH_SPEED;
					m_Motion.ChangeMotion(MOTION_ATTACK_DASH);
				}
				else
				{
					m_Move.x = ENEMY_ATTACKDASH_SPEED;
					m_Motion.ChangeMotion(MOTION_ATTACK_DASH);
				}
			}
			else
			{
				//���t�g�ɏ���ĂȂ��Ƃ��̏���
				//�v���C���[����������ɂ���Ƃ���60%�̊m���Łu�W�����v�U���v�A�u���t�g��ɃW�����v�v��ԂɈڍs����
				int rand = CUtilities::Random(100);
				//��ԏ�̃��t�g�Ƀv���C���[������Ƃ�60%�̊m���Łu�W�����v�U���v��ԂɈڍs
				if (m_TargetPosY <= PLAYER_Lift_2 && rand < 60)
				{
					if (!m_bReverse)
					{
						m_Move.x = -ENEMY_ATTACKDASH_SPEED;
						m_Move.y = ENEMY_JUMP;
						m_Motion.ChangeMotion(MOTION_ATTACK_JUMP);
					}
					else
					{
						m_Move.x = ENEMY_ATTACKDASH_SPEED;
						m_Move.y = ENEMY_JUMP;
						m_Motion.ChangeMotion(MOTION_ATTACK_JUMP);
					}
				}
				//�^�񒆂̃��t�g�Ƀv���C���[������Ƃ�60%�̊m���Łu���t�g��ɃW�����v�v��ԂɈڍs
				else if (m_TargetPosY <= PLAYER_Lift_1 && rand < 60)
				{
					m_Move.y = ENEMY_JUMP;
					m_bIsOnLift = true;
					m_Motion.ChangeMotion(MOTION_JUMP);
				}
				else
				{
					//�����_���Ń_�b�V���U���A�W�����v�U���A�a���U���A���t�g��ɃW�����v�Ɉڍs
					int rand = CUtilities::Random(4);
					if (rand == 0)
					{
						m_Motion.ChangeMotion(MOTION_ATTACK_DASH_READY);


					}
					else if (rand == 1)
					{
						//�W�����v�U���Ɉڍs
						if (!m_bReverse)
						{
							m_Move.x = -ENEMY_ATTACKDASH_SPEED;
							m_Move.y = ENEMY_JUMP;
							m_Motion.ChangeMotion(MOTION_ATTACK_JUMP);
						}
						else
						{
							m_Move.x = ENEMY_ATTACKDASH_SPEED;
							m_Move.y = ENEMY_JUMP;
							m_Motion.ChangeMotion(MOTION_ATTACK_JUMP);
						}
					}
					else if (rand == 2)
					{
						//�a���U���Ɉڍs
						m_Motion.ChangeMotion(MOTION_ATTACK_SLASH_READY);
					}

					else if (rand == 3)
					{
						//���t�g��ɃW�����v
						m_Move.y = ENEMY_JUMP;
						m_bIsOnLift = true;
						m_Motion.ChangeMotion(MOTION_JUMP);
					}
				}
			}
		}
		else
		{
			m_MotionWait--;
		}

		m_OldMotionNo = MOTION_Idle;
		break;

		//MOTION_MOVE�̏��
	case MOTION_MOVE:

		if (m_OldMotionNo == MOTION_ATTACK_JUMP)
		{
			m_bReverse = !m_bReverse;
		}

		if (!m_bReverse)
		{
			if (m_Pos.x + -ENEMY_MOTION_MOVE >= ENEMY_DEFAULT_RIGHTPOS)
			{
				m_Move.x = -ENEMY_MOTION_MOVE;
			}
			else
			{
				m_Move.x = 0;
				m_MotionWait = ENEMY_MOTION_WAIT;
				m_Motion.ChangeMotion(MOTION_Idle);
			}
		}
		else
		{
			if (m_Pos.x + ENEMY_MOTION_MOVE <= ENEMY_DEFAULT_LEFTPOS)
			{
				m_Move.x = ENEMY_MOTION_MOVE;
			}
			else
			{
				m_Move.x = 0;
				m_MotionWait = ENEMY_MOTION_WAIT;
				m_Motion.ChangeMotion(MOTION_Idle);
			}
		}

		m_OldMotionNo = MOTION_MOVE;
		break;

		//MOTION_JUMP�̏��
	case MOTION_JUMP:
		if (!m_bJump)
		{
			m_Move.x = 0;
			m_Move.y = ENEMY_JUMP;
			m_bTouchGround = false; 
			m_bJump = true;
			for (int j = 0; j < SE_COUNT; j++)
			{
				if (m_pSEManager[j].IsPlaySE())
					continue;
				m_pSEManager[j].SEPlayer(SE_BOSS_JUMP);
				break;
			}
		}

		if (m_bJump && m_bTouchGround)
		{
			m_bJump = false;
			m_Motion.ChangeMotion(MOTION_FALL);
		}
		m_OldMotionNo = MOTION_JUMP;
		break;

		//���n���[�V����
	case MOTION_FALL:
	{
		m_Move.x = 0;
		m_Move.y = 0;
		if (m_Motion.IsEndMotion())
		{
			if (m_OldMotionNo == MOTION_JUMP)
			{
				m_Motion.ChangeMotion(MOTION_ATTACK_DASH_READY);
			}
			else if (m_OldMotionNo == MOTION_ATTACK_JUMP)
			{
				m_bReverse = !m_bReverse;
				m_Motion.ChangeMotion(MOTION_MOVE);
			}
			m_OldMotionNo = MOTION_FALL;
		}
		break;
	}

	case MOTION_ATTACK_DASH_READY:
		if (m_Motion.IsEndMotion())
		{
			//�_�b�V���U���Ɉڍs
			if (!m_bReverse)
			{
				m_Move.x = -ENEMY_ATTACKDASH_SPEED;
				m_Motion.ChangeMotion(MOTION_ATTACK_DASH);
			}
			else
			{
				m_Move.x = ENEMY_ATTACKDASH_SPEED;
				m_Motion.ChangeMotion(MOTION_ATTACK_DASH);
			}
			for (int j = 0; j < SE_COUNT; j++)
			{
				if (m_pSEManager[j].IsPlaySE())
					continue;
				m_pSEManager[j].SEPlayer(SE_BOSS_ATTACK03);
				break;
			}
		}
		break;

		//�_�b�V���U���̏��
	case MOTION_ATTACK_DASH:
		if (!m_bReverse)
		{
			m_bIsOnLift = false;
			m_Move.x = -ENEMY_ATTACKDASH_SPEED;
		}
		else
		{
			m_bIsOnLift = false;
			m_Move.x = ENEMY_ATTACKDASH_SPEED;
		}
		m_OldMotionNo = MOTION_ATTACK_DASH;
		break;

		//�W�����v�U���̏��
	case MOTION_ATTACK_JUMP:
		if (!m_bJump)
		{
			m_Move.y = 1.2f * ENEMY_JUMP;
			if (!m_bReverse)
			{
				m_Move.x = -ENEMY_ATTACKDASH_SPEED * 0.95f;
				//m_bReverse = false;
				m_bJump = true;
			}
			else
			{
				m_Move.x = ENEMY_ATTACKDASH_SPEED * 0.95f;
				//m_bReverse = true;
				m_bJump = true;
			}
			for (int j = 0; j < SE_COUNT; j++)
			{
				if (m_pSEManager[j].IsPlaySE())
					continue;
				m_pSEManager[j].SEPlayer(SE_BOSS_JUMP);
				break;
			}
		}
		m_OldMotionNo = MOTION_ATTACK_JUMP;
		break;

		//�a���U���O�s��
	case MOTION_ATTACK_SLASH_READY:
		m_OldMotionNo = MOTION_ATTACK_SLASH_READY;
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_ATTACK_SLASH_START);
		}
		break;

		//�a���U���̏��
	case MOTION_ATTACK_SLASH_START:
		if (!m_AttackSlash)
		{
			if (!m_bReverse)
			{
				//m_Move.x = -ENEMY_ATTACKSLASH_MOVE;
				m_AttakSlashRect = CRectangle(m_Pos.x - ENEMY_ATTACKSLASH_WIDTH + BOSS1_RECT_WIDTH_DECREASE, m_Pos.y + BOSS1_RECT_HEIGHT_DECREASE, m_Pos.x + BOSS1_RECT_WIDTH_DECREASE, m_Pos.y + m_SrcRect.GetHeight());
				for (int i = 0; i < ENEMY_BOSS_SLASH_COUNT; i++)
				{
					if (m_ShotArray[i].GetShow())
						continue;
					m_ShotArray[i].SetReverse(true);
					m_ShotArray[i].Fire(m_Pos.x, m_Pos.y + 80.0f, -10.0f, 0);
					break;
				}
			}
			else
			{
				//m_Move.x = ENEMY_ATTACKSLASH_MOVE;
				m_AttakSlashRect = CRectangle(m_Pos.x + m_SrcRect.GetWidth() - BOSS1_RECT_WIDTH_DECREASE, m_Pos.y + BOSS1_RECT_HEIGHT_DECREASE, m_Pos.x + m_SrcRect.GetWidth() + ENEMY_ATTACKSLASH_WIDTH - BOSS1_RECT_WIDTH_DECREASE, m_Pos.y + m_SrcRect.GetHeight());
				for (int i = 0; i < ENEMY_BOSS_SLASH_COUNT; i++)
				{
					if (m_ShotArray[i].GetShow())
						continue;
					m_ShotArray[i].SetReverse(false);
					m_ShotArray[i].Fire(m_Pos.x + m_SrcRect.GetWidth(), m_Pos.y + 80.0f, 10.0f, 0);
					break;
				}
			}
			m_AttackSlash = true;
			for (int j = 0; j < SE_COUNT; j++)
			{
				if (m_pSEManager[j].IsPlaySE())
					continue;
				m_pSEManager[j].SEPlayer(SE_BOSS_ATTACK01);
				break;
			}
		}
		//�U�����[�V�����̏I��
		if (m_Motion.IsEndMotion())
		{
			m_AttackSlash = false;
			m_Motion.ChangeMotion(MOTION_ATTACK_SLASH_END);
		}

		m_OldMotionNo = MOTION_ATTACK_SLASH_START;
		break;

		//�[���̏��
	case MOTION_ATTACK_SLASH_END:
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_Idle);
		}
		m_OldMotionNo = MOTION_ATTACK_SLASH_END;
		break;

		//�A�^�b�N�_�b�V���I�����[�V����
	case MOTION_ATTACK_DASH_END:
		m_OldMotionNo = MOTION_ATTACK_DASH_END;
		m_Move.x = 0;
		if (m_Motion.IsEndMotion())
		{
			if (GetReverse())
				SetReverse(false);
			else
				SetReverse(true);

			m_Motion.ChangeMotion(MOTION_MOVE);
		}
		break;
	}
	AbStateMoveDec();
	//�d�͂ɂ�艺�ɏ�����������
	m_Move.y += GRAVITY;
	if (m_Move.y >= 20.0f) { m_Move.y = 20.0f; }

	m_Pos.x += m_Move.x;
	m_Pos.y += m_Move.y;

	/*
	if (m_OldMotionNo == MOTION_ATTACK_SLASH_START)
	{
		m_Move.x = 0;
	}
	*/


	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

/**
 * �X�e�[�W�Ƃ̓�����
 *
 * ����
 * [in]			ox					X���܂��
 * [in]			oy					Y���܂��
 */
void CEnemy_Stage1_Boss::CollisionStage(float ox, float oy) {
	m_Pos.x += ox;
	m_Pos.y += oy;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if (oy < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
	}
	else if (oy > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	if (ox < 0 && m_Move.x > 0)
	{
		m_Move.x *= -1;
		//m_bReverse = true;
	}
	else if (ox > 0 && m_Move.x < 0)
	{
		m_Move.x *= -1;
		//m_bReverse = false;
	}
}

void CEnemy_Stage1_Boss::CollisionWall()
{
	if (GetBossMotionNo() == MOTION_ATTACK_DASH)
	{
		m_Motion.ChangeMotion(MOTION_ATTACK_DASH_END);
	}
}

void CEnemy_Stage1_Boss::Damage(int dmg, bool direction) {

	if (m_HP <= 0)
		return;

	if (m_DamageWait > 0)
		return;

	m_DamageWait = ENEMY_BOSS_ATTACK_WAIT;

	if (direction)
	{
		DeffenceProc(dmg, ENEMY_BOSS_FRONT_DEF);
	}
	else
	{
		DeffenceProc(dmg, ENEMY_BOSS_BACK_DEF);
	}

	if (m_HP <= 0)
	{
		//�����G�t�F�N�g�𔭐�������
		//m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
		for (int j = 0; j < SE_COUNT; j++)
		{
			if (m_pSEManager[j].IsPlaySE()) {
				continue;
			}
			m_pSEManager[j].SEPlayer(SE_ENEMY_DIE);
			break;
		}
		m_Move.x = 0;
		m_OldMotionNo = MOTION_END;
		m_Motion.ChangeMotion(MOTION_END);
	}
	else
	{
		for (int j = 0; j < SE_COUNT; j++)
		{
			if (m_pSEManager[j].IsPlaySE()) {
				continue;
			}
			m_pSEManager[j].SEPlayer((direction) ? SE_BOSS_SHIELD : SE_BOSS_DAMAGE);
			break;
		}
		//�_���[�W�G�t�F�N�g�𔭐�������
		m_pEffectManager->Start(SetStartPos(), (direction) ? EFC_SHIELD : EFC_WEAK);
	}
}

bool CEnemy_Stage1_Boss::isCollisionBossAttack(CRectangle prec)
{
	if (!m_AttackSlash)
		return false;

	if (prec.CollisionRect(m_AttakSlashRect))
	{
		return true;
	}
	
	return false;
}

void CEnemy_Stage1_Boss::DeffenceProc(int dmg,int deff) {
	m_Deffence = deff;

	float def = m_Deffence - dmg;

	if (def < 0) { m_HP += def; }
}
//TODO : AbStateMoveDec
void	CEnemy_Stage1_Boss::AbStateMoveDec() {

}
/**
 * �`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CEnemy_Stage1_Boss::Render(float wx, float wy) {
	for (int i = 0; i < ENEMY_BOSS_SLASH_COUNT; i++)
	{
		m_ShotArray[i].Render(wx, wy);
	}

	//��\��
	if (!m_bShow)
	{
		return;
	}

	//�C���^�[�o��2�t���[�����Ƃɕ`������Ȃ�
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}

	//�`���`
	CRectangle dr = m_SrcRect;
	//���]�t���O��ON�̏ꍇ�`���`�𔽓]������
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}
	//�e�N�X�`���̕`��
	(GetAbStateNo() == STATE_FROST) ? m_Texture.Render(m_Pos.x - wx, m_Pos.y - wy, dr, MOF_XRGB(0, 255, 255)) : m_Texture.Render(m_Pos.x - wx, m_Pos.y - wy, dr);
}

void CEnemy_Stage1_Boss::RenderStatus() {

	if (m_HP <= 0) {
		return;
	}
	CRectangle hprec(0, 0, 822 * (m_HP * 0.01f), 61);


	m_HPTex.Render(g_pGraphics->GetTargetWidth() * 0.55f, g_pGraphics->GetTargetHeight() - 112, hprec);
	m_FrameTex.Render(g_pGraphics->GetTargetWidth() * 0.51f, g_pGraphics->GetTargetHeight() - 128);

}
/**
 * �f�o�b�O�`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CEnemy_Stage1_Boss::RenderDebug(float wx, float wy) {
	//�e�̕`��
	for (int i = 0; i < ENEMY_BOSS_SLASH_COUNT; i++)
	{
		m_ShotArray[i].RenderDebug(wx, wy);
	}

	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 255));

	//PosX,PosY�m�F�p
	CGraphicsUtilities::RenderCircle(m_Pos.x - wx, m_Pos.y - wy, 2, MOF_XRGB(255, 0, 0));
	CGraphicsUtilities::RenderFillRect(GetBossFrontRect(), MOF_XRGB(0, 0, 255));
	//CGraphicsUtilities::RenderCircle(m_TargetPosX - wx, m_TargetPosY - wy, 2, MOF_XRGB(255, 0, 0));
	CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() * 0.5f, 20, " % .0f", (float)m_Motion.GetMotionNo());

	CGraphicsUtilities::RenderFillRect(GetBossSideRect(), MOF_XRGB(255, 255, 0));

	if (m_AttackSlash)
	{
		CGraphicsUtilities::RenderFillRect(m_AttakSlashRect, MOF_XRGB(255, 0, 0));
	}
}

/**
 * ���
 *
 */
void CEnemy_Stage1_Boss::Release(void) {
	m_Motion.Release();
	m_Texture.Release();
	m_ShotTexture.Release();
	m_HPTex.Release();
	m_FrameTex.Release();
}
