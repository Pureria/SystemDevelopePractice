#include "Enemy_Stage1_Boss.h"
#include	"Enemy_Stage1_Boss.h"


/**
 * �R���X�g���N�^
 *
 */
CEnemy_Stage1_Boss::CEnemy_Stage1_Boss() :
	m_Texture(),
	m_Motion(),
	m_PosX(0.0f),
	m_PosY(0.0f),
	m_MoveX(0.0f),
	m_MoveY(0.0f),
	m_bShow(true),
	m_bReverse(false),
	m_SrcRect(),
	m_AttackSlash(){
}

/**
 * �f�X�g���N�^
 *
 */
CEnemy_Stage1_Boss::~CEnemy_Stage1_Boss() {
	Release();
}

bool CEnemy_Stage1_Boss::Load()
{
	if (!m_Texture.Load("Enemy/Stage1Boss/BossTestAnimation/boss.png"))
		return false;

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
			0,0,320,320,FALSE,
			{{5,0,0}}
		},
		{
			"�_�b�V���U��",
			0,0,240,256,FALSE,
			{{5,0,0}}
		},
		{
			"�W�����v�U��",
			0,0,320,320,FALSE,
			{{5,0,0}}
		},
		{
			"�a���U��",
			0,0,320,320,FALSE,
			{{60,0,0}}
		},
		{
			"�[�����[�V����",
			0,0,320,320,FALSE,
			{{60,0,0}}
		},
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
	m_PosX = ENEMY_DEFAULT_RIGHTPOS;
	m_PosY = 896 - m_Texture.GetHeight();
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bReverse = false;
	m_bShow = true;
	m_HP = 10;
	m_MotionWait = ENEMY_MOTION_WAIT;
	m_bIsEnemyPosLeft = false;
	m_bIsOnLift = false;
	m_bJump = false;
	m_bTouchGround = true;
	m_AttackSlash = false;
	m_OldMotionNo = MOTION_Idle;
}

/**
 * �X�V
 *
 */
