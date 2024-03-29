#pragma once
#include	 "Mof.h"
#include     "GameDefine.h"
#include	"BGM_Manager.h"
#include	"SE_Manager.h"
#include	"PublicFunction.h"
#include	"CMenu.h"

#define		FILEKEY 0x65

#define		START_FLASH_COUNT	120
/*
* 各シーンの共通モジュールを、純粋仮想関数でまとめた基盤となるシーンクラス
* 
*/
class Scene_Base
{
protected:
	//シーン終了の確認フラグ
	bool					m_bEnd;
	//次のシーン
	int						m_SceneNo;

	//ひとつ前のシーン
	int						m_OldSceneNo;

	float					m_Time;
	//プレイヤーのHPを保存する変数
	int						m_PlayerHp;

	CMenu					m_Menu;

	//BGM
	CBGM_Manager			m_BGMManager;

	//SE
	CSE_Manager				m_SEManager;

	CPublicFunction			m_Function;

	//フェードイン・フェードアウト用
	int						m_Alpha;
	float					m_NowTime;
	bool					m_bFadeIn;
	bool					m_bFadeOut;

	int						m_FlashCount;

public:
	Scene_Base() : m_bEnd(false), m_SceneNo(), m_OldSceneNo(0),m_Time(), m_PlayerHp(), m_Alpha(255), m_NowTime(0), m_bFadeIn(true), m_bFadeOut(false), m_FlashCount(0){};
	virtual ~Scene_Base() {};

	virtual void Initialize()  = 0;
	virtual void Update()	   = 0;
	virtual void Render()	   = 0;
	virtual void RenderDebug() = 0;
	virtual void Release()     = 0;

	int GetNextScene()		    { return m_SceneNo; }
	int GetOldScene()			{ return m_OldSceneNo; }
	bool IsEnd()				{ return m_bEnd; }

	
	void SetTime(float time) {
		m_Time += time;
	}

	//ボスステージは入れない
	void SetOldScene(int no)	{ m_OldSceneNo = no; }

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

