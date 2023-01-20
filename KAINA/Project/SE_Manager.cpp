#include "SE_Manager.h"

CSE_Manager::CSE_Manager() :
	m_Volume(1.0f),
	m_NowSetSE(0)
{};
bool CSE_Manager::Load(void) {
	CUtilities::SetCurrentDirectory("Resource");
	return TRUE;
}

void CSE_Manager::Release() {
	TitleRelease();
	SelectRelease();
	GameRelease();
	BossRelease();
	PlayerRelease();
	StageRelease();
	Enemy1Release();
	Enemy2Release();
}


void CSE_Manager::SEPlayer(int request) {
	m_NowSetSE = request;
	/*for (int j = 0; j < SE_TYPE; j++)
	{
		for (int i = 0; i < SE_CNT; i++)
		{
			m_Sound[i][j].SetVolume(m_Volume);
		}
	}
	*/

	if (request == SE_BURNER)
	{
		if (!m_Sound[SE_BURNER][0].IsPlay())
			m_Sound[SE_BURNER][0].Play();
	}
	else
	{
		for (int j = 0; j < SE_TYPE; j++)
		{
			if (m_Sound[request][j].IsPlay()) { continue; }
		
			m_Sound[request][j].Play();
			break;
		}
	}
}


void CSE_Manager::StopSE(int request)
{
	if (request == SE_BURNER)
	{
		m_Sound[request][0].Stop();
	}
	else
	{
		for (int j = 0; j < SE_TYPE; j++) {

			if (m_Sound[request][j].IsPlay()) { continue; }
			m_Sound[request][j].Stop();
		}
	}
	
}

/******************************************　　　　　　　　各クラスのLoad()　　　　　　　　　*********************************************/

//Title画面へ
void CSE_Manager::TitleLoad() {

	for (int j = 0; j < SE_TYPE; j++)
	{
		m_Sound[SE_SELECT_CHANGE][j].Load("SE/SE_Select_Change.mp3");
		m_Sound[SE_SELECT_OK][j].Load("SE/SE_Select_OK.mp3");
	}
}

//ステージ選択、メニューへ
void CSE_Manager::SelectLoad() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		m_Sound[SE_SELECT_CHANGE][j].Load("SE/SE_Select_Change.mp3");
		m_Sound[SE_SELECT_OK][j].Load("SE/SE_Select_OK.mp3");
	}
}

//ゲームへ
void CSE_Manager::GameLoad() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		m_Sound[SE_WALL_CONTACT][j].Load("SE/SE_Wall_Contact.mp3");
	}

	m_Sound[SE_BURNER][0].Load("SE/SE_burner.wav");
	//m_Sound[SE_BURNER][0].SetVolume(m_Volume * 0.5f);
}

//ボスへ
void CSE_Manager::BossLoad() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		m_Sound[SE_ENEMY_DIE][j].Load("SE/SE_Enemy_Die.mp3");

		m_Sound[SE_BOSS_ATTACK01][j].Load("SE/SE_Boss_Attack_Nomal.mp3");
		
		m_Sound[SE_BOSS_ATTACK03][j].Load("SE/SE_Boss_Attack_Rush1.mp3");
		
		m_Sound[SE_BOSS_JUMP][j].Load("SE/SE_Boss_Jump.wav");

		m_Sound[SE_BOSS_DAMAGE][j].Load("SE/SE_Boss_Damage.mp3");
		
		m_Sound[SE_BOSS_SHIELD][j].Load("SE/SE_Boss_Shield.mp3");
	}

}

//プレイヤーへ
void CSE_Manager::PlayerLoad() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		m_Sound[SE_ATTACK_REFLECTION][j].Load("SE/SE_Reflection.mp3");
		
		m_Sound[SE_ATTACK_THROUGH][j].Load("SE/SE_Attack_Throuth.mp3");
		
		m_Sound[SE_ATTACK_HEAVY][j].Load("SE/SE_Attack_Heavy.mp3");
		
		m_Sound[SE_PLAYER_DAMAGE][j].Load("SE/SE_Player_Damage.mp3");
		
		m_Sound[SE_PLAYER_DIE][j].Load("SE/SE_Player_Die.mp3");
		
		m_Sound[SE_JUMP][j].Load("SE/SE_Player_Jump.mp3");
		
		m_Sound[SE_HEAVY][j].Load("SE/SE_Attack_Heavy.mp3");
		
		m_Sound[SE_HEAL][j].Load("SE/SE_Heal.mp3");
		
		m_Sound[SE_ICE][j].Load("SE/SE_Ice.mp3");
		
		m_Sound[SE_FIRE][j].Load("SE/SE_Fire.mp3");
		
		m_Sound[SE_FIRE_SPIDERWEB][j].Load("SE/SE_Fire_Spiderweb.mp3");
	}
}