void CEnemy_Stage1_Boss::Update() {
	//��\��
	if (!m_bShow)
	{
		return;
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
					m_MoveX = -ENEMY_ATTACKDASH_SPEED;
					m_Motion.ChangeMotion(MOTION_ATTACK_DASH);
				}
				else
				{
					m_MoveX = ENEMY_ATTACKDASH_SPEED;
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
						m_MoveX = -ENEMY_ATTACKDASH_SPEED;
						m_MoveY = ENEMY_JUMP;
						m_Motion.ChangeMotion(MOTION_ATTACK_JUMP);
					}
					else
					{
						m_MoveX = ENEMY_ATTACKDASH_SPEED;
						m_MoveY = ENEMY_JUMP;
						m_Motion.ChangeMotion(MOTION_ATTACK_JUMP);
					}
				}
				//�^�񒆂̃��t�g�Ƀv���C���[������Ƃ�60%�̊m���Łu���t�g��ɃW�����v�v��ԂɈڍs
				else if (m_TargetPosY <= PLAYER_Lift_1 && rand < 60)
				{
					m_MoveY = ENEMY_JUMP;
					m_bIsOnLift = true;
					m_Motion.ChangeMotion(MOTION_JUMP);
				}
				else
				{
					//�����_���Ń_�b�V���U���A�W�����v�U���A�a���U���A���t�g��ɃW�����v�Ɉڍs
					int rand = CUtilities::Random(4);
					if (rand == 0)
					{
						//�_�b�V���U���Ɉڍs
						if (!m_bReverse)
						{
							m_MoveX = -ENEMY_ATTACKDASH_SPEED;
							m_Motion.ChangeMotion(MOTION_ATTACK_DASH);
						}
						else
						{
							m_MoveX = ENEMY_ATTACKDASH_SPEED;
							m_Motion.ChangeMotion(MOTION_ATTACK_DASH);
						}
						
						
					}
					else if (rand == 1)
					{
						//�W�����v�U���Ɉڍs
						if (!m_bReverse)
						{
							m_MoveX = -ENEMY_ATTACKDASH_SPEED;
							m_MoveY = ENEMY_JUMP;
							m_Motion.ChangeMotion(MOTION_ATTACK_JUMP);
						}
						else
						{
							m_MoveX = ENEMY_ATTACKDASH_SPEED;
							m_MoveY = ENEMY_JUMP;
							m_Motion.ChangeMotion(MOTION_ATTACK_JUMP);
						}
					}
					else if (rand == 2)
					{
						//�a���U���Ɉڍs
						m_Motion.ChangeMotion(MOTION_ATTACK_SLASH_START);
					}

					else if (rand == 3)
					{
						//���t�g��ɃW�����v
						m_MoveY = ENEMY_JUMP;
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
			if (m_PosX + -ENEMY_MOTION_MOVE >= ENEMY_DEFAULT_RIGHTPOS)
			{
				m_MoveX = -ENEMY_MOTION_MOVE;
			}
			else
			{
				m_MoveX = 0;
				m_MotionWait = ENEMY_MOTION_WAIT;
				m_Motion.ChangeMotion(MOTION_Idle);
			}
		}
		else
		{
			if (m_PosX + ENEMY_MOTION_MOVE <= ENEMY_DEFAULT_LEFTPOS)
			{
				m_MoveX = ENEMY_MOTION_MOVE;
			}
			else
			{
				m_MoveX = 0;
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
			m_MoveX - 0;
			m_MoveY = ENEMY_JUMP;
			m_bTouchGround = false;
			m_bJump = true;
		}

		if (m_bJump && m_bTouchGround)
		{
			m_bJump = false;
			m_Motion.ChangeMotion(MOTION_ATTACK_DASH);
		}
		m_OldMotionNo = MOTION_JUMP;
		break;

		//�_�b�V���U���̏��
	case MOTION_ATTACK_DASH:
		if (!m_bReverse)
		{
			m_bIsOnLift = false;
			m_MoveX = -ENEMY_ATTACKDASH_SPEED;
		}
		else
		{
			m_bIsOnLift = false;
			m_MoveX = ENEMY_ATTACKDASH_SPEED;
		}
		m_OldMotionNo = MOTION_ATTACK_DASH;
		break;

		//�W�����v�U���̏��
	case MOTION_ATTACK_JUMP:
		if (!m_bJump)
		{
			m_MoveY = 1.2f * ENEMY_JUMP;
			if (!m_bReverse)
			{
				m_MoveX = -ENEMY_ATTACKDASH_SPEED * 0.95f;
				//m_bReverse = false;
				m_bJump = true;
			}
			else
			{
				m_MoveX = ENEMY_ATTACKDASH_SPEED * 0.95f;
				//m_bReverse = true;
				m_bJump = true;
			}
		}
		m_OldMotionNo = MOTION_ATTACK_JUMP;
		break;

		//�a���U���̏��
	case MOTION_ATTACK_SLASH_START:
		if (!m_AttackSlash)
		{
			if (!m_bReverse)
			{
				//m_MoveX = -ENEMY_ATTACKSLASH_MOVE;
				m_AttakSlashRect = CRectangle(m_PosX - ENEMY_ATTACKSLASH_WIDTH + BOSS1_RECT_WIDTH_DECREASE, m_PosY, m_PosX + BOSS1_RECT_WIDTH_DECREASE, m_PosY + m_SrcRect.GetHeight());
			}
			else
			{
				//m_MoveX = ENEMY_ATTACKSLASH_MOVE;
				m_AttakSlashRect = CRectangle(m_PosX + m_SrcRect.GetWidth() - BOSS1_RECT_WIDTH_DECREASE, m_PosY, m_PosX + m_SrcRect.GetWidth() + ENEMY_ATTACKSLASH_WIDTH - BOSS1_RECT_WIDTH_DECREASE, m_PosY + m_SrcRect.GetHeight());
			}
			m_AttackSlash = true;
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
	}

	//�d�͂ɂ�艺�ɏ�����������
m_MoveY += GRAVITY;
if (m_MoveY >= 20.0f) { m_MoveY = 20.0f; }

m_PosX += m_MoveX;
m_PosY += m_MoveY;

/*
if (m_OldMotionNo == MOTION_ATTACK_SLASH_START)
{
	m_MoveX = 0;
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
	m_PosX += ox;
	m_PosY += oy;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if (oy < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
	}
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	if (ox < 0 && m_MoveX > 0)
	{
		m_MoveX *= -1;
		//m_bReverse = true;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX *= -1;
		//m_bReverse = false;
	}
}

void CEnemy_Stage1_Boss::CollisionWall()
{
	if (GetBossMotionNo() == MOTION_ATTACK_DASH)
	{
		if (GetReverse())
			SetReverse(false);
		else
			SetReverse(true);
		SetMotionMove();
	}
}

void CEnemy_Stage1_Boss::Damage(int dmg, bool direction) {


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
		m_bShow = false;
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

/**
 * �`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CEnemy_Stage1_Boss::Render(float wx, float wy) {
	//��\��
	if (!m_bShow)
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
	m_Texture.Render(m_PosX - wx, m_PosY - wy, dr);
}

/**
 * �f�o�b�O�`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CEnemy_Stage1_Boss::RenderDebug(float wx, float wy) {
	//��\��
	if (!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 255));

	//PosX,PosY�m�F�p
	CGraphicsUtilities::RenderCircle(m_PosX - wx, m_PosY - wy, 2, MOF_XRGB(255, 0, 0));
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
}
