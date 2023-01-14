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

	//���[�V������ޒ�`
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

	//�e�̔z��
	CPlayerShot 			m_PlShotAry[PLAYERSHOT_COUNT];
	Laser					m_Laser[PLAYERSHOT_COUNT];

	//�e�̊Ԋu
	int						m_ShotWait;

	//��
	bool					m_bTop;

	//��
	bool					m_bBottom;

	//�e�̎��
	int						m_ShotType;

	//�e�̓�����ۊ�
	int						m_NatuType;

	//�e���̌���
	int						m_DrcType;



	//�{�X�����p�t���O
	bool					m_bNextBossScene;

	int						m_SpWait;


	//UI�e�N�X�`��
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
	
	/**********************************************public Collision�֐�********************************************/

#pragma region Collision�֐�

	void CollisionStage(float ox, float oy);
	bool CollisionEnemy(CEnemyBase_Shot& ene, int eneType);
	bool Collision_Stage1_Boss(CEnemy_Stage1_Boss& ene);
	bool ColisionItem(CItem& itm);
	bool CollisionAttackItem(CItem& itm);

#pragma endregion

	/************************************************public Shot�֐�***********************************************/

#pragma region Shot�֐�




	//�e�̔��ˁi���j
	void ShotRefLeft(int i)										{		m_PlShotAry[i].SetPowerLeft();							}
	//�e�̔��ˁi��j
	void ShotRefTop(int i)										{		m_PlShotAry[i].SetPowerTop();							}
	//�e�̔��ˁi�E�j
	void ShotRefRight(int i)									{		m_PlShotAry[i].SetPowerRight();							}
	//�e�̔��ˁi���j
	void ShotRefBottom(int i)									{		m_PlShotAry[i].SetPowerBottom();						}


#pragma endregion

	/************************************************public Get�֐�************************************************/

#pragma region Get�֐�


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

	//�e�̎��
	int  GetType()												{		return m_ShotType;										}

	int	 GetNatu()												{		return m_NatuType;										}
	//�e���̌���
	int  GetDirec()												{		return m_DrcType;										}

	int  GetNatuShot(int i)										{		return m_PlShotAry[i].GetNatu();						}

	int  GetNatuLaser(int i)									{		return m_Laser[i].GetNatu();							}

	bool GetLaserShotShow(int i)								{		return m_Laser[i].GetShow();							}

	inline int GetHp()											{		return m_HP;											}

	inline bool GetLaserWallHit(int i)							{		return m_Laser[i].GetWallHit();							}
	
#pragma endregion

	/************************************************public Set�֐�************************************************/

#pragma region Set�֐�
	
	void SetEffectManager(CEffectManager* pmng)					{ 		m_pEffectManager = pmng; 								}

	void SetNormalShotShow(bool flg, int i)						{		m_PlShotAry[i].SetShow(flg);							}
	//�X�e�[�W�ɓ��������ꍇ�@true	: false
	void SetWallLaser(int i,bool flg)							{		m_Laser[i].SetWallHitLaser(flg);						}
	
	inline void SetPlayerPos(float PosX, float PosY)			{		m_PosX = PosX; m_PosY = PosY;							}
	
	inline void SetHp(int hp)									{		m_HP = hp;												}

#pragma endregion	

	/************************************************public Is�֐�*************************************************/

#pragma region Is�֐�


	bool IsEnd(void)											{		return m_bDead;											}
	//�㏸���@: true
	bool IsJump();
	
	bool IsLaser()												{		return m_ShotType == LASER;								}
	
	
	
#pragma endregion

	/************************************************public Other�֐�**********************************************/

#pragma region Other�֐�

	//���� �_���[�W����̂��̂��v���C���[��� false : �E	true : ��
	void PlayerDamage(bool flg, float damage);
	void PlayerDamage(float damage);

#pragma endregion



private:

	/************************************************private Shot�֐�**********************************************/

#pragma region Shot�֐�

	//Shot�֐����܂Ƃ߂��֐�
	void ShotManager();

	//���˒e�̔��ˏ�Ԃ̊Ǘ�
	void FireShot();
	//���˒e�̌��������u�ԂɃZ�b�g
	void ShotRev(int i);

	//���[�U�[�̔��ˏ�Ԃ̊Ǘ�
	void FireShotLaser();
	//���[�U�[�̌��������u�ԂɃZ�b�g
	void ShotRevLaser(int i);

#pragma endregion
	
	/************************************************private Update�֐�**********************************************/

#pragma region Update�֐�

	//Key���͂̍X�V
	void UpdateKey();

	//�����̍X�V
	void UpdateMove();

	//�e�̍X�V
	void UpdateShot();


#pragma endregion

	/************************************************private Move�֐�**********************************************/

#pragma region Move�֐�

	//�v���C���[�̓����̐���
	void MoveKey();

	//�v���C���[�̌����ɂ���Ē�~���Ă���A�j���[�V�������ړ��A�j���[�V�����ɕύX����֐�
	void MoveTpBtmAnim();

	//�v���C���[�̌����ɂ���Ĉړ����Ă���A�j���[�V�������~�A�j���[�V�����ɕύX����֐�
	void MoveStopAnim();

	//�e�̎�ނɂ���Č����Ă���e���̃A�j���[�V������e�̎�ނɍ������A�j���[�V�����ɕύX����֐�
	void BltChangeTpBtmAnim();

#pragma endregion

	/************************************************private Set�֐�**********************************************/

#pragma region Set�֐�

	//�����ʒu
	inline Vector2 SetStartPos() {
		return Vector2(m_PosX + m_SrcRect.GetWidth() * 0.5f, m_PosY + m_SrcRect.GetHeight() * 0.5f);
	}

#pragma endregion

	/************************************************private Change�֐�*******************************************/

#pragma region Change�֐�

	//�e���̌�����ς��鏈��
	void DirecTpBtmChange();

	//������ς��鏈��
	void NatuChange();

	//�e�̎�ނ�ς��鏈��
	void BulletChange();
	void TypeChange();

	void DirecMotionChange();

#pragma endregion

	/************************************************private Other�֐�********************************************/

#pragma region Other�֐�

	//�v���C���[�̗�������
	void Fall();

	//�v���C���[���S���̏���
	bool PlayerEnd();

#pragma endregion

};