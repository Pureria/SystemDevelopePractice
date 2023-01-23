#include	"GameDefine.h"
#include	"GameOver.h"

/**
 * �f�X�g���N�^
 *
 */
CGameOver::~CGameOver(){
	Release();
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
	m_SEManager.SelectLoad();


	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * ��Ԃ��������������Ƃ��Ɏ��s����B
 */
void CGameOver::Initialize(void){
	Load();

	char* m_pTitle = "���g���C���܂����H";

	char* m_pMenuString[TEXTCOUNT_MAX] = {
						"���g���C����",
						"�^�C�g����",
	};
	// �|�[�Y�@�\�ɕK�v�Ȓl��n���B	
	m_Menu.Create(m_pTitle, m_pMenuString, TEXTCOUNT_MAX);

	m_BGMManager.Initialize();
	m_BGMManager.BGMPlayer(BGM_GAMEOVER);

}

void CGameOver::UpdateMenu() {
	if (m_Menu.IsShow()) {
		m_Menu.Update();
		if (m_Menu.IsEnter()) {
			if (m_Menu.GetSelect() == 0) {
				m_bEnd = true;
				m_SceneNo = (GetOldScene() == SCENENO_GAME_STAGE1) ? SCENENO_GAME_STAGE1 : SCENENO_GAME_STAGE2;
				SetOldScene(SCENENO_GAMEOVER);
			}
			else {
				m_bEnd = true;
				m_SceneNo = SCENENO_TITLE;
				SetOldScene(SCENENO_GAMEOVER);
			}
		}
	}
	else if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {

		m_SEManager.SEPlayer(SE_SELECT_OK);
		m_Menu.Show(Vector2(g_pGraphics->GetTargetWidth() * 0.5f, g_pGraphics->GetTargetHeight() * 0.5f + 150));
	}
}

/**
 * �X�V
 *
 */
void CGameOver::Update(void){
	UpdateMenu();
	if (m_Menu.IsShow()) {
		return;
	}

	if (m_FlashCount > 0) {
		m_FlashCount--;
	}
	//Enter�L�[�Ń^�C�g����ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_RETURN) && !m_bEnd)
	{
		m_bEnd = true;
		m_SceneNo = SCENENO_SELECT;
		m_FlashCount = START_FLASH_COUNT;
		m_SEManager.SEPlayer(SE_SELECT_OK);
	}
}

/**
 * �`��
 *
 */
void CGameOver::Render(void){
	m_BackImage.Render(0, 0);

	if (m_Menu.IsShow()) {
		m_Menu.Render();
		return;
	}

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
	m_Menu.Release();
	m_SEManager.SelectRelease();
}