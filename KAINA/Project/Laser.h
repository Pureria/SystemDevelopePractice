#pragma once
#include "Shot_Base.h"

class Laser : public Shot_Base
{
private:
	

	//レーザーの当たった座標の保管
	Vector2				m_LaserHitPos;

	//レーザー減衰幅の変数
	float				m_LaserDecrealse;
	//レーザーが止まる時間
	float				m_StopCount;

	//レーザーの拡張範囲の変数
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
	//Set関数
public:
	//発射する情報をセット
	void Fire(Vector2& pos, int tb, int natuyype, int type);
	void SetFireTexture(CTexture* pt)								{		m_pShotTex = pt;				}
	void SetFrostTexture(CTexture* pt)								{		m_phShotTex = pt;				}
	void SetFireLaserUpDownTexture(CTexture* pt)					{ m_pFireLaserUpDownTexture = pt;		}
	void SetFrostLaserUpDownTexture(CTexture* pt)					{		m_pFrostLaserUpDownTexture = pt;}
	//ステージに当たった場合　true	: false
	void SetWallHitLaser(bool flg)									{		m_bHitWall = flg;				}
	//Get関数
public:
	CRectangle GetRect();
	//CRectangle GetSearchRect();

	bool GetWallHit()												{		return m_bHitWall;				}

	void SetMapChipPos(Vector2& pos)								{		m_LaserHitPos = pos;			}

	void SetUp();

	int	GetDecrealse()												{		return m_LaserDecrealse;		}

	//処理を省略するための関数
private:

	//Laserの処理
	void ShotLaser();

	//消去処理
	void OutRange();

	bool GetRev();
};

