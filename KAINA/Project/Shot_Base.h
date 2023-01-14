#pragma once
#include "Mof.h"
#include "GameDefine.h"
#include "ShotDefine.h"

class Shot_Base
{
protected:
	//弾のテクスチャ
	CTexture*		m_pShotTex;

	CTexture*		m_phShotTex;

	//弾の位置
	Vector2         m_ShotPos;
	
	//弾の描画の真偽値
	bool			m_bShow;
	//壁に当たったかどうか
	bool			m_bHitWall;
	//弾の方向
	int				m_DrcType;
	//弾の特性
	int				m_NatuType;

//仮想関数まとめ
public:
	Shot_Base() : m_pShotTex(), m_phShotTex(), m_ShotPos(0, 0), m_bShow(false), m_bHitWall(false), m_DrcType(RIGHT), m_NatuType(HEAL) {};
	virtual void Initialize()										= 0;
	virtual void Update()											= 0;
	virtual void Render(float wx, float wy)							= 0;
	virtual void RenderDebug(float wx, float wy)					= 0;
	/*
	*引数     ：　

	第一引数　：　弾の発射位置　
	第二引数　：　銃口の左右上下の方向
	第三引数　：　弾の特性

	*処理内容  ：　撃つ瞬間の情報をセット
	*/
	virtual void Fire(Vector2& pos, int tb, int natuyype)			= 0;
	virtual CRectangle GetRect()									= 0;
//Set関数
public:
	//描画するかどうか
	inline void		SetShow(bool bs)				{		m_bShow	= bs;					}
//Get関数	
public:
	//撃つ方向
	inline int		GetDirec()						{		return m_DrcType;				}
	//弾の特性
	inline int		GetNatu()						{		return m_NatuType;				}
	//描画されているかどうか
	inline bool		GetShow()						{		return m_bShow;					}
//Is関数
public:

};

