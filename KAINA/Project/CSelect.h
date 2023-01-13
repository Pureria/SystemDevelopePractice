#pragma once
#include	"Scene_Base.h"

//ステージ選択画面の最大数
#define     COUNT_NO				4


class CSelect : public Scene_Base
{
private:
	CTexture	m_SelectTex;
	int m_NowSelect;
public:
	CSelect() : m_SelectTex(), m_NowSelect(0) {};
	~CSelect();
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void RenderDebug();
	void Release();
};

