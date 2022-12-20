#pragma once
#include "Shot_Base.h"

class Laser : public Shot_Base
{
private:
	//���[�U�[�̓����������W�̕ۊ�
	Vector2			m_LaserHitPos;

	//float			m_FmTime;

	//���[�U�[�̊g���͈�
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
	void Fire(Vector2& pos, int tb, int natuyype);
	void SetTexture(CTexture* pt) { m_pShotTex = pt; }
	void SetShow(bool bs) { m_bShow = bs; }
	//�X�e�[�W�ɓ��������ꍇ�@true	: false
	void SetWallHitLaser() { m_bHitWall = true; }
	//�����������W���Z�b�g
	void DirecPosSet();
	//Get�֐�
public:
	CRectangle GetRect();

	CRectangle* GetFireRect();

	//CRectangle GetSlopeRect();

	//�������ȗ����邽�߂̊֐�
private:

	//Laser�̏���
	void ShotLaser();

	//��������
	void OutRange();
};

