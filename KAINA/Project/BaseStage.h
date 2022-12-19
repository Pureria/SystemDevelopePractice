#pragma once

#include	"Player.h"
#include	"Enemy.h"
#include	"Enemy_2.h"
#include	"Item.h"
#include	"EffectManager.h"

//左傾斜チップ
#define		LEFTSLOPE		9
//右傾斜チップ
#define		RIGHTSLOPE		4
//水チップ
#define		WATER			12
//氷チップ
#define		ICE				11
//ボタンチップ
#define		BUTTON_RED		10
#define		BUTTON_BLUE		16
#define		BUTTON_YELLOW	15
//ボタン対応ブロック
#define		BUTTON_BLOCK_RED	17
#define		BUTTON_BLOCK_BLUE	18
#define		BUTTON_BLOCK_YELLOW	19
//バーナーチップ
#define		BURNER			13
//リフトチップ
#define		LIFT			14

class CStage {
private:
	CTexture				m_ChipTexture;
	CTexture				m_BackTexture;

	float					m_ChipSize;
	int						m_XCount;
	int						m_YCount;
	char*					m_pChipData;

	float					m_ScrollX;
	float					m_ScrollY;

	int						m_EnemyTextureCount;
	int						m_EnemyShotTextureCount;
	CTexture*				m_pEnemyTexture;
	CTexture*				m_pEnemyShotTexture;
	char*					m_pEnemyData;
	int						m_Enemy1Count;
	int						m_Enemy2_1Count;
	int						m_Enemy2_2Count;

	int						m_ItemTextureCount;
	CTexture*				m_pItemTexture;
	char*					m_pItemData;
	int						m_ItemCount;

	//押したボタンの数
	int						ButtonCount;
	int						NextBlockDel;

	Vector2					m_IniPlayerPos;

	CEffectManager*			m_pEffectManager;

	//ボタン判定
	bool					m_bButtonRed;
	bool					m_bButtonBlue;
	bool					m_bButtonYellow;

	//テスト用
	CRectangle				FireRec;

public:
	CStage();
	~CStage();
	bool Load(char* pName , int nowscene);
	void Initialize(CEnemy* pEnemy,CEnemy_2* pEnemy2,CItem* pItem);
	void Initialize(CItem* pItem);
	void Update(CPlayer& pl);
	void Render(void);
	void RenderDebug(void);
	void Release(int nowscene);
	float GetScrollX(){ return m_ScrollX; }
	float GetScrollY(){ return m_ScrollY; }
	bool Collision(CRectangle r);
	bool CollisionBoss1(CRectangle r);
	bool Collision(CRectangle r, float& ox, float& oy);

	//引数　：　プレイヤーの攻撃Rect		プレイヤーがステージに攻撃した時の処理(ボタン処理)
	bool StageAttackCollision(CRectangle r);

	int GetEnemy1Count() { return m_Enemy1Count; }
	int GetEnemy2Count() { return m_Enemy2_1Count + m_Enemy2_2Count; }
	int GetItemCount() { return m_ItemCount; }

	void ButtonGimmic();

	//水を氷にする	引数：弾のRect
	void CollisionFreezeWater(CRectangle r);

	//氷を水にする　引数:弾のRect
	void CollisionIceFroe(CRectangle r);

	//リフト処理
	bool CollisionLift(CRectangle r, float& ox, float& oy);

	//バーナー処理
	bool FireBar(CRectangle prec,bool FireEffect);

	Vector2 GetIniPlayerPos() { return m_IniPlayerPos;}
	void SetScroll(float scrollX, float scrollY) { m_ScrollX = scrollX; m_ScrollY = scrollY; }

	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }

	//テスト用
	void SetFireRec(CRectangle rec) { FireRec = rec; }
};