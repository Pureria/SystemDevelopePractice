#pragma once
#include	"Mof.h"
#include	"EffectManager.h"

//�����蔻�茸����
#define			ENEMY_RECTDECREALSE		20

class CEnemy_2{
private:
	CTexture*				m_pTexture;
	CSpriteMotionController m_Motion;
	CRectangle				m_SrcRect;
	
	int m_Type;
	int m_HP;
	int m_DamageWait;

	Vector2		m_Pos;

	bool		m_bShow;
	//TRUE : ��ʓ�		FALSE : ��ʊO
	bool		m_bWidthOut;

	CEffectManager* m_pEffectManager;

	//���[�V������ޒ�`
	enum tag_Motion {
		MOTION_IDLE,
		MOTION_MOVE,
		MOTION_DAMAGE,
		
		MOTION_COUNT,
	};
public:
	CEnemy_2();
	~CEnemy_2();

	void Initialize(float px, float py, int type);
	void Update(float wx);
	void CollisionStage(float ox, float oy);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release();
	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }

	bool GetShow() { return m_bShow; }

	CRectangle GetRect() { return CRectangle(m_Pos.x + ENEMY_RECTDECREALSE, m_Pos.y + ENEMY_RECTDECREALSE, m_Pos.x + m_SrcRect.GetWidth() - ENEMY_RECTDECREALSE, m_Pos.y + m_SrcRect.GetHeight()); }
};

