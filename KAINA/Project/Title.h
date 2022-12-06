#pragma once
#include	"Scene_Base.h"
#include    "CMenu.h"

class CTitle : public Scene_Base {
private:
	CTexture				m_BackImage;
	CTexture                m_SelectArrow;

	//遷移フラグ        true : ステージ選択        false : ゲーム終了
	bool                    m_bSelectArrow;
	//ゲーム終了確認画面
	CMenu					m_Menu;

	//フェードイン・フェードアウト用


public:
	CTitle() : m_BackImage(), m_SelectArrow(), m_bSelectArrow(false),m_Menu() {};
	~CTitle();
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void Render(void);
	void RenderDebug(void);
	void Release(void);

public://Update内の処理を分割した関数
	void UpdateSelect();
	void UpdateMenu();
};