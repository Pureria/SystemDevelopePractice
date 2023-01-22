#pragma once
#include	"Mof.h"
#include	"SE_Manager.h"

//************************���j���[�N���X*************************
/*
* 
* �e�V�[���Ŏg�������Ƃ��Ɏg�����j���[�@�\
* 
*/
class CMenu
{
private:

	//���j���[��ʂ̕\���ʒu���R�s�[����ŕۑ�
	Vector2		m_c;

	//���j���[���ڂ̗]��
	int			m_HSpace, m_VSpace;

	//�������Ŏ󂯎����������̃|�C���^��ۑ�
	char*		m_pTitle;

	//�������Ŏ󂯎����������̓��I�z��̃|�C���^��ۑ�
	char**		m_pText;

	//��O�����Ŏ󂯎�������ڐ����R�s�[����ŕۑ�
	int			m_Count;

	//���j���[���ڂ�I������l
	int			m_Select;

	//���j���[��ʂ̕\���̐؂�ւ�
	bool		m_bShow;

	//Enter�L�[�Ō���
	bool		m_bEnter;

	//���j���[���ڂ̍ŏ���`
	CRectangle	m_Rect;

	//���j���[���ڂ̍ő��`
	CRectangle m_HeaderRect;

	CSE_Manager		m_SE;

	CTexture		m_TutorialTex;


public:
	//�f�t�H���g�R���X�g���N�^
	CMenu() : m_c(0, 0), m_HSpace(12), m_VSpace(8), m_Count(0), m_pTitle(), m_pText(), m_Select(0), m_bShow(false), m_bEnter(false), m_Rect(0, 0, 0, 0), m_HeaderRect(0, 0, 0, 0) {};
	//�f�X�g���N�^
	~CMenu() {};
	/*
	* 
	* �������@�F�@���j���[��ʂ̃^�C�g����n���B�@
	* �������@�F�@���j���[��ʂ̕\���ɕ\������e�L�X�g�̔z���n���B
	* ��O�����@�F	���j���[��ʂɕ\������e�L�X�g�̍��ڐ���n���B
	* 
	* �������e�@�F�@���j���[��ʂ̐ݒ�
	* 
	*/
	void Create(char* pTitle, char** pText, int cnt);
	/*
	* 
	* �������e	�F	�\�����ꂽ���j���[��ʂőI������I�сAEnter�L�[�Ŋm�肷��@�\
	* 
	*/
	void Update();
	/*
	* 
	* �������e	�F	���j���[��ʂ̕`�揈��
	*
	*/
	void Render();
	/*
	* 
	* �������e	�F	�f�[�^�̉��
	*
	*/
	void Release();
	/*
	* 
	* �������e	�F�@�����Ŏ󂯎�����l���g���āA���j���[��ʂ̕\���ʒu�����߂�B
	*
	*/
	void Show(Vector2 cp);
	/*
	* �@
	* �������e	�F�@���j���[��ʂ̕\�����I�t�ɂ���B�@
	*
	*/
	void Hide()		{ m_bShow = false; }
	/*
	* 
	* �������e	�F	���j���[��ʂ��\������Ă��邩�̊m�F
	* 
	* �߂�l	�F�@�^�U�l
	*
	*/
	bool IsShow()	{ return m_bShow; }
	/*
	* 
	* �������e	�F	Enter�L�[�������ꂽ���̊m�F
	* 
	*  true�F	������Ă���	false�F�@�@������Ă��Ȃ�
	* 
	* �߂�l	�F�@�^�U�l
	*
	*/
	bool IsEnter()  { return m_bEnter; }
	/*
	*
	* �������e	�F	�I�΂�Ă��鐔�l���擾����B
	* 
	* �߂�l	�F�@�����^
	*
	*/
	int GetSelect() { return m_Select; }
	/*
	*
	* �������e	�F	�ۑ����Ă��鍀�ڂ̐����擾����B
	*
	* �߂�l	�F�@�����^
	*
	*/
	int GetCount()  { return m_Count; }

};

