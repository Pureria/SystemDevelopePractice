#pragma once

#include	"Mof.h"
#include	"GameDefine.h"

//�G�t�F�N�g��ޗ�
enum tag_EFFECTTYPE {
	EFC_DAMAGE,						//�_���[�W
	EFC_EXPLOSION01,				//�G���j
	EFC_EXPLOSION02,				//�v���C���[���j
	EFC_FIREBAR,				//�X�e�[�W�M�~�b�N�̉Β��i�ォ�甭�ˁj
	/*EFC_FIREBAR_BOTTOM,				//�X�e�[�W�M�~�b�N�̉Β��i�����甭�ˁj
	EFC_SLASH,						//�a��
	EFC_SHIELD,						//�V�[���h*/


	EFC_TYPECOUNT,
};

class CEffect {
private:
	CTexture*				m_pTexture;
	CSpriteMotionController	m_Motion;
	float					m_PosX;
	float					m_PosY;
	bool					m_bShow;
	CRectangle				m_SrcRect;
public:
	CEffect();
	~CEffect();
	void Initialize(int type);
	void Start(float px,float py);
	void Update(void);
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release(void);
	void SetTexture(CTexture* pt){ m_pTexture = pt; }
	bool GetShow(void){ return m_bShow; }
};