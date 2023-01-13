#pragma once

enum tas_EnemyType {
	Turret,
	Bike,
};

/************敵共通**********/
#define		ENEMY_KNOCKBACK_POWER_Y	5.0f
#define		ENEMY_KNOCKBACK_TIME	0.5f

/***************************/

/************Enemy2ステータス**********/
#define		ENEMY_2_1_HP				12
#define		ENEMY_2_2_HP				15
#define		ENEMY_2_1_DEFFENCE_POWER	1
#define		ENEMY_2_2_DEFFENCE_POWER	0
/**************************************/

/*ステージ1ボスのステータス*/
#define		ENEMY_BOSS_HP				50
#define		ENEMY_BOSS_FRONT_DEF		9
#define		ENEMY_BOSS_BACK_DEF			7

#define		ENEMY_BOSS_FRONTDEF_DIRECTION 10
#define		ENEMY_BOSS_ATTACK_WAIT		10

/***************************/