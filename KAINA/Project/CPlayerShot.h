#pragma once
#include "Shot_Base.h"

class CPlayerShot : public Shot_Base
{
private:
	int			m_RefCount;
	float		m_MoveX;
	float		m_MoveY;
public:
	CPlayerShot();
	~CPlayerShot() {};
	void Initialize();
	void Update();
	/*
	*����     �F�@

	�������@�F�@�e�̔��ˈʒu�@
	�������@�F�@�e���̍��E�㉺�̕���
	��O�����@�F�@�e�̓���

	*�������e  �F�@���u�Ԃ̏����Z�b�g
	*/
	void Fire(Vector2& pos, int tb, int natuyype);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);

	CRectangle GetRect()
	{
		return CRectangle(m_ShotPos.x,
			m_ShotPos.y,
			m_ShotPos.x + m_pShotTex->GetWidth(),
			m_ShotPos.y + m_pShotTex->GetHeight());
	}

	void SetShotType(int type) { m_ShotType = type; }

	void SetPowerLeft();

	void SetPowerTop();

	void SetPowerRight();

	void SetPowerBottom();

	void SetDirection(int dic);

	//�������ȗ����邽�߂̊֐�
private:
	//������
	void Direction();


	void ShotRemove();
	//�e�̉�ʊO����
	void OutRange();

	void SpeedSave();
};

