#pragma once
#include	"Player.h"
#include	"BaseStage.h"
#include	"Enemy_Stage1_Boss.h"
#include	"Item.h"
#include	"EffectManager.h"
#include    "CMenu.h"
#include	"Scene_Base.h"



class CStage1_Boss : public Scene_Base {
private:
	//�v���C���[
	CPlayer				m_Player;

	//�X�e�[�W
	CStage				m_Stage;

	//�G�̃|�C���^�z��
	CEnemy_Stage1_Boss	m_Boss;

	//�G�t�F�N�g
	CEffectManager		m_EffectManager;

	//�A�C�e���̃|�C���^�z��
	CItem*				m_ItemArray;

	//�|�[�Y
	CMenu				m_Menu;

	int					m_NowSceneNo;

public:
	CStage1_Boss() : m_Player(), m_Stage(), m_Boss(), m_EffectManager(), m_ItemArray(), m_Menu() , m_NowSceneNo(SCENENO_GAME_STAGE1_BOSS) {};
	~CStage1_Boss();
	bool Load();
	void Initialize();
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);

private:
	void StgCollPlayer();
	void StgCollEne();
	void StgCollBoss();
	void StgCollItm();
	void StgCollBullet();
	
};