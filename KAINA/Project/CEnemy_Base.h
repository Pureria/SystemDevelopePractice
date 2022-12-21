#pragma once
#include	"Mof.h"
#include	"EnemyStateDefine.h"
#include	"EffectManager.h"

class CEnemy_Base
{
protected:
	//false : ç∂å¸Ç´	true : âEå¸Ç´
	bool					m_bReverse;

	CTexture*				m_pTexture;
	CSpriteMotionController m_Motion;
	CRectangle				m_SrcRect;

	int m_Type;
	int m_EnemyType;
	int m_HP;
	int m_DamageWait;

	Vector2		m_Pos;
	Vector2		m_Move;
	Vector2		m_CurrentMove;

	bool		m_bShow;
	//TRUE : âÊñ ì‡		FALSE : âÊñ äO
	bool		m_bWidthOut;

	float		m_KnockbackTime;


	CEffectManager* m_pEffectManager;

public:
	void virtual Initialize(float px, float py, int type)	= 0;
	void virtual Update(float wx)							= 0;
	void virtual CollisionStage(float ox, float oy)			= 0;
	void virtual Render(float wx, float wy)					= 0;
	void virtual RenderDebug(float wx, float wy)			= 0;
	void virtual Release()									= 0;
	void virtual SetTexture(CTexture* pt, CTexture* st)		= 0;
	CRectangle virtual GetRect()							= 0;


	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }
	bool GetShow() { return m_bShow; }
	int	 GetEnemyType() { return m_EnemyType; }
	
	void virtual Damage(float dmg) { return; }
	void virtual KnockBack() { return; }


};

