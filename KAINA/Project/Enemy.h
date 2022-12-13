#pragma once

#include	"GameDefine.h"
#include	"EffectManager.h"
#include	"EnemyShot.h"


//�����蔻�茸����
#define		ENEMY_RECTDECREASE		10

class CEnemy{
private:
	CTexture*				m_pTexture;
	CSpriteMotionController	m_Motion;
	int						m_Type;
	float					m_PosX;
	float					m_PosY;
	float					m_MoveY;

	Vector2					m_TargetPos;

	bool					m_bShow;
	CRectangle				m_SrcRect;

	int						m_HP;
	int						m_DamageWait;

	CEffectManager*			m_pEffectManager;

	//�G����ʓ��ɂ��邩�̔���
	//TRUE :�@��ʓ�	FALSE : ��ʊO
	bool					m_WidthOut;
	
	//���[�V������ޒ�`
	enum tag_MOTION {
		MOTION_MOVE,
		MOTION_DAMAGE,
		MOTION_COUNT,
	};

	//�e�p�ϐ�
	CEnemyShot				m_ShotArray[ENEMY_SHOT_COUNT];
	int						m_ShotWait;
	float					m_TargetPosX;
	float					m_TargetPosY;

public:
	CEnemy();
	~CEnemy();
	void Initialize(float px,float py,int type);
	void Update(float wx);
	void CollisionStage(float ox,float oy);
	void Render(float wx,float wy);
	void RenderDebug(float wx,float wy);
	void Release(void);

	void SetTexture(CTexture* pt, CTexture* st);

	bool GetShow(void){ return m_bShow; }
	CRectangle GetRect(){
		return CRectangle(m_PosX + ENEMY_RECTDECREASE,m_PosY + ENEMY_RECTDECREASE,m_PosX + m_SrcRect.GetWidth() - ENEMY_RECTDECREASE,m_PosY + m_SrcRect.GetHeight());
	}
	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }

	//�v���C���[�̍��W�Z�b�g
	void SetTargetPos(float tx, float ty) { m_TargetPosX = tx; m_TargetPosY = ty; }

	//�e��Show�ERectangle��Ԃ�
	bool	   ShotArrayBool(int i) { return m_ShotArray[i].GetShow(); }
	CRectangle ShotArrayRect(int i) { return m_ShotArray[i].GetRect(); }

	//�e��Show���Z�b�g����
	void	   SetShotShow(bool flg, int i) { m_ShotArray[i].SetShow(flg); }

	//�v���C���[�̍��W���Z�b�g����
	void	   SetPlayerPos(Vector2 ppos) { m_TargetPos = ppos; }

};