#pragma once
#include	"Scene_Base.h"
#include    "CMenu.h"

class CTitle : public Scene_Base {
private:
	CTexture				m_BackImage;
	CTexture                m_SelectArrow;

	//�J�ڃt���O        true : �X�e�[�W�I��        false : �Q�[���I��
	bool                    m_bSelectArrow;
	//�Q�[���I���m�F���
	CMenu					m_Menu;

	//�t�F�[�h�C���E�t�F�[�h�A�E�g�p


public:
	CTitle() : m_BackImage(), m_SelectArrow(), m_bSelectArrow(false),m_Menu() {};
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