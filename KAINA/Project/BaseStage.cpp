#include	"BaseStage.h"
#include	<sys/stat.h>

/**
 * �R���X�g���N�^
 *
 */
CBaseStage::CBaseStage() :
m_ChipTexture() ,
m_BackTexture() ,
m_ChipSize(0) ,
m_XCount(0) ,
m_YCount(0) ,
m_pChipData(NULL) ,
m_ScrollX(0) ,
m_ScrollY(0),
m_EnemyTextureCount(0),
m_EnemyShotTextureCount(0),
m_pEnemyTexture(NULL),
m_pEnemyShotTexture(NULL),
m_Enemy1Count(0),
m_Enemy2_1Count(0),
m_Enemy2_2Count(0),
m_ItemTextureCount(0),
m_pItemTexture(NULL),
m_ItemCount(0),
m_IniPlayerPos(Vector2(0,0)),
m_bButtonRed(false),
m_bButtonBlue(false),
m_bButtonYellow(false){
}

/**
 * �f�X�g���N�^
 *
 */
CBaseStage::~CBaseStage(){
}

/**
 * �ǂݍ���
 * ���p����e�N�X�`���ƃX�e�[�W�t�@�C����ǂݍ��ށB
 *
 * ����
 * [in]			pName				�X�e�[�W�t�@�C���̖��O
 */
bool CBaseStage::Load(char* pName , int nowscene){
	//�e�L�X�g�t�@�C�����J��
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return false;
	}
	//�t�@�C���̑S�e�ʂ𒲂ׂ�
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//�t�@�C���T�C�Y�������̃��������m�ۂ���
	char* pBuffer = (char*)malloc(fSize + 1);
	//�t�@�C�������ׂăo�b�t�@�ɓǂݍ���
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	//strtok : ����1�̕����񂩂�A����2�̃g�[�N����������܂ł̕������擾
	//�@strtok (pBuffer, ",") : pBuffer�̕����񂩂� , ��������܂ł̕������擾
	//�e�N�X�`���̓ǂݍ���
	pstr = strtok(pBuffer, ",");
	if (!m_BackTexture.Load(pstr))
	{
		return false;
	}

	//strtok : 2��ڈȍ~�͕����̎w�肪�Ȃ��ꍇ�͑O�̎w�肵�������̑�������擾
	//strtok(NULL, ",") : ��قǎ擾����pBuffer�̑������� , ��������܂ł̕������擾
	pstr = strtok(NULL, ",");
	if (!m_ChipTexture.Load(pstr))
	{
		return false;
	}

	//�v���C���[�̏����ʒu
	m_IniPlayerPos.x = atoi(strtok(NULL, ","));
	m_IniPlayerPos.y = atoi(strtok(NULL, ","));

	//�`�b�v�T�C�Y
	//atof : �����̕������float(�����^)�̒l�ɕϊ�����
	//float.Parse : atof
	m_ChipSize = atof(strtok(NULL, ","));

	//�}�b�v�̃`�b�v��
	//atof : �����̕������int(�����^)�̒l�ɕϊ�����
	//int.Parse : atof
	m_XCount = atoi(strtok(NULL, ","));
	m_YCount = atoi(strtok(NULL, ","));

	//�}�b�v�`�b�v�p�̃������m��
	m_pChipData = (char*)malloc(m_XCount * m_YCount);
	//������������Ӗ�
	//m_pChipData = new char[(m_XCount * m_YCount)];

	//�`�b�v�f�[�^�̓ǂݍ���
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pChipData[y * m_XCount + x] = atoi(strtok(NULL, ","));
		}
	}

	if (nowscene == SCENENO_GAME_STAGE1)
	{
		//�G�̃e�N�X�`���ǂݍ���
		pstr = strtok(NULL, ",");
		m_EnemyTextureCount = atoi(pstr);
		m_pEnemyTexture = new CTexture[m_EnemyTextureCount];
		for (int i = 0; i < m_EnemyTextureCount; i++)
		{
			pstr = strtok(NULL, ",");
			if (!m_pEnemyTexture[i].Load(pstr))
			{
				return false;
			}
		}

		//�G�̒e�̃e�N�X�`���ǂݍ���
		m_EnemyShotTextureCount = atoi(strtok(NULL, ","));
		//�e�̃e�N�X�`���̃��[�h
		m_pEnemyShotTexture = new CTexture[m_EnemyShotTextureCount];
		for (int i = 0; i < m_EnemyShotTextureCount; i++)
		{
			pstr = strtok(NULL, ",");
			if (!m_pEnemyShotTexture[i].Load(pstr))
				return false;
		}

		//�z�u�f�[�^�̓ǂݍ���
		m_pEnemyData = (char*)malloc(m_XCount * m_YCount);
		m_Enemy1Count = 0;
		m_Enemy2_1Count = 0;
		for (int y = 0; y < m_YCount; y++)
		{
			for (int x = 0; x < m_XCount; x++)
			{
				m_pEnemyData[y * m_XCount + x] = atoi(strtok(NULL, ","));
				if (m_pEnemyData[y * m_XCount + x] == 1)
				{
					m_Enemy1Count++;
				}
				else if (m_pEnemyData[y * m_XCount + x] == 2)
				{
					m_Enemy2_1Count++;
				}
				else if (m_pEnemyData[y * m_XCount + x] == 3)
				{
					m_Enemy2_2Count++;
				}
			}
		}
	}
	else if (nowscene == SCENENO_GAME_STAGE1_BOSS)
	{

	}

	//�A�C�e���̃e�N�X�`���ǂݍ���
	pstr = strtok(NULL, ",");
	m_ItemTextureCount = atoi(pstr);
	m_pItemTexture = new CTexture[m_ItemTextureCount];
	for (int i = 0; i < m_ItemTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!m_pItemTexture[i].Load(pstr))
		{
			return false;
		}
	}

	//�z�u�f�[�^�̓ǂݍ���
	m_pItemData = (char*)malloc(m_XCount * m_YCount);
	m_ItemCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			pstr = strtok(NULL, ",");
			m_pItemData[y * m_XCount + x] = atoi(pstr);
			if (m_pItemData[y * m_XCount + x] > 0)
			{
				m_ItemCount++;
			}
		}
	}

	//�t�@�C�������
	fclose(fp);
	free(pBuffer);
	return true;
}

