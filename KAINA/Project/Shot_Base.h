#pragma once
#include "Mof.h"
#include "GameDefine.h"

class Shot_Base
{
protected:
	//�e�̃e�N�X�`��
	CTexture*		m_pShotTex;

	CTexture*		m_phShotTex;

	//�e�̈ʒu
	Vector2         m_ShotPos;
	
	//�e�̕`��̐^�U�l
	bool			m_bShow;
	//�ǂɓ����������ǂ���
	bool			m_bHitWall;
	//�e�̎��
	int				m_ShotType;
	//�e�̕���
	int				m_DrcType;
	//�e�̓���
	int				m_NatuType;

	float			m_ScrollX, m_ScrollY;

//���z�֐��܂Ƃ�
public:
	Shot_Base() : m_pShotTex(), m_phShotTex(), m_ShotPos(0, 0), m_bShow(false), m_bHitWall(false), m_ShotType(NORMAL), m_DrcType(RIGHT), m_NatuType(HEAL), m_ScrollX(0), m_ScrollY(0) {};
	virtual void Initialize()								= 0;
	virtual void Update()									= 0;
	virtual void Render(float wx, float wy)					= 0;
	virtual void RenderDebug(float wx, float wy)			= 0;
	/*
	*����     �F�@

	�������@�F�@�e�̔��ˈʒu�@
	�������@�F�@�e���̍��E�㉺�̕���
	��O�����@�F�@�e�̓���

	*�������e  �F�@���u�Ԃ̏����Z�b�g
	*/
	virtual void Fire(Vector2& pos, int tb, int natuyype)	= 0;
	virtual CRectangle GetRect()							= 0;
//Set�֐�
public:
	//�e�N�X�`���̔z��
	void		SetHealTexture(CTexture* pt)		{		m_pShotTex = pt;				}
	void		SetHeavyTexture(CTexture* pt)		{		m_phShotTex = pt;				}
	//�`�悷�邩�ǂ���
	void		SetShow(bool bs)					{		m_bShow	= bs;					}
//Get�֐�	
public:
	//�e�̎��
	int			GetType()							{		return m_ShotType;				}
	//������
	int			GetDirec()							{		return m_DrcType;				}
	//�e�̓���
	int			GetNatu()							{		return m_NatuType;				}
	//�`�悳��Ă��邩�ǂ���
	bool		GetShow()							{		return m_bShow;					}
//Is�֐�
public:
	bool		IsLazer()							{		return m_ShotType == LASER;		}

	bool		IsHitWall()							{		return m_bHitWall;				}

	void		SetScroll(float wx, float wy)		{		m_ScrollX = wx; m_ScrollY = wy; }

	void SetBullet(int type, int drc, int natu)		{		m_ShotType = type; m_DrcType = drc; m_NatuType = natu; }
};

