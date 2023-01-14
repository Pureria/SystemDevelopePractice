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
	//テクスチャの配列
	inline void		SetHealTexture(CTexture* pt)		{		m_pShotTex = pt;		}
	inline void		SetHeavyTexture(CTexture* pt)		{		m_phShotTex = pt;		}

	void SetPowerLeft();

	void SetPowerTop();

	void SetPowerRight();

	void SetPowerBottom();

	void SetDirection(int dic);

	void SetThroughCount();

	void SetRectCount()										{		m_ThroughCount++;	}

	//処理を省略するための関数
private:
	//撃つ方向
	void Direction();


	void ShotRemove();
	//弾の画面外処理
	void OutRange();

	void SpeedSave();
};

