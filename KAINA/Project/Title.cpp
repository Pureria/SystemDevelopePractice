#include	"GameDefine.h"
#include	"Title.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
//extern int						gChangeScene;

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

	m_bSelectArrow = true;

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
}

/**
 * �X�V
 *
 */
void CTitle::Update(void){
	UpdateExitkey();
	UpdateMenu();

	if (m_Menu.IsShow()) {
		return;
	}
	UpdateSelect();
	//Enter�L�[�ŃQ�[����ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && m_bSelectArrow && !m_bEnd) {
		m_bEnd = true;
		m_SceneNo = SCENENO_SELECT;
	}
}

/*
* ��ʑI��
*
*/
void CTitle::UpdateSelect() {

	if (g_pInput->IsKeyPush(MOFKEY_UP) || g_pInput->IsKeyPush(MOFKEY_DOWN))
	{
		if (!m_bSelectArrow)
			m_bSelectArrow = true;
		else
			m_bSelectArrow = false;
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
	else if (!m_bSelectArrow) {
		if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
			m_Menu.Show(Vector2(g_pGraphics->GetTargetWidth() * 0.5f, g_pGraphics->GetTargetHeight() * 0.5f));
		}
	}
}
/**
 * �`��
 *
 */
void CTitle::Render(void){
	CGraphicsUtilities::RenderFillRect(0, 0, 1024, 768, MOF_COLOR_WHITE);
	m_BackImage.Render(0, 0);

	CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() / 2.5, g_pGraphics->GetTargetHeight() / 1.3, MOF_XRGB( 0, 0, 0), "�Q�[���X�^�[�g");
	CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() / 2.2, g_pGraphics->GetTargetHeight() / 1.2, MOF_XRGB(0, 0, 0), "�I��");

	(m_bSelectArrow) ?	m_SelectArrow.Render(g_pGraphics->GetTargetWidth() / 3.5, g_pGraphics->GetTargetHeight() / 1.35, MOF_XRGB(255, 255, 255)) :
		m_SelectArrow.Render(g_pGraphics->GetTargetWidth() / 3.5, g_pGraphics->GetTargetHeight() / 1.25, MOF_XRGB(255, 255, 255));

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
	m_Menu.Release();
	m_BGMManager.Release();
}