/**
 * ������
 * �p�����[�^�[����W������������B
 */
void CBaseStage::Initialize(CEnemy* pEnemy,CEnemy_2* pEnemy2, CItem* pItem){
	m_ScrollX = 0;
	m_ScrollY = 0;
	ButtonCount = 0;
	NextBlockDel = 0;

	int n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�z�u�ԍ�
			//�ԍ�0�͔z�u���Ȃ�
			char on = m_pEnemyData[y * m_XCount + x] - 1;
			if (on != 0)
			{
				continue;
			}
			pEnemy[n].SetTexture(&m_pEnemyTexture[on],&m_pEnemyShotTexture[on]);
			pEnemy[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}

	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�z�u�ԍ�
			//�ԍ�0�͔z�u���Ȃ�
			char on = m_pEnemyData[y * m_XCount + x] - 1;
			if (on != 1)
			{
				continue;
			}
			pEnemy2[n].SetTexture(&m_pEnemyTexture[on], &m_pEnemyShotTexture[on]);
			pEnemy2[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}

	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�z�u�ԍ�
			//�ԍ�0�͔z�u���Ȃ�
			char on = m_pEnemyData[y * m_XCount + x] - 1;
			if (on != 2)
			{
				continue;
			}
			pEnemy2[m_Enemy2_1Count + n].SetTexture(&m_pEnemyTexture[on - 1], &m_pEnemyShotTexture[on - 1]);
			pEnemy2[m_Enemy2_1Count + n].SetFallFlg(true);
			pEnemy2[m_Enemy2_1Count + n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}

	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�z�u�ԍ�
			//�ԍ�0�͈ʒu���Ȃ�
			char on = m_pItemData[y * m_XCount + x] - 1;
			if (on < 0)
				continue;
			pItem[n].SetTexture(&m_pItemTexture[on]);
			pItem[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}

	
}

