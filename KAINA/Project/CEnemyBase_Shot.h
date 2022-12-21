#pragma once
#include "CEnemy_Base.h"
#include "EnemyShot.h"

class CEnemyBase_Shot : public CEnemy_Base
{
protected:
	//’e—p•Ï”
	CEnemyShot				m_ShotArray[ENEMY_SHOT_COUNT];
	int						m_ShotWait;

public:
	CEnemyBase_Shot() : m_ShotArray(),m_ShotWait(0) {};
	virtual ~CEnemyBase_Shot() {};
	//’e‚ÌShow‚ğ•Ô‚·
	bool	   ShotArrayBool(int i) { return m_ShotArray[i].GetShow(); }
	//’e‚ÌShowERectangle‚ğ•Ô‚·
	CRectangle ShotArrayRect(int i) { return m_ShotArray[i].GetRect(); }
	//’e‚ÌShow‚ğƒZƒbƒg‚·‚é
	void	   SetShotShow(bool flg, int i) { m_ShotArray[i].SetShow(flg); }

};

