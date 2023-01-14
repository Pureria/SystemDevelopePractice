#pragma once
#include "Shot_Base.h"

class CPlayerShot : public Shot_Base
{
private:
	int			m_RefCount;
	int			m_ThroughCount;
	float		m_MoveX;
	float		m_MoveY;
public:
	CPlayerShot();
	~CPlayerShot() {};

	void Initialize()								override;
	void Update()									override;
	void Fire(Vector2& pos, int tb, int natuyype)	override;
	void Render(float wx, float wy)					override;
	void RenderDebug(float wx, float wy)			override;

	inline CRectangle GetRect()						override
	{
		return CRectangle(m_ShotPos.x,
			m_ShotPos.y,
			m_ShotPos.x + m_pShotTex->GetWidth(),
			m_ShotPos.y + m_pShotTex->GetHeight());
	}

	int GetThroughCount()								{		return m_ThroughCount;	}
	//�e�N�X�`���̔z��
	inline void		SetHealTexture(CTexture* pt)		{		m_pShotTex = pt;		}
	inline void		SetHeavyTexture(CTexture* pt)		{		m_phShotTex = pt;		}

	void SetPowerLeft();

	void SetPowerTop();

	void SetPowerRight();

	void SetPowerBottom();

	void SetDirection(int dic);

	void SetThroughCount();

	void SetRectCount()										{		m_ThroughCount++;	}

	//�������ȗ����邽�߂̊֐�
private:
	//������
	void Direction();


	void ShotRemove();
	//�e�̉�ʊO����
	void OutRange();

	void SpeedSave();
};