void CBaseStage::Initialize(CItem* pItem)
{
	m_ScrollX = 0;
	m_ScrollY = 0;
	ButtonCount = 0;
	NextBlockDel = 0;

	int n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�z�u�ԍ�
			//�ԍ�0�͈ʒu���Ȃ�
			char on = m_pItemData[y * m_XCount + x] - 1;
			if (on < 0)
				continue;
			pItem[n].SetTexture(&m_pItemTexture[on]);
			pItem[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}
}

/**
 * �X�V
 *
 * ����
 * [in]			pl					�v���C���[�A�X�N���[���̔���Ɏg�p
 */
void CBaseStage::Update(CPlayer& pl){
	//�v���C���[�̒Z�a�擾
	CRectangle prec = pl.GetRect();
	//�X�N���[���̕�
	float sw = CGraphicsUtilities::GetGraphics()->GetTargetWidth();
	float sh = CGraphicsUtilities::GetGraphics()->GetTargetHeight();
	//�X�e�[�W�S�̂̕�
	float stgw = m_ChipSize * m_XCount;
	float stgh = m_ChipSize * m_YCount;
	//���W����ʒ[�ɂ���Ă���i�e�[����200pixel�j�ꍇ�X�N���[�����s���ĕ␳����
	if (prec.Left - m_ScrollX < 800)
	{
		m_ScrollX -= 800 - (prec.Left - m_ScrollX);
		if (m_ScrollX <= 0)
		{
			m_ScrollX = 0;
		}
	}
	else if (prec.Right - m_ScrollX > sw - 800)
	{
		m_ScrollX += (prec.Right - m_ScrollX) - (sw - 800);
		if (m_ScrollX >= stgw - sw)
		{
			m_ScrollX = stgw - sw;
		}
	}

	if (prec.Top - m_ScrollY < 100)
	{
		m_ScrollY -= 100 - (prec.Top - m_ScrollY);
		if (m_ScrollY <= 0)
		{
			m_ScrollY = 0;
		}
	}
	else if (prec.Bottom - m_ScrollY > sh - 100)
	{
		m_ScrollY += (prec.Bottom - m_ScrollY) - (sh - 100);
		if (m_ScrollY >= stgh - sh)
		{
			m_ScrollY = stgh - sh;
		}
	}

	ButtonGimmic();
}

void CBaseStage::ButtonGimmic()
{
	if (m_bButtonRed)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			for (int y = 0; y < m_YCount; y++)
			{
				char cn = m_pChipData[y * m_XCount + x] - 1;
				if (cn == BUTTON_BLOCK_RED)
				{
					m_pChipData[y * m_XCount + x] = 0;
				}
			}
		}
		m_bButtonRed = false;
	}

	if (m_bButtonBlue)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			for (int y = 0; y < m_YCount; y++)
			{
				char cn = m_pChipData[y * m_XCount + x] - 1;
				if (cn == BUTTON_BLOCK_BLUE)
				{
					m_pChipData[y * m_XCount + x] = 0;
				}
			}
		}
		m_bButtonBlue = false;
	}

	if (m_bButtonYellow)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			for (int y = 0; y < m_YCount; y++)
			{
				char cn = m_pChipData[y * m_XCount + x] - 1;
				if (cn == BUTTON_BLOCK_YELLOW)
				{
					m_pChipData[y * m_XCount + x] = 0;
				}
			}
		}
		m_bButtonYellow = false;
	}
}


