#pragma once
#include	 "Mof.h"
#include     "GameDefine.h"
#include	"BGM_Manager.h"
#include	"SE_Manager.h"
#include	"PublicFunction.h"

#define		FILEKEY 0x65

#define		START_FLASH_COUNT	120
/*
* �e�V�[���̋��ʃ��W���[�����A�������z�֐��ł܂Ƃ߂���ՂƂȂ�V�[���N���X
* 
*/
class Scene_Base
{
protected:
	//�V�[���I���̊m�F�t���O
	bool					m_bEnd;
	//���̃V�[��
	int						m_SceneNo;
	//
	bool					m_bChange;

	float					m_Time;
	//�v���C���[��HP��ۑ�����ϐ�
	int						m_PlayerHp;

	//BGM
	CBGM_Manager			m_BGMManager;

	//SE
	CSE_Manager				m_pSEManager;

	CPublicFunction			m_Function;

	//�t�F�[�h�C���E�t�F�[�h�A�E�g�p
	int						m_Alpha;
	float					m_NowTime;
	bool					m_bFadeIn;
	bool					m_bFadeOut;

	int						m_FlashCount;

public:
	Scene_Base() : m_bEnd(false), m_SceneNo(),m_bChange(false),m_Time(), m_PlayerHp(), m_Alpha(255), m_NowTime(0), m_bFadeIn(true), m_bFadeOut(false), m_FlashCount(0){};
	virtual ~Scene_Base() {};

	virtual void Initialize()  = 0;
	virtual void Update()	   = 0;
	virtual void Render()	   = 0;
	virtual void RenderDebug() = 0;
	virtual void Release()     = 0;

	int GetNextScene()		    { return m_SceneNo; }
	bool IsEnd()				{ return m_bEnd; }


	void UpdateExitkey() {
		if (g_pInput->IsKeyPush(MOFKEY_ESCAPE)) {
			exit(0);
		}
	}

	void SetTime(float time) {
		m_Time += time;
	}

	float Time() {

		return m_Time;
	}

	void SetSaveToFile() {
		std::ofstream SaveDataFile("SaveDataFile/Save.txt");
		if (SaveDataFile.is_open()) {
			SaveDataFile << m_PlayerHp;
			SaveDataFile.close();
		}
	}

	void GetSaveToFile() {
		std::ifstream SaveDataFile("SaveDataFile/Save.txt");
		if (SaveDataFile.is_open()) {
			SaveDataFile >> m_PlayerHp;
			SaveDataFile.close();
		}
	}

	void SetSEManager(CSE_Manager* sem) { m_pSEManager = *sem; }
		
};

