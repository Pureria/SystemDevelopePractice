#pragma once

#define		SE_TYPE		5

enum BGMCode
{
	BGM_TITLE,
	BGM_STAGE1,
	BGM_BOSS1,
	BGM_GAMECLEAR,
	BGM_GAMEOVER
};
//TODO：　追加済みはコメントアウトする
enum SECode{
	SE_ATTACK_REFLECTION,		//追加済み
	SE_ATTACK_THROUGH,			//追加済み
	SE_ATTACK_HEAVY,			//追加済み
	SE_WALL_CONTACT,			//追加済み		//プレイヤーの球が壁にぶつかる
	SE_FIREBER,					
	SE_DIVEWATER,				//追加済み
	SE_INSIDEWATER,				
	SE_PLAYER_DAMAGE,			//追加済み
	SE_PLAYER_DIE,				//追加済み
	SE_JUMP,					//追加済み
	SE_HEAL,					//追加済み
	SE_HEAVY,					//追加済み
	SE_ICE,						//追加済み
	SE_FIRE,					//追加済み		//フレイムピラーの音
	SE_FIRE_SPIDERWEB,			//追加済み		//蜘蛛の巣
	SE_FIRE_ICE,				//追加済み		//氷
	SE_BURNER,					//追加済み
	SE_ENEMY_ATTACK01,			//追加済み		//通常
	SE_ENEMY_ATTACK02,			//追加済み		//大砲
	SE_ENEMY_DAMAGE,			//追加済み
	SE_ENEMY_DIE,				//追加済み
	SE_BOSS_ATTACK01,			//追加済み		//剣を振り下ろす
	SE_BOSS_ATTACK02,							//ジャンプ斬り
	SE_BOSS_ATTACK03,			//追加済み		//盾突進1
	SE_BOSS_ATTACK04,							//盾突進2
	SE_BOSS_JUMP,				//追加済み
	SE_BOSS_DAMAGE,				//追加済み
	SE_BOSS_SHIELD,				//追加済み
	SE_SELECT_CHANGE,			//追加済み
	SE_SELECT_OK,				//追加済み
	SE_CNT,						
};