//�����蔻��
bool CBaseStage::Collision(CRectangle r) {
	//�����蔻�肷��Z�a�̍���ƉE���̃`�b�v�ʒu�����߂�
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;

	//�X�e�[�W�͈̔͊O�ɂ͂Ȃ�Ȃ��悤�ɂ���
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	//�����蔻��ȊO������Z�a�̍��ォ��E���͈̔͂̂ݓ����蔻����s��
	//����ȊO�̔ԍ��͓����邱�Ƃ͂Ȃ��̂Ŕ��肪�K�v�Ȃ�
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ�0�͓����蔻�肵�Ȃ�
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}

			//���t�g�̓����蔻��
			//if (cn == LIFT)
				//continue;

			if (cn == WATER)
				continue;

			if (cn == CRACK_STONE)
				continue;
			/*
			if (cn == BUTTON_RED || cn == BUTTON_BLUE || cn == BUTTON_YELLOW)
			{
				continue;
			}
			*/

			//�}�b�v�`�b�v�̒Z�a
			CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
			if (cr.CollisionRect(r))
			{
				return true;
			}
		}
	}
	return false;
}

bool CBaseStage::CollisionBoss1(CRectangle r) {
	//�����蔻�肷��Z�a�̍���ƉE���̃`�b�v�ʒu�����߂�
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;

	//�X�e�[�W�͈̔͊O�ɂ͂Ȃ�Ȃ��悤�ɂ���
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	//�����蔻��ȊO������Z�a�̍��ォ��E���͈̔͂̂ݓ����蔻����s��
	//����ȊO�̔ԍ��͓����邱�Ƃ͂Ȃ��̂Ŕ��肪�K�v�Ȃ�
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ�0�͓����蔻�肵�Ȃ�
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}

			//���t�g�̓����蔻��
			if (cn == LIFT)
				continue;

			if (cn == WATER)
				continue;

			if (cn == CRACK_STONE)
				continue;


			if (cn == BUTTON_RED || cn == BUTTON_BLUE || cn == BUTTON_YELLOW)
			{
				continue;
			}
			

			//�}�b�v�`�b�v�̒Z�a
			CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
			if (cr.CollisionRect(r))
			{
				if (cn == BUTTON_RED)
				{
					m_bButtonRed = true;
				}

				else if (cn == BUTTON_BLUE)
				{
					m_bButtonBlue = true;
				}

				else if (cn == BUTTON_YELLOW)
				{
					m_bButtonYellow = true;
				}
				return true;
			}
		}
	}
	return false;
}

