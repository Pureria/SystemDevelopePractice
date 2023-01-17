#include	"GameDefine.h"
#include	"Stage1.h"

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
	m_BaseStage.Load("ChipData/1-1MAP_noWall.txt",m_NowSceneNo);
	//m_BaseStage.Load("ChipData/New1-1_��.txt", m_NowSceneNo);
	//�G�������m��
	m_EnemyArray	= new CEnemy[m_BaseStage.GetEnemy1Count()];
	m_Enemy2Array	= new CEnemy_2[m_BaseStage.GetEnemy2Count()];
	//�A�C�e���������m��
	m_ItemArray		= new CItem[m_BaseStage.GetItemCount()];
	//�G�t�F�N�g�̑f�ޓǂݍ���
	m_EffectManager.Load();	

	//BGM�̓ǂݍ���
	m_BGMManager.Load();
	
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
	m_Player.SetSEManager(&m_pSEManager);
	m_Player.SetPlayerPos(m_BaseStage.GetIniPlayerPos().x, m_BaseStage.GetIniPlayerPos().y);
	//�X�e�[�W�̏�ԏ�����
	m_BaseStage.Initialize(m_EnemyArray, m_Enemy2Array, m_ItemArray);
	//�G�t�F�N�g�̏�ԏ�����
	m_EffectManager.Initialize();
	//�v���C���[�ƓG�ɃG�t�F�N�g�N���X�̐ݒ�
	m_Player.SetEffectManager(&m_EffectManager);
	for (int i = 0; i < m_BaseStage.GetEnemy1Count(); i++)
	{
		m_EnemyArray[i].SetEffectManager(&m_EffectManager);
	}
	char* m_pTitle = "�|�[�Y";
	char* m_pMenuString[TEXTCOUNT_MAX] = {
						"�Q�[���ɖ߂�",
						"�X�e�[�W�I����ʂ�",
	};

	m_Menu.Create(m_pTitle, m_pMenuString, TEXTCOUNT_MAX);

	m_intervalFire = FIREBAR_INTERVAL;
	m_bFire = false;

	//Enemy2�ɃG�t�F�N�g�N���X�̐ݒ�
	for (int i = 0; i < m_BaseStage.GetEnemy2Count(); i++)
	{
		m_Enemy2Array[i].SetEffectManager(&m_EffectManager);
		m_Enemy2Array[i].SetSEManager(&m_pSEManager);
	}

	//�X�e�[�W�ɃG�t�F�N�g�N���X�̐ݒ�
	m_BaseStage.SetEffectManager(&m_EffectManager);
	//�X�e�[�W��SE�}�l�[�W���[�̐ݒ�
	m_BaseStage.SetSEManager(&m_pSEManager);

	//BGM�̏�����
	m_BGMManager.Initialize();
	m_BGMManager.BGMPlayer(BGM_STAGE1);
}

/**
 * �X�V
 *
 */
