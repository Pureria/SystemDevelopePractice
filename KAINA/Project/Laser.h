#pragma once
#include "Shot_Base.h"

class Laser : public Shot_Base
{
private:
	//レーザーの当たった座標の保管
	Vector2			m_LazerHitPos;

	//float			m_FmTime;

	//レーザーの拡張範囲
	int				m_LaserRange;

public:
	Laser();
	~Laser() {};
	void Initialize();
	void Update();
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	//Set関数
public:
	//発射する情報をセット
	void Fire(Vector2& pos, int tb, int natuyype);
	void SetTexture(CTexture* pt) { m_pShotTex = pt; }
	void SetShow(bool bs) { m_bShow = bs; }
	//ステージに当たった場合　true	: false
	void SetWallHitLaser() { m_bHitWall = true; }
	//当たった座標をセット
	void DirecPosSet();
	//Get関数
public:
	CRectangle GetRect();

	CRectangle GetFireRect();

	//処理を省略するための関数
private:
	//FPSの速度処理
	float FpsSpd();

	//Lazerの処理
	void ShotLaser();

	//消去処理
	void OutRange();
};

