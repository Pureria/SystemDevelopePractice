#include	"GameDefine.h"
#include	"Stage1.h"

//�ύX����V�[��(�O���Q�ƁA���̂�GameApp.cpp)
//extern int						gChangeScene;

/**
 * �f�X�g���N�^
 *
 */
CStage1::~CStage1(){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`����ǂݍ��ށB
 */
bool CStage1::Load(){
	//�v���C���[�̑f�ޓǂݍ���
	m_Player.Load();
	//�X�e�[�W�̑f�ޓǂݍ���
	m_Stage.Load("ChipData/1-1MAP_noWall.txt",m_NowSceneNo);
	//�G�������m��
	int a = m_Stage.GetEnemy1Count();
	m_EnemyArray = new CEnemy[m_Stage.GetEnemy1Count()];
	a = m_Stage.GetEnemy2Count();
	m_Enemy2Array = new CEnemy_2[m_Stage.GetEnemy2Count()];
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
void CStage1::Initialize(){
	
	Load();
	//�v���C���[�̏�ԏ�����
	m_Player.Initialize();
	m_Player.SetPlayerPos(m_Stage.GetIniPlayerPos().x, m_Stage.GetIniPlayerPos().y);
	//�X�e�[�W�̏�ԏ�����
	m_Stage.Initialize(m_EnemyArray, m_Enemy2Array, m_ItemArray);
	//�G�t�F�N�g�̏�ԏ�����
	m_EffectManager.Initialize();
	//�v���C���[�ƓG�ɃG�t�F�N�g�N���X�̐ݒ�
	m_Player.SetEffectManager(&m_EffectManager);
	for (int i = 0; i < m_Stage.GetEnemy1Count(); i++)
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
void CStage1::Update(void){
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


	//�����蔻��̎��s�E�v���C���[�̍��W���Z�b�g
	for (int i = 0; i < m_Stage.GetEnemy1Count(); i++)
	{
		m_Player.CollisionEnemy_1(m_EnemyArray[i]);
		m_EnemyArray[i].SetPlayerPos(Vector2(m_Player.GetPosX(), m_Player.GetPosY()));
	}

	//�����蔻��̎��s�EEnemy2�Ƀv���C���[�̍��W���Z�b�g
	for (int i = 0; i < m_Stage.GetEnemy2Count(); i++)
	{
		//TODO::Player��CollisionEnemy2�̒ǉ�
		if (!m_Enemy2Array[i].GetShow())
			continue;

		if (m_Enemy2Array[i].GetRect().CollisionRect(m_Player.GetRect()))
		{
			if (m_Enemy2Array[i].GetPos().x > m_Player.GetPosX())
			{
				//TODO::�_���[�W�ʂ͂��Ƃ���EnemyDefine�Ɏ�������
				m_Player.PlayerDamage(true,10);
			}
			else
			{
				m_Player.PlayerDamage(false, 10);
			}
		}

		//�e�Ƃ̔���
		for (int j = 0; j < ENEMY_SHOT_COUNT; j++)
		{
			if (!m_Enemy2Array[i].GetShotShow(j))
				continue;

			if (m_Enemy2Array[i].GetShotRect(j).CollisionRect(m_Player.GetRect()))
			{
				m_Enemy2Array[i].SetShotShow(false, j);
				if (m_Enemy2Array[i].GetShotPos(j).x > m_Player.GetPosX())
				{
					//TODO::��Ɠ��l�Ƀ_���[�W�ʂ�EnemyDefine�Ɏ�������
					m_Player.PlayerDamage(true, 10);
				}
				else
				{
					m_Player.PlayerDamage(false, 10);
				}
			}
		}

		//TODO::�G�ƃv���C���[�̒e�̓����蔻��
		//TODO::�v���C���[�̒e�ƓG�̒e�̓����蔻��


		m_Enemy2Array[i].SetTargetPos(m_Player.GetPosX(), m_Player.GetPosY());
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

void CStage1::StgCollPlayer() {
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
		if (!m_Player.GetLaserShotShow(i)) { continue; }

		ox = 0, oy = 0;
		if (m_Stage.Collision(m_Player.GetLaserRect(i), ox, oy))
		{
			m_Player.SetWallLaser(i);
		}

		//���ƒe�̔���
		if (m_Player.GetNatuLaser(i) == FROST)
		{
			m_Stage.CollisionFreezeWater(m_Player.GetLaserRect(i));
		}

		//�X�ƒe�̔���
		if (m_Player.GetNatuLaser(i) == FIRE)
		{
			m_Stage.CollisionIceFroe(m_Player.GetLaserRect(i));
		}
	}

	//�C��ƃv���C���[�̓����蔻��
	for (int i = 0; i < m_Stage.GetEnemy1Count(); i++)
	{
		ox = 0; oy = 0;
		if (EnemyOnPlayer(m_EnemyArray[i].GetRect(), m_Player.GetRect(), ox, oy))
		{
			m_Player.CollisionStage(ox, oy);
		}

	}

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
			m_Player.PlayerDamage(false, 5);
		}
		if (m_Stage.FireBar(CRectangle(-m_Stage.GetScrollX() + m_Player.GetRect().GetCenter().x + 10, -m_Stage.GetScrollY() + m_Player.GetRect().Top, -m_Stage.GetScrollX() + m_Player.GetRect().Right, -m_Stage.GetScrollY() + m_Player.GetRect().Bottom), bFireEffect))
		{
			m_Player.PlayerDamage(true, 5);
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

void CStage1::StgCollBullet() {
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		float ox = 0, oy = 0;
		if (!m_Player.IsLaser()) {
			if (!m_Player.GetNormalShow(i))
			{
				continue;
			}

			CRectangle psrec = m_Player.GetNormalRect(i);
			if (m_Stage.StageAttackCollision(psrec))
			{
				m_Player.SetNormalShotShow(false, i);
				continue;
			}

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

void CStage1::StgCollEne() {
	float PPosX = m_Player.GetPosX() + 30;
	float PPosY = m_Player.GetPosY() + 30;

	for (int i = 0; i < m_Stage.GetEnemy1Count(); i++)
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
				if (m_Stage.Collision(m_EnemyArray[i].ShotArrayRect(j)))
				{
					m_EnemyArray[i].SetShotShow(false, j);
				}
			}
		}
	}

	for (int i = 0; i < m_Stage.GetEnemy2Count(); i++)
	{
		if (!m_Enemy2Array[i].GetShow())
		{
			continue;
		}
		m_Enemy2Array[i].SetTargetPos(PPosX, PPosY);
		m_Enemy2Array[i].Update(m_Stage.GetScrollX());
		float ox = 0, oy = 0;
		if (m_Stage.Collision(m_Enemy2Array[i].GetRect(), ox, oy))
		{
			m_Enemy2Array[i].CollisionStage(ox, oy);

			//�G�̒e�ƃX�e�[�W�̓����蔻��
			for (int j = 0; j < ENEMY_SHOT_COUNT; j++)
			{
				if (m_Stage.Collision(m_Enemy2Array[i].ShotArrayRect(j)))
				{
					m_Enemy2Array[i].SetShotShow(false, j);
				}
			}
		}

		if (m_Enemy2Array[i].GetFallFlg())
		{
			continue;
		}
		if (!m_Stage.Collision(m_Enemy2Array[i].GetLedgeCheckRect()))
		{
			m_Enemy2Array[i].Flip();
		}
	}
}

void CStage1::StgCollItm() {
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

bool CStage1::EnemyOnPlayer(CRectangle eneRect, CRectangle playerRect, float& ox, float& oy)
{
	bool re = false;

	CRectangle brec = playerRect;
	brec.Top = brec.Bottom - 1;
	brec.Expansion(-6, -0);
	//���Ɠ����蔻��
	if (eneRect.CollisionRect(brec))
	{
		re = true;
		oy += eneRect.Top - playerRect.Bottom;
		playerRect.Top += eneRect.Top - brec.Bottom;
		playerRect.Bottom += eneRect.Top - brec.Bottom;
	}

	//��̓����蔻��
	CRectangle trec = playerRect;
	trec.Bottom = trec.Top + 1;
	trec.Expansion(-12, 0);
	if (eneRect.CollisionRect(trec))
	{
		re = true;
		oy += eneRect.Bottom - trec.Top;
		playerRect.Top += eneRect.Bottom - trec.Top;
		playerRect.Bottom += eneRect.Bottom - trec.Top;
	}

	//���E�̓����蔻��
	CRectangle lrec = playerRect;
	lrec.Right = lrec.Left + 1;
	lrec.Expansion(0, -12);
	CRectangle rrec = playerRect;
	rrec.Left = rrec.Right - 1;
	rrec.Expansion(0, -12);

	if (eneRect.CollisionRect(lrec))
	{
		re = true;
		ox += eneRect.Right - lrec.Left;
		playerRect.Left += eneRect.Right - lrec.Left;
		playerRect.Right += eneRect.Right - lrec.Left;
	}
	else if (eneRect.CollisionRect(rrec))
	{
		re = true;
		ox += eneRect.Left - rrec.Right;
		playerRect.Left += eneRect.Left - rrec.Right;
		playerRect.Right += eneRect.Left - rrec.Right;
	}

	return re;
}

/**
 * �`��
 *
 */
void CStage1::Render(void){
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
	for (int i = 0; i < m_Stage.GetEnemy1Count(); i++)
	{
		m_EnemyArray[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}

	//�G2�̕`��
	for (int i = 0; i < m_Stage.GetEnemy2Count(); i++)
	{
		m_Enemy2Array[i].Render(m_Stage.GetScrollX(), m_Stage.GetScrollY());
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
void CStage1::RenderDebug(void){
	//�X�e�[�W�f�o�b�O�`��
	m_Stage.RenderDebug();
	//�v���C���[�f�o�b�O�`��
	m_Player.RenderDebug(m_Stage.GetScrollX(),m_Stage.GetScrollY());
	//�G�̃f�o�b�O�`��
	for (int i = 0; i < m_Stage.GetEnemy1Count(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
	}
	//�G2�̃f�o�b�O�`��
	for (int i = 0; i < m_Stage.GetEnemy2Count(); i++)
	{
		m_Enemy2Array[i].RenderDebug(m_Stage.GetScrollX(), m_Stage.GetScrollY());
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
void CStage1::Release(void){
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
	//�G2�̊J��
	if (m_Enemy2Array)
	{
		delete[] m_Enemy2Array;
		m_Enemy2Array = NULL;
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