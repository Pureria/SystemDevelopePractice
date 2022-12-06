#pragma once
#include	"GameDefine.h"

class CEnemyShot
{
private:
	CTexture*	m_pTexture;
	Vector2		m_Pos;
	Vector2		m_Spd;

	//TRUE : �\��		FALSE : ��\��
	bool		m_bShow;
public:
	CEnemyShot();
	~CEnemyShot();
	void Initialize();
	void Fire(float px, float py, float sx, float sy);
	void Update(float wx);
	void Render(float wx,float wy);
	void RenderDebug(float wx, float wy);
	void SetTexture(CTexture* pt) { m_pTexture = pt; }
	bool GetShow() { return m_bShow; }
	void SetShow(bool bs) { m_bShow = bs; }

	CRectangle GetRect() { return CRectangle(m_Pos.x, m_Pos.y, m_Pos.x + m_pTexture->GetWidth(), m_Pos.y + m_pTexture->GetHeight()); }
};

