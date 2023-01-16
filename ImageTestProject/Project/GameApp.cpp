/*************************************************************************//*!
					
					@file	GameApp.cpp
					@brief	��{�Q�[���A�v���B

															@author	�_�c�@��
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
		@brief			�A�v���P�[�V�����̏�����
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
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
		@brief			�A�v���P�[�V�����̍X�V
		@param			None
				
		@return			TRUE		����<br>
						����ȊO	���s�A�G���[�R�[�h���߂�l�ƂȂ�
*//**************************************************************************/
MofBool CGameApp::Update(void){
	//�L�[�̍X�V
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

	TestImage.Render(Pos.x + sal + hoge, Pos.y, Rect);
	CGraphicsUtilities::RenderCircle(Pos.x + sal + hoge, Pos.y, 2, MOF_XRGB(255, 255, 255));

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
	//�e�N�X�`���̊J��
	TestImage.Release();
	return TRUE;
}