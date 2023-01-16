#include "SE_Manager.h"
bool CSE_Manager::Load(void) {
	CUtilities::SetCurrentDirectory("Resource");
	return TRUE;
}

void CSE_Manager::Initialize(void)
{
	for (int i = 0; i < SE_CNT; i++)
	{
		switch (i)
		{
		case SE_ATTACK_REFLECTION:
			gSound[i].Load("SE/SE_Reflection.mp3");			
			break;
		case SE_ATTACK_THROUGH:
			gSound[i].Load("SE/SE_Attack_Throuth.mp3");
			break;
		case SE_ATTACK_HEAVY:
			gSound[i].Load("SE/SE_Attack_Heavy.mp3");
			break;
		case SE_WALL_CONTACT:
			gSound[i].Load("SE/SE_Wall_Contact.mp3");
			break;
		case SE_FIREBER:
			gSound[i].Load("SE/SE_FIREBER.mp3");			
			break;
		case SE_DIVEWATER:
			gSound[i].Load("SE/SE_Divewater.mp3");			
			break;
		case SE_INSIDEWATER:
			gSound[i].Load("SE/SE_Insidewater.mp3");			
			break;
		case SE_PLAYER_DAMAGE:
			gSound[i].Load("SE/SE_Player_Damage.mp3");			
			break;
		case SE_PLAYER_DIE:
			gSound[i].Load("SE/SE_Player_Die.mp3");			
			break;
		case SE_JUMP:
			gSound[i].Load("SE/SE_Player_Jump.mp3");			
			break;
		case SE_HEAVY:
			gSound[i].Load("SE/SE_Heal.mp3");			
			break;
		case SE_HEAL:
			gSound[i].Load("SE/SE_Heal.mp3");			
			break;
		case SE_ICE:
			gSound[i].Load("SE/SE_Ice.mp3");			
			break;
		case SE_FIRE:
			gSound[i].Load("SE/SE_Fire.mp3");			
			break;
		case SE_FIRE_SPIDERWEB:
			gSound[i].Load("SE/SE_Fire_Spiderweb.mp3");			
			break;
		case SE_FIRE_ICE:
			gSound[i].Load("SE/SE_Fire_Ice.mp3");			
			break;
		case SE_BURNER:
			gSound[i].Load("SE/SE_burner.wav");
			gSound[i].SetVolume(m_Volume * 0.5f);			
			break;
		case SE_ENEMY_ATTACK01:
			gSound[i].Load("SE/SE_Enemy_Attack.mp3");			
			break;
		case SE_ENEMY_ATTACK02:
			gSound[i].Load("SE/SE_Enemy_Canon.mp3");			
			break;
		case SE_ENEMY_DAMAGE:
			gSound[i].Load("SE/SE_Enemy_Damage.mp3");			
			break;
		case SE_ENEMY_DIE:
			gSound[i].Load("SE/SE_Enemy_Die.mp3");			
			break;
		case SE_BOSS_ATTACK01:
			gSound[i].Load("SE/SE_Boss_Attack_Nomal.mp3");			
			break;
		case SE_BOSS_ATTACK02:
			gSound[i].Load("SE/SE_Attack_Locate.mp3");			
			break;
		case SE_BOSS_ATTACK03:
			gSound[i].Load("SE/SE_Boss_Attack_Rush1.mp3");			
			break;
		case SE_BOSS_ATTACK04:
			gSound[i].Load("SE/SE_Boss_Attack_Rush2.mp3");			
			break;
		case SE_BOSS_JUMP:
			gSound[i].Load("SE/SE_Boss_Jump.wav");			
			break;
		case SE_BOSS_DAMAGE:
			gSound[i].Load("SE/SE_Boss_Damage.mp3");			
			break;
		case SE_BOSS_SHIELD:
			gSound[i].Load("SE/SE_Boss_Shield.mp3");			
			break;
		case SE_SELECT_CHANGE:
			gSound[i].Load("SE/SE_Select_Change.mp3");			
			break;
		case SE_SELECT_OK:
			gSound[i].Load("SE/SE_Select_OK.mp3");			
			break;
		}
		m_Volume = gSound[i].GetVolume();

	}
}

void CSE_Manager::SEPlayer(int request) {
	m_NowSetSE = request;

	for (int i = 0; i < SE_CNT; i++)
	{
		gSound[i].SetVolume(m_Volume);
	}

	gSound[request].Play();
	
}

bool CSE_Manager::IsPlaySE()
{
	for (int i = 0; i < SE_CNT; i++)
	{
		if (gSound[i].IsPlay())
			return true;
	}
	return false;
}

void CSE_Manager::StopSE()
{
	gSound[m_NowSetSE].Stop();
}

void CSE_Manager::Release(void) {
	for (int i = 0; i < SE_CNT; i++)
	{
		gSound[i].Release();
	}
}