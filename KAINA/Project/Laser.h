#pragma once
#include "Shot_Base.h"

class Laser : public Shot_Base
{
private:
	

	//���[�U�[�̓����������W�̕ۊ�
	Vector2				m_LaserHitPos;

	//���[�U�[�������̕ϐ�
	float				m_LaserDecrealse;
	//���[�U�[���~�܂鎞��
	float				m_StopCount;

	//���[�U�[�̊g���͈͂̕ϐ�
	int					m_LaserRange;

	int					m_HitRange;

	bool				m_bRev;

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
	void SetFireTexture(CTexture* pt)								{		m_pShotTex = pt;				}
	void SetFrostTexture(CTexture* pt)								{		m_phShotTex = pt; }
	//�X�e�[�W�ɓ��������ꍇ�@true	: false
	void SetWallHitLaser(bool flg)									{		m_bHitWall = flg;				}
	//Get�֐�
public:
	CRectangle GetRect();
	CRectangle GetSearchRect();

	bool GetWallHit()												{		return m_bHitWall;				}

	void SetMapChipPos(Vector2& pos)								{		m_LaserHitPos = pos;			}

	void SetUp();

	//�������ȗ����邽�߂̊֐�
private:

	//Laser�̏���
	void ShotLaser();

	//��������
	void OutRange();

	bool GetRev();
};

