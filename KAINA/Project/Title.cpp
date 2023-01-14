#include	"GameDefine.h"
#include	"Title.h"

/**
 * �f�X�g���N�^
 *
 */
CTitle::~CTitle(){}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CTitle::Load(void){
	//�e�N�X�`���̓ǂݍ���
	if (!m_BackImage.Load("BackGround/Title.png"))
		return false;
	
	if (!m_SelectArrow.Load("SelectArrow.png"))
		return false;

	if (!m_StartImage.Load("BackGround/Start.png"))
		return false;

	if (!m_ExitImage.Load("BackGround/Exit.png"))
		return false;


	m_BGMManager.Load();

	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * ��Ԃ��������������Ƃ��Ɏ��s����B
 */
void CTitle::Initialize(void){

	this->Load();

	m_Alpha = 0;

	char* m_pTitle = "�Q�[�����I�����܂����H";

	char* m_pMenuString[TEXTCOUNT_MAX] = {
						"������",
						"�͂�",
	};
	// �|�[�Y�@�\�ɕK�v�Ȓl��n���B	
	m_Menu.Create(m_pTitle, m_pMenuString, TEXTCOUNT_MAX);

	m_BGMManager.Initialize();
	m_BGMManager.BGMPlayer(BGM_TITLE);

	m_Alpha = 255;

	m_SelectNo = 0;
}

/**
 * �X�V
 *
 */
void CTitle::Update(void){
	UpdateExitkey();
	if (m_FlashCount > 0) {
		m_FlashCount--;
	}
#pragma region Fade
	if (m_bFadeIn)
	{
		m_NowTime += CUtilities::GetFrameSecond();
		m_Alpha = (int)m_Function.Animation(0, FADE_TIME, 255, 0, m_NowTime);
		if (m_Alpha <= 0)
			m_bFadeIn = false;
		return;
	}

	if (m_bFadeOut)
	{
		m_NowTime += CUtilities::GetFrameSecond();
		m_Alpha = (int)m_Function.Animation(0, FADE_TIME, 0, 255, m_NowTime);
		if (m_Alpha >= 255)
		{
			m_bEnd = true;
			m_SceneNo = SCENENO_SELECT;
		}
			
		return;
	}
#pragma endregion

	UpdateMenu();

	if (m_Menu.IsShow()) {
		return;
	}

	UpdateSelect();
	//Enter�L�[�ŃQ�[����ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && m_SelectNo == 0 && !m_bEnd) {

		m_bFadeOut = true;
		m_NowTime = 0;
		m_Alpha = 0;
		m_FlashCount = START_FLASH_COUNT;
		for (int i = 0; i < SE_COUNT; i++)
		{
			if (m_SEManager[i].IsPlaySE())
				continue;
			m_SEManager[i].SEPlayer(SE_SELECT_OK);
			break;
		}
	}
}

/*
* ��ʑI��
*
*/
void CTitle::UpdateSelect() {

	if (g_pInput->IsKeyPush(MOFKEY_W))
	{
		for (int i = 0; i < SE_COUNT; i++)
		{
			if (m_SEManager[i].IsPlaySE())
				continue;
			m_SEManager[i].SEPlayer(SE_SELECT_CHANGE);
			break;
		}
		if (m_SelectNo > 0) {
			--m_SelectNo;
		}
		
	}

	if (g_pInput->IsKeyPush(MOFKEY_S))
	{
		for (int i = 0; i < SE_COUNT; i++)
		{
			if (m_SEManager[i].IsPlaySE())
				continue;
			m_SEManager[i].SEPlayer(SE_SELECT_CHANGE);
			break;
		}

		if (m_SelectNo < COUNT_NO - 1) {
			++m_SelectNo;
		}
	}
}
/*
* �Q�[���I���m�F�̃��j���[�\��
*
*/
void CTitle::UpdateMenu() {

	if (m_Menu.IsShow()) {
		m_Menu.Update();
		if (m_Menu.IsEnter()) {
			if (m_Menu.GetSelect() == 0) {
				m_Menu.Hide();
			}
			else {
				exit(0);
			}
		}
	}
	else if (g_pInput->IsKeyPush(MOFKEY_RETURN) && m_SelectNo == 1) {
		for (int i = 0; i < SE_COUNT; i++)
		{
			if (m_SEManager[i].IsPlaySE())
				continue;
			m_SEManager[i].SEPlayer(SE_SELECT_OK);
			break;
		}
		m_FlashCount = EXIT_FALSH_COUNT;
		m_Menu.Show(Vector2(g_pGraphics->GetTargetWidth() * 0.5f, g_pGraphics->GetTargetHeight() * 0.5f));
	}
}

/**
 * �`��
 *
 */
void CTitle::Render(void){
	CGraphicsUtilities::RenderFillRect(0, 0, 1024, 768, MOF_COLOR_WHITE);
	m_BackImage.Render(0, 0);

	switch (m_SelectNo)
	{
	case 0:
		m_ExitImage.Render(g_pGraphics->GetTargetWidth() * 0.5f - 190, 780, MOF_XRGB(128, 128, 128));
		m_SelectArrow.Render(g_pGraphics->GetTargetWidth() * 0.5f - 250, 660, MOF_XRGB(255, 255, 255));
		if (m_FlashCount % 4 >= 2)
		{
			break;
		}
		m_StartImage.Render(g_pGraphics->GetTargetWidth() * 0.5f - 230, 610);
		break;
	case 1:
		m_StartImage.Render(g_pGraphics->GetTargetWidth() * 0.5f - 230, 610, MOF_XRGB(128, 128, 128));
		m_SelectArrow.Render(g_pGraphics->GetTargetWidth() * 0.5f - 250, 840, MOF_XRGB(255, 255, 255));
		if (m_FlashCount % 4 >= 2)
		{
			break;
		}
		m_ExitImage.Render(g_pGraphics->GetTargetWidth() * 0.5f - 190, 780);
		break;
	}

	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_ARGB(m_Alpha, 0, 0, 0));

	if (m_Menu.IsShow()) {
		m_Menu.Render();
	}
	
}

/**
 * �f�o�b�O�`��
 *
 */
void CTitle::RenderDebug(void){

}

/**
 * ���
 *
 */
void CTitle::Release(void){
	m_BackImage.Release();
	m_SelectArrow.Release();
	m_StartImage.Release();
	m_ExitImage.Release();
	m_Menu.Release();
	m_BGMManager.Release();
	for (int i = 0; i < SE_COUNT; i++)
	{
		m_SEManager[i].Release();
	}
}