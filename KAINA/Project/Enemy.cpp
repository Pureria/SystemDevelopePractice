#include	"Enemy.h"

/**
 * �R���X�g���N�^
 *
 */
CEnemy::CEnemy() :
m_pTexture(NULL) ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_MoveY(0.0f) ,
m_bShow(false) ,
m_SrcRect(){
}

/**
 * �f�X�g���N�^
 *
 */
CEnemy::~CEnemy(){
	//delete[] �ŉ�������悤��Release���f�X�g���N�^�Ŏ��s����
	Release();
}

/**
 * ������
 * �p�����[�^�[����W������������B
 *
 * ����
 * [in]			px					X���W
 * [in]			py					Y���W
 * [in]			type				�G�^�C�v
 */
void CEnemy::Initialize(float px,float py,int type){
	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_bShow = true;
	m_HP = 10;
	m_DamageWait = 0;
	m_WidthOut = true;

	//�e�p�ϐ���Initialize
	m_ShotWait = ENEMY_SHOT_WAIT;


	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim[ ] = {
		{
			"�ړ�",
			0,0,120,128,TRUE,
			{ { 5,0,0 },{ 5,1,0 },{ 5,2,0 },{ 5,3,0 }, }
		},
		{
			"�_���[�W",
			0,210,
			120,128,
			FALSE,{{20,0,0}}
		},
	};
	m_Motion.Create( anim, MOTION_COUNT );
}

/**
 * �X�V
 *
 */
void CEnemy::Update(float wx){
	if (m_PosX - wx + m_pTexture->GetWidth() <= 0 || m_PosX - wx > g_pGraphics->GetTargetWidth())
		m_WidthOut = false;
	else
		m_WidthOut = true;

	//�e�̍X�V
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
		m_ShotArray[i].Update(wx);

	if (!m_WidthOut)
		return;

	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�_���[�W���̓���
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		m_ShotWait = ENEMY_SHOT_WAIT;

		//�I���őҋ@�ɖ߂�
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
			if (m_HP <= 0)
			{
				m_bShow = false;
				//�����G�t�F�N�g�𔭐�������
				m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f, m_PosY + m_SrcRect.GetHeight() * 0.5f, EFC_EXPLOSION01);
			}
			//m_MoveX = ((m_bReverse) ? -3.0f : 3.0f);
		}
		/*
		else
		{
			if (m_MoveX > 0)
			{
				m_MoveX -= 0.2f;
				if (m_MoveX <= 0)
				{
					m_MoveX = 0;
				}
			}
			else if (m_MoveX < 0)
			{
				m_MoveX += 0.2f;
				if (m_MoveX >= 0)
				{
					m_MoveX = 0;
				}
			}
		}
		*/
	}

	//�d�͂ɂ�艺�ɏ�����������
	m_MoveY += GRAVITY;
	if ( m_MoveY >= 20.0f ) { m_MoveY = 20.0f; }

	m_PosY += m_MoveY;

	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer( CUtilities::GetFrameSecond( ) );
	m_SrcRect = m_Motion.GetSrcRect( );

	//�_���[�W�̃C���^�[�o�������炷
	if ((m_DamageWait > 0))
	{
		m_DamageWait--;
	}

	//�e�̔���
	if (m_ShotWait <= 0)
	{
		for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
		{
			if (m_PosX > m_TargetPos.x)
			{
				if (m_ShotArray[i].GetShow())
					continue;
				m_ShotWait = ENEMY_SHOT_WAIT;
				Vector2 cv = m_SrcRect.GetCenter();
				//�e�̔��ˈʒu
				float stx = m_PosX + 30;
				float sty = m_PosY + 30;
				//�ڕW�n�_�Ɍ��������߂̕���
				float dx = m_TargetPosX - stx;
				float dy = m_TargetPosY - sty;
				//�ڕW�n�_�܂ł̋��������߂�
				float d = sqrt(dx * dx + dy * dy);
				//������0�ȉ� = ���S�ɓ����ʒu�̏ꍇ�͔��˂��Ȃ�
				if (d <= 0)
					break;
				//�����𐳋K��
				dx /= d;
				dy /= d;
				m_ShotArray[i].Fire(stx, sty, dx * 5, dy * 5);
				break;
			}
		}
	}
	else
	{
		m_ShotWait--;
	}


}

/**
 * �X�e�[�W�Ƃ̓�����
 *
 * ����
 * [in]			ox					X���܂��
 * [in]			oy					Y���܂��
 */
void CEnemy::CollisionStage(float ox,float oy){
	m_PosX += ox;
	m_PosY += oy;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if(oy < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
	}
	else if(oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
}

/**
 * �`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CEnemy::Render(float wx,float wy){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�e�̕`��
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
		m_ShotArray[i].Render(wx,wy);

	//�C���^�[�o��2�t���[�����Ƃɕ`������Ȃ�
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}

	//�`���`
	CRectangle dr = m_SrcRect;
	//�e�N�X�`���̕`��
	m_pTexture->Render(m_PosX - wx,m_PosY - wy,dr);


}

/**
 * �f�o�b�O�`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CEnemy::RenderDebug(float wx,float wy){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx,hr.Top - wy,hr.Right - wx,hr.Bottom - wy,MOF_XRGB(255,0,0));

	//�e�̕`��
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
		m_ShotArray[i].RenderDebug(wx, wy);

	//PosX,PosY�m�F�p
	CGraphicsUtilities::RenderCircle(m_PosX - wx, m_PosY - wy, 2, MOF_XRGB(255, 0, 0));
	//CGraphicsUtilities::RenderCircle(m_TargetPosX - wx, m_TargetPosY - wy, 2, MOF_XRGB(255, 0, 0));
}

void CEnemy::SetTexture(CTexture* pt, CTexture* st)
{
	m_pTexture = pt;
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++) { m_ShotArray[i].SetTexture(st); }
}

/**
 * ���
 *
 */
void CEnemy::Release(void){
	m_Motion.Release();
}
