#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include	"CEnemyBase_Shot.h"
#include	"EnemyStateDefine.h"
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
		MOTION_NORMAL_MUZZLETOP,
		MOTION_NORMAL_MUZZLEBOTTOM,
		MOTION_LASER_MUZZLETOP,
		MOTION_LASER_MUZZLEBOTTOM,
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


public:
	CPlayer();
	~CPlayer() {};
	bool Load();
	void Initialize();
	void Update();
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void RenderStatus();
	void Release();
	
	//ゲームパッド追加時の処理
	//void UpdatePadKey(LPGamePad pPad);



	/**********************************************public Collision関数********************************************/
#pragma region Collision関数

	void CollisionStage(float ox, float oy);
	bool CollisionEnemy(CEnemyBase_Shot& ene, int eneType);
	bool Collision_Stage1_Boss(CEnemy_Stage1_Boss& ene);
	bool ColisionItem(CItem& itm);
	bool CollisionAttackItem(CItem& itm);

#pragma endregion
	/************************************************public Shot関数***********************************************/
#pragma region Shot関数




	//弾の反射（左）
	void ShotRefLeft(int i)										{		m_PlShotAry[i].SetPowerLeft();							}
	//弾の反射（上）
	void ShotRefTop(int i)										{		m_PlShotAry[i].SetPowerTop();							}
	//弾の反射（右）
	void ShotRefRight(int i)									{		m_PlShotAry[i].SetPowerRight();							}
	//弾の反射（下）
	void ShotRefBottom(int i)									{		m_PlShotAry[i].SetPowerBottom();						}


#pragma endregion
	/************************************************public Get関数************************************************/
#pragma region Get関数


	CRectangle GetRect()										{
																		return CRectangle(m_PosX + PLAYER_RECTDECREASE,
																				m_PosY + PLAYER_RECTDECREASE,
																				m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE,
																				m_PosY + m_SrcRect.GetHeight());
																}
	int	 GetLaserDirec(int i)									{		return m_Laser[i].GetDirec();							}

	CRectangle GetLaserRect(int i)								{		return m_Laser[i].GetRect();							}

	CRectangle* GetLaserFireRect(int i)							{ 		return m_Laser[i].GetFireRect();						}

	CRectangle GetNormalRect(int i)								{ 		return m_PlShotAry[i].GetRect();						}

	bool GetNormalShow(int i)									{ 		return m_PlShotAry[i].GetShow();						}

	float GetPosX()												{		return m_PosX;											}
	float GetPosY()												{		return m_PosY;											}

	bool GetNextBossScene()										{		return m_NextBossScene;									}

	//弾の種類
	int  GetType()												{		return m_ShotType;										}

	//銃口の向き
	int  GetDirec()												{		return m_DrcType;										}

	int  GetNatuShot(int i)										{		return m_PlShotAry[i].GetNatu();						}

	int  GetNatuLaser(int i)									{		return m_Laser[i].GetNatu();							}

	bool GetLaserShotShow(int i)								{		return m_Laser[i].GetShow();							}

	int GetHp()													{		return m_HP;											}

#pragma endregion
	/************************************************public Set関数************************************************/
#pragma region Set関数
	
	void SetEffectManager(CEffectManager* pmng)					{ 		m_pEffectManager = pmng; 								}

	void SetNormalShotShow(bool flg, int i)						{		m_PlShotAry[i].SetShow(flg);							}
	
	void SetScroll(float wx, float wy, int i)					{		m_PlShotAry[i].SetScroll(wx, wy);						}

	//PlayerPosセット
	void SetPlayerPos(float PosX, float PosY)					{		m_PosX = PosX; m_PosY = PosY;							}

	void SetWallLaser(int i)									{		m_Laser[i].SetWallHitLaser();							}
	
	void SetHp(int hp)											{		m_HP = hp;												}
#pragma endregion	
	/************************************************public Is関数*************************************************/
#pragma region Is関数


	bool IsAttack()												{		return m_Motion.GetMotionNo() == MOTION_ATTACK;			}

	bool IsGoal(void)											{		return m_bGoal;											}

	bool IsEnd(void)											{		return m_bDead;											}
	//上昇中　: true
	bool IsJump();
	
	bool IsLaser()												{		return m_ShotType == LASER;								}
	
	bool IsWallLaser(int i)										{		return m_Laser[i].IsHitWall();							}
	
	
	
#pragma endregion
	/************************************************public Other関数**********************************************/
#pragma region Other関数

	//引数 ダメージ判定のものがプレイヤーより false : 右	true : 左
	void PlayerDamage(bool flg, float damage);

#pragma endregion

private:

	void ShotManager();
	//弾の向きを撃つ瞬間にセット
	void ShotRev(int i);
	void ShotRevLaser(int i);

	void FireShot();
	void FireShotLaser();
	
	void UpdateKey();

	void UpdateMove();

	//プレイヤーの動きの制限
	void MoveKey();

	//弾の更新
	void UpdateShot();

	//プレイヤー死亡時の処理
	bool PlayerEnd();

	//プレイヤーの落下処理
	void Fall();

	//銃口の向きを変える処理
	void DirecTpBtmChange();

	//特性を変える処理
	void NatuChange();

	//弾の種類を変える処理
	void BulletChange();
	void TypeChange();

	//発生位置
	Vector2 SetStartPos() {
		return Vector2(m_PosX + m_SrcRect.GetWidth() * 0.5f, m_PosY + m_SrcRect.GetHeight() * 0.5f - 20);
	}

	void DirecMotionChange();

};