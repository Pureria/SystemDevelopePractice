#pragma once
#include	"Mof.h"
#include	"SE_Manager.h"

//************************メニュークラス*************************
/*
* 
* 各シーンで使いたいときに使うメニュー機能
* 
*/
class CMenu
{
private:

	//メニュー画面の表示位置をコピー代入で保存
	Vector2		m_c;

	//メニュー項目の余白
	int			m_HSpace, m_VSpace;

	//第一引数で受け取った文字列のポインタを保存
	char*		m_pTitle;

	//第二引数で受け取った文字列の動的配列のポインタを保存
	char**		m_pText;

	//第三引数で受け取った項目数をコピー代入で保存
	int			m_Count;

	//メニュー項目を選択する値
	int			m_Select;

	//メニュー画面の表示の切り替え
	bool		m_bShow;

	//Enterキーで決定
	bool		m_bEnter;

	//メニュー項目の最小矩形
	CRectangle	m_Rect;

	//メニュー項目の最大矩形
	CRectangle m_HeaderRect;

	CSE_Manager		m_SE;

	CTexture		m_TutorialTex;


public:
	//デフォルトコンストラクタ
	CMenu() : m_c(0, 0), m_HSpace(12), m_VSpace(8), m_Count(0), m_pTitle(), m_pText(), m_Select(0), m_bShow(false), m_bEnter(false), m_Rect(0, 0, 0, 0), m_HeaderRect(0, 0, 0, 0) {};
	//デストラクタ
	~CMenu() {};
	/*
	* 
	* 第一引数　：　メニュー画面のタイトルを渡す。　
	* 第二引数　：　メニュー画面の表示に表示するテキストの配列を渡す。
	* 第三引数　：	メニュー画面に表示するテキストの項目数を渡す。
	* 
	* 処理内容　：　メニュー画面の設定
	* 
	*/
	void Create(char* pTitle, char** pText, int cnt);
	/*
	* 
	* 処理内容	：	表示されたメニュー画面で選択肢を選び、Enterキーで確定する機能
	* 
	*/
	void Update();
	/*
	* 
	* 処理内容	：	メニュー画面の描画処理
	*
	*/
	void Render();
	/*
	* 
	* 処理内容	：	データの解放
	*
	*/
	void Release();
	/*
	* 
	* 処理内容	：　引数で受け取った値を使って、メニュー画面の表示位置を決める。
	*
	*/
	void Show(Vector2 cp);
	/*
	* 　
	* 処理内容	：　メニュー画面の表示をオフにする。　
	*
	*/
	void Hide()		{ m_bShow = false; }
	/*
	* 
	* 処理内容	：	メニュー画面が表示されているかの確認
	* 
	* 戻り値	：　真偽値
	*
	*/
	bool IsShow()	{ return m_bShow; }
	/*
	* 
	* 処理内容	：	Enterキーが押されたかの確認
	* 
	*  true：	押されている	false：　　押されていない
	* 
	* 戻り値	：　真偽値
	*
	*/
	bool IsEnter()  { return m_bEnter; }
	/*
	*
	* 処理内容	：	選ばれている数値を取得する。
	* 
	* 戻り値	：　整数型
	*
	*/
	int GetSelect() { return m_Select; }
	/*
	*
	* 処理内容	：	保存してある項目の数を取得する。
	*
	* 戻り値	：　整数型
	*
	*/
	int GetCount()  { return m_Count; }

};