void CStage1::Update(void){
#pragma region Fade
	if (m_bFadeIn)
	{
		m_NowTime += CUtilities::GetFrameSecond();
		m_Alpha = (int)m_Function.Animation(0, FADE_TIME, 255, 0, m_NowTime);
		if (m_Alpha <= 0)
			m_bFadeIn = false;
	}

	if (m_bFadeOut)
	{
		m_NowTime += CUtilities::GetFrameSecond();
		m_Alpha = (int)m_Function.Animation(0, FADE_TIME, 0, 255, m_NowTime);
		if (m_Alpha >= 255)
		{
			m_bEnd = true;
			m_SceneNo = SCENENO_GAMECLEAR;
		}
		return;
	}
#pragma endregion

	UpdateExitkey();

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
		for (int i = 0; i < m_BaseStage.GetItemCount(); i++)
		{
			if (m_ItemArray[i].GetType() != BOSS_DOOR)
				continue;

			m_ItemArray[i].StartDoorAnimation();

			if (m_ItemArray[i].IsEndDoorAnimation())
			{
				m_bFadeOut = true;
				m_Alpha = 0;
				m_NowTime = 0;
				m_PlayerHp = m_Player.GetHp();
				SetSaveToFile();
				break;
			}
		}
		return;
	}

	//�v���C���[�̍X�V
	m_Player.Update();
	//�X�e�[�W�ƃv���C���[�̓����蔻��
	StgCollPlayer();

	float wx = m_BaseStage.GetScrollX();
	float wy = m_BaseStage.GetScrollY();

	StgCollBullet();

	//�G�̍X�V
	StgCollEne();

	//�A�C�e���̍X�V
	StgCollItm();

	//�X�e�[�W�̍X�V
	m_BaseStage.Update(m_Player);

	//�G�t�F�N�g�̍X�V
	m_EffectManager.Update();

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
		m_SceneNo = SCENENO_GAMEOVER;
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
	if (m_BaseStage.Collision(m_Player.GetRect(), ox, oy))
	{
		m_Player.CollisionStage(ox, oy);
	}

	if (!m_Player.IsJump())
	{
		if (m_BaseStage.CollisionLift(m_Player.GetRect(), ox, oy))
		{
			m_Player.CollisionStage(ox, oy);
		}
	}

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_Player.GetLaserShotShow(i)) { continue; }

		ox = 0, oy = 0;
		if (m_BaseStage.Collision(m_Player.GetLaserRect(i), ox, oy))
		{
			m_Player.SetWallLaser(i,true);
		}

		if (m_Player.IsLaser(i)) {
			m_BaseStage.CollisionCrack(m_Player.GetLaserRect(i));
		}

		//TODO: ���ƒe�̔���
		if (m_Player.GetNatuLaser(i) == FROST)
		{
			m_BaseStage.CollisionFreezeWater(m_Player.GetLaserRect(i),m_Player.GetRect());
		}

		//TODO: �X�ƒe�̔���
		if (m_Player.GetNatuLaser(i) == FIRE)
		{
			m_BaseStage.CollisionIceFroe(m_Player.GetLaserRect(i));
		}
	}

	//TODO: �C��ƃv���C���[�̓����蔻��
	for (int i = 0; i < m_BaseStage.GetEnemy1Count(); i++)
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

		if (m_BaseStage.FireBar(CRectangle(-m_BaseStage.GetScrollX() + m_Player.GetRect().Left, -m_BaseStage.GetScrollY() + m_Player.GetRect().Top, -m_BaseStage.GetScrollX() + m_Player.GetRect().GetCenter().x - 10, -m_BaseStage.GetScrollY() + m_Player.GetRect().Bottom), bFireEffect))
		{
			m_Player.PlayerDamage(false, 5);
		}
		if (m_BaseStage.FireBar(CRectangle(-m_BaseStage.GetScrollX() + m_Player.GetRect().GetCenter().x + 10, -m_BaseStage.GetScrollY() + m_Player.GetRect().Top, -m_BaseStage.GetScrollX() + m_Player.GetRect().Right, -m_BaseStage.GetScrollY() + m_Player.GetRect().Bottom), bFireEffect))
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
		for (int i = 0; i < SE_COUNT; i++)
		{
			if (m_pSEManager.GetNowSetSE() == SE_BURNER &&m_pSEManager.IsPlaySE())
				m_pSEManager.StopSE();
		}

		m_EffectManager.Stop(EFC_FIREBAR_TOP);
		m_EffectManager.Stop(EFC_FIREBAR_BOTTOM);

		if (m_intervalFire <= 0)
		{
			m_bFire = true;
			m_intervalFire = FIREBAR_INTERVAL;
		}
		else
			m_intervalFire -= 1;
	}


	if (m_BaseStage.CollisionWater(m_Player.GetRect()))
	{
		m_Player.PlayerDamage(1);
	}

}

