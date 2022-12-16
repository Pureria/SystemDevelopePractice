#pragma once
#include	"Player.h"
#include	"BaseStage.h"
#include	"Enemy.h"
#include	"Enemy_2.h"
#include	"Item.h"
#include	"EffectManager.h"
#include    "CMenu.h"
#include	"Scene_Base.h"



class CGame : public Scene_Base{
private:
	//�v���C���[
	CPlayer			m_Player;

	//�X�e�[�W
	CStage			m_Stage;

	//�G�̃|�C���^�z��
	CEnemy*		    m_EnemyArray;
	CEnemy_2*		m_Enemy2Array;

	//�G�t�F�N�g
	CEffectManager	m_EffectManager;

	//�A�C�e���̃|�C���^�z��
	CItem*			m_ItemArray;

	//�|�[�Y
	CMenu			m_Menu;

	//���̐؂�ւ�
	int				m_intervalFire;
	bool			m_bFire;

	int				m_NowSceneNo;



public:
	CGame() : m_Player(),m_Stage(),m_EnemyArray(),m_EffectManager(),m_ItemArray(),m_Menu(),m_NowSceneNo(SCENENO_GAME_STAGE1){};
	~CGame();
	bool Load();
	void Initialize();
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);

private:
	void StgCollPlayer();
	void StgCollEne();
	void StgCollItm();
	void StgCollBullet();
};