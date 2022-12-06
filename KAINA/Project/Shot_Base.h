#pragma once
#include "Mof.h"
#include "GameDefine.h"

class Shot_Base
{
protected:
	//�e�̃e�N�X�`��
	CTexture*		m_pShotTex;
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

//���z�֐��܂Ƃ�
public:
	Shot_Base() : m_pShotTex(), m_ShotPos(0, 0), m_bShow(false), m_bHitWall(false), m_ShotType(0), m_DrcType(0),m_NatuType(0) {};
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
	void		SetTexture(CTexture* pt)	{	 m_pShotTex = pt;	}
	//�X�e�[�W�ɓ��������ꍇ�@true	: false
	void		SetWallHitLaser(bool flg) { m_bHitWall = flg; }
	//�`�悷�邩�ǂ���
	void		SetShow(bool bs)			{	 m_bShow	= bs;	}
//Get�֐�	
public:
	//�e�̎��
	int			GetType()					{	return m_ShotType;	}
	//������
	int			GetDirec()					{	return m_DrcType;	}
	//�e�̓���
	int			GetNatu()					{	return m_NatuType;	}
	//�`�悳��Ă��邩�ǂ���
	bool		GetShow()					{	return m_bShow;		}
//Is�֐�
public:
	bool		IsLazer()					{	return m_ShotType == LASER; }

	bool		IsHitWall()					{	return m_bHitWall; }
};