void CStage1::StgCollBullet() {

	float x, y;
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (m_BaseStage.GetMapChipPos(m_Player.GetLaserRect(i), x, y, false)) {
			m_Player.SetMapChipPos(Vector2(x, y), i);
		}
		if (m_Player.GetLaserShotShow(i)) {
			m_BaseStage.StageAttackCollision(m_Player.GetLaserRect(i));
		}
	}

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		float ox = 0, oy = 0;
		if (!m_Player.GetNormalShow(i))
		{
			continue;
		}

		CRectangle psrec = m_Player.GetNormalRect(i);
		if (m_BaseStage.StageAttackCollision(psrec))
		{
			m_Player.SetNormalShotShow(false, i);
			continue;
		}

		//��̔���
		psrec.Bottom = psrec.Top + 1;
		psrec.Expansion(-15, 0);
		if (m_BaseStage.Collision(psrec))
		{
			m_Player.ShotRefTop(i);
			for (int j = 0; j < SE_COUNT; j++)
			{
				if (m_pSEManager.IsPlaySE())
					continue;
				m_pSEManager.SEPlayer(SE_WALL_CONTACT);
				break;
			}
		}

		//���̔���
		psrec = m_Player.GetNormalRect(i);
		psrec.Top = psrec.Bottom - 1;
		psrec.Expansion(-15, 0);
		if (m_BaseStage.Collision(psrec))
		{
			m_Player.ShotRefBottom(i);
			for (int j = 0; j < SE_COUNT; j++)
			{
				if (m_pSEManager.IsPlaySE())
					continue;
				m_pSEManager.SEPlayer(SE_WALL_CONTACT);
				break;
			}
		}

		//���̔���
		psrec = m_Player.GetNormalRect(i);
		psrec.Right = psrec.Left + 1;
		psrec.Expansion(0, -15);
		if (m_BaseStage.Collision(psrec))
		{
			m_Player.ShotRefLeft(i);
			for (int j = 0; j < SE_COUNT; j++)
			{
				if (m_pSEManager.IsPlaySE())
					continue;
				m_pSEManager.SEPlayer(SE_WALL_CONTACT);
				break;
			}
		}

		//�E�̔���
		psrec = m_Player.GetNormalRect(i);
		psrec.Left = psrec.Right - 1;
		psrec.Expansion(0, -15);
		if (m_BaseStage.Collision(psrec))
		{
			m_Player.ShotRefRight(i);
			for (int j = 0; j < SE_COUNT; j++)
			{
				if (m_pSEManager.IsPlaySE())
					continue;
				m_pSEManager.SEPlayer(SE_WALL_CONTACT);
				break;
			}
		}
	}
}

void CStage1::StgCollEne() {
	float PPosX = m_Player.GetPosX() + 30;
	float PPosY = m_Player.GetPosY() + 30;

	for (int i = 0; i < m_BaseStage.GetEnemy1Count(); i++)
	{
		if (!m_EnemyArray[i].GetShow())
		{
			continue;
		}
		m_EnemyArray[i].SetTime(Time());
		m_Player.CollisionEnemy(m_EnemyArray[i], m_EnemyArray[i].GetEnemyType());
		m_EnemyArray[i].Update(m_BaseStage.GetScrollX());
		float ox = 0, oy = 0;
		if (m_BaseStage.Collision(m_EnemyArray[i].GetRect(), ox, oy))
		{
			m_EnemyArray[i].CollisionStage(ox, oy);

			//TODO: �G�̒e�ƃX�e�[�W�̓����蔻��
			for (int j = 0; j < ENEMY_SHOT_COUNT; j++)
			{
				if (m_BaseStage.Collision(m_EnemyArray[i].ShotArrayRect(j)))
				{
					m_EnemyArray[i].SetShotShow(false, j);
				}
			}
		}
	}

	for (int i = 0; i < m_BaseStage.GetEnemy2Count(); i++)
	{
		if (!m_Enemy2Array[i].GetShow())
		{
			continue;
		}
		if (!m_BaseStage.Collision(m_Enemy2Array[i].GetLedgeCheckRect()) && !m_Enemy2Array[i].GetKnockback())
		{
			m_Enemy2Array[i].Flip();
		}
		m_Player.CollisionEnemy(m_Enemy2Array[i], m_Enemy2Array[i].GetEnemyType());
		m_Enemy2Array[i].SetTime(Time());
		m_Enemy2Array[i].SetTargetPos(PPosX, PPosY);
		m_Enemy2Array[i].Update(m_BaseStage.GetScrollX());
		float ox = 0, oy = 0;
		if (m_BaseStage.Collision(m_Enemy2Array[i].GetRect(), ox, oy))
		{
			m_Enemy2Array[i].CollisionStage(ox, oy);

			//TODO: �G�̒e�ƃX�e�[�W�̓����蔻��
			for (int j = 0; j < ENEMY_SHOT_COUNT; j++)
			{
				if (m_BaseStage.Collision(m_Enemy2Array[i].ShotArrayRect(j)))
				{
					m_Enemy2Array[i].SetShotShow(false, j);
				}
			}
		}

		if (m_Enemy2Array[i].GetFallFlg())
			continue;
	}
}

