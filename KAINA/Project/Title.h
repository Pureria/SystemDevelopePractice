#pragma once
#include	"Scene_Base.h"
#include    "CMenu.h"

#define		COUNT_NO			2

#define		EXIT_FALSH_COUNT	15

class CTitle : public Scene_Base {
private:
	CTexture				m_BackImage;
	CTexture				m_StartImage;
	CTexture				m_ExitImage;

	int						m_SelectNo;

public:
	CTitle() : m_BackImage(),m_StartImage(),m_ExitImage(),m_SelectNo(0){};
	~CTitle();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);

public://Update“à‚Ìˆ—‚ğ•ªŠ„‚µ‚½ŠÖ”
	void UpdateSelect();
	void UpdateMenu();
};