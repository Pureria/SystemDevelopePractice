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

	void Initialize();
	void Update();

	void Fire(Vector2& pos, int tb, int natuyype) override;
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

	//処理を省略するための関数
private:
	//撃つ方向
	void Direction();


	void ShotRemove();
	//弾の画面外処理
	void OutRange();

	void SpeedSave();
};

