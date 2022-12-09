#include	"GameDefine.h"
#include	"Stage1.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
//extern int						gChangeScene;

/**
 * �f�X�g���N�^
 *
 */
CGame::~CGame(){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CGame::Load(){
	//�v���C���[�̑f�ޓǂݍ���
	m_Player.Load();
	//�X�e�[�W�̑f�ޓǂݍ���
	m_Stage.Load("1-1MAP_noWall.txt",m_NowSceneNo);
	//�G�������m��
	m_EnemyArray = new CEnemy[m_Stage.GetEnemyCount()];
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
void CGame::Initialize(){
	
	Load();
	//�v���C���[�̏�ԏ�����
	m_Player.Initialize();
	m_Player.SetPlayerPos(m_Stage.GetIniPlayerPos().x, m_Stage.GetIniPlayerPos().y);
	//�X�e�[�W�̏�ԏ�����
	m_Stage.Initialize(m_EnemyArray,m_ItemArray);
	//�G�t�F�N�g�̏�ԏ�����
	m_EffectManager.Initialize();
	//�v���C���[�ƓG�ɃG�t�F�N�g�N���X�̐ݒ�
	m_Player.SetEffectManager(&m_EffectManager);
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].SetEffectManager(&m_EffectManager);
	}
	char* m_pTitle = "�|�[�Y";
	char* m_pMenuString[TEXTCOUNT_MAX] = {
						"�Q�[���ɖ߂�",
						"�X�e�[�W�I����ʂ�",
	};
	// �|�[�Y�@�\�ɕK�v�Ȓl��n���B	
	m_Menu.Create(m_pTitle, m_pMenuString, TEXTCOUNT_MAX);
	m_Alpha = 0;

	m_intervalFire = FIREBAR_INTERVAL;
	m_bFire = false;

	//�X�e�[�W�ɃG�t�F�N�g�N���X�̐ݒ�
	m_Stage.SetEffectManager(&m_EffectManager);
}

/**
 * �X�V
 *
 */
void CGame::Update(void){
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
				m_SceneNo = SCENENO_GAME_STAGE1_BOSS;
			}
		}
		return;
	}

	//�v���C���[�̍X�V
	m_Player.Update();
	//�X�e�[�W�ƃv���C���[�̓����蔻��
	StgCollPlayer();

	float wx = m_Stage.GetScrollX();
	float wy = m_Stage.GetScrollY();

	StgCollBullet();

	//�G�̍X�V
	StgCollEne();

	//�A�C�e���̍X�V
	StgCollItm();


	//�����蔻��̎��s
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_Player.CollisionEnemy_1(m_EnemyArray[i]);
	}

	//Enemy1�Ƀv���C���[�̍��W���Z�b�g
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].SetPlayerPos(Vector2(m_Player.GetPosX(), m_Player.GetPosY()));
	}

	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		m_Player.ColisionItem(m_ItemArray[i]);
		m_Player.CollisionAttackItem(m_ItemArray[i]);
	}

	//�X�e�[�W�̍X�V
	m_Stage.Update(m_Player);
	if (m_Player.IsAttack())
	{
		for (int i = 0;i < PLAYERSHOT_COUNT; i++)
		{
			m_Stage.StageAttackCollision(m_Player.GetLaserRect(i));
		}
	}

	//�G�t�F�N�g�̍X�V
	m_EffectManager.Update();

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

void CGame::StgCollPlayer() {
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

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_Player.GetLaserRect(i), ox, oy))
		{
			if (m_Player.IsLaser()) {
				m_Player.SetWallLaser(i);
			}
		}

		//���ƒe�̔���
		if (m_Player.GetNatuLaser(i) == FROST)
		{
			for (int i = 0; i < PLAYERSHOT_COUNT; i++)
			{
				m_Stage.CollisionFreezeWater(m_Player.GetLaserRect(i));
			}
		}
		//�X�ƒe�̔���
		if (m_Player.GetNatuLaser(i) == FIRE)
		{
			for (int i = 0; i < PLAYERSHOT_COUNT; i++)
			{
				m_Stage.CollisionIceFroe(m_Player.GetLaserRect(i));
			}
		}
	}

	
	//TODO::else�̔���ŃX�N���[���l���������������蔻����ω�����
	//���̔���
	if (m_bFire)
	{
		bool	bFireEffect;
		if (m_intervalFire == FIREBAR_INTERVAL)
			bFireEffect = true;
		else
			bFireEffect = false;

		if (m_Stage.FireBar(CRectangle(-m_Stage.GetScrollX() + m_Player.GetRect().Left, -m_Stage.GetScrollY() + m_Player.GetRect().Top, -m_Stage.GetScrollX() + m_Player.GetRect().GetCenter().x - 10, -m_Stage.GetScrollY() + m_Player.GetRect().Bottom), bFireEffect))
		{
			m_Player.PlayerDamage(false);
		}
		if (m_Stage.FireBar(CRectangle(-m_Stage.GetScrollX() + m_Player.GetRect().GetCenter().x + 10, -m_Stage.GetScrollY() + m_Player.GetRect().Top, -m_Stage.GetScrollX() + m_Player.GetRect().Right, -m_Stage.GetScrollY() + m_Player.GetRect().Bottom), bFireEffect))
		{
			m_Player.PlayerDamage(true);
		}

		if (m_intervalFire <= 0)
		{
			m_bFire = false;
			m_intervalFire = FIREBAR_INTERVAL;
		}
		else
			m_intervalFire -= 1;
	}
	else
	{
		//m_Stage.FireBar(CRectangle(-m_Stage.GetScrollX() + m_Player.GetRect().Left, -m_Stage.GetScrollY() + m_Player.GetRect().Top, -m_Stage.GetScrollX() + m_Player.GetRect().Left + 1, -m_Stage.GetScrollY() + m_Player.GetRect().Bottom));
		//m_Stage.FireBar(CRectangle(-m_Stage.GetScrollX() + m_Player.GetRect().Right - 1, -m_Stage.GetScrollY() + m_Player.GetRect().Top, -m_Stage.GetScrollX() + m_Player.GetRect().Right, -m_Stage.GetScrollY() + m_Player.GetRect().Bottom));

		if (m_intervalFire <= 0)
		{
			m_bFire = true;
			m_intervalFire = FIREBAR_INTERVAL;
		}
		else
			m_intervalFire -= 1;
	}

}

