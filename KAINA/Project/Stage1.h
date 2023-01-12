#pragma once
#include	"Player.h"
#include	"BaseStage.h"
#include	"Enemy.h"
#include	"Enemy_2.h"
#include	"Item.h"
#include	"EffectManager.h"
#include    "CMenu.h"
#include	"Scene_Base.h"
#include	"SoundDefine.h"



class CStage1 : public Scene_Base{
private:
	//プレイヤー
	CPlayer			m_Player;

	//ステージ
	CBaseStage			m_BaseStage;

	//敵のポインタ配列
	CEnemy*		    m_EnemyArray;
	CEnemy_2*		m_Enemy2Array;

	//エフェクト
	CEffectManager	m_EffectManager;

	//アイテムのポインタ配列
	CItem*			m_ItemArray;

	//ポーズ
	CMenu			m_Menu;

	//炎の切り替え
	int				m_intervalFire;
	bool			m_bFire;

	int				m_NowSceneNo;



public:
	CStage1() : m_Player(),m_BaseStage(),m_EnemyArray(),m_EffectManager(),m_ItemArray(),m_Menu(),m_NowSceneNo(SCENENO_GAME_STAGE1){};
	~CStage1();
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

	bool EnemyOnPlayer(CRectangle eneRect, CRectangle playerRect, float& ox, float& oy);
};