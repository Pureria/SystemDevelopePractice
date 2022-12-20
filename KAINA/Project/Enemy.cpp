#include	"Enemy.h"

/**
 * �R���X�g���N�^
 *
 */
CEnemy::CEnemy(){}

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
	m_Pos.x = px;
	m_Pos.y = py;
	m_bShow = true;
	m_bWidthOut = true;
	m_EnemyType = Turret;

	//�e�p�ϐ���Initialize
	m_ShotWait = ENEMY_SHOT_WAIT;


	//�A�j���[�V�������쐬
	SpriteAnimationCreate anim[ ] = {
		{
			"�ҋ@���",
			0,0,256,128,TRUE,
			{ { 5,0,0 },{ 5,1,0 },{ 5,2,0 },{ 5,3,0 }, }
		},
	};
	m_Motion.Create( anim, MOTION_COUNT );
}

/**
 * �X�V
 *
 */
void CEnemy::Update(float wx){
	if (m_Pos.x - wx + m_pTexture->GetWidth() <= 0 || m_Pos.x - wx > g_pGraphics->GetTargetWidth())
		m_bWidthOut = false;
	else
		m_bWidthOut = true;

	//�e�̍X�V
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
		m_ShotArray[i].Update(wx);

	//if (!m_WidthOut)
		//return;

	//��\��
	if(!m_bShow)
	{
		return;
	}

	//�d�͂ɂ�艺�ɏ�����������
	m_Move.y += GRAVITY;
	if ( m_Move.y >= 20.0f ) { m_Move.y = 20.0f; }

	m_Pos.y += m_Move.y;

	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer( CUtilities::GetFrameSecond( ) );
	m_SrcRect = m_Motion.GetSrcRect( );

	//�e�̔���
	if (m_ShotWait <= 0)
	{
		for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
		{
			if (m_ShotArray[i].GetShow())
				continue;

			m_ShotArray[i].Fire(m_Pos.x, m_Pos.y + 20, -5, 0);
			m_ShotWait = ENEMY_SHOT_WAIT;
			break;
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
	m_Pos.x += ox;
	m_Pos.y += oy;
	//�������̉����܂�A�W�����v���̏㖄�܂�̏ꍇ�͈ړ�������������B
	if(oy < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
	}
	else if(oy > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
}

void CEnemy::Damage(float dmg)
{
	return;
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

	//�`���`
	CRectangle dr = m_SrcRect;
	//�e�N�X�`���̕`��
	m_pTexture->Render(m_Pos.x - wx,m_Pos.y - wy,dr);


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
	CGraphicsUtilities::RenderCircle(m_Pos.x - wx, m_Pos.y - wy, 2, MOF_XRGB(255, 0, 0));
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
