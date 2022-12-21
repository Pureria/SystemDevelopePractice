#pragma once

#include	"EnemyShot.h"
#include	"CEnemyBase_Shot.h"

//�����蔻�茸����
#define			ENEMY_RECTDECREALSE		10

class CEnemy_2 : public CEnemyBase_Shot{
private:
	//fallFlg : TRUE �������� : FALSE �������Ȃ�
	bool					m_bFallFlg;
	//ShotTarget : TRUE �e�̋O�����܂�����	FALSE : �e�̋O�����v���C���[�Ɍ�������
	bool					m_bShotTarget;
	//KnockBack : TRUE �m�b�N�o�b�N�� : FALSE : �m�b�N�o�b�N����
	bool					m_bKnockback;


	float					m_TargetPosX;
	float					m_TargetPosY;


	//���[�V������ޒ�`
	enum tag_Motion {
		MOTION_MOVE,
		MOTION_DAMAGE,
		
		MOTION_COUNT,
	};
public:
	CEnemy_2();
	~CEnemy_2();

	void Initialize(float px, float py, int type);
	void Update(float wx);
	void CollisionStage(float ox, float oy);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release();
	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }

	void SetTexture(CTexture* pt, CTexture* st);

	bool		GetShow() { return m_bShow; }

	CRectangle  GetRect() { return CRectangle(m_Pos.x + ENEMY_RECTDECREALSE, m_Pos.y + ENEMY_RECTDECREALSE, m_Pos.x + m_SrcRect.GetWidth() - ENEMY_RECTDECREALSE, m_Pos.y + m_SrcRect.GetHeight()); }
	Vector2		GetPos() { return m_Pos; }

	//�v���C���[�̍��W�Z�b�g
	void		SetTargetPos(float tx, float ty) { m_TargetPosX = tx; m_TargetPosY = ty; }
	bool		ShotTarget(int i);

	//�e��Show��Ԃ�
	bool		GetShotShow(int i) { return m_ShotArray[i].GetShow(); }
	//�e��Rect��Ԃ�
	CRectangle	GetShotRect(int i) { return m_ShotArray[i].GetRect(); }
	//�e�̃|�W�V������Ԃ�
	Vector2		GetShotPos(int i) { return m_ShotArray[i].GetPos(); }

	//�R����pRect��Ԃ�
	CRectangle	GetLedgeCheckRect();
	void		Flip() { m_bReverse = !m_bReverse; }
	bool		GetFallFlg() { return m_bFallFlg; }

	void		SetFallFlg(bool flg) { m_bFallFlg = flg; }

	void Damage(float dmg) override;
	void KnockBack() override;
};

