#pragma once
#include "Mof.h"
#include "SoundDefine.h"
#include <string>
class CBGM_Manager
{
private:
	CSoundBuffer gSound;
public:
	CBGM_Manager() : gSound(){}
	~CBGM_Manager(){}

	bool Load(void);
	void Initialize(void);
	void BGMPlayer(int request);
	void Render(void);
	void Release(void);

};







