#pragma once
#include	"Mof.h"
#include	"EnemyStateDefine.h"
#include	"EffectManager.h"
#include	"SE_Manager.h"

#define		FROST_WAIT		120

class CEnemy_Base
{
protected:
	//false : 左向き	true : 右向き
	bool					m_bReverse;

	CTexture*				m_pTexture;
	CSpriteMotionController m_Motion;
	CRectangle				m_SrcRect;

	int						m_Type;
	int						m_EnemyType;
	int						m_HP;
	int						m_DamageWait;

	Vector2					m_Pos;
	Vector2					m_Move;
	Vector2					m_CurrentMove;

	bool					m_bShow;
	//TRUE : 画面内		FALSE : 画面外
	bool					m_bWidthOut;
	//KnockBack : TRUE ノックバック中 : FALSE : ノックバック無し
	bool					m_bKnockback;

	float					m_KnockbackTime;


	CEffectManager*			m_pEffectManager;

	int						m_Deffence;

	float					m_EneTime;

	bool					m_bDead;

	int						m_AbState;
	int						m_AbStateWait;
	MofU32					m_Color;

public:
	CEnemy_Base();
	virtual ~CEnemy_Base() {};
	void virtual Initialize(float px, float py, int type)	= 0;
	void virtual Update(float wx)							= 0;
	void virtual CollisionStage(float ox, float oy)			= 0;
	void virtual Render(float wx, float wy)					= 0;
	void virtual RenderDebug(float wx, float wy)			= 0;
	void virtual Release()									= 0;
	CRectangle virtual GetRect()							= 0;

	void virtual SetTexture(CTexture* pt, CTexture* st)					{			return;							}
	void virtual DeffenceProc(int dmg)									{			return;							}
	void virtual DeffenceProc(int dmg,int deff)							{			return;							}
	void virtual Damage(float dmg)										{			return;							}
	void virtual KnockBack()											{			return;							}


	void		SetEffectManager(CEffectManager* pmng)							{			m_pEffectManager = pmng;		}
	void		SetTime(float time)												{			m_EneTime = time;				}
	
	void		SetAbState(int ab)												{			m_AbState = ab;					}

	//元の状態に戻す。
	void		SetAbReturnState()												{			m_AbState = STATE_IDLE;			}

	void		SetAbStateWait(int wait)										{			m_AbStateWait = wait;			}

	bool		GetShow()														{			return m_bShow;					}
	bool		GetKnockback()													{			return m_bKnockback;			}
	int			GetEnemyType()													{			return m_EnemyType;				}

	bool		IsDead()														{			return m_bDead;					}

	Vector2		GetMove()														{			return m_Move;					}

	int			GetAbStateNo()													{			return m_AbState;				}

	void		AbStateMoveDec() {
		switch (GetAbStateNo())
		{
		case STATE_FROST:
			m_Move.x *= 0.8f;
			m_Move.y *= 0.0f;
			break;
		}
	}

	void ReturnWaitStates() {
		if (m_AbStateWait > 0) {
			m_AbStateWait--;
		}
		else if (m_AbStateWait <= 0) {
			SetAbReturnState();
		}
	}
};

