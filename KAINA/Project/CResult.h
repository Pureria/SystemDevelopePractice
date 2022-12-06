#pragma once
#include	"Scene_Base.h"

class CResult : public Scene_Base
{
private:
	char*		m_String;
	Vector2		m_StrPos;
public:
	CResult() : m_String(), m_StrPos(0.0f, 0.0f){};
	~CResult();
	bool Load(void);
	void Initialize();
	void Update();
	void Render() { CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_BLACK, m_String); }
	void RenderDebug();
	void Release();

};