void CGame::StgCollBullet() {
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

void CGame::StgCollEne() {
	float PPosX = m_Player.GetPosX() + 30;
	float PPosY = m_Player.GetPosY() + 30;

	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		m_EnemyArray[i].SetTargetPos(PPosX, PPosY);
		m_EnemyArray[i].Update(m_Stage.GetScrollX());
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_EnemyArray[i].GetRect(), ox, oy))
		{
			m_EnemyArray[i].CollisionStage(ox, oy);

			//�G�̒e�ƃX�e�[�W�̓����蔻��
			for (int j = 0; j < ENEMY_SHOT_COUNT; j++)
			{
				ox = 0, oy = 0;
				if (m_Stage.Collision(m_EnemyArray[i].ShotArrayRect(j), ox, oy))
				{
					m_EnemyArray[i].SetShotShow(false, j);
				}
			}
		}
	}
}

void CGame::StgCollItm() {
	for (int i = 0; i < m_Stage.GetItemCount(); i++)
	{
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
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
void CGame::Render(void){
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
	m_Player.Render(m_Stage.GetScrollX(),m_Stage.GetScrollY());

	//�G�̕`��
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}

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

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (m_Stage.Collision(m_Player.GetLaserRect(i)))
		{
			//TODO: �Β��̏���
			CRectangle rec = m_Player.GetLaserRect(i);

			CRectangle FireRec[3] = { CRectangle(rec.Left -= LASER_ATTACKWIDTH, rec.Top - 50, rec.Right, rec.Bottom - 60),
									  CRectangle(rec.Left, rec.Top - 5, rec.Right, rec.Bottom + 5),
									  CRectangle(rec.Left, rec.Top + 60, rec.Right, rec.Bottom + 70),
			};
			for (int j = 0; j < 3; j++)
			{
				MofU32 Color[3] = {
					MOF_COLOR_RED,
					MOF_COLOR_GREEN,
					MOF_COLOR_BLUE,
				};

				CGraphicsUtilities::RenderFillRect(FireRec[j], Color[j]);
			}
		}
	}

	CGraphicsUtilities::RenderString(10,10,"�Q�[�����");
	CGraphicsUtilities::RenderString(10,40,"F2�L�[�ŃQ�[���N���A�AF3�L�[�ŃQ�[���I�[�o�[");
	if (m_Menu.IsShow()) {
		m_Menu.Render();
	}
}

/**
 * �f�o�b�O�`��
 *
 */
void CGame::RenderDebug(void){
	//�X�e�[�W�f�o�b�O�`��
	m_Stage.RenderDebug();
	//�v���C���[�f�o�b�O�`��
	m_Player.RenderDebug(m_Stage.GetScrollX(),m_Stage.GetScrollY());
	//�G�̃f�o�b�O�`��
	for (int i = 0; i < m_Stage.GetEnemyCount(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
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
void CGame::Release(void){
	//�X�e�[�W�̊J��
	m_Stage.Release(m_NowSceneNo);
	//�v���C���[�̊J��
	m_Player.Release();
	//�G�̉��
	if (m_EnemyArray)
	{
		delete[] m_EnemyArray;
		m_EnemyArray = NULL;
	}
	//�A�C�e���̉��
	if (m_ItemArray)
	{
		delete[] m_ItemArray;
		m_ItemArray = NULL;
	}
	
	//�G�t�F�N�g�̉��
	m_EffectManager.Release();
	m_Menu.Release();
}