#pragma once
#include "Shot_Base.h"

class CPlayerShot : public Shot_Base
{
private:
	int			m_RefCount;
	int			m_ThroughCount;
	float		m_MoveX;
	float		m_MoveY;
	float		m_Time;
public:
	CPlayerShot();
	~CPlayerShot() {};

	void Initialize();
	void Update();
	void Fire(Vector2& pos, int tb, int natuyype, int type);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);

	inline CRectangle GetRect()
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

	void ShotTime();

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

