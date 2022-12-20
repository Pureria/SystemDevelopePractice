#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include	"CEnemyBase_Shot.h"
#include	"Enemy_Stage1_Boss.h"
#include	"EffectManager.h"
#include	"Item.h"
#include	"CPlayerShot.h"
#include	"Laser.h"


class CPlayer {
private:
	CTexture				m_Texture;
	CSpriteMotionController	m_Motion;
	float					m_PosX;
	float					m_PosY;
	bool					m_bMove;
	float					m_MoveX;
	float					m_MoveY;
	bool					m_bJump;
	bool					m_bReverse;
	CRectangle				m_SrcRect;
	
	int						m_HP;
	int						m_SP;
	int						m_DamageWait;

	CTexture				m_FrameTexture;
	CTexture				m_HPTexture;
	CTexture				m_HPBarTexture;
	CTexture				m_SPTexture;
	CTexture				m_SPBarTexture;

	CEffectManager*			m_pEffectManager;

	//モーション種類定義
	enum tag_MOTION {
		MOTION_WAIT,
		MOTION_MOVE,
		MOTION_JUMPSTART,
		MOTION_JUMPEND,
		MOTION_ATTACK,
		MOTION_DAMAGE,
		MOTION_COUNT,
	};


	CEffect*				m_pEndEffect;
	bool					m_bDead;

	bool					m_bGoal;

	CTexture                m_ShotHeavyTex;
	CTexture				m_ShotHealTex;

	//弾の配列
	CPlayerShot 			m_PlShotAry[PLAYERSHOT_COUNT];
	Laser					m_Laser[PLAYERSHOT_COUNT];

	//弾の間隔
	int						m_ShotWait;

	//上
	bool					m_bTop;

	//下
	bool					m_bBottom;
	/*MofU32					m_GamePadCnt;
	LPGamePad				m_pGamePad;//ゲームパッド接続時*/
	//弾の種類
	int						m_ShotType;

	//弾の特性を保管
	int						m_NatuType;

	//銃口の向き
	int						m_DrcType;


	//レーザーのテクスチャ
	CTexture                m_LaserFireTex;
	CTexture                m_LaserFrostTex;

	//ボス部屋用フラグ
	bool					m_NextBossScene;

	int						m_Deffence;


public:
	CPlayer();
	~CPlayer() {};
	bool Load(void);
	void Initialize(void);
	void Update(void);
	void UpdateKey(void);
	void UpdateMove(void);
	void MoveKey();
	void DirecTpBtm();
	//ゲームパッド追加時の処理
	//void UpdatePadKey(LPGamePad pPad);
	void UpdateShot();
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release(void);
	bool IsAttack()												{		return m_Motion.GetMotionNo() == MOTION_ATTACK;			}
	CRectangle GetRect() {
		return CRectangle(m_PosX + PLAYER_RECTDECREASE,
			m_PosY + PLAYER_RECTDECREASE,
			m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE,
			m_PosY + m_SrcRect.GetHeight());
	}
	int	 GetLaserDirec(int i)									{		return m_Laser[i].GetDirec();						}

	CRectangle GetLaserRect(int i)								{		return m_Laser[i].GetRect();						}

	CRectangle* GetLaserFireRect(int i)							{ 		return m_Laser[i].GetFireRect();						}

	CRectangle GetNormalRect(int i)								{ 		return m_PlShotAry[i].GetRect();						}

	bool GetNormalShow(int i)									{ 		return m_PlShotAry[i].GetShow();						}

	void CollisionStage(float ox, float oy);
	bool CollisionEnemy_1(CEnemyBase_Shot& ene);
	bool Collision_Stage1_Boss(CEnemy_Stage1_Boss& ene);
	void RenderStatus(void);

	void SetEffectManager(CEffectManager* pmng)					{ 		m_pEffectManager = pmng; 								}


	//プレイヤー死亡時の処理
	void PlayerEnd();
	bool IsEnd(void)											{		return m_bDead;											}

	bool ColisionItem(CItem& itm);
	bool CollisionAttackItem(CItem& itm);

	bool IsGoal(void)											{		return m_bGoal;											}
	//画面外で落下
	void Fall();
	//弾の向きを撃つ瞬間にセット
	void ShotRev(int i);
	void ShotRevLaser(int i);

	void FireShot();
	void FireShotLaser();

	float GetPosX()												{		return m_PosX;											}
	float GetPosY()												{		return m_PosY;											}

	bool GetNextBossScene()										{		return m_NextBossScene;									}

	//上昇中　: true
	bool IsJump();

	void ShotManager();


	//引数 ダメージ判定のものがプレイヤーより false : 右	true : 左
	void PlayerDamage(bool flg, float damage);

	//弾の反射
	void ShotRefLeft(int i)										{		m_PlShotAry[i].SetPowerLeft();							}

	void ShotRefTop(int i)										{		m_PlShotAry[i].SetPowerTop();							}

	void ShotRefRight(int i)									{		m_PlShotAry[i].SetPowerRight();							}

	void ShotRefBottom(int i)									{		m_PlShotAry[i].SetPowerBottom();						}







	/************************************************Get関数************************************************/


	int GetType()												{		return m_ShotType;										}

	int GetDirec()												{		return m_DrcType;										}

	int GetNatuShot(int i)										{		return m_PlShotAry[i].GetNatu();						}

	int GetNatuLaser(int i)										{		return m_Laser[i].GetNatu();							}

	bool GetLaserShotShow(int i)								{		return m_Laser[i].GetShow();							}



	/************************************************Set関数************************************************/
	


	void SetNormalShotShow(bool flg, int i)						{		m_PlShotAry[i].SetShow(flg);							}
	

	void SetScroll(float wx, float wy, int i)					{		m_PlShotAry[i].SetScroll(wx, wy);						}

	//PlayerPosセット
	void SetPlayerPos(float PosX, float PosY)					{		m_PosX = PosX; m_PosY = PosY;							}

	void SetLaserShotShow(bool flg, int i)						{		m_Laser[i].SetShow(flg);								}

	void SetWallLaser(int i)									{		m_Laser[i].SetWallHitLaser();							}
	
	
	/************************************************Is関数*************************************************/
	
	
	bool IsLaser()												{		return m_ShotType == LASER;								}
	
	bool IsWallLaser(int i)										{		return m_Laser[i].IsHitWall();							}
	
	
	
	/************************************************Other関数**********************************************/
private:

	void NatuChange();

	//弾の特性切り替え
	void BulletChange();

	void TypeChange();

	//発生位置
	Vector2 SetStartPos() {
		return Vector2(m_PosX + m_SrcRect.GetWidth() * 0.5f, m_PosY + m_SrcRect.GetHeight() * 0.5f - 20);
	}

	void DeffenceProc(int dmg) {
		m_Deffence = PLAYER_DEFFENCE_POWER;
		float deff = m_Deffence - dmg;
		if (deff > 0) {
			m_HP += deff;
		}
	};
};