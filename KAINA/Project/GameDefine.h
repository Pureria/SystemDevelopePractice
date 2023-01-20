#pragma once

#include	"Mof.h"

//SE配列用
#define			SE_COUNT	30

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

//レーザーアニメーション用enum
enum tag_LaserAnimation {
	LASER_SIDE,
	LASER_UPDOWN,

	LASER_ANIMATION_COUNT,
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

//水の当たり判定減衰幅
#define		PLAYER_WATERDEC_WIDTH			44
#define		PLAYER_WATERDEC_HEIGHT			20

//弾の最大数
#define		PLAYERSHOT_COUNT				20

//弾の間隔	HEAL
#define     PLAYERSHOT_HEALWAIT				15

//弾の間隔	HEAVY
#define     PLAYERSHOT_HEAVYWAIT			60

//レーザーの間隔
#define     LASER_WAIT						120

//SP消費の間隔			
#define		PLAYER_SPWAIT					5	

//HEAL弾の回復量
#define		HEAL_POWER						1

//SPの回復量
#define		SP_POWER						1

//SPの回復までのインターバル(秒)
#define		PLAYERSHOT_INTERVAL				180


//HEAL弾のダメージ量
#define		HEAL_DAMAGE						3

//HEAVY弾のダメージ量
#define		HEAVY_DAMAGE					6

//FROST弾のダメージ量
#define		FROST_DAMAGE					6

//FIRE弾のダメージ量
#define		FIRE_DAMAGE						8

//HEALのSP減少値
#define		HEAL_DECREASE					2

//HEAVYのSP減少値
#define		HEAVY_DECREASE					6

//FIREのSP減少値
#define		FIRE_DECREASE					16

//FROSTのSP減少値
#define		FROST_DECREASE					12

#define		THROUGH_COUNT					3

//頭上UI表示時間（秒）
#define		PLAYER_UI_UP					0.5f
#define		PLAYER_UI_STOP					1.0f
#define		PLAYER_UI_DOWN					0.5f

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

#define		BOSS_SLASH_COUNT				5
#define		BOSS_SHOT_WAIT					5
