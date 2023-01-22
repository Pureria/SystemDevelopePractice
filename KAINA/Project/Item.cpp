#include	"Item.h"

/**
 * �R���X�g���N�^
 *
 */
CItem::CItem() :
m_pTexture(NULL) ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_MoveX(0.0f) ,
m_MoveY(0.0f) ,
m_bShow(false) ,
m_SrcRect(),
m_bBossEliminated(false){
}

/**
 * �f�X�g���N�^
 *
 */
CItem::~CItem(){
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
void CItem::Initialize(float px,float py,int type){
	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bShow = true;
	m_bBossEliminated = false;
	//�A�j���[�V�������쐬
	if (m_Type == BOSS_DOOR)
	{
		SpriteAnimationCreate anim = {
		"�h�A",
		0,0,
		128,256,
		FALSE,{{30,0,0},{30,1,0},{30,2,0},{30,3,0},{30,4,0}}
		};
		m_Motion.Create(anim);
	}
	else
	{
		SpriteAnimationCreate anim = {
			"�A�C�e��",
			0,0,
			64,64,
			TRUE,{{5,0,0}}
		};
		m_Motion.Create(anim);
	}
}

/**
 * �X�V
 *
 */
void CItem::Update(void){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�d�͂ɂ�艺�ɏ�����������
	if (m_Type != ITEM_SPIDERWEB && m_Type != BOSS_DOOR)
	{
		m_MoveY += GRAVITY;
		if (m_MoveY >= 20.0f)
		{
			m_MoveY = 20.0f;
		}
		//���ۂɍ��W���ړ�������
		m_PosX += m_MoveX;
		m_PosY += m_MoveY;
		//�A�j���[�V�����̍X�V
		m_Motion.AddTimer(CUtilities::GetFrameSecond());
	}

	m_SrcRect = m_Motion.GetSrcRect();
}

void CItem::Effect(bool jump, bool& BScene,float& PMoveX,float& PMoveY) {
	switch (GetType())
	{
	case BOSS_DOOR:
		if (g_pInput->IsKeyPush(MOFKEY_P) && jump && m_bBossEliminated)
			BScene = true;
		break;
	case ITEM_SPIDERWEB:
		PMoveX *= 0.8f;
		PMoveY *= 0.5f;
		break;
	}
}

void CItem::StartDoorAnimation()
{
	if (m_Type != BOSS_DOOR)
		return;

	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

bool CItem::IsEndDoorAnimation()
{
	return m_Motion.IsEndMotion();
}

/**
 * �X�e�[�W�Ƃ̓�����
 *
 * ����
 * [in]			ox					X���܂��
 * [in]			oy					Y���܂��
 */
void CItem::CollisionStage(float ox,float oy){
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
	//���ړ����̍����܂�A�E�ړ����̉E���܂�̏ꍇ�͈ړ�������������B
	if(ox < 0 && m_MoveX > 0)
	{
		m_MoveX = 0;
	}
	else if(ox > 0 && m_MoveX < 0)
	{
		m_MoveX = 0;
	}
}

/**
 * �`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CItem::Render(float wx,float wy){
	//��\��
	if(!m_bShow)
	{
		return;
	}

	if (m_Type == BOSS_DOOR)
	{
		if (m_bBossEliminated)
			m_pTexture->Render(m_PosX - wx, m_PosY - wy, m_SrcRect);
	}
	else
	{
		//�e�N�X�`���̕`��
		m_pTexture->Render(m_PosX - wx,m_PosY - wy,m_SrcRect);
	}
}

/**
 * �f�o�b�O�`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CItem::RenderDebug(float wx,float wy){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	//�����蔻��̕\��
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx,hr.Top - wy,hr.Right - wx,hr.Bottom - wy,MOF_XRGB(255,0,0));
}

/**
 * ���
 *
 */
void CItem::Release(void){
	m_Motion.Release();
}
