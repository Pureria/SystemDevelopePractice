#pragma once
#include	"Scene_Base.h"

class CGameOver : public Scene_Base {
private:
	CTexture				m_BackImage;
public:
	CGameOver() : m_BackImage() {};
	~CGameOver();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};