#include "BGM_Manager.h"


bool CBGM_Manager::Load(void) {
	CUtilities::SetCurrentDirectory("Resource");
	
	m_Sound.SetLoop(TRUE);

	
	return TRUE;
}
void CBGM_Manager::Initialize(void) {
	Load();
}
void CBGM_Manager::BGMPlayer(int request) {

	switch (request)
	{
	case BGM_TITLE:
		m_Sound.Stop();
		m_Sound.Load("BGM/BGM_Title.mp3");
		m_Sound.Play();
		break;
	case BGM_STAGE1:
		m_Sound.Stop();
		m_Sound.Load("BGM/BGM_Stage1.mp3");
		m_Sound.Play();
		break;
	case BGM_BOSS1:
		m_Sound.Stop();
		m_Sound.Load("BGM/BGM_Boss1.mp3");
		m_Sound.Play();
		break;
	case BGM_GAMECLEAR:
		m_Sound.Stop();
		m_Sound.Load("BGM/BGM_Gameclear.mp3");
		m_Sound.Play();
		break;
	case BGM_GAMEOVER:
		m_Sound.Stop();
		m_Sound.Load("BGM/BGM_Gameover.mp3");
		m_Sound.Play();
		break;
	}

	

}
void CBGM_Manager::Render(void) {

}
void CBGM_Manager::Release(void) {
	m_Sound.Release();
}