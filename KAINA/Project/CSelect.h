#pragma once
#include	"Scene_Base.h"


class CSelect : public Scene_Base
{
private:
	CTexture	m_SlctTex;
	int m_NowSelect;
public:
	CSelect() : m_SlctTex(), m_NowSelect(0) {};
	~CSelect();
	void Initialize();
	void Update();
	void Render();
	void RenderDebug();
	void Release() { m_SlctTex.Release(); }
};

