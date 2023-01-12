#pragma once
#include "Mof.h"
#include "SoundDefine.h"
#include <string>
class CSE_Manager
{
private:
	CSoundBuffer gSound;
public:

	bool Load(void);
	void SEPlayer(int request);
	void Release(void);

	bool IsPlaySE() { return gSound.IsPlay(); }

	void StopSE() { gSound.Stop(); }
};

