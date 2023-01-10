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

//�G�̎��
enum tag_EnemyType
{
	Enemy_1,
	Enemy_2,

	EnemyTypeCount,
};

//�e�̔��ˉ�
#define		REFLECTION_COUNT		5	
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

//�e�̑���
#define	    PLAYERSHOT_SPEED		10

//�e�̍ő吔
#define		PLAYERSHOT_COUNT		20

//�e�̊Ԋu
#define     PLAYERSHOT_WAIT			10


#define     LASER_ATTACKWIDTH		64


#define		LAZER_REVCOUNT			3

#define		LASER_FIRE_COUNT		3

#define		LASER_DELAY				0.5


#define		ENEMY_ATTAK_POWER		10


#define		HEAL_POWER				10


//************************�X�e�[�W�V�[���Ŏg��Define*************************//
//�X�e�[�W�I����ʂ̍ő吔
#define     COUNT_NO				4

//************************���j���[�\���Ŏg��Define*************************//
//�\��������e�L�X�g�̍ő吔
#define     TEXTCOUNT_MAX			2

//************************�t�F�[�h�A�E�g �t�F�[�h�C���Ŏg��Define*************************//
//�A���t�@�l
#define		FADE_ALPHA				5

//�A���t�@�ő�l
#define		FADE_ALPHA_MAX			255

//�G�̒e�ő吔
#define		ENEMY_SHOT_COUNT		20
#define		ENEMY_SHOT_WAIT			100

//FireBar�C���^�[�o��
#define		FIREBAR_INTERVAL		90

//Stage1_BOSS�X�N���[���Œ�l
//#define		STAGE1_BOSS_FIXSCROLL_WIDTH		185.0f
//#define		STAGE1_BOSS_FIXSCROLL_HEIGHT	 120.0f

#define		STAGE1_BOSS_FIXSCROLL_WIDTH		0.0f
#define		STAGE1_BOSS_FIXSCROLL_HEIGHT	0.0f
//Y44


