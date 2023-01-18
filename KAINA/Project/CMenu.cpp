#include "CMenu.h"


void CMenu::Create(char* pTitle, char** pText, int cnt) {
	//古いデータの解放
	Release();
	//引数の文字列を保存
	m_Count = cnt;

	/*
	*　処理内容  ：char*型のキャスト
	*			 　strlen関数で受け取った文字の長さ+1分のメモリを確保
	*			 　C言語の動的メモリ確保
	*
	*　詳細　　　：malloc関数の引数に、指定バイト分のメモリを確保して、確保したメモリ領域のポインタを返している。
	*			 ：strlen関数は、最初にnull値と一致するまでの長さを返している。
	*/
	m_pTitle = (char*)malloc(strlen(pTitle) + 1);

	/*
	*引数    　：　第一引数にコピー先の文字列　　第二引数にコピー元の文字列
	*処理内容  ：　第二引数で受け取った文字列を、メモリ確保したm_pTitleにコピーする。
	*/
	strcpy(m_pTitle, pTitle);

	/*　
	*　処理内容  ：char**型のキャスト
	*			   受け取った引数が使用するサイズ分をメモリ空間で確保し、確保した先のポインタを渡している。
	*			   C言語の動的メモリ確保
	*
	*　詳細　　	 ：sizeof演算子では、メモリサイズを調べてポインタのバイト数を取得した後、pTextの数だけ乗算して動的メモリの確保。
	*			　 確保したメモリを、動的配列のm_pTextへポインタで渡す。
	*
	*/
	m_pText = (char**)malloc(sizeof(pText) * cnt);

	/*　
	*　処理内容  ：char*型のキャスト
	*			   strlen関数で受け取った文字の長さ+1分のメモリを確保
	*			   C言語の動的メモリ確保
	*
	*			   確保したメモリをm_Count分繰り返して、動的配列のm_pTextの要素へ1つずつコピー代入。
	*
	*/
	for (int i = 0; i < m_Count; i++) {
		m_pText[i] = (char*)malloc(strlen(pText[i]) + 1);
		strcpy(m_pText[i], pText[i]);
	}

	CRectangle trec;
	CGraphicsUtilities::CalculateStringRect(0, 0, m_pTitle, trec);
	m_Rect.Right = MOF_MAX(m_Rect.Right, trec.Right + m_HSpace * 2);
	m_Rect.Bottom += trec.Bottom + m_VSpace * 2;
	m_HeaderRect = m_Rect;

	for (int i = 0; i < m_Count; i++) {
		CGraphicsUtilities::CalculateStringRect(0, 0, m_pText[i], trec);
		m_HeaderRect.Right = m_Rect.Right = MOF_MAX(m_Rect.Right, trec.Right + m_HSpace * 2);
		m_Rect.Bottom += trec.Bottom + m_VSpace;
	}
	m_Rect.Bottom += m_VSpace;

	m_SE.SelectLoad();
}

void CMenu::InitSE() {
	return;
}


void CMenu::Update() {
	if (!m_bShow) {
		return;
	}
	if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
		m_bEnter = true;
		m_SE.SEPlayer(SE_SELECT_OK);
	}
	//上下のキーで選択
	if (g_pInput->IsKeyPush(MOFKEY_W)) {
		m_Select--;
		if (m_Select < 0) {
			m_Select = m_Count - 1;
		}
		m_SE.SEPlayer(SE_SELECT_CHANGE);	
	}
	else if (g_pInput->IsKeyPush(MOFKEY_S)) {
		m_Select++;
		if (m_Select >= m_Count) {
			m_Select = 0;
		}
		m_SE.SEPlayer(SE_SELECT_CHANGE);
	}
}

void CMenu::Show(Vector2 cp) {

	m_c.x = cp.x;
	m_c.y = cp.y;
	m_bShow = true;
	m_bEnter = false;
	m_Select = 0;
	float w = m_Rect.GetWidth();
	float h = m_Rect.GetHeight();

	m_Rect.Top = m_c.y - h * 0.5f;
	m_Rect.Bottom = m_Rect.Top + h;
	m_Rect.Left = m_c.x - w * 0.5f;
	m_Rect.Right = m_Rect.Left + w;

	m_HeaderRect.Bottom = m_Rect.Top + m_HeaderRect.GetHeight();
	m_HeaderRect.Top = m_Rect.Top;
	m_HeaderRect.Right = m_Rect.Left + m_HeaderRect.GetWidth();
	m_HeaderRect.Left = m_Rect.Left;

}

void CMenu::Render() {
	if (!m_bShow) {
		return;
	}

	//ポーズの背景描画
	CGraphicsUtilities::RenderFillRect(m_Rect, MOF_ARGB(200, 0, 0, 0));
	CGraphicsUtilities::RenderFillRect(m_HeaderRect, MOF_ARGB(200, 64, 64, 64));

	//文字の描画
	CRectangle trec;
	float py = m_Rect.Top + m_VSpace;
	CGraphicsUtilities::CalculateStringRect(0, 0, m_pTitle, trec);
	CGraphicsUtilities::RenderString(m_c.x - trec.GetWidth() * 0.5f, py, MOF_COLOR_WHITE, m_pTitle);

	py += trec.Bottom + m_VSpace;
	for (int i = 0; i < m_Count; i++) {
		CGraphicsUtilities::CalculateStringRect(0, 0, m_pText[i], trec);
		CGraphicsUtilities::RenderString(m_c.x - trec.GetWidth() * 0.5f, py + m_VSpace,
			((m_Select == i) ? MOF_XRGB(255, 255, 255) : MOF_XRGB(128, 128, 128)), m_pText[i]);
		py += trec.Bottom + m_VSpace;
	}
}

void CMenu::Release() {

	if (m_pTitle) {
		free(m_pTitle);
		m_pTitle = NULL;
	}
	if (m_pText) {
		for (int i = 0; i < m_Count; i++) {
			free(m_pText[i]);
		}
		free(m_pText);
		m_pText = NULL;
		m_Count = 0;
	}
	m_Rect = CRectangle(0, 0, 0, 0);

	m_SE.SelectRelease();
}
