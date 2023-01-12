#pragma once

#include	"Mof.h"

//存在するシーンの列挙
enum tag_SCENENO{
	SCENENO_TITLE,
	SCENENO_SELECT,
	SCENENO_GAME_STAGE1,
	SCENENO_GAME_STAGE1_BOSS,
	SCENENO_GAMECLEAR,
	SCENENO_GAMEOVER,
};

//発射の方向
enum tag_Direction {
	RIGHT,
	LEFT,
	RIGHTTOP,
	LEFTTOP,
	RIGHTBOTTOM,
	LEFTBOTTOM
};

//弾の種類
enum tag_AttackType {
	NORMAL,
	LASER,
};

//弾の特性変化
enum tag_NormalNaturalChangeType {
	HEAL,
	HEAVY,
	FIRE,
	FROST,
};


//************************全ステージの重力Define*************************//
//重力
#define		GRAVITY					0.3f

#define		DAMAGE_WAIT				60
//************************プレイヤーで使うDefine*************************//
//移動速度
#define		PLAYER_SPEED			0.3f

//移動最大速度
#define		PLAYER_MAXSPEED			7.0f

//ジャンプ初速
#define		PLAYER_JUMP				-13.0f

//攻撃幅
#define		PLAYER_ATTACKWIDTH		30

//当たり判定減衰幅
#define		PLAYER_RECTDECREASE		12

//弾の最大数
#define		PLAYERSHOT_COUNT		20

//弾の間隔	HEAL
#define     PLAYERSHOT_HEALWAIT		15

//弾の間隔	HEAVY
#define     PLAYERSHOT_HEAVYWAIT	60

//HEAL弾の回復量
#define		HEAL_POWER				10

//通常弾のSP減少値
#define		PLAYERSHOT_DECREASE		10

#define		PLAYER_SPWAIT			10

//レーザーの間隔
#define     LASER_WAIT				120

//レーザーのSP減少値
#define		LASER_DECREASE			10

//************************メニュー表示で使うDefine*************************//
//表示させるテキストの最大数
#define     TEXTCOUNT_MAX			2

//敵の弾最大数
#define		ENEMY_SHOT_COUNT		20
#define		ENEMY_SHOT_WAIT			100

//FireBarインターバル
#define		FIREBAR_INTERVAL		90

#define		STAGE1_BOSS_FIXSCROLL_WIDTH		0.0f
#define		STAGE1_BOSS_FIXSCROLL_HEIGHT	0.0f

#define		ENEMY_ATTAK_POWER		10


