/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	基本ゲームアプリ。

															@author	濱田　享
															@date	2014.05.14
*//**************************************************************************/

//INCLUDE
#include	"GameApp.h"
#include	"GameDefine.h"
#include	"Title.h"
#include    "CSelect.h"

#include	"Stage1.h"
#include	"Stage2.h"
#include	"Stage1_BOSS.h"

#include    "CResult.h"
#include	"GameClear.h"
#include	"GameOver.h"
#include	"Scene_Base.h"

#include	"SE_Manager.h"

Scene_Base*				g_pScene = NULL;
CSE_Manager				g_SEManager[SE_COUNT];

//デバッグ表示フラグ
bool					g_bDebug = false;

float					gTimer = 0.0f;

/*************************************************************************//*!
		@brief			アプリケーションの初期化
		@param			None
				
		@return			TRUE		成功<br>
						それ以外	失敗、エラーコードが戻り値となる
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//リソース配置ディレクトリの設定
	CUtilities::SetCurrentDirectory("Resource");
	//シーンの必要リソースを全て読み込む
	
	for (int i = 0; i < SE_COUNT; i++)
	{
		g_SEManager[i].Initialize();
	}

	g_pScene = new CTitle();
	g_pScene->SetSEManager(g_SEManager);
	g_pScene->Initialize();
	
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
	
	
	g_pScene->Update();
	gTimer += CUtilities::GetFrameSecond();
	g_pScene->SetTime(gTimer);

	if (g_pScene->IsEnd()) {
		g_pScene->Release();

		int	Change = g_pScene->GetNextScene();
		
		delete  g_pScene;

		//シーン番号によって更新
		switch (Change)
		{
		case SCENENO_TITLE:
			g_pScene = new CTitle();
			break;
		case SCENENO_SELECT:
			g_pScene = new CSelect();
			break;
		case SCENENO_GAME_STAGE1:
			g_pScene = new CStage1();
			break;
		case SCENENO_GAME_STAGE2:
			g_pScene = new CStage2();
			break;
		case SCENENO_GAME_STAGE1_BOSS:
			g_pScene = new CStage1_Boss();
			break;
		case SCENENO_GAMECLEAR:
			g_pScene = new CGameClear();
			break;
		case SCENENO_GAMEOVER:
			g_pScene = new CGameOver();
			break;
		}
		g_pScene->SetSEManager(g_SEManager);
		g_pScene->Initialize();
	}

	//デバッグ表示の切り替え
	if(g_pInput->IsKeyPush(MOFKEY_F1))
	{
		g_bDebug = ((g_bDebug) ? false : true);
	}
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
	
	
	g_pScene->Render();
	//デバッグ表示をする場合
	if(g_bDebug)
	{
		g_pScene->RenderDebug();
	}

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

	if (g_pScene != nullptr) {
		g_pScene->Release();
	}

	for (int i = 0; i < SE_COUNT; i++)
	{
		g_SEManager[i].Release();
	}
	return TRUE;
}