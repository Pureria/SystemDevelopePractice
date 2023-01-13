#include	"GameDefine.h"
#include	"GameClear.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
//extern int						gChangeScene;

/**
 * �R���X�g���N�^
 *
 */

/**
 * �f�X�g���N�^
 *
 */
CGameClear::~CGameClear(){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CGameClear::Load(void){
	//�e�N�X�`���̓ǂݍ���
	if (!m_BackImage.Load("BackGround/stage clear.png"))
	{
		return false;
	}

	m_BGMManager.Load();

	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * ��Ԃ��������������Ƃ��Ɏ��s����B
 */
void CGameClear::Initialize(void){
	this->Load();
	m_Alpha = 0;

	m_BGMManager.Initialize();
	m_BGMManager.BGMPlayer(BGM_GAMECLEAR);

	m_Alpha = 255;
}

/**
 * �X�V
 *
 */
void CGameClear::Update(void){
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

	//Enter�L�[�Ń^�C�g����ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_bEnd)
	{
		m_bFadeOut = true;
		m_Alpha = 0;
		m_NowTime = 0;
	}
}

/**
 * �`��
 *
 */
void CGameClear::Render(void){
	m_BackImage.Render(0, 0);
	CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() * 0.5 - 100, g_pGraphics->GetTargetHeight() * 0.5 + 200, MOF_COLOR_WHITE, "Press Enter Key");

	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_ARGB(m_Alpha, 0, 0, 0));
}

/**
 * �f�o�b�O�`��
 *
 */
void CGameClear::RenderDebug(void){
}

/**
 * ���
 *
 */
void CGameClear::Release(void){
	m_BackImage.Release();
	m_BGMManager.Release();
}