bool CBaseStage::Collision(CRectangle r, float& ox, float& oy) {
	bool re = false;

	//�����蔻�肷��Z�a�̍���ƉE���̃`�b�v�ʒu�����߂�
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;

	//�X�e�[�W�͈̔͊O�ɂ͂Ȃ�Ȃ��悤�ɂ���
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	//�����蔻��ȊO������Z�a�̍��ォ��E���͈̔͂̂ݓ����蔻����s��
	//����ȊO�̔ԍ��͓����邱�Ƃ͂Ȃ��̂Ŕ��肪�K�v�Ȃ�
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ�0�͓����蔻�肵�Ȃ�
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}

			//���̓����蔻��
			if (cn == WATER)
			{
				continue;
			}

			if (cn == CRACK_STONE) {
				continue;
			}

			//�{�^���̓����蔻��
			if (cn == BUTTON_RED || cn == BUTTON_BLUE || cn == BUTTON_YELLOW)
			{
				continue;
			}
			
			//���t�g�̓����蔻��
			if (cn == LIFT)
				continue;
			
			//�}�b�v�`�b�v�̒Z�a
			CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
			//�����蔻��p�̃L�����N�^�Z�a
			//���Ŕ͈͂����肵����p�̒Z�a���쐬����
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;		//���̒Z�a�͏㑤�������Ɠ����l�ɂ���
			brec.Expansion(-6, 0);			//���͈̔͂��������߂�
			//���Ɠ����蔻��
			if (cr.CollisionRect(brec))
			{
				re = true;
				//�`�b�v���Ζʂ̏ꍇ�����̗����ʒu���獂���̊��������߂�
				if (cn == LEFTSLOPE)
				{
					float sp = (brec.Right - cr.Left) / cr.GetWidth();
					if		(sp < 0.0f)		{ sp = 0.0f; }
					else if (sp > 1.0f)		{ sp = 1.0f; }
					//�Ζʂ̏�̈ʒu�����߂�
					float cTop = cr.Bottom - cr.GetHeight() * sp;
					//���߂���ӂ���ɂ���ꍇ�͖��܂��Ă��Ȃ�
					if (brec.Bottom < cTop) { continue; }
					//���̖��܂�Ȃ̂ō��[����Z�a�̉��[�̒l���������l�����܂�̒l
					oy += cTop - brec.Bottom;
					r.Top += cTop - brec.Bottom;
					r.Bottom += cTop - brec.Bottom;
				}
				else if (cn == RIGHTSLOPE)
				{
					float sp = ((brec.Left - cr.Right) / cr.GetWidth()) * -1;
					if		(sp < 0.0f)	{ sp = 0.0f; }
					else if (sp > 1.0f) { sp = 1.0f; }
					float cTop = cr.Bottom - cr.GetHeight() * sp;
					if (brec.Bottom < cTop) { continue; }
					oy += cTop - brec.Bottom;
					r.Top += cTop - brec.Bottom;
					r.Bottom += cTop - brec.Bottom;
				}
				else
				{
					//���̖��܂�Ȃ̂Ń`�b�v��[����Z�a�̉��[�̒l���������l�����܂�̒l
					oy += cr.Top - brec.Bottom;
					r.Top += cr.Top - brec.Bottom;
					r.Bottom += cr.Top - brec.Bottom;
				}
			}

			//��Ŕ͈͂����肵����p�̒Z�a���쐬����B
			CRectangle trec = r;
			trec.Bottom = trec.Top + 1;	//��̒Z�a�͉�������Ɠ����l�ɂ���
			trec.Expansion(-12, 0);		//���͈̔͂��������߂�
			//��Ɠ����蔻��
			if (cr.CollisionRect(trec))
			{
				re = true;
				//��̖��܂�Ȃ̂Ń`�b�v�����[����Z�a�̏�[�̒l���������l�����܂�̒l
				oy += cr.Bottom - trec.Top;
				r.Top += cr.Bottom - trec.Top;
				r.Bottom += cr.Bottom - trec.Top;
			}

			//�`�b�v���Ζʂ̏ꍇ�ǁE�V��Ƃ��Ă̓����蔻����s��Ȃ�
			if (cn == LEFTSLOPE) { continue; }
			if (cn == RIGHTSLOPE) { continue; }

			//�����蔻��p�̃L�����N�^�Z�a
			//���A�E�A���ꂼ��Ŕ͈͂����肵����p�̒Z�a���쐬����
			CRectangle lrec = r;
			lrec.Right = lrec.Left + 1;
			lrec.Expansion(0, -12);
			CRectangle rrec = r;
			rrec.Left = rrec.Right - 1;
			rrec.Expansion(0, -12);
			//���Ɠ����蔻��
			if (cr.CollisionRect(lrec))
			{
				re = true;
				//���̖��܂�Ȃ̂Ń`�b�v�E�[����Z�a�̍��[�̒l���������l�����܂�̒l
				ox		+= cr.Right - lrec.Left;
				r.Left	+= cr.Right - lrec.Left;
				r.Right += cr.Right - lrec.Left;
			}
			//�E�Ɠ����蔻��
			else if (cr.CollisionRect(rrec))
			{
				re = true;
				//�E�̖��܂�Ȃ̂Ń`�b�v���[����Z�a�̉E�[�̒l���������l�����܂�̒l
				ox		+= cr.Left - rrec.Right;
				r.Left	+= cr.Left - rrec.Right;
				r.Right += cr.Left - rrec.Right;
			}
			//�����蔻��p�̃L�����N�^�Z�a
		}
	}
	return re;
}


