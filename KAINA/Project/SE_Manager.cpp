#include "SE_Manager.h"
bool CSE_Manager::Load(void) {
	CUtilities::SetCurrentDirectory("Resource");
	return TRUE;
}

/*case SE_ENEMY_ATTACK01:
			m_Sound[i].Load("SE/SE_Enemy_Attack.mp3");
			break;
		case SE_ENEMY_ATTACK02:
			m_Sound[i].Load("SE/SE_Enemy_Canon.mp3");
			break;*/

void CSE_Manager::SEPlayer(int request) {
	m_NowSetSE = request;
	for (int j = 0; j < SE_TYPE; j++)
	{
		for (int i = 0; i < SE_CNT; i++)
		{
			m_Sound[i][j].SetVolume(m_Volume);
		}
	}

	for (int j = 0; j < SE_TYPE; j++)
	{
		if (m_Sound[request][j].IsPlay()) { continue; }
		
		m_Sound[request][j].Play();
	}

	
	
}

bool CSE_Manager::IsPlaySE()
{
	for (int j = 0; j < SE_TYPE; j++)
	{
		for (int i = 0; i < SE_CNT; i++)
		{
			if (m_Sound[i][j].IsPlay())
				return true;
		}
	}
	return false;
}

void CSE_Manager::StopSE()
{
	for (int j = 0; j < SE_TYPE; j++) {
		m_Sound[m_NowSetSE][j].Stop();
	}
	
}

//Todo Titleへ
void CSE_Manager::TitleLoad() {

	for (int j = 0; j < SE_TYPE; j++)
	{
		for (int i = 0; i < SE_CNT; i++)
		{
			switch (i)
			{
			case SE_SELECT_CHANGE:
				m_Sound[i][j].Load("SE/SE_Select_Change.mp3");
				break;
			case SE_SELECT_OK:
				m_Sound[i][j].Load("SE/SE_Select_OK.mp3");
				break;
			}
		}
	}
}
//ステージ選択、メニューへ
void CSE_Manager::SelectLoad() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		for (int i = 0; i < SE_CNT; i++)
		{
			switch (i)
			{
			case SE_SELECT_CHANGE:
				m_Sound[i][j].Load("SE/SE_Select_Change.mp3");
				break;
			case SE_SELECT_OK:
				m_Sound[i][j].Load("SE/SE_Select_OK.mp3");
				break;
			}
		}
	}
}

//ゲームへ
void CSE_Manager::GameLoad() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		for (int i = 0; i < SE_CNT; i++)
		{
			switch (i)
			{
			case SE_WALL_CONTACT:
				m_Sound[i][j].Load("SE/SE_Wall_Contact.mp3");
				break;
			case SE_BURNER:
				m_Sound[i][j].Load("SE/SE_burner.wav");
				m_Sound[i][j].SetVolume(m_Volume * 0.5f);
				break;
			}			
		}
	}
}

//ボスへ
void CSE_Manager::BossLoad() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		for (int i = 0; i < SE_CNT; i++)
		{
			switch (i)
			{
			case SE_ENEMY_DIE:
				m_Sound[i][j].Load("SE/SE_Enemy_Die.mp3");
				break;
			case SE_BOSS_ATTACK01:
				m_Sound[i][j].Load("SE/SE_Boss_Attack_Nomal.mp3");
				break;
			case SE_BOSS_ATTACK03:
				m_Sound[i][j].Load("SE/SE_Boss_Attack_Rush1.mp3");
				break;
			case SE_BOSS_JUMP:
				m_Sound[i][j].Load("SE/SE_Boss_Jump.wav");
				break;
			case SE_BOSS_DAMAGE:
				m_Sound[i][j].Load("SE/SE_Boss_Damage.mp3");
				break;
			case SE_BOSS_SHIELD:
				m_Sound[i][j].Load("SE/SE_Boss_Shield.mp3");
				break;
			}
		}
	}
	
}

//プレイヤーへ
void CSE_Manager::PlayerLoad() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		for (int i = 0; i < SE_CNT; i++)
		{
			switch (i) {
			case SE_ATTACK_REFLECTION:
				m_Sound[i][j].Load("SE/SE_Reflection.mp3");
				break;
			case SE_ATTACK_THROUGH:
				m_Sound[i][j].Load("SE/SE_Attack_Throuth.mp3");
				break;
			case SE_ATTACK_HEAVY:
				m_Sound[i][j].Load("SE/SE_Attack_Heavy.mp3");
				break;
			case SE_PLAYER_DAMAGE:
				m_Sound[i][j].Load("SE/SE_Player_Damage.mp3");
				break;
			case SE_PLAYER_DIE:
				m_Sound[i][j].Load("SE/SE_Player_Die.mp3");
				break;
			case SE_JUMP:
				m_Sound[i][j].Load("SE/SE_Player_Jump.mp3");
				break;
			case SE_HEAVY:
				m_Sound[i][j].Load("SE/SE_Heal.mp3");
				break;
			case SE_HEAL:
				m_Sound[i][j].Load("SE/SE_Heal.mp3");
				break;
			case SE_ICE:
				m_Sound[i][j].Load("SE/SE_Ice.mp3");
				break;
			case SE_FIRE:
				m_Sound[i][j].Load("SE/SE_Fire.mp3");
				break;
			case SE_FIRE_SPIDERWEB:
				m_Sound[i][j].Load("SE/SE_Fire_Spiderweb.mp3");
				break;
			}
		}
	}
}

//ステージへ
void CSE_Manager::StageLoad() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		for (int i = 0; i < SE_CNT; i++)
		{
			switch (i)
			{
			case SE_FIRE_ICE:
				m_Sound[i][j].Load("SE/SE_Fire_Ice.mp3");
				break;
			case SE_BURNER:
				m_Sound[i][j].Load("SE/SE_burner.wav");
				m_Sound[i][j].SetVolume(m_Volume * 0.5f);
				break;
			}
		}
	}
}

//敵へ
void CSE_Manager::EnemyLoad() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		for (int i = 0; i < SE_CNT; i++)
		{
			switch (i)
			{
			case SE_ENEMY_DAMAGE:
				m_Sound[i][j].Load("SE/SE_Enemy_Damage.mp3");
				break;
			case SE_ENEMY_DIE:
				m_Sound[i][j].Load("SE/SE_Enemy_Die.mp3");
				break;
			}
		}
	}
}

void CSE_Manager::Release(void) {
	for (int j = 0; j < SE_TYPE; j++)
	{
		for (int i = 0; i < SE_CNT; i++)
		{
			m_Sound[i][j].Release();
		}
	}
}