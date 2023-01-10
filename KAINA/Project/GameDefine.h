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

//敵の種類
enum tag_EnemyType
{
	Enemy_1,
	Enemy_2,

	EnemyTypeCount,
};

//弾の反射回数
#define		REFLECTION_COUNT		5	
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

//弾の速さ
#define	    PLAYERSHOT_SPEED		10

//弾の最大数
#define		PLAYERSHOT_COUNT		20

//弾の間隔
#define     PLAYERSHOT_WAIT			10


#define     LASER_ATTACKWIDTH		64


#define		LAZER_REVCOUNT			3

#define		LASER_FIRE_COUNT		3

#define		LASER_DELAY				0.5


#define		ENEMY_ATTAK_POWER		10


#define		HEAL_POWER				10


//************************ステージシーンで使うDefine*************************//
//ステージ選択画面の最大数
#define     COUNT_NO				4

//************************メニュー表示で使うDefine*************************//
//表示させるテキストの最大数
#define     TEXTCOUNT_MAX			2

//************************フェードアウト フェードインで使うDefine*************************//
//アルファ値
#define		FADE_ALPHA				5

//アルファ最大値
#define		FADE_ALPHA_MAX			255

//敵の弾最大数
#define		ENEMY_SHOT_COUNT		20
#define		ENEMY_SHOT_WAIT			100

//FireBarインターバル
#define		FIREBAR_INTERVAL		90

//Stage1_BOSSスクロール固定値
//#define		STAGE1_BOSS_FIXSCROLL_WIDTH		185.0f
//#define		STAGE1_BOSS_FIXSCROLL_HEIGHT	 120.0f

#define		STAGE1_BOSS_FIXSCROLL_WIDTH		0.0f
#define		STAGE1_BOSS_FIXSCROLL_HEIGHT	0.0f
//Y44


