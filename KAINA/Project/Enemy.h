#pragma once
#include	"CEnemyBase_Shot.h"

//ìñÇΩÇËîªíËå∏êäïù
#define		ENEMY_RECT_WIDTH_DECREASE		10

class CEnemy : public CEnemyBase_Shot{
private:
	
	//ÉÇÅ[ÉVÉáÉìéÌóﬁíËã`
	enum tag_MOTION {
		MOTION_IDLE,

		MOTION_COUNT,
	};


public:
	CEnemy();
	~CEnemy();
	void Initialize(float px,float py,int type);
	void Update(float wx);
	void CollisionStage(float ox,float oy);
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release(void);
	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }

	void SetTexture(CTexture* pt, CTexture* st);

	bool GetShow(void){ return m_bShow; }
	CRectangle GetRect(){
		return CRectangle(m_Pos.x + ENEMY_RECT_WIDTH_DECREASE,m_Pos.y + ENEMY_RECT_WIDTH_DECREASE,m_Pos.x + m_SrcRect.GetWidth() - ENEMY_RECT_WIDTH_DECREASE,m_Pos.y + m_SrcRect.GetHeight());
	}

};