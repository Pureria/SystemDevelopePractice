#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include	"EffectManager.h"
#include	"EnemyStateDefine.h"

//�����蔻�茸����
#define		ENEMY_RECTDECREASE		10

//�{�X��{��ʒu
#define		ENEMY_DEFAULT_LEFTPOS			440
#define		ENEMY_DEFAULT_RIGHTPOS			1359

#define		PLAYER_Lift_2					350
#define		PLAYER_Lift_1					606

#define		ENEMY_MOTION_WAIT				60
#define		ENEMY_MOTION_MOVE				5.0f
#define		ENEMY_ATTACKDASH_SPEED			10.0f
#define		ENEMY_JUMP						-13.0f
#define		ENEMY_ATTACKSLASH_WIDTH			150.0f
#define		ENEMY_ATTACKSLASH_MOVE			90

class CEnemy_Stage1_Boss {
private:
	CTexture				m_Texture;
	CSpriteMotionController	m_Motion;
	float					m_PosX;
	float					m_PosY;
	float					m_MoveX;
	float					m_MoveY;
	bool					m_bShow;
	//m_bRevese �@ true : ������	false : �E����
	bool					m_bReverse;
	bool					m_bIsEnemyPosLeft;
	bool					m_bIsOnLift;
	bool					m_bJump;
	bool					m_bTouchGround;
	bool					m_AttackSlash;

	CRectangle				m_SrcRect;
	CRectangle				m_AttakSlashRect;


	//�{�X��HP
	int						m_HP;
	int						m_MotionWait;
	int						m_OldMotionNo;

	CEffectManager* m_pEffectManager;

	//���[�V������ޒ�`
	enum tag_MOTION {
		MOTION_Idle,
		MOTION_MOVE,
		MOTION_JUMP,
		MOTION_ATTACK_DASH,
		MOTION_ATTACK_JUMP,
		MOTION_ATTACK_SLASH_START,
		MOTION_ATTACK_SLASH_END,


		MOTION_COUNT,
	};

	float					m_TargetPosX;
	float					m_TargetPosY;



public:
	CEnemy_Stage1_Boss();
	~CEnemy_Stage1_Boss();
	bool Load();
	void Initialize();
	void Update();
	void CollisionStage(float ox, float oy);
	void CollisionWall ();
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release(void);

	bool GetShow(void) { return m_bShow; }
	CRectangle GetRect() {
		return CRectangle(m_PosX + ENEMY_RECTDECREASE, m_PosY + ENEMY_RECTDECREASE, m_PosX + m_SrcRect.GetWidth() - ENEMY_RECTDECREASE, m_PosY + m_SrcRect.GetHeight());
	}

	//�{�X�̃_���[�W����
	//���� : dmg = �_���[�W : direction = ���ɓ��������ꍇtrue�A������Ȃ������ꍇfalse
	void Damage(int dmg, bool direction);
	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }

	//�v���C���[�̍��W�Z�b�g
	void SetTargetPos(float tx, float ty) { m_TargetPosX = tx; m_TargetPosY = ty; }

	int GetBossMotionNo() { return m_Motion.GetMotionNo(); }

	CRectangle GetBossBottomRect() { return CRectangle(m_SrcRect.Left, m_SrcRect.Bottom - 1, m_SrcRect.Right, m_SrcRect.Bottom); }
	CRectangle GetBossSideRect() 
	{
		CRectangle hr = GetRect();
		return CRectangle(hr.Left - ENEMY_RECTDECREASE, (hr.Top + 80), hr.Right + ENEMY_RECTDECREASE, (hr.Bottom - 80));
	}
	//�{�X�̃t�����gRect
	CRectangle GetBossFrontRect()
	{
		if (m_bReverse)
		{
			return CRectangle(m_PosX + ENEMY_RECTDECREASE, m_PosY + ENEMY_RECTDECREASE, m_PosX + ENEMY_BOSS_FRONTDEF_DIRECTION, m_PosY + m_SrcRect.GetHeight());
		}
		else
		{
			return CRectangle((m_PosX + m_SrcRect.GetWidth() - ENEMY_BOSS_FRONTDEF_DIRECTION), m_PosY + ENEMY_RECTDECREASE, m_PosX + m_SrcRect.GetWidth() - ENEMY_RECTDECREASE, m_PosY + m_SrcRect.GetHeight());
		}
	}

	void SetMotionMove() { m_Motion.ChangeMotion(MOTION_MOVE); }
	void SetReverse(bool reverse) { m_bReverse = reverse; }
	bool GetReverse() { return m_bReverse; }
	bool IsJump()
	{
		if (m_MoveY <= 0)
			return true;
		else
			return false;
	}
	void SetTouchGround(bool flg) { m_bTouchGround = flg; }
	void SetJumpAttackEnd()
	{
		m_bJump = false;
		m_Motion.ChangeMotion(MOTION_MOVE);
	}

	//�{�X�X���b�V���U���̔���
	bool isCollisionBossAttack(CRectangle prec);
};