bool CBaseStage::StageAttackCollision(CRectangle r)
{
	//�����蔻�肷��Z�a�̍���ƉE���̃`�b�v�ʒu�����߂�
	int lc = m_ScrollX / m_ChipSize;
	int rc = (g_pGraphics->GetTargetWidth() + m_ScrollX) / m_ChipSize;
	int tc = m_ScrollY / m_ChipSize;
	int bc = (g_pGraphics->GetTargetHeight() + m_ScrollY) / m_ChipSize;

	//�X�e�[�W�͈̔͊O�ɂ͂Ȃ�Ȃ��悤�ɂ���
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }


	//�����蔻��ȊO������Z�a�̍��ォ��E���͈̔͂̂ݓ����蔻����s��
	//����ȊO�̔ԍ��͓����邱�Ƃ͂Ȃ��̂Ŕ��肪�K�v�Ȃ�
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ�0�͓����蔻�肵�Ȃ�
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//�}�b�v�`�b�v�̒Z�a
			CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);

			if (cn == WATER)
			{
				continue;
			}

			if (cn == CRACK_STONE) {
				if (cr.CollisionRect(r)) {
					m_pChipData[y * m_XCount + x] = 0;
					return true;
				}
			}

			if (cn == BUTTON_RED || cn == BUTTON_BLUE || cn == BUTTON_YELLOW)
			{				
				if (cr.CollisionRect(r))
				{
					m_pChipData[y * m_XCount + x] = 0;
					if (cn == BUTTON_RED)
					{
						m_bButtonRed = true;
					}

					else if (cn == BUTTON_BLUE)
					{
						m_bButtonBlue = true;
					}

					else if (cn == BUTTON_YELLOW)
					{
						m_bButtonYellow = true;
					}
					return true;
				}
			}
		}
	}
	return false;
}

void CBaseStage::CollisionCrack(CRectangle r) {
	int lc = m_ScrollX / m_ChipSize;
	int rc = (g_pGraphics->GetTargetWidth() + m_ScrollX) / m_ChipSize;
	int tc = m_ScrollY / m_ChipSize;
	int bc = (g_pGraphics->GetTargetHeight() + m_ScrollY) / m_ChipSize;

	//�X�e�[�W�͈̔͊O�ɂ͂Ȃ�Ȃ��悤�ɂ���
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn == CRACK_STONE)
			{
				CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
				if (cr.CollisionRect(r))
				{
					m_pChipData[y * m_XCount + x] = 0;
				}
			}
		}
	}
}

void CBaseStage::CollisionFreezeWater(CRectangle r)
{
	int lc = m_ScrollX / m_ChipSize;
	int rc = (g_pGraphics->GetTargetWidth() + m_ScrollX) / m_ChipSize;
	int tc = m_ScrollY / m_ChipSize;
	int bc = (g_pGraphics->GetTargetHeight() + m_ScrollY) / m_ChipSize;

	//�X�e�[�W�͈̔͊O�ɂ͂Ȃ�Ȃ��悤�ɂ���
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn == WATER)
			{
				CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
				if (cr.CollisionRect(r))
				{
					m_pChipData[y * m_XCount + x] = 12;

					//���̐�
					if (m_pChipData[y * m_XCount + (x - 1)] - 1 == WATER)
					{
						m_pChipData[y * m_XCount + (x - 1)] = 12;
					}

					//�E�̐�
					if (m_pChipData[y * m_XCount + (x + 1)] - 1 == WATER)
					{
						m_pChipData[y * m_XCount + (x + 1)] = 12;
					}

					//��̐�
					if (m_pChipData[(y - 1) * m_XCount + x] - 1 == WATER)
					{
						m_pChipData[(y - 1) * m_XCount + x] = 12;
					}

					//���̐�
					if (m_pChipData[(y + 1) * m_XCount + x] - 1 == WATER)
					{
						m_pChipData[(y + 1) * m_XCount + x] = 12;
					}
				}
			}
		}
	}
}

