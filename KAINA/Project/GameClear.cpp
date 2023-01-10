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
	if (!m_BackImage.Load("stage clear.png"))
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
}

/**
 * �X�V
 *
 */
void CGameClear::Update(void){
	//Enter�L�[�Ń^�C�g����ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_bEnd && m_NowScene == m_SceneNo)
	{
		m_bEnd = true;
		m_SceneNo = SCENENO_RESULT;
	}
}

/**
 * �`��
 *
 */
void CGameClear::Render(void){
	m_BackImage.Render(0, 0);
	CGraphicsUtilities::RenderString(400, 500, MOF_COLOR_WHITE, "Press Enter Key");
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