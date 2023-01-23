#include	"Effect.h"
#include	"EffectManager.h"

/**
 * �R���X�g���N�^
 *
 */
CEffect::CEffect() :
m_pTexture(NULL) ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_bShow(false) ,
m_SrcRect() {
}

/**
 * �f�X�g���N�^
 *
 */
CEffect::~CEffect(){
}

/**
 * �J�n
 * �p�����[�^�[����W������������B
 *
 * ����
 * [in]			type				�^�C�v
 */
void CEffect::Initialize(int type){
	m_PosX = 0.0f;
	m_PosY = 0.0f;
	m_bShow = false;
	
	

	switch (type)
	{
		case EFC_DAMAGE:
		{
			//�A�j���[�V�������쐬
			SpriteAnimationCreate anim[] = {
				{
					"�G�t�F�N�g",
					0, 0,
					256, 256,
					FALSE,
					{
								{ 2, 0, 0 }, { 2, 1, 0 }, { 2, 2, 0 }, { 2, 3, 0 },
								{ 2, 0, 1 }, { 2, 1, 1 }, { 2, 2, 1 }, { 2, 3, 1 },
								{ 2, 0, 2 }, { 2, 1, 2 }, { 2, 2, 2 }, { 2, 3, 2 },
								{ 2, 0, 3 }, { 2, 1, 3 }, { 2, 2, 3 }, { 2, 3, 3 },
								{ 2, 0, 4 }, { 2, 1, 4 }, { 2, 2, 4 }, { 2, 3, 4 },
								{ 2, 0, 5 }, { 2, 1, 5 }, { 2, 2, 5 }, { 2, 3, 5 },
								{ 2, 0, 6 }, { 2, 1, 6 }, { 2, 2, 6 }, { 2, 3, 6 },
					}
				}
			};
			m_Motion.Create(anim, 1);
			break;
		}
		case EFC_EXPLOSION01:
		{
			SpriteAnimationCreate anim[] = {
				{
					"�G�t�F�N�g",
					0, 0,
					120, 120,
					FALSE, {
						{ 3, 0, 0 }, { 3, 1, 0 }, { 3, 2, 0 }, { 3, 3, 0 }, { 3, 4, 0 },
						{ 3, 5, 0 }, { 3, 6, 0 }, { 3, 7, 0 }, { 3, 8, 0 }, { 3, 9, 0 },
						{ 3, 10, 0 }, { 3, 11, 0 }, { 3, 12, 0 }, { 3, 13, 0 }, { 3, 14, 0 }, { 3, 15, 0 }, }
				}
			};
			m_Motion.Create(anim, 1);
			break;
		}
		case EFC_EXPLOSION02:
		{
			SpriteAnimationCreate anim[] =
			{
				{
					"�G�t�F�N�g",
					0, 0,
					180, 180,
					FALSE, {
						{ 3, 0, 0 }, { 3, 1, 0 }, { 3, 2, 0 }, { 3, 3, 0 }, { 3, 4, 0 },
						{ 3, 5, 0 }, { 3, 6, 0 }, { 3, 7, 0 }, { 3, 8, 0 }, { 3, 9, 0 }, { 3, 10, 0 },
						{ 3, 0, 1 }, { 3, 1, 1 }, { 3, 2, 1 }, { 3, 3, 1 }, { 3, 4, 1 },
						{ 3, 5, 1 }, { 3, 6, 1 }, { 3, 7, 1 }, { 3, 8, 1 }, { 3, 9, 1 }, { 3, 10, 1 }, }
				}
			};
			m_Motion.Create(anim, 1);
			break;
		}
		case EFC_FIREBAR_TOP:
		{
			SpriteAnimationCreate anim[] =
			{
				{
					"�G�t�F�N�g",
					0,0,
					64,128,
					FALSE,
					{
								{ 3, 0, 0 },  { 3, 1, 0 },  { 3, 2, 0 },  { 3, 3, 0 },
								{ 3, 4, 0 },  { 3, 5, 0 },  { 3, 6, 0 },  { 3, 7, 0 },
								{ 3, 8, 0 },  { 3, 9, 0 },  { 3, 10, 0 }, { 3, 11, 0 },
								{ 3, 12, 0 }, { 3, 13, 0 }, { 3, 14, 0 }, { 3, 15, 0 },
								{ 3, 16, 0 }, { 3, 17, 0 }, { 3, 18, 0 }, { 3, 19, 0 },
								{ 3, 20, 0 }, { 3, 21, 0 }, { 3, 22, 0 }, { 3, 23, 0 },
								{ 3, 24, 0 }, { 3, 25, 0 }, { 3, 26, 0 }, { 3, 27, 0 },
								{ 3, 28, 0 }, { 3, 29, 0 },
					}
				}
			};
			m_Motion.Create(anim, 1);
			break;
		}

		case EFC_FIREBAR_BOTTOM:
		{
			SpriteAnimationCreate anim[] =
			{
				{
					"�G�t�F�N�g",
					0,0,
					64,128,
					FALSE,
					{
								{ 3, 0, 0 },  { 3, 1, 0 },  { 3, 2, 0 },  { 3, 3, 0 },
								{ 3, 4, 0 },  { 3, 5, 0 },  { 3, 6, 0 },  { 3, 7, 0 },
								{ 3, 8, 0 },  { 3, 9, 0 },  { 3, 10, 0 }, { 3, 11, 0 },
								{ 3, 12, 0 }, { 3, 13, 0 }, { 3, 14, 0 }, { 3, 15, 0 },
								{ 3, 16, 0 }, { 3, 17, 0 }, { 3, 18, 0 }, { 3, 19, 0 },
								{ 3, 20, 0 }, { 3, 21, 0 }, { 3, 22, 0 }, { 3, 23, 0 },
								{ 3, 24, 0 }, { 3, 25, 0 }, { 3, 26, 0 }, { 3, 27, 0 },
								{ 3, 28, 0 }, { 3, 29, 0 },
					}
				}
			};
			m_Motion.Create(anim, 1);
			break;
		}

		case EFC_WEAK:
		{
			//�A�j���[�V�������쐬
			SpriteAnimationCreate anim[] = {
				{
					"�G�t�F�N�g",
					0, 0,
					256, 256,
					FALSE,
					{
								{ 2, 0, 0 }, { 2, 1, 0 }, { 2, 2, 0 }, { 2, 3, 0 },
								{ 2, 4, 0 }, { 2, 5, 0 }, { 2, 6, 0 }, { 2, 7, 0 },
								{ 2, 8, 0 }, { 2, 9, 0 }, { 2, 10, 0 }, { 2, 11, 0 },
								{ 2, 12, 0 }, { 2, 13, 0 }, { 2, 14, 0 }, { 2, 15, 0 },
								{ 2, 16, 0 }, { 2, 17, 0 }, { 2, 18, 0 }, { 2, 19, 0 },
								{ 2, 20, 0 }, { 2, 21, 0 }, { 2, 22, 0 }, { 2, 23, 0 },
								{ 2, 24, 0 }, { 2, 25, 0 }, { 2, 26, 0 }, { 2, 27, 0 },
								{ 2, 28, 0 }, { 2, 0, 1 }, 
					}
				}
			};
			m_Motion.Create(anim, 1);
			break;
		}

		case EFC_SHIELD:
		{
			//�A�j���[�V�������쐬
			SpriteAnimationCreate anim[] = {
				{
					"�G�t�F�N�g",
					0, 0,
					256, 256,
					FALSE,
					{
								{ 2, 0, 0 }, { 2, 1, 0 }, { 2, 2, 0 }, { 2, 3, 0 },
								{ 2, 0, 1 }, { 2, 1, 1 }, { 2, 2, 1 }, { 2, 3, 1 },
								{ 2, 0, 2 }, { 2, 1, 2 }, { 2, 2, 2 }, { 2, 3, 2 },
								{ 2, 0, 3 }, { 2, 1, 3 }, { 2, 2, 3 }, { 2, 3, 3 },
								{ 2, 0, 4 }, { 2, 1, 4 }, { 2, 2, 4 }, { 2, 3, 4 },
								{ 2, 0, 5 }, { 2, 1, 5 }, { 2, 2, 5 }, { 2, 3, 5 },
								{ 2, 0, 6 }, { 2, 1, 6 }, { 2, 2, 6 }, { 2, 3, 6 },
					}
				}
			};
			m_Motion.Create(anim, 1);
			break;
		}

		case EFC_HEAL:
		{
			//�A�j���[�V�������쐬
			SpriteAnimationCreate anim[] = {
				{
					"�G�t�F�N�g",
					0, 0,
					128, 256,
					FALSE,
					{
								{ 2, 0, 0 }, { 2, 1, 0 }, { 2, 2, 0 }, { 2, 3, 0 },
								{ 2, 4, 0 }, { 2, 5, 0 }, { 2, 6, 0 }, { 2, 7, 0 },
								{ 2, 8, 0 }, { 2, 9, 0 }, { 2, 10, 0 }, { 2, 11, 0 },
								{ 2, 12, 0 }, { 2, 13, 0 }, { 2, 14, 0 }, { 2, 15, 0 },
								{ 2, 16, 0 }, { 2, 17, 0 }, { 2, 18, 0 }, { 2, 19, 0 },
								{ 2, 20, 0 }, { 2, 21, 0 },
					}
				}
			};
			m_Motion.Create(anim, 1);
			break;
		}

		case EFC_FIRE_HAND_LR:
		{
			//�A�j���[�V�������쐬
			SpriteAnimationCreate anim[] = {
				{
					"�G�t�F�N�g",
					0, 0,
					128, 256,
					FALSE,
					{
								{ 2, 0, 0 }, { 2, 1, 0},{ 2, 2, 0}, {2, 3, 0},
								{ 2, 4, 0 }, { 2, 5, 0 }, { 2, 6, 0 }, { 2, 7, 0 },
								{ 2, 8, 0 }, { 2, 9, 0 }, { 2, 10, 0 },{ 2, 11, 0 },
								{ 2, 12, 0 },{ 2, 13, 0 },{ 2, 14, 0 },
					}
				}
			};
			m_Motion.Create(anim, 1);
			break;
		}
		case EFC_FIRE_HAND_TB:
		{
			//�A�j���[�V�������쐬
			SpriteAnimationCreate anim[] = {
				{
					"�G�t�F�N�g",
					0, 0,
					256, 128,
					FALSE,
					{
								{ 2, 0, 0 }, { 2, 0, 1 }, { 2, 0, 2},  { 2, 0, 3 },
								{ 2, 0, 4 }, { 2, 0, 5 }, { 2, 0, 6 }, { 2, 0, 7 },
								
					}
				}
			};
			m_Motion.Create(anim, 1);
			break;
		}
		case EFC_FROST_HAND_LR:
		{
			//�A�j���[�V�������쐬
			SpriteAnimationCreate anim[] = {
				{
					"�G�t�F�N�g",
					0, 0,
					128, 256,
					FALSE,
					{
								{ 2, 0, 0 }, { 2, 1, 0},{ 2, 2, 0}, {2, 3, 0},
								{ 2, 4, 0 }, { 2, 5, 0 }, { 2, 6, 0 }, { 2, 7, 0 },
								{ 2, 8, 0 }, { 2, 9, 0 }, { 2, 10, 0 },{ 2, 11, 0 },
								{ 2, 12, 0 },{ 2, 13, 0 },{ 2, 14, 0 },
					}
				}
			};
			m_Motion.Create(anim, 1);
			break;
		}
		case EFC_FROST_HAND_TB:
		{
			//�A�j���[�V�������쐬
			SpriteAnimationCreate anim[] = {
				{
					"�G�t�F�N�g",
					0, 0,
					256, 128,
					FALSE,
					{
								{ 2, 0, 0 }, { 2, 0, 1 }, { 2, 0, 2},  { 2, 0, 3 },
								{ 2, 0, 4 }, { 2, 0, 5 }, { 2, 0, 6 }, { 2, 0, 7 },

					}
				}
			};
			m_Motion.Create(anim, 1);
			break;
		}
	}
}

/**
 * �J�n
 * ���W��ݒ肵�ă��[�V�������J�n����B
 *
 * ����
 * [in]			px					X���W
 * [in]			py					Y���W
 */
void CEffect::Start(float px,float py){
  //�\����`���擾
  m_SrcRect = m_Motion.GetSrcRect( );

  //���W��ݒ�B�w�肳�ꂽ���W���㉺���E�����ɂȂ�悤��
  m_PosX = px - m_SrcRect.GetWidth() * 0.5f;
  m_PosY = py - m_SrcRect.GetHeight() * 0.5f;

  //�\����Ԃ�
  m_bShow = true;

  //�ݒ肵���A�j���[�V�������Đ��J�n
  m_Motion.ChangeMotion( 0 );

}

/**
 * �X�V
 *
 */
void CEffect::Update(void){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	
	//�A�j���[�V�����̍X�V
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
	//�A�j���[�V�����̏I���Ŕ�\���ɂ���
	if (m_Motion.IsEndMotion())
	{
		m_bShow = false;
	}
}

/**
 * �`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CEffect::Render(float wx,float wy){
	//��\��
	if(!m_bShow)
	{
		return;
	}
	m_pTexture->Render(m_PosX - wx, m_PosY - wy, m_SrcRect);
}

/**
 * �f�o�b�O�`��
 *
 * ����
 * [in]			wx					���[���h�̕ω�
 * [in]			wy					���[���h�̕ω�
 */
void CEffect::RenderDebug(float wx,float wy){
	//��\��
	if(!m_bShow)
	{
		return;
	}

}

/**
 * ���
 *
 */
void CEffect::Release(void){
	m_Motion.Release();
}