#pragma once

#include	"Mof.h"

//SE配列用
#define			SE_COUNT	10

//存在するシーンの列挙
enum tag_SCENENO{
	SCENENO_TITLE,
	SCENENO_SELECT,
	SCENENO_GAME_STAGE1,
	SCENENO_GAME_STAGE2,
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

//Fade時間(秒)
#define		FADE_TIME				2

//弾の反射回数
#define		REFLECTION_COUNT		5	

//************************全ステージの重力Define*************************//
//重力
#define		GRAVITY					0.3f

#define		DAMAGE_WAIT				60
//************************プレイヤーで使うDefine*************************//
//移動速度
#define		PLAYER_SPEED					0.3f

//移動最大速度
#define		PLAYER_MAXSPEED					7.0f

//ジャンプ初速
#define		PLAYER_JUMP						-13.0f

//攻撃幅
#define		PLAYER_ATTACKWIDTH				30

//当たり判定減衰幅
#define		PLAYER_RECTDECREASE_WIDTH		32

#define		PLAYER_RECTDECREASE_HEIGHT		12

//弾の最大数
#define		PLAYERSHOT_COUNT				20

//弾の間隔	HEAL
#define     PLAYERSHOT_HEALWAIT				15

//弾の間隔	HEAVY
#define     PLAYERSHOT_HEAVYWAIT			60

//レーザーの間隔
#define     LASER_WAIT						120

//SP消費の間隔
#define		PLAYER_SPWAIT					60

//HEAL弾の回復量
#define		HEAL_POWER						3

//SPの回復量
#define		SP_POWER						3


//HEAL弾のダメージ量
#define		HEAL_DAMAGE						3

//HEAVY弾のダメージ量
#define		HEAVY_DAMAGE					6

//FROST弾のダメージ量
#define		FROST_DAMAGE					6

//FIRE弾のダメージ量
#define		FIRE_DAMAGE						8

//HEALのSP減少値
#define		HEAL_DECREASE					1

//HEAVYのSP減少値
#define		HEAVY_DECREASE					6

//FIREのSP減少値
#define		FIRE_DECREASE					16

//FROSTのSP減少値
#define		FROST_DECREASE					12

#define		THROUGH_COUNT					3

//************************メニュー表示で使うDefine*************************//


//表示させるテキストの最大数
#define     TEXTCOUNT_MAX			2


//****************************Enemyで使うDefine****************************//


//敵の弾最大数
#define		ENEMY_SHOT_COUNT				20
#define		ENEMY_SHOT_WAIT					100

//FireBarインターバル
#define		FIREBAR_INTERVAL				90

#define		STAGE1_BOSS_FIXSCROLL_WIDTH		0.0f
#define		STAGE1_BOSS_FIXSCROLL_HEIGHT	0.0f

#define		ENEMY_ATTAK_POWER				10

#define		STAGE1_BOSS_SLASH_DAMAGE		30