bool CBaseStage::CollisionWater(CRectangle prec)
{
	int lc = m_ScrollX / m_ChipSize;
	int rc = (g_pGraphics->GetTargetWidth() + m_ScrollX) / m_ChipSize;
	int tc = m_ScrollY / m_ChipSize;
	int bc = (g_pGraphics->GetTargetHeight() + m_ScrollY) / m_ChipSize;

	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn == WATER)
			{
				CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
				if (prec.CollisionRect(cr))
				{
					return true;
				}
			}
		}
	}

	return false;
}


void CBaseStage::CollisionIceFroe(CRectangle r)
{
	int lc = m_ScrollX / m_ChipSize;
	int rc = (g_pGraphics->GetTargetWidth() + m_ScrollX) / m_ChipSize;
	int tc = m_ScrollY / m_ChipSize;
	int bc = (g_pGraphics->GetTargetHeight() + m_ScrollY) / m_ChipSize;

	//�X�e�[�W�͈̔͊O�ɂ͂Ȃ�Ȃ��悤�ɂ���
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn == ICE)
			{
				CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
				if (cr.CollisionRect(r))
				{
					for (int i = 0; i < SE_COUNT; i++)
					{
						if (m_pSEManager[i].IsPlaySE())
							continue;
						m_pSEManager[i].SEPlayer(SE_FIRE_ICE);
						break;
					}
					m_pChipData[y * m_XCount + x] = 13;
				}
			}
			else if (cn == ICE2)
			{
				CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
				if (cr.CollisionRect(r))
				{
					for (int i = 0; i < SE_COUNT; i++)
					{
						if (m_pSEManager[i].IsPlaySE())
							continue;
						m_pSEManager[i].SEPlayer(SE_FIRE_ICE);
						break;
					}
					m_pChipData[y * m_XCount + x] = 0;
				}
			}
		}
	}
}

bool CBaseStage::CollisionLift(CRectangle r, float& ox, float& oy)
{
	bool re = false;

	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;

	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn != LIFT)
				continue;
			CRectangle cr(x * m_ChipSize + 10, y * m_ChipSize, x * m_ChipSize + m_ChipSize - 10, y * m_ChipSize + 20);
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;
			brec.Expansion(-6, 0);
			if (cr.CollisionRect(brec))
			{
				re = true;
				oy += cr.Top - brec.Bottom;
				r.Top += cr.Top - brec.Bottom;
				r.Bottom += cr.Top - brec.Bottom;
			}
		}
	}
	return re;
}

