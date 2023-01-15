#pragma once
#include "Shot_Base.h"

class Laser : public Shot_Base
{
private:
	//���[�U�[�̓����������W�̕ۊ�
	Vector2			m_LaserHitPos;

	//���[�U�[�������̕ϐ�
	float			m_LaserDecrealse;
	//���[�U�[���~�܂鎞��
	float			m_StopCount;

	//���[�U�[�̊g���͈͂̕ϐ�
	int				m_LaserRange;

	CRectangle		m_FireRec[LASER_FIRE_COUNT];


public:
	Laser();
	~Laser() {};
	void Initialize();
	void Update();
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	//Set�֐�
public:
	//���˂�������Z�b�g
	void Fire(Vector2& pos, int tb, int natuyype, int type);
	void SetTexture(CTexture* pt)								{		m_pShotTex = pt;				}
	//�X�e�[�W�ɓ��������ꍇ�@true	: false
	void SetWallHitLaser(bool flg)								{		m_bHitWall = flg;				}
	void DirecPosSet();
	//Get�֐�
public:
	CRectangle GetRect();

	CRectangle* GetFireRect();


	bool GetWallHit()											{		return m_bHitWall;				}

	//�������ȗ����邽�߂̊֐�
private:

	//Laser�̏���
	void ShotLaser();

	//��������
	void OutRange();
};

