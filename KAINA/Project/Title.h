#pragma once
#include	"Scene_Base.h"
#include    "CMenu.h"

#define		COUNT_NO			2
#define		START_FLASH_COUNT	120
#define		EXIT_FALSH_COUNT	30

class CTitle : public Scene_Base {
private:
	CTexture				m_BackImage;
	CTexture                m_SelectArrow;
	CTexture				m_StartImage;
	CTexture				m_ExitImage;

	//�Q�[���I���m�F���
	CMenu					m_Menu;
	int						m_SelectNo;

	int						m_FlashCount;

public:
	CTitle() : m_BackImage(), m_SelectArrow(),m_Menu(),m_StartImage(),m_ExitImage(),m_SelectNo(0),m_FlashCount(0){};
	~CTitle();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);

public://Update���̏����𕪊������֐�
	void UpdateSelect();
	void UpdateMenu();
};