#include "CMenu.h"


void CMenu::Create(char* pTitle, char** pText, int cnt) {
	//�Â��f�[�^�̉��
	Release();
	//�����̕������ۑ�
	m_Count = cnt;

	/*
	*�@�������e  �Fchar*�^�̃L���X�g
	*			 �@strlen�֐��Ŏ󂯎���������̒���+1���̃��������m��
	*			 �@C����̓��I�������m��
	*
	*�@�ڍׁ@�@�@�Fmalloc�֐��̈����ɁA�w��o�C�g���̃��������m�ۂ��āA�m�ۂ����������̈�̃|�C���^��Ԃ��Ă���B
	*			 �Fstrlen�֐��́A�ŏ���null�l�ƈ�v����܂ł̒�����Ԃ��Ă���B
	*/
	m_pTitle = (char*)malloc(strlen(pTitle) + 1);

	/*
	*����    �@�F�@�������ɃR�s�[��̕�����@�@�������ɃR�s�[���̕�����
	*�������e  �F�@�������Ŏ󂯎������������A�������m�ۂ���m_pTitle�ɃR�s�[����B
	*/
	strcpy(m_pTitle, pTitle);

	/*�@
	*�@�������e  �Fchar**�^�̃L���X�g
	*			   �󂯎�����������g�p����T�C�Y������������ԂŊm�ۂ��A�m�ۂ�����̃|�C���^��n���Ă���B
	*			   C����̓��I�������m��
	*
	*�@�ڍׁ@�@	 �Fsizeof���Z�q�ł́A�������T�C�Y�𒲂ׂă|�C���^�̃o�C�g�����擾������ApText�̐�������Z���ē��I�������̊m�ہB
	*			�@ �m�ۂ������������A���I�z���m_pText�փ|�C���^�œn���B
	*
	*/
	m_pText = (char**)malloc(sizeof(pText) * cnt);

	/*�@
	*�@�������e  �Fchar*�^�̃L���X�g
	*			   strlen�֐��Ŏ󂯎���������̒���+1���̃��������m��
	*			   C����̓��I�������m��
	*
	*			   �m�ۂ�����������m_Count���J��Ԃ��āA���I�z���m_pText�̗v�f��1���R�s�[����B
	*
	*/
	for (int i = 0; i < m_Count; i++) {
		m_pText[i] = (char*)malloc(strlen(pText[i]) + 1);
		strcpy(m_pText[i], pText[i]);
	}

	CRectangle trec;
	CGraphicsUtilities::CalculateStringRect(0, 0, m_pTitle, trec);
	m_Rect.Right = MOF_MAX(m_Rect.Right, trec.Right + m_HSpace * 2);
	m_Rect.Bottom += trec.Bottom + m_VSpace * 2;
	m_HeaderRect = m_Rect;

	for (int i = 0; i < m_Count; i++) {
		CGraphicsUtilities::CalculateStringRect(0, 0, m_pText[i], trec);
		m_HeaderRect.Right = m_Rect.Right = MOF_MAX(m_Rect.Right, trec.Right + m_HSpace * 2);
		m_Rect.Bottom += trec.Bottom + m_VSpace;
	}
	m_Rect.Bottom += m_VSpace;

	m_SE.SelectLoad();
}

void CMenu::InitSE() {
	return;
}


void CMenu::Update() {
	if (!m_bShow) {
		return;
	}
	if (g_pInput->IsKeyPush(MOFKEY_RETURN)) {
		m_bEnter = true;
		m_SE.SEPlayer(SE_SELECT_OK);
	}
	//�㉺�̃L�[�őI��
	if (g_pInput->IsKeyPush(MOFKEY_W)) {
		m_Select--;
		if (m_Select < 0) {
			m_Select = m_Count - 1;
		}
		m_SE.SEPlayer(SE_SELECT_CHANGE);	
	}
	else if (g_pInput->IsKeyPush(MOFKEY_S)) {
		m_Select++;
		if (m_Select >= m_Count) {
			m_Select = 0;
		}
		m_SE.SEPlayer(SE_SELECT_CHANGE);
	}
}

void CMenu::Show(Vector2 cp) {

	m_c.x = cp.x;
	m_c.y = cp.y;
	m_bShow = true;
	m_bEnter = false;
	m_Select = 0;
	float w = m_Rect.GetWidth();
	float h = m_Rect.GetHeight();

	m_Rect.Top = m_c.y - h * 0.5f;
	m_Rect.Bottom = m_Rect.Top + h;
	m_Rect.Left = m_c.x - w * 0.5f;
	m_Rect.Right = m_Rect.Left + w;

	m_HeaderRect.Bottom = m_Rect.Top + m_HeaderRect.GetHeight();
	m_HeaderRect.Top = m_Rect.Top;
	m_HeaderRect.Right = m_Rect.Left + m_HeaderRect.GetWidth();
	m_HeaderRect.Left = m_Rect.Left;

}

void CMenu::Render() {
	if (!m_bShow) {
		return;
	}

	//�|�[�Y�̔w�i�`��
	CGraphicsUtilities::RenderFillRect(m_Rect, MOF_ARGB(200, 0, 0, 0));
	CGraphicsUtilities::RenderFillRect(m_HeaderRect, MOF_ARGB(200, 64, 64, 64));

	//�����̕`��
	CRectangle trec;
	float py = m_Rect.Top + m_VSpace;
	CGraphicsUtilities::CalculateStringRect(0, 0, m_pTitle, trec);
	CGraphicsUtilities::RenderString(m_c.x - trec.GetWidth() * 0.5f, py, MOF_COLOR_WHITE, m_pTitle);

	py += trec.Bottom + m_VSpace;
	for (int i = 0; i < m_Count; i++) {
		CGraphicsUtilities::CalculateStringRect(0, 0, m_pText[i], trec);
		CGraphicsUtilities::RenderString(m_c.x - trec.GetWidth() * 0.5f, py + m_VSpace,
			((m_Select == i) ? MOF_XRGB(255, 255, 255) : MOF_XRGB(128, 128, 128)), m_pText[i]);
		py += trec.Bottom + m_VSpace;
	}
}

void CMenu::Release() {

	if (m_pTitle) {
		free(m_pTitle);
		m_pTitle = NULL;
	}
	if (m_pText) {
		for (int i = 0; i < m_Count; i++) {
			free(m_pText[i]);
		}
		free(m_pText);
		m_pText = NULL;
		m_Count = 0;
	}
	m_Rect = CRectangle(0, 0, 0, 0);

	m_SE.SelectRelease();
}
