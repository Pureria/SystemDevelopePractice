#pragma once
#include "CEnemy_Base.h"
#include "EnemyShot.h"

class CEnemyBase_Shot : public CEnemy_Base
{
protected:
	//弾用変数
	CEnemyShot				m_ShotArray[ENEMY_SHOT_COUNT];
	int						m_ShotWait;

public:
	CEnemyBase_Shot() : m_ShotArray(),m_ShotWait(0) {};
	virtual ~CEnemyBase_Shot() {};
	//弾のShowを返す
	virtual bool		ShotArrayBool(int i) { return m_ShotArray[i].GetShow(); }
	//弾のRectangleを返す
	virtual CRectangle	ShotArrayRect(int i) { return m_ShotArray[i].GetRect(); }
	//弾のShowをセットする
	virtual void		SetShotShow(bool flg, int i) { m_ShotArray[i].SetShow(flg); }

};