void CStage1::StgCollItm() {
	for (int i = 0; i < m_BaseStage.GetItemCount(); i++)
	{
		if (!m_ItemArray[i].GetShow())
		{
			continue;
		}
		m_Player.ColisionItem(m_ItemArray[i]);
		m_Player.CollisionAttackItem(m_ItemArray[i]);
		m_ItemArray[i].SetBossEliminated(true);
		m_ItemArray[i].Update();
		float ox = 0, oy = 0;
		if (m_BaseStage.Collision(m_ItemArray[i].GetRect(), ox, oy))
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
	//TODO: ���Ɠ����蔻��
	if (eneRect.CollisionRect(brec))
	{
		re = true;
		oy += eneRect.Top - playerRect.Bottom;
		playerRect.Top += eneRect.Top - brec.Bottom;
		playerRect.Bottom += eneRect.Top - brec.Bottom;
	}

	//TODO: ��̓����蔻��
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

	//TODO: ���E�̓����蔻��
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
	m_BaseStage.BackTexRender();
	m_Player.ShotRender(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
	m_BaseStage.Render();


	//�h�A�̕`��
	for (int i = 0; i < m_BaseStage.GetItemCount(); i++)
	{
		if (m_ItemArray[i].GetType() == BOSS_DOOR)
		{
			m_ItemArray[i].Render(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
		}
	}

	//�v���C���[�̕`��
	m_Player.Render(m_BaseStage.GetScrollX(),m_BaseStage.GetScrollY());

	//�G�̕`��
	for (int i = 0; i < m_BaseStage.GetEnemy1Count(); i++)
	{
		m_EnemyArray[i].Render(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
	}

	//�G2�̕`��
	for (int i = 0; i < m_BaseStage.GetEnemy2Count(); i++)
	{
		m_Enemy2Array[i].Render(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
	}

	//�A�C�e���̕`��
	for (int i = 0; i < m_BaseStage.GetItemCount(); i++)
	{
		if (m_ItemArray[i].GetType() != BOSS_DOOR)
		{
			m_ItemArray[i].Render(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
		}
	}

	//�G�t�F�N�g�̕`��
	m_EffectManager.Render(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());

	//�v���C���[�̏�ԕ`��
	m_Player.RenderStatus();

	if (m_Menu.IsShow()) {
		m_Menu.Render();
	}

	CGraphicsUtilities::RenderFillRect(0, 0, g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), MOF_ARGB(m_Alpha, 0, 0, 0));
}

/**
 * �f�o�b�O�`��
 *
 */
void CStage1::RenderDebug(void){
	//�X�e�[�W�f�o�b�O�`��
	m_BaseStage.RenderDebug();
	//�v���C���[�f�o�b�O�`��
	m_Player.RenderDebug(m_BaseStage.GetScrollX(),m_BaseStage.GetScrollY());
	//�G�̃f�o�b�O�`��
	for (int i = 0; i < m_BaseStage.GetEnemy1Count(); i++)
	{
		m_EnemyArray[i].RenderDebug(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
	}
	//�G2�̃f�o�b�O�`��
	for (int i = 0; i < m_BaseStage.GetEnemy2Count(); i++)
	{
		m_Enemy2Array[i].RenderDebug(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
	}
	//�A�C�e���̃f�o�b�O�`��
	for (int i = 0; i < m_BaseStage.GetItemCount(); i++)
	{
		m_ItemArray[i].RenderDebug(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
	}

	//�G�t�F�N�g�̃f�o�b�O�`��
	m_EffectManager.RenderDebug(m_BaseStage.GetScrollX(), m_BaseStage.GetScrollY());
}

/**
 * ���
 *
 */
void CStage1::Release(void){
	//�X�e�[�W�̊J��
	m_BaseStage.Release(m_NowSceneNo);
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
	m_BGMManager.Release();
}