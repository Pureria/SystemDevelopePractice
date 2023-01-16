/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
CTexture	TestImage;
CRectangle	Rect;
float		sal;
float		hoge;
Vector2		Pos;

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	CUtilities::SetCurrentDirectory("Resorce");
	if (!TestImage.Load("TeruTeru.png"))
		return false;
	sal = 0;
	Pos.x = 0;
	Pos.y = 200;
	hoge = 0;

	//Rect = CRectangle(hoge , 0, TestImage.GetWidth(), TestImage.GetHeight());
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの更新
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//キーの更新
	g_pInput->RefreshKey();

	if (g_pInput->IsMouseKeyHold(MOFMOUSE_LBUTTON))
		sal += 10;

	if (g_pInput->IsMouseKeyHold(MOFMOUSE_RBUTTON))
		sal -= 10;

	if (g_pInput->IsKeyHold(MOFKEY_UPARROW))
		hoge += 10;

	if (g_pInput->IsKeyHold(MOFKEY_DOWNARROW))
		hoge -= 10;

	Rect = CRectangle(hoge, 0, TestImage.GetWidth(), TestImage.GetHeight());

	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの描画
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//描画開始
	g_pGraphics->RenderStart();
	//画面のクリア
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);

	TestImage.Render(Pos.x + sal + hoge, Pos.y, Rect);
	CGraphicsUtilities::RenderCircle(Pos.x + sal + hoge, Pos.y, 2, MOF_XRGB(255, 255, 255));

	//描画の終了
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			アプリケーションの解放
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Release(void){
	//テクスチャの開放
	TestImage.Release();
	return TRUE;
}