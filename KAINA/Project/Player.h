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

	//���[�V������ޒ�`
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

	//�e�̔z��
	CPlayerShot 			m_PlShotAry[PLAYERSHOT_COUNT];
	Laser					m_Laser[PLAYERSHOT_COUNT];

	//�e�̊Ԋu
	int						m_ShotWait;

	//��
	bool					m_bTop;

	//��
	bool					m_bBottom;
	/*MofU32					m_GamePadCnt;
	LPGamePad				m_pGamePad;//�Q�[���p�b�h�ڑ���*/
	//�e�̎��
	int						m_ShotType;

	//�e�̓�����ۊ�
	int						m_NatuType;

	//�e���̌���
	int						m_DrcType;


	//���[�U�[�̃e�N�X�`��
	CTexture                m_LaserFireTex;
	CTexture                m_LaserFrostTex;

	//�{�X�����p�t���O
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
	
	//�Q�[���p�b�h�ǉ����̏���
	//void UpdatePadKey(LPGamePad pPad);



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

	//�e�̎��
	int  GetType()												{		return m_ShotType;										}

	//�e���̌���
	int  GetDirec()												{		return m_DrcType;										}

	int  GetNatuShot(int i)										{		return m_PlShotAry[i].GetNatu();						}

	int  GetNatuLaser(int i)									{		return m_Laser[i].GetNatu();							}

	bool GetLaserShotShow(int i)								{		return m_Laser[i].GetShow();							}

	int GetHp()													{		return m_HP;											}

#pragma endregion
	/************************************************public Set�֐�************************************************/
#pragma region Set�֐�
	
	void SetEffectManager(CEffectManager* pmng)					{ 		m_pEffectManager = pmng; 								}

	void SetNormalShotShow(bool flg, int i)						{		m_PlShotAry[i].SetShow(flg);							}
	
	void SetScroll(float wx, float wy, int i)					{		m_PlShotAry[i].SetScroll(wx, wy);						}

	//PlayerPos�Z�b�g
	void SetPlayerPos(float PosX, float PosY)					{		m_PosX = PosX; m_PosY = PosY;							}

	void SetWallLaser(int i)									{		m_Laser[i].SetWallHitLaser();							}
	
	void SetHp(int hp)											{		m_HP = hp;												}
#pragma endregion	
	/************************************************public Is�֐�*************************************************/
#pragma region Is�֐�


	bool IsAttack()												{		return m_Motion.GetMotionNo() == MOTION_ATTACK;			}

	bool IsGoal(void)											{		return m_bGoal;											}

	bool IsEnd(void)											{		return m_bDead;											}
	//�㏸���@: true
	bool IsJump();
	
	bool IsLaser()												{		return m_ShotType == LASER;								}
	
	bool IsWallLaser(int i)										{		return m_Laser[i].IsHitWall();							}
	
	
	
#pragma endregion
	/************************************************public Other�֐�**********************************************/
#pragma region Other�֐�

	//���� �_���[�W����̂��̂��v���C���[��� false : �E	true : ��
	void PlayerDamage(bool flg, float damage);

#pragma endregion

private:

	void ShotManager();
	//�e�̌��������u�ԂɃZ�b�g
	void ShotRev(int i);
	void ShotRevLaser(int i);

	void FireShot();
	void FireShotLaser();
	
	void UpdateKey();

	void UpdateMove();

	//�v���C���[�̓����̐���
	void MoveKey();

	//�e�̍X�V
	void UpdateShot();

	//�v���C���[���S���̏���
	bool PlayerEnd();

	//�v���C���[�̗�������
	void Fall();

	//�e���̌�����ς��鏈��
	void DirecTpBtmChange();

	//������ς��鏈��
	void NatuChange();

	//�e�̎�ނ�ς��鏈��
	void BulletChange();
	void TypeChange();

	//�����ʒu
	Vector2 SetStartPos() {
		return Vector2(m_PosX + m_SrcRect.GetWidth() * 0.5f, m_PosY + m_SrcRect.GetHeight() * 0.5f - 20);
	}

	void DirecMotionChange();

};