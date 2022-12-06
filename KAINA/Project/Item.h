#pragma once

#include	"Mof.h"
#include	"GameDefine.h"

//�A�C�e����ޗ�
enum tag_ITEMTYPE {
	ITEM_SPIDERWEB,					//�w偂̑�
	BOSS_DOOR,
	ITEM_RECOVER,					//��
	ITEM_GOAL,						//�S�[��

	ITEM_TYPECOUNT,
};

class CItem {
private:
	CTexture*				m_pTexture;
	CSpriteMotionController	m_Motion;
	int						m_Type;
	float					m_PosX;
	float					m_PosY;
	float					m_MoveX;
	float					m_MoveY;
	bool					m_bShow;
	CRectangle				m_SrcRect;
public:
	CItem();
	~CItem();
	void Initialize(float px,float py,int type);
	void Update(void);
	void CollisionStage(float ox,float oy);
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release(void);
	void SetTexture(CTexture* pt){ m_pTexture = pt; }
	bool GetShow(void){ return m_bShow; }
	void SetShow(bool bs){ m_bShow = bs; }
	int GetType(void){ return m_Type; }
	CRectangle GetRect(){ return CRectangle(m_PosX,m_PosY,m_PosX + m_SrcRect.GetWidth(),m_PosY + m_SrcRect.GetHeight()); }

	void StartDoorAnimation();
	bool IsEndDoorAnimation();

	void Effect(int& hp, bool& gl, bool jump, bool& BScene, float& PMovex, float& PMoveY);
};