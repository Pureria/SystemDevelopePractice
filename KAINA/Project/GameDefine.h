#pragma once

#include	"Mof.h"

//SE�z��p
#define			SE_COUNT	10

//���݂���V�[���̗�
enum tag_SCENENO{
	SCENENO_TITLE,
	SCENENO_SELECT,
	SCENENO_GAME_STAGE1,
	SCENENO_GAME_STAGE2,
	SCENENO_GAME_STAGE1_BOSS,
	SCENENO_GAMECLEAR,
	SCENENO_GAMEOVER,
};

//���˂̕���
enum tag_Direction {
	RIGHT,
	LEFT,
	RIGHTTOP,
	LEFTTOP,
	RIGHTBOTTOM,
	LEFTBOTTOM
};

//�e�̎��
enum tag_AttackType {
	NORMAL,
	LASER,
};

//�e�̓����ω�
enum tag_NormalNaturalChangeType {
	HEAL,
	HEAVY,
	FIRE,
	FROST,
};

//Fade����(�b)
#define		FADE_TIME				2

//�e�̔��ˉ�
#define		REFLECTION_COUNT		5	

//************************�S�X�e�[�W�̏d��Define*************************//
//�d��
#define		GRAVITY					0.3f

#define		DAMAGE_WAIT				60
//************************�v���C���[�Ŏg��Define*************************//
//�ړ����x
#define		PLAYER_SPEED					0.3f

//�ړ��ő呬�x
#define		PLAYER_MAXSPEED					7.0f

//�W�����v����
#define		PLAYER_JUMP						-13.0f

//�U����
#define		PLAYER_ATTACKWIDTH				30

//�����蔻�茸����
#define		PLAYER_RECTDECREASE_WIDTH		32

#define		PLAYER_RECTDECREASE_HEIGHT		12

//�e�̍ő吔
#define		PLAYERSHOT_COUNT				20

//�e�̊Ԋu	HEAL
#define     PLAYERSHOT_HEALWAIT				15

//�e�̊Ԋu	HEAVY
#define     PLAYERSHOT_HEAVYWAIT			60

//���[�U�[�̊Ԋu
#define     LASER_WAIT						120

//SP����̊Ԋu
#define		PLAYER_SPWAIT					60

//HEAL�e�̉񕜗�
#define		HEAL_POWER						3

//SP�̉񕜗�
#define		SP_POWER						3


//HEAL�e�̃_���[�W��
#define		HEAL_DAMAGE						3

//HEAVY�e�̃_���[�W��
#define		HEAVY_DAMAGE					6

//FROST�e�̃_���[�W��
#define		FROST_DAMAGE					6

//FIRE�e�̃_���[�W��
#define		FIRE_DAMAGE						8

//HEAL��SP�����l
#define		HEAL_DECREASE					1

//HEAVY��SP�����l
#define		HEAVY_DECREASE					6

//FIRE��SP�����l
#define		FIRE_DECREASE					16

//FROST��SP�����l
#define		FROST_DECREASE					12

#define		THROUGH_COUNT					3

//************************���j���[�\���Ŏg��Define*************************//


//�\��������e�L�X�g�̍ő吔
#define     TEXTCOUNT_MAX			2


//****************************Enemy�Ŏg��Define****************************//


//�G�̒e�ő吔
#define		ENEMY_SHOT_COUNT				20
#define		ENEMY_SHOT_WAIT					100

//FireBar�C���^�[�o��
#define		FIREBAR_INTERVAL				90

#define		STAGE1_BOSS_FIXSCROLL_WIDTH		0.0f
#define		STAGE1_BOSS_FIXSCROLL_HEIGHT	0.0f

#define		ENEMY_ATTAK_POWER				10

#define		STAGE1_BOSS_SLASH_DAMAGE		30
