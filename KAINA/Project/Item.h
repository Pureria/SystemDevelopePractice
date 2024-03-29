#pragma once

#include	"Mof.h"
#include	"GameDefine.h"

//アイテム種類列挙
enum tag_ITEMTYPE {
	ITEM_SPIDERWEB,					//蜘蛛の巣
	BOSS_DOOR,

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
	bool					m_bBossEliminated;
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

	void Effect(bool jump, bool& BScene, float& PMovex, float& PMoveY);

	//ボスがいないステージでは常にTRUE、ボスがいるステージではボスの討伐情報
	void SetBossEliminated(bool flg) { m_bBossEliminated = flg; }
};