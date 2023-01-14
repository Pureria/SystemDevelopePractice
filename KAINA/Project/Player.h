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
#include	"SE_Manager.h"


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
	CTexture				m_HPBarTexture;
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
		MOTION_NORMAL_MOVETOP,
		MOTION_NORMAL_MOVEBOTTOM,
		MOTION_LASER_MUZZLETOP,
		MOTION_LASER_MUZZLEBOTTOM,
		MOTION_LASER_MOVETOP,
		MOTION_LASER_MOVEBOTTOM,
		MOTION_RETURN_MUZZLE,
		MOTION_DAMAGE,

		MOTION_COUNT,
	};


	CEffect*				m_pEndEffect;
	bool					m_bDead;

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

	//弾の種類
	int						m_ShotType;

	//弾の特性を保管
	int						m_NatuType;

	//銃口の向き
	int						m_DrcType;



	//ボス部屋用フラグ
	bool					m_bNextBossScene;

	int						m_SpWait;


	//UIテクスチャ
	CTexture                m_HealTex;
	CTexture                m_HeavyTex;
	CTexture				m_FireTex;
	CTexture				m_FrostTex;

public:
	CPlayer();
	~CPlayer() {};
	bool Load();
	void Initialize();
	void Update();
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void RenderStatus();
	void ShotRender(float wx, float wy);
	void Release();
	
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
																		return CRectangle(m_PosX + PLAYER_RECTDECREASE_WIDTH,
																				m_PosY + PLAYER_RECTDECREASE_HEIGHT,
																				m_PosX + m_SrcRect.GetWidth() - PLAYER_RECTDECREASE_WIDTH,
																				m_PosY + m_SrcRect.GetHeight());
																}
	int	 GetLaserDirec(int i)									{		return m_Laser[i].GetDirec();							}

	CRectangle GetLaserRect(int i)								{		return m_Laser[i].GetRect();							}

	CRectangle* GetLaserFireRect(int i)							{ 		return m_Laser[i].GetFireRect();						}

	CRectangle GetNormalRect(int i)								{ 		return m_PlShotAry[i].GetRect();						}

	bool GetNormalShow(int i)									{ 		return m_PlShotAry[i].GetShow();						}

	float GetPosX()												{		return m_PosX;											}
	float GetPosY()												{		return m_PosY;											}

	bool GetNextBossScene()										{		return m_bNextBossScene;								}

	//弾の種類
	int  GetType()												{		return m_ShotType;										}

	int	 GetNatu()												{		return m_NatuType;										}
	//銃口の向き
	int  GetDirec()												{		return m_DrcType;										}

	int  GetNatuShot(int i)										{		return m_PlShotAry[i].GetNatu();						}

	int  GetNatuLaser(int i)									{		return m_Laser[i].GetNatu();							}

	bool GetLaserShotShow(int i)								{		return m_Laser[i].GetShow();							}

	inline int GetHp()											{		return m_HP;											}

	inline bool GetLaserWallHit(int i)							{		return m_Laser[i].GetWallHit();							}
	
#pragma endregion

	/************************************************public Set関数************************************************/

#pragma region Set関数
	
	void SetEffectManager(CEffectManager* pmng)					{ 		m_pEffectManager = pmng; 								}

	void SetNormalShotShow(bool flg, int i)						{		m_PlShotAry[i].SetShow(flg);							}
	//ステージに当たった場合　true	: false
	void SetWallLaser(int i,bool flg)							{		m_Laser[i].SetWallHitLaser(flg);						}
	
	inline void SetPlayerPos(float PosX, float PosY)			{		m_PosX = PosX; m_PosY = PosY;							}
	
	inline void SetHp(int hp)									{		m_HP = hp;												}

#pragma endregion	

	/************************************************public Is関数*************************************************/

#pragma region Is関数


	bool IsEnd(void)											{		return m_bDead;											}
	//上昇中　: true
	bool IsJump();
	
	bool IsLaser()												{		return m_ShotType == LASER;								}
	
	
	
#pragma endregion

	/************************************************public Other関数**********************************************/

#pragma region Other関数

	//引数 ダメージ判定のものがプレイヤーより false : 右	true : 左
	void PlayerDamage(bool flg, float damage);
	void PlayerDamage(float damage);

#pragma endregion



private:

	/************************************************private Shot関数**********************************************/

#pragma region Shot関数

	//Shot関数をまとめた関数
	void ShotManager();

	//反射弾の発射状態の管理
	void FireShot();
	//反射弾の向きを撃つ瞬間にセット
	void ShotRev(int i);

	//レーザーの発射状態の管理
	void FireShotLaser();
	//レーザーの向きを撃つ瞬間にセット
	void ShotRevLaser(int i);

#pragma endregion
	
	/************************************************private Update関数**********************************************/

#pragma region Update関数

	//Key入力の更新
	void UpdateKey();

	//動きの更新
	void UpdateMove();

	//弾の更新
	void UpdateShot();


#pragma endregion

	/************************************************private Move関数**********************************************/

#pragma region Move関数

	//プレイヤーの動きの制限
	void MoveKey();

	//プレイヤーの向きによって停止しているアニメーションを移動アニメーションに変更する関数
	void MoveTpBtmAnim();

	//プレイヤーの向きによって移動しているアニメーションを停止アニメーションに変更する関数
	void MoveStopAnim();

	//弾の種類によって向けている銃口のアニメーションを弾の種類に合ったアニメーションに変更する関数
	void BltChangeTpBtmAnim();

#pragma endregion

	/************************************************private Set関数**********************************************/

#pragma region Set関数

	//発生位置
	inline Vector2 SetStartPos() {
		return Vector2(m_PosX + m_SrcRect.GetWidth() * 0.5f, m_PosY + m_SrcRect.GetHeight() * 0.5f);
	}

#pragma endregion

	/************************************************private Change関数*******************************************/

#pragma region Change関数

	//銃口の向きを変える処理
	void DirecTpBtmChange();

	//特性を変える処理
	void NatuChange();

	//弾の種類を変える処理
	void BulletChange();
	void TypeChange();

	void DirecMotionChange();

#pragma endregion

	/************************************************private Other関数********************************************/

#pragma region Other関数

	//プレイヤーの落下処理
	void Fall();

	//プレイヤー死亡時の処理
	bool PlayerEnd();

#pragma endregion

};