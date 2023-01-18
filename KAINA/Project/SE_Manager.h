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
	CSE_Manager();
	~CSE_Manager() { Release(); }
	bool Load(void);
	void SEPlayer(int request);

	void StopSE();
	int  GetNowSetSE() { return m_NowSetSE; }

	void TitleLoad();
	void SelectLoad();
	void GameLoad();
	void BossLoad();
	void PlayerLoad();
	void StageLoad();
	void Enemy1Load();
	void Enemy2Load();


	void Release();


	void TitleRelease();
	void SelectRelease();
	void GameRelease();
	void BossRelease();
	void PlayerRelease();
	void StageRelease();
	void Enemy1Release();
	void Enemy2Release();
};

