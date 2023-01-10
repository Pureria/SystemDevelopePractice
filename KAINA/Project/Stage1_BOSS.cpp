#include	"GameDefine.h"
#include	"Stage1_BOSS.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
//extern int						gChangeScene;

/**
 * �f�X�g���N�^
 *
 */
CStage1_Boss::~CStage1_Boss() {
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CStage1_Boss::Load() {
	//�X�e�[�W�̑f�ޓǂݍ���
	m_Stage.Load("ChipData/1-1bossmap.txt",m_NowSceneNo);
	//�A�C�e���������m��
	m_ItemArray = new CItem[m_Stage.GetItemCount()];
	//�G�t�F�N�g�̑f�ޓǂݍ���
	m_EffectManager.Load();

	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 * ��Ԃ��������������Ƃ��Ɏ��s����B
 */
void CStage1_Boss::Initialize() {

	Load();
	//�v���C���[�̏�ԏ�����
	m_Player.Initialize();
	m_Player.SetPlayerPos(m_Stage.GetIniPlayerPos().x, m_Stage.GetIniPlayerPos().y);
	GetSaveToFile();
	m_Player.SetHp(m_PlayerHp);
	//�{�X�̏�ԏ�����
	m_Boss.Initialize();

	//�X�e�[�W�̏�ԏ�����
	m_Stage.Initialize(m_ItemArray);
	//�G�t�F�N�g�̏�ԏ�����
	m_EffectManager.Initialize();
	//�v���C���[�ƓG�ɃG�t�F�N�g�N���X�̐ݒ�
	m_Player.SetEffectManager(&m_EffectManager);
	m_Boss.SetEffectManager(&m_EffectManager);

	char* m_pTitle = "�|�[�Y";
	char* m_pMenuString[TEXTCOUNT_MAX] = {
						"�Q�[���ɖ߂�",
						"�X�e�[�W�I����ʂ�",
	};
	// �|�[�Y�@�\�ɕK�v�Ȓl��n���B	
	m_Menu.Create(m_pTitle, m_pMenuString, TEXTCOUNT_MAX);
	m_Alpha = 0;

	m_BGMManager.Initialize();
	m_BGMManager.BGMPlayer(BGM_BOSS1);
}

/**
 * �X�V
 *
 */
void CStage1_Boss::Update(void) {
	UpdateExitkey();
	//���j���[��ʂ̕\��
	if (m_Menu.IsShow()) {
		m_Menu.Update();
		if (m_Menu.IsEnter()) {
			if (m_Menu.GetSelect() == 1) {
				m_bEnd = true;
				m_SceneNo = SCENENO_SELECT;
			}
			m_Menu.Hide();
		}
		return;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
		m_Menu.Show(Vector2(g_pGraphics->GetTargetWidth() * 0.5f, g_pGraphics->GetTargetHeight() * 0.5f));
	}
	
	//�{�X�����h�A�A�j���[�V����
	if (m_Player.GetNextBossScene())
	{
		for (int i = 0; i < m_Stage.GetItemCount(); i++)
		{
			if (m_ItemArray[i].GetType() != BOSS_DOOR)
				continue;

			m_ItemArray[i].StartDoorAnimation();

			if (m_ItemArray[i].IsEndDoorAnimation())
			{
				m_bEnd = true;
				m_SceneNo = SCENENO_RESULT;
			}
		}
		return;
	}

	//�v���C���[�̍X�V
	m_Player.Update();
	StgCollPlayer();
	StgCollBullet();

	//�X�e�[�W�ƃv���C���[�̓����蔻��
	float ox = 0, oy = 0;

	//�G�̍X�V
	StgCollEne();

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_Player.IsLaser()) {
			if (!m_Player.GetNormalShow(i)) { continue; }
			
			CRectangle prec = m_Player.GetNormalRect(i);
			CRectangle erec = m_Boss.GetBossFrontRect();
			if (prec.CollisionRect(erec)) {
				if (m_Player.GetNatuShot(i) == HEAL) {
					m_Boss.Damage(10,true);
					m_Player.SetNormalShotShow(false,i);
				}
				else if (m_Player.GetNatuShot(i) == HEAVY) {
					m_Boss.Damage(12,true);
					m_Player.SetNormalShotShow(false,i);
				}
				continue;
			}
			else {
				erec = m_Boss.GetRect();
				if (prec.CollisionRect(erec)) {
					if (m_Player.GetNatuShot(i) == HEAL) {
						m_Boss.Damage(10, false);
						m_Player.SetNormalShotShow(false, i);
					}
					else if (m_Player.GetNatuShot(i) == HEAVY) {
						m_Boss.Damage(12, false);
						m_Player.SetNormalShotShow(false, i);
					}
					continue;
				}
			}
		}
		else {
			if (!m_Player.GetLaserShotShow(i)) { continue; }
			CRectangle prec = m_Player.GetLaserRect(i);
			CRectangle erec = m_Boss.GetBossFrontRect();
			if (prec.CollisionRect(erec)) {
				if (m_Player.GetNatuLaser(i) == FIRE) {
					m_Boss.Damage(10, true);
					m_Player.SetWallLaser(i);
				}
				else if (m_Player.GetNatuLaser(i) == FROST) {
					m_Boss.Damage(12, true);
					m_Player.SetWallLaser(i);
				}
				continue;
			}
			else {
				erec = m_Boss.GetRect();
				if (prec.CollisionRect(erec)) {
					if (m_Player.GetNatuLaser(i) == FIRE) {
						m_Boss.Damage(10, false);
					}
					else if (m_Player.GetNatuLaser(i) == FROST) {
						m_Boss.Damage(12, false);
					}
					continue;
				}
			}
		}



	}

	//�A�C�e���̍X�V
	StgCollItm();

	//�����蔻��̎��s
	m_Player.Collision_Stage1_Boss(m_Boss);

	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_Player.ColisionItem(m_ItemArray[i]);
		m_Player.CollisionAttackItem(m_ItemArray[i]);
	}

	//�X�e�[�W�̍X�V
	m_Stage.Update(m_Player);

	//�G�t�F�N�g�̍X�V
	m_EffectManager.Update();

	//�X�N���[���l�̌Œ�
	m_Stage.SetScroll(STAGE1_BOSS_FIXSCROLL_WIDTH, STAGE1_BOSS_FIXSCROLL_HEIGHT);

	//�f�o�b�O�p

	//�v���C���[�̃S�[���t���O�Ń��U���g��ʂ�
	if (m_Player.IsGoal())
	{
		m_bEnd = true;
		m_SceneNo = SCENENO_RESULT;
	}

	//F2�L�[�Ń��U���g��ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_F2))
	{
		m_bEnd = true;
		m_SceneNo = SCENENO_GAMECLEAR;
	}

	//�v���C���[�̏I���t���O�Ń��U���g��ʂ�
	if (m_Player.IsEnd())
	{
		m_bEnd = true;
		m_SceneNo = SCENENO_RESULT;
	}

	//F3�L�[�Ń��U���g��ʂ�
	if (g_pInput->IsKeyPush(MOFKEY_F3))
	{
		m_bEnd = true;
		m_SceneNo = SCENENO_GAMEOVER;
	}
}

void CStage1_Boss::StgCollPlayer()
{
	float ox = 0, oy = 0;
	if (m_Stage.Collision(m_Player.GetRect(), ox, oy))
	{
		m_Player.CollisionStage(ox, oy);
	}

	if (!m_Player.IsJump())
	{
		if (m_Stage.CollisionLift(m_Player.GetRect(), ox, oy))
		{
			m_Player.CollisionStage(ox, oy);
		}
	}
}

void CStage1_Boss::StgCollBullet()
{
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		float ox = 0, oy = 0;
		if (!m_Player.IsLaser()) {
			if (!m_Player.GetNormalShow(i))
			{
				continue;
			}

			CRectangle psrec = m_Player.GetNormalRect(i);
			//��̔���
			psrec.Bottom = psrec.Top + 1;
			psrec.Expansion(-15, 0);
			if (m_Stage.Collision(psrec))
			{
				m_Player.ShotRefTop(i);
			}

			//���̔���
			psrec = m_Player.GetNormalRect(i);
			psrec.Top = psrec.Bottom - 1;
			psrec.Expansion(-15, 0);
			if (m_Stage.Collision(psrec))
			{
				m_Player.ShotRefBottom(i);
			}

			//���̔���
			psrec = m_Player.GetNormalRect(i);
			psrec.Right = psrec.Left + 1;
			psrec.Expansion(0, -15);
			if (m_Stage.Collision(psrec))
			{
				m_Player.ShotRefLeft(i);
			}

			//�E�̔���
			psrec = m_Player.GetNormalRect(i);
			psrec.Left = psrec.Right - 1;
			psrec.Expansion(0, -15);
			if (m_Stage.Collision(psrec))
			{
				m_Player.ShotRefRight(i);
			}
		}
		else if (m_Stage.Collision(m_Player.GetLaserRect(i)))
		{
			m_Player.SetWallLaser(i);
		}

		//TODO: �Β��̋�`�͊������Ă�
	}
}

void CStage1_Boss::StgCollEne()
{
	float PPosX = m_Player.GetPosX() + 30;
	float PPosY = m_Player.GetPosY() + 30;

	//�{�X�̍X�V
	m_Boss.SetTargetPos(PPosX, PPosY);
	//3 = �_�b�V���U����
	/*
	if (m_Boss.GetBossMotionNo() == 3)
	{
		if (m_Stage.Collision(m_Boss.GetBossSideRect()))
		{
			if (m_Boss.GetReverse())
				m_Boss.SetReverse(false);
			else
				m_Boss.SetReverse(true);
			m_Boss.SetMotionMove();
		}
	}
	*/
	m_Boss.Update();
	float ox = 0; float oy = 0;
	if (m_Stage.Collision(m_Boss.GetRect(), ox, oy))
	{
		m_Boss.SetTouchGround(true);
		m_Boss.CollisionStage(ox, oy);
	}

	if (m_Stage.Collision(m_Boss.GetBossSideRect()))
	{
		m_Boss.CollisionWall();
	}

	//4 = �W�����v�U��
	if (m_Boss.GetBossMotionNo() == 4)
	{
		if (m_Stage.CollisionBoss1(CRectangle(m_Boss.GetRect().Left, m_Boss.GetRect().Bottom - 1, m_Boss.GetRect().Right, m_Boss.GetRect().Bottom)))
		{
			m_Boss.SetJumpAttackEnd();
		}
	}

	if (!m_Boss.IsJump())
	{
		if (m_Boss.GetBossMotionNo() != 4)
		{
			if (m_Stage.CollisionLift(m_Boss.GetRect(), ox, oy))
			{
				m_Boss.SetTouchGround(true);
				m_Boss.CollisionStage(ox, oy);
			}
		}
	}
}

void CStage1_Boss::StgCollItm()
{
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_ItemArray[i].SetBossEliminated(m_Boss.isBossEliminated());
		m_ItemArray[i].Update();
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_ItemArray[i].GetRect(), ox, oy))
		{
			m_ItemArray[i].CollisionStage(ox, oy);
		}
	}
}

/**
 * �`��
 *
 */
void CStage1_Boss::Render(void) {
	//�X�e�[�W�̕`��
	m_Stage.Render();

	//�h�A�̕`��
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		if (m_ItemArray[i].GetType() == BOSS_DOOR)
		{
			m_ItemArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
		}
	}

	//�v���C���[�̕`��
	m_Player.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());

	//�G�̕`��
	m_Boss.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());

	//�A�C�e���̕`��
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		if (m_ItemArray[i].GetType() != BOSS_DOOR)
		{
			m_ItemArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
		}
	}

	//�G�t�F�N�g�̕`��
	m_EffectManager.Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());

	CGraphicsUtilities::RenderString(500 - m_Stage.GetScrollX(), 300 - m_Stage.GetScrollY(), "W,A,S,D�ňړ�");

	//�v���C���[�̏�ԕ`��
	m_Player.RenderStatus();

	CGraphicsUtilities::RenderString(10, 10, "�Q�[�����");
	CGraphicsUtilities::RenderString(10, 40, "F2�L�[�ŃQ�[���N���A�AF3�L�[�ŃQ�[���I�[�o�[");
	if (m_Menu.IsShow()) {
		m_Menu.Render();
	}
}

/**
 * �f�o�b�O�`��
 *
 */
void CStage1_Boss::RenderDebug(void) {
	//�X�e�[�W�f�o�b�O�`��
	m_Stage.RenderDebug();
	//�v���C���[�f�o�b�O�`��
	m_Player.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	//�G�̃f�o�b�O�`��
	m_Boss.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());

	//�A�C�e���̃f�o�b�O�`��
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_ItemArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}

	//�G�t�F�N�g�̃f�o�b�O�`��
	m_EffectManager.RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
}

/**
 * ���
 *
 */
void CStage1_Boss::Release(void) {
	//�X�e�[�W�̊J��
	m_Stage.Release(m_NowSceneNo);
	//�v���C���[�̊J��
	m_Player.Release();

	//�{�X�̊J��
	m_Boss.Release();

	//�A�C�e���̉��
	if (m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}

	//�G�t�F�N�g�̉��
	m_EffectManager.Release();
	m_Menu.Release();

	m_BGMManager.Release();
}