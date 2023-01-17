#pragma once
#include "Mof.h"
#include "SoundDefine.h"

class CSE_Manager
{
private:
	CSoundBuffer m_Sound[SE_CNT][SE_TYPE];
	int			m_NowSetSE;
	int			m_Volume;
public:

	bool Load(void);
	void SEPlayer(int request);
	void Release(void);

	bool IsPlaySE();

	void StopSE();
	int  GetNowSetSE() { return m_NowSetSE; }

	void TitleLoad();
	void SelectLoad();
	void GameLoad();
	void BossLoad();
	void PlayerLoad();
	void StageLoad();
	void EnemyLoad();
};

