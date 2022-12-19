#pragma once

#include	"Player.h"
#include	"Enemy.h"
#include	"Enemy_2.h"
#include	"Item.h"
#include	"EffectManager.h"

//���X�΃`�b�v
#define		LEFTSLOPE		9
//�E�X�΃`�b�v
#define		RIGHTSLOPE		4
//���`�b�v
#define		WATER			12
//�X�`�b�v
#define		ICE				11
//�{�^���`�b�v
#define		BUTTON_RED		10
#define		BUTTON_BLUE		16
#define		BUTTON_YELLOW	15
//�{�^���Ή��u���b�N
#define		BUTTON_BLOCK_RED	17
#define		BUTTON_BLOCK_BLUE	18
#define		BUTTON_BLOCK_YELLOW	19
//�o�[�i�[�`�b�v
#define		BURNER			13
//���t�g�`�b�v
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

	//�������{�^���̐�
	int						ButtonCount;
	int						NextBlockDel;

	Vector2					m_IniPlayerPos;

	CEffectManager*			m_pEffectManager;

	//�{�^������
	bool					m_bButtonRed;
	bool					m_bButtonBlue;
	bool					m_bButtonYellow;

	//�e�X�g�p
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

	//�����@�F�@�v���C���[�̍U��Rect		�v���C���[���X�e�[�W�ɍU���������̏���(�{�^������)
	bool StageAttackCollision(CRectangle r);

	int GetEnemy1Count() { return m_Enemy1Count; }
	int GetEnemy2Count() { return m_Enemy2_1Count + m_Enemy2_2Count; }
	int GetItemCount() { return m_ItemCount; }

	void ButtonGimmic();

	//����X�ɂ���	�����F�e��Rect
	void CollisionFreezeWater(CRectangle r);

	//�X�𐅂ɂ���@����:�e��Rect
	void CollisionIceFroe(CRectangle r);

	//���t�g����
	bool CollisionLift(CRectangle r, float& ox, float& oy);

	//�o�[�i�[����
	bool FireBar(CRectangle prec,bool FireEffect);

	Vector2 GetIniPlayerPos() { return m_IniPlayerPos;}
	void SetScroll(float scrollX, float scrollY) { m_ScrollX = scrollX; m_ScrollY = scrollY; }

	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }

	//�e�X�g�p
	void SetFireRec(CRectangle rec) { FireRec = rec; }
};