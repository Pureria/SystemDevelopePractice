#pragma once
#include	 "Mof.h"
#include     "GameDefine.h"
#include	"BGM_Manager.h"

#define		FILEKEY 0x65

/*
* 各シーンの共通モジュールを、純粋仮想関数でまとめた基盤となるシーンクラス
* 
*/
class Scene_Base
{
protected:
	//シーン終了の確認フラグ
	bool			m_bEnd;
	//次のシーン
	int				m_SceneNo;
	//現在のシーン
	int				m_NowScene;
	//
	int				m_Alpha;
	//
	bool			m_bChange;

	float			m_Time;
	//プレイヤーのHPを保存する変数
	int				m_PlayerHp;

	//BGM
	CBGM_Manager	m_BGMManager;

public:
	Scene_Base() : m_bEnd(false), m_SceneNo(), m_Alpha(255),m_bChange(false),m_Time(), m_PlayerHp(){};
	virtual ~Scene_Base() {};

	virtual void Initialize()  = 0;
	virtual void Update()	   = 0;
	virtual void Render()	   = 0;
	virtual void RenderDebug() = 0;
	virtual void Release()     = 0;

	int GetNextScene()		    { return m_SceneNo; }
	bool IsEnd()				{ return m_bEnd; }

	//フェード処理
	void UpdateFade() {
		if (m_bEnd) {
			m_Alpha -= FADE_ALPHA;
			if (m_Alpha <= 0) {
				m_NowScene = m_SceneNo;
				m_bChange = false;
			}
		}
		else {
			if (m_Alpha < FADE_ALPHA_MAX) {
				m_Alpha += FADE_ALPHA;
			}
		}
	}

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
		
};

