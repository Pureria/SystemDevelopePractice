/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
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

float					gTimer = 0.0f;

/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̏�����
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Initialize(void){
	//���\�[�X�z�u�f�B���N�g���̐ݒ�
	CUtilities::SetCurrentDirectory("Resource");
	//�V�[���̕K�v���\�[�X��S�ēǂݍ���

	g_pScene = new CTitle();
	g_pScene->Initialize();
	
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̍X�V
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//�L�[�̍X�V
	g_pInput->RefreshKey();
	
	g_pScene->Update();
	gTimer += CUtilities::GetFrameSecond();
	g_pScene->SetTime(gTimer);

	if (g_pScene->IsEnd()) {
		g_pScene->Release();

		int Change = g_pScene->GetNextScene();

		int Old = g_pScene->GetOldScene();
		
		delete  g_pScene;

		//�V�[���ԍ��ɂ���čX�V
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
		g_pScene->Initialize();
		g_pScene->SetOldScene(Old);
	}
	
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̕`��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Render(void){
	//�`��J�n
	g_pGraphics->RenderStart();
	//��ʂ̃N���A
	g_pGraphics->ClearTarget(0.0f,0.0f,1.0f,0.0f,1.0f,0);
	
	
	g_pScene->Render();

	//�`��̏I��
	g_pGraphics->RenderEnd();
	return TRUE;
}
/*************************************************************************//*!
		@brief			�A�v���P�[�V�����̉��
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Release(void){

	if (g_pScene != nullptr) {
		g_pScene->Release();
	}

	return TRUE;
}