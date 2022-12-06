#pragma once
#include	"Scene_Base.h"

class CGameClear : public Scene_Base {
private:
	CTexture				m_BackImage;
public:
	CGameClear() : m_BackImage() {};
	~CGameClear();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);
};