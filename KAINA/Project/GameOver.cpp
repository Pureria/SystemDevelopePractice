#include	"GameDefine.h"
#include	"GameOver.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
//extern int						gChangeScene;


/**
 * �f�X�g���N�^
 *
 */
CGameOver::~CGameOver(){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CGameOver::Load(void){
	//�e�N�X�`���̓ǂݍ���
	if (!m_BackImage.Load("BackGround/game over.png"))
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
void CGameOver::Initialize(void){
	Load();

	m_BGMManager.Initialize();
	m_BGMManager.BGMPlayer(BGM_GAMEOVER);

}

/**
 * �X�V
 *
 */
void CGameOver::Update(void){
	UpdateExitkey();
	if (m_FlashCount > 0) {
		m_FlashCount--;
	}
	//Enter�L�[�Ń^�C�g����ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_bEnd)
	{
		m_bEnd = true;
		m_SceneNo = SCENENO_SELECT;
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

/**
 * �`��
 *
 */
void CGameOver::Render(void){
	m_BackImage.Render(0, 0);
	if (m_FlashCount % 4 >= 2)
	{
		return;
	}
	CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() * 0.5 - 100, g_pGraphics->GetTargetHeight() * 0.5 + 200, MOF_COLOR_WHITE, "Press Enter Key");
}

/**
 * �f�o�b�O�`��
 *
 */
void CGameOver::RenderDebug(void){
}

/**
 * ���
 *
 */
void CGameOver::Release(void){
	m_BackImage.Release();
	m_BGMManager.Release();

	for (int i = 0; i < SE_COUNT; i++)
	{
		m_SEManager[i].Release();
	}
}