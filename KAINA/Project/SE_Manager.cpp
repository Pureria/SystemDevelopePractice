#include "SE_Manager.h"
bool CSE_Manager::Load(void) {
	CUtilities::SetCurrentDirectory("Resource");
	return TRUE;
}

void CSE_Manager::Initialize(void)
{
	m_Volume = gSound.GetVolume();
}

void CSE_Manager::SEPlayer(int request) {
	if (!IsPlaySE())
		gSound.Release();

	m_NowSetSE = request;

	gSound.SetVolume(m_Volume);

	switch (request)
	{
	case SE_ATTACK_REFLECTION:
		gSound.Load("SE/SE_Reflection.mp3");
		gSound.Play();
		break;
	case SE_ATTACK_THROUGH:
		gSound.Load("SE/SE_Attack_Throuth.mp3");
		gSound.Play();
		break;
	case SE_ATTACK_HEAVY:
		gSound.Load("SE/SE_Attack_Heavy.mp3");
		gSound.Play();
		break;
	case SE_WALL_CONTACT:
		gSound.Load("SE/SE_Wall_Contact.mp3");
		gSound.Play();
		break;
	case SE_FIREBER:
		gSound.Load("SE/SE_FIREBER.mp3");
		gSound.Play();
		break;
	case SE_DIVEWATER:
		gSound.Load("SE/SE_Divewater.mp3");
		gSound.Play();
		break;
	case SE_INSIDEWATER:
		gSound.Load("SE/SE_Insidewater.mp3");
		gSound.Play();
		break;
	case SE_PLAYER_DAMAGE:
		gSound.Load("SE/SE_Player_Damage.mp3");
		gSound.Play();
		break;	
	case SE_PLAYER_DIE:
		gSound.Load("SE/SE_Player_Die.mp3");
		gSound.Play();
		break;
	case SE_JUMP:
		gSound.Load("SE/SE_Player_Jump.mp3");
		gSound.Play();
		break;
	case SE_HEAVY:
		gSound.Load("SE/SE_Heal.mp3");
		gSound.Play();
		break;
	case SE_HEAL:
		gSound.Load("SE/SE_Heal.mp3");
		gSound.Play();
		break;
	case SE_ICE:
		gSound.Load("SE/SE_Ice.mp3");
		gSound.Play();
		break;
	case SE_FIRE:
		gSound.Load("SE/SE_Fire.mp3");
		gSound.Play();
		break;
	case SE_FIRE_SPIDERWEB:
		gSound.Load("SE/SE_Fire_Spiderweb.mp3");
		gSound.Play();
		break;
	case SE_FIRE_ICE:
		gSound.Load("SE/SE_Fire_Ice.mp3");
		gSound.Play();
		break;
	case SE_BURNER:
		gSound.Load("SE/SE_burner.wav");
		gSound.SetVolume(m_Volume * 0.5f);
		gSound.Play();
		break;
	case SE_ENEMY_ATTACK01:
		gSound.Load("SE/SE_Enemy_Attack.mp3");
		gSound.Play();
		break;
	case SE_ENEMY_ATTACK02:
		gSound.Load("SE/SE_Enemy_Canon.mp3");
		gSound.Play();
		break;
	case SE_ENEMY_DAMAGE:
		gSound.Load("SE/SE_Enemy_Damage.mp3");
		gSound.Play();
		break;
	case SE_ENEMY_DIE:
		gSound.Load("SE/SE_Enemy_Die.mp3");
		gSound.Play();
		break;
	case SE_BOSS_ATTACK01:
		gSound.Load("SE/SE_Boss_Attack_Nomal.mp3");
		gSound.Play();
		break;
	case SE_BOSS_ATTACK02:
		gSound.Load("SE/SE_Attack_Locate.mp3");
		gSound.Play();
		break;
	case SE_BOSS_ATTACK03:
		gSound.Load("SE/SE_Boss_Attack_Rush1.mp3");
		gSound.Play();
		break;
	case SE_BOSS_ATTACK04:
		gSound.Load("SE/SE_Boss_Attack_Rush2.mp3");
		gSound.Play();
		break;

	case SE_BOSS_JUMP:
		gSound.Load("SE/SE_Boss_Jump.wav");
		gSound.Play();
		break;
	case SE_BOSS_DAMAGE:
		gSound.Load("SE/SE_Boss_Damage.mp3");
		gSound.Play();
		break;
	case SE_BOSS_SHIELD:
		gSound.Load("SE/SE_Boss_Shield.mp3");
		gSound.Play();
		break;
	case SE_SELECT_CHANGE:
		gSound.Load("SE/SE_Select_Change.mp3");
		gSound.Play();
		break;
	case SE_SELECT_OK:
		gSound.Load("SE/SE_Select_OK.mp3");
		gSound.Play();
		break;
	}
}

void CSE_Manager::Release(void) {
	gSound.Release();
}