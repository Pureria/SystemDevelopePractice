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
//TODO�F�@�ǉ��ς݂̓R�����g�A�E�g����
enum SECode{
	SE_ATTACK_REFLECTION,		//�ǉ��ς�
	SE_ATTACK_THROUGH,			//�ǉ��ς�
	SE_ATTACK_HEAVY,			//�ǉ��ς�
	SE_WALL_CONTACT,			//�ǉ��ς�		//�v���C���[�̋����ǂɂԂ���
	SE_FIREBER,					
	SE_DIVEWATER,				//�ǉ��ς�
	SE_INSIDEWATER,				
	SE_PLAYER_DAMAGE,			//�ǉ��ς�
	SE_PLAYER_DIE,				//�ǉ��ς�
	SE_JUMP,					//�ǉ��ς�
	SE_HEAL,					//�ǉ��ς�
	SE_HEAVY,					//�ǉ��ς�
	SE_ICE,						//�ǉ��ς�
	SE_FIRE,					//�ǉ��ς�		//�t���C���s���[�̉�
	SE_FIRE_SPIDERWEB,			//�ǉ��ς�		//�w偂̑�
	SE_FIRE_ICE,				//�ǉ��ς�		//�X
	SE_BURNER,					//�ǉ��ς�
	SE_ENEMY_ATTACK01,			//�ǉ��ς�		//�ʏ�
	SE_ENEMY_ATTACK02,			//�ǉ��ς�		//��C
	SE_ENEMY_DAMAGE,			//�ǉ��ς�
	SE_ENEMY_DIE,				//�ǉ��ς�
	SE_BOSS_ATTACK01,			//�ǉ��ς�		//����U�艺�낷
	SE_BOSS_ATTACK02,							//�W�����v�a��
	SE_BOSS_ATTACK03,			//�ǉ��ς�		//���ːi1
	SE_BOSS_ATTACK04,							//���ːi2
	SE_BOSS_JUMP,				//�ǉ��ς�
	SE_BOSS_DAMAGE,				//�ǉ��ς�
	SE_BOSS_SHIELD,				//�ǉ��ς�
	SE_SELECT_CHANGE,			//�ǉ��ς�
	SE_SELECT_OK,				//�ǉ��ς�
	SE_CNT,						
};

