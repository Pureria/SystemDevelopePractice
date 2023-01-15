#pragma once
#include "Mof.h"
#include "SoundDefine.h"

class CSE_Manager
{
private:
	CSoundBuffer gSound;
	int			m_NowSetSE;
	int			m_Volume;
public:

	void Initialize(void);
	bool Load(void);
	void SEPlayer(int request);
	void Release(void);

	bool IsPlaySE() { return gSound.IsPlay(); }

	void StopSE() { gSound.Stop(); }
	int GetNowSetSE() { return m_NowSetSE; }
};

