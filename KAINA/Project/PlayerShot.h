#pragma once
#include "Mof.h"
#include "GameDefine.h"

class PlayerShot
{
private:
	CTexture*		m_pShotTex;
	Vector2         m_ShotPos;
	int             m_Shottype;
	bool			m_bShow;
	
public:
	PlayerShot() : m_pShotTex(), m_ShotPos(0, 0), m_Shottype(0), m_bShow(false) {};
	~PlayerShot();
	void Init() { m_ShotPos = Vector2(0, 0); m_Shottype = 0; m_bShow = false; }
	void Update(bool rev);
	void Fire(Vector2& pos) { m_ShotPos.x = pos.x - m_pShotTex->GetWidth() * 0.5; m_ShotPos.y = pos.y; m_bShow = true; }
	void Render();
	void RenderDebug();
	void SetTexture(CTexture* pt) { m_pShotTex = pt; }
	void SetShow(bool bs)         { m_bShow = bs; }
	bool GetShow()				  { return m_bShow; }
	int GetType()				  { return m_Shottype; }
	CRectangle GetRect()		  { return CRectangle(m_ShotPos.x, m_ShotPos.y, 
									m_ShotPos.x + m_pShotTex->GetWidth(), 
									m_ShotPos.y + m_pShotTex->GetHeight()); }
};