//ステージへ
void CSE_Manager::StageLoad() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		m_Sound[SE_DIVEWATER][j].Load("SE/SE_Divewater.mp3");
		m_Sound[SE_DIVEWATER][j].SetVolume(m_Volume * 1.5f);
		m_Sound[SE_FIRE_ICE][j].Load("SE/SE_Fire_Ice.mp3");
	}
	m_Sound[SE_BURNER][0].Load("SE/SE_burner.wav");
	//m_Sound[SE_BURNER][0].SetVolume(m_Volume * 0.5f);
}

//敵1へ
void CSE_Manager::Enemy1Load() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		m_Sound[SE_ENEMY_ATTACK02][j].Load("SE/SE_Enemy_Attack.mp3");
	}
}

//敵２へ
void CSE_Manager::Enemy2Load() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		m_Sound[SE_ENEMY_ATTACK01][j].Load("SE/SE_Enemy_Attack.mp3");
		m_Sound[SE_ENEMY_DAMAGE][j].Load("SE/SE_Enemy_Damage.mp3");
		m_Sound[SE_ENEMY_DIE][j].Load("SE/SE_Enemy_Die.mp3");
	}
}


/******************************************　　　　　　　　各クラスのRelsease()　　　　　　　　　*********************************************/



void CSE_Manager::TitleRelease() {

	for (int j = 0; j < SE_TYPE; j++)
	{
		m_Sound[SE_SELECT_CHANGE][j].Release();
		m_Sound[SE_SELECT_OK][j].Release();
	}
}

//ステージ選択、メニューへ
void CSE_Manager::SelectRelease() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		m_Sound[SE_SELECT_CHANGE][j].Release();
		m_Sound[SE_SELECT_OK][j].Release();
	}
}

//ゲームへ
void CSE_Manager::GameRelease() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		m_Sound[SE_WALL_CONTACT][j].Release();
	}
	m_Sound[SE_BURNER][0].Release();
}

//ボスへ
void CSE_Manager::BossRelease() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		m_Sound[SE_ENEMY_DIE][j].Release();
		m_Sound[SE_BOSS_ATTACK01][j].Release();
		m_Sound[SE_BOSS_ATTACK03][j].Release();
		m_Sound[SE_BOSS_JUMP][j].Release();
		m_Sound[SE_BOSS_DAMAGE][j].Release();
		m_Sound[SE_BOSS_SHIELD][j].Release();
	}

}

//プレイヤーへ
void CSE_Manager::PlayerRelease() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		m_Sound[SE_ATTACK_REFLECTION][j].Release();
		m_Sound[SE_ATTACK_THROUGH][j].Release();
		m_Sound[SE_ATTACK_HEAVY][j].Release();
		m_Sound[SE_PLAYER_DAMAGE][j].Release();
		m_Sound[SE_PLAYER_DIE][j].Release();
		m_Sound[SE_JUMP][j].Release();
		m_Sound[SE_HEAVY][j].Release();
		m_Sound[SE_HEAL][j].Release();
		m_Sound[SE_ICE][j].Release();
		m_Sound[SE_FIRE][j].Release();
		m_Sound[SE_FIRE_SPIDERWEB][j].Release();
	}
}

//ステージへ
void CSE_Manager::StageRelease() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		m_Sound[SE_DIVEWATER][j].Release();
		m_Sound[SE_FIRE_ICE][j].Release();
	}
	m_Sound[SE_BURNER][0].Release();
}

//敵へ
void CSE_Manager::Enemy1Release() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		m_Sound[SE_ENEMY_ATTACK02][j].Release();
	}
}

void CSE_Manager::Enemy2Release() {
	for (int j = 0; j < SE_TYPE; j++)
	{
		m_Sound[SE_ENEMY_ATTACK01][j].Release();
		m_Sound[SE_ENEMY_DAMAGE][j].Release();
		m_Sound[SE_ENEMY_DIE][j].Release();
	}
}