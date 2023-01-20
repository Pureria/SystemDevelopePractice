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

	CSpriteMotionController m_Motion;
	CRectangle			m_SrcRect;

	CTexture*			m_pFireLaserUpDownTexture;
	CTexture*			m_pFrostLaserUpDownTexture;

public:
	Laser();
	~Laser() {};
	void Initialize();
	void Update();
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release();
	//Set�֐�
public:
	//���˂�������Z�b�g
	void Fire(Vector2& pos, int tb, int natuyype, int type);
	void SetFireTexture(CTexture* pt)								{		m_pShotTex = pt;				}
	void SetFrostTexture(CTexture* pt)								{		m_phShotTex = pt;				}
	void SetFireLaserUpDownTexture(CTexture* pt)					{ m_pFireLaserUpDownTexture = pt;		}
	void SetFrostLaserUpDownTexture(CTexture* pt)					{		m_pFrostLaserUpDownTexture = pt;}
	//�X�e�[�W�ɓ��������ꍇ�@true	: false
	void SetWallHitLaser(bool flg)									{		m_bHitWall = flg;				}
	//Get�֐�
public:
	CRectangle GetRect();
	//CRectangle GetSearchRect();

	bool GetWallHit()												{		return m_bHitWall;				}

	void SetMapChipPos(Vector2& pos)								{		m_LaserHitPos = pos;			}

	void SetUp();

	int	GetDecrealse()												{		return m_LaserDecrealse;		}

	//�������ȗ����邽�߂̊֐�
private:

	//Laser�̏���
	void ShotLaser();

	//��������
	void OutRange();

	bool GetRev();
};

