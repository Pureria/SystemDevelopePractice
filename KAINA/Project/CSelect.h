#pragma once
#include	"Scene_Base.h"

//ステージ選択画面の最大数
#define     COUNT_NO				2
#define		FLASH_COUNT				120

class CSelect : public Scene_Base
{
private:
	int						m_NowSelect;

	int						m_FlashCount;

	CTexture				m_Stage1Str;
	CTexture				m_Stage2Str;
public:
	CSelect() : m_NowSelect(0), m_FlashCount(0),m_Stage1Str(),m_Stage2Str(){};
	~CSelect();
	bool Load();
	void Initialize();
	void Update();
	void Render();
	void RenderDebug();
	void Release();
};