bool CBaseStage::FireBar(CRectangle prec,bool FireEffect)
{
	int lc = m_ScrollX / m_ChipSize;
	int rc = (g_pGraphics->GetTargetWidth() + m_ScrollX) / m_ChipSize;
	int tc = m_ScrollY / m_ChipSize;
	int bc = (g_pGraphics->GetTargetHeight() + m_ScrollY) / m_ChipSize;

	//�X�e�[�W�͈̔͊O�ɂ͂Ȃ�Ȃ��悤�ɂ���
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	for (int y = tc; y < bc; y++)
	{
		for (int x = lc; x < rc; x++)
		{
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn != BURNER)
				continue;

			//�o�[�i�[��SE
			for (int i = 0; i < SE_COUNT; i++)
			{
				if (m_pSEManager[i].IsPlaySE())
					continue;
				m_pSEManager[i].SEPlayer(SE_BURNER);
				break;
			}

			//�㉺�m�F
			//�����
			if (m_pChipData[(y - 1) * m_XCount + x] - 1 <= 0)
			{
				CRectangle UpFireRec(-m_ScrollX + x * m_ChipSize, -m_ScrollY + y * m_ChipSize - (m_ChipSize * 2), (-m_ScrollX + x * m_ChipSize) + m_ChipSize, -m_ScrollY + y * m_ChipSize);
				//SetFireRec(UpFireRec);
				if(FireEffect)
					m_pEffectManager->Start(UpFireRec.GetCenter().x + m_ScrollX, UpFireRec.GetCenter().y + m_ScrollY, EFC_FIREBAR_TOP);
				if (prec.CollisionRect(UpFireRec))
					return true;
			}
			//������
			else
			{
				CRectangle DownFireRec(-m_ScrollX + x * m_ChipSize, -m_ScrollY + y * m_ChipSize + m_ChipSize, (-m_ScrollX + x * m_ChipSize) + m_ChipSize, -m_ScrollY + y * m_ChipSize + (m_ChipSize * 3));
				//SetFireRec(DownFireRec);
				if(FireEffect)
					m_pEffectManager->Start(DownFireRec.GetCenter().x + m_ScrollX, DownFireRec.GetCenter().y + m_ScrollY, EFC_FIREBAR_BOTTOM);
				if (prec.CollisionRect(DownFireRec))
					return true;
			}
		}
	}
	return false;
}
/**
 * �`��
 *
 */
void CBaseStage::Render(void){

	//�e�N�X�`���̉�������}�b�v�`�b�v�̏c�I�t�Z�b�g�����߂�
	int tcx = m_ChipTexture.GetWidth() / m_ChipSize;
	//�}�b�v�`�b�v�̕`��
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//�`�悷��`�b�v�ԍ�
			//�`�b�v�ԍ�0�͕`�悵�Ȃ�
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//�}�b�v�`�b�v�̒Z�a
			CRectangle cr(m_ChipSize * (cn % tcx), m_ChipSize * (cn / tcx), m_ChipSize * (cn % tcx + 1), m_ChipSize * (cn / tcx + 1));
			//�}�b�v�`�b�v�̕`��
			m_ChipTexture.Render(-m_ScrollX + x * m_ChipSize, -m_ScrollY + y * m_ChipSize, cr);
		}
	}
}

void CBaseStage::BackTexRender() {
	//���i�̕`��
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int wn = m_BackTexture.GetWidth();
	int hn = m_BackTexture.GetHeight();
	for (float y = ((int)-m_ScrollY % hn) - hn; y < scw; y += hn)
	{
		for (float x = ((int)-m_ScrollX % wn) - wn; x < scw; x += wn)
		{
			m_BackTexture.Render(x, y);
		}
	}
}
/**
 * �f�o�b�O�`��
 *
 */
void CBaseStage::RenderDebug(void){
	//�ʒu�̕`��
	CGraphicsUtilities::RenderString(10,100,"�X�N���[�� X : %.0f , Y : %.0f",m_ScrollX,m_ScrollY);
	//CGraphicsUtilities::RenderRect(FireRec, MOF_XRGB(255, 0, 0));
}

/**
 * ���
 *
 */
void CBaseStage::Release(int nowscene){
	m_ChipTexture.Release();
	m_BackTexture.Release();
	if (m_pChipData)
	{
		free(m_pChipData);
		m_pChipData = NULL;
	}

	if (nowscene == SCENENO_GAME_STAGE1)
	{
		if (m_pEnemyTexture)
		{
			delete[] m_pEnemyTexture;
			m_pEnemyTexture = NULL;
		}
		if (m_pEnemyShotTexture)
		{
			delete[] m_pEnemyShotTexture;
			m_pEnemyShotTexture = NULL;
		}
		if (m_pEnemyData)
		{
			free(m_pEnemyData);
			m_pEnemyData = NULL;
		}
	}

	if (m_pItemData)
	{
		free(m_pItemData);
		m_pItemData = NULL;
	}
	if (m_pItemTexture)
	{
		delete[] m_pItemTexture;
		m_pItemTexture = NULL;
	}
}