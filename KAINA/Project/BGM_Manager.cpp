#include "BGM_Manager.h"


bool CBGM_Manager::Load(void) {
	CUtilities::SetCurrentDirectory("Resource");
	
	gSound.SetLoop(TRUE);

	
	return TRUE;
}
void CBGM_Manager::Initialize(void) {
	
	
}
void CBGM_Manager::BGMPlayer(int request) {

	switch (request)
	{
	case BGM_TITLE:
		gSound.Stop();
		gSound.Load("BGM/BGM_Title.mp3");
		gSound.Play();
		break;
	case BGM_STAGE1:
		gSound.Stop();
		gSound.Load("BGM/BGM_Stage1.mp3");
		gSound.Play();
		break;
	case BGM_BOSS1:
		gSound.Stop();
		gSound.Load("BGM/BGM_Boss1.mp3");
		gSound.Play();
		break;
	case BGM_GAMECLEAR:
		gSound.Stop();
		gSound.Load("BGM/BGM_Gameclear.mp3");
		gSound.Play();
		break;
	case BGM_GAMEOVER:
		gSound.Stop();
		gSound.Load("BGM/BGM_Gameover.mp3");
		gSound.Play();
		break;
	}

	

}
void CBGM_Manager::Render(void) {

}
void CBGM_Manager::Release(void) {
	gSound.Release();
}