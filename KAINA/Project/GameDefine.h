#pragma once

#include	"Mof.h"

//���݂���V�[���̗�
enum tag_SCENENO{
	SCENENO_TITLE,
	SCENENO_SELECT,
	SCENENO_GAME_STAGE1,
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


//************************�S�X�e�[�W�̏d��Define*************************//
//�d��
#define		GRAVITY					0.3f

#define		DAMAGE_WAIT				60
//************************�v���C���[�Ŏg��Define*************************//
//�ړ����x
#define		PLAYER_SPEED			0.3f

//�ړ��ő呬�x
#define		PLAYER_MAXSPEED			7.0f

//�W�����v����
#define		PLAYER_JUMP				-13.0f

//�U����
#define		PLAYER_ATTACKWIDTH		30

//�����蔻�茸����
#define		PLAYER_RECTDECREASE		12

//�e�̍ő吔
#define		PLAYERSHOT_COUNT		20

//�e�̊Ԋu	HEAL
#define     PLAYERSHOT_HEALWAIT		15

//�e�̊Ԋu	HEAVY
#define     PLAYERSHOT_HEAVYWAIT	60

//HEAL�e�̉񕜗�
#define		HEAL_POWER				10

//�ʏ�e��SP�����l
#define		PLAYERSHOT_DECREASE		10

#define		PLAYER_SPWAIT			10

//���[�U�[�̊Ԋu
#define     LASER_WAIT				120

//���[�U�[��SP�����l
#define		LASER_DECREASE			10

//************************���j���[�\���Ŏg��Define*************************//
//�\��������e�L�X�g�̍ő吔
#define     TEXTCOUNT_MAX			2

//�G�̒e�ő吔
#define		ENEMY_SHOT_COUNT		20
#define		ENEMY_SHOT_WAIT			100

//FireBar�C���^�[�o��
#define		FIREBAR_INTERVAL		90

#define		STAGE1_BOSS_FIXSCROLL_WIDTH		0.0f
#define		STAGE1_BOSS_FIXSCROLL_HEIGHT	0.0f

#define		ENEMY_ATTAK_POWER		10


