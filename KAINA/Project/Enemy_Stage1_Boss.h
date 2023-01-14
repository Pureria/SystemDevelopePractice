#pragma once

#include	"Mof.h"
#include	"GameDefine.h"
#include	"EffectManager.h"
#include	"EnemyStateDefine.h"
#include	"CEnemy_Base.h"

//当たり判定減衰幅
#define		BOSS1_RECT_WIDTH_DECREASE		100.0f
#define		BOSS1_RECT_HEIGHT_DECREASE		100.0f

//ボス基本定位置
#define		ENEMY_DEFAULT_LEFTPOS			440
#define		ENEMY_DEFAULT_RIGHTPOS			1359

#define		PLAYER_Lift_2					350
#define		PLAYER_Lift_1					606

#define		ENEMY_MOTION_WAIT				60
#define		ENEMY_MOTION_MOVE				5.0f
#define		ENEMY_ATTACKDASH_SPEED			10.0f
#define		ENEMY_JUMP						-13.0f
#define		ENEMY_ATTACKSLASH_WIDTH			150.0f
#define		ENEMY_ATTACKSLASH_MOVE			90

class CEnemy_Stage1_Boss : public CEnemy_Base {
private:
	CTexture				m_Texture;
	bool					m_bIsEnemyPosLeft;
	bool					m_bIsOnLift;
	bool					m_bJump;
	bool					m_bTouchGround;
	bool					m_AttackSlash;
	bool					m_bEliminated;

	CRectangle				m_AttakSlashRect;


	//ボスのHP
	int						m_MotionWait;
	int						m_OldMotionNo;

	//モーション種類定義
	enum tag_MOTION {
		MOTION_Idle,
		MOTION_MOVE,
		MOTION_JUMP,
		MOTION_ATTACK_DASH,
		MOTION_ATTACK_JUMP,
		MOTION_ATTACK_SLASH_START,
		MOTION_ATTACK_SLASH_END,
		MOTION_FALL,
		MOTION_ATTACK_SLASH_READY,
		MOTION_ATTACK_DASH_READY,
		MOTION_ATTACK_DASH_END,


		MOTION_COUNT,
	};

	float					m_TargetPosX;
	float					m_TargetPosY;


	CEffect*				m_pEndEffect;

	CTexture				m_HPTex;
	CTexture				m_FrameTex;
public:
	CEnemy_Stage1_Boss();
	~CEnemy_Stage1_Boss();
	bool Load();
	void Initialize();
	void Update();
	void CollisionStage(float ox, float oy);
	void CollisionWall ();
	void Render(float wx, float wy);
	void RenderStatus();
	void RenderDebug(float wx, float wy);
	void Release(void);

	bool GetShow(void) { return m_bShow; }
	CRectangle GetRect() {
		return CRectangle(m_Pos.x + BOSS1_RECT_WIDTH_DECREASE, m_Pos.y + BOSS1_RECT_HEIGHT_DECREASE, m_Pos.x + m_SrcRect.GetWidth() - BOSS1_RECT_WIDTH_DECREASE, m_Pos.y + m_SrcRect.GetHeight());
	}

	//ボスのダメージ処理
	//引数 : dmg = ダメージ : direction = 盾に当たった場合true、当たらなかった場合false
	void Damage(int dmg, bool direction);
	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }

	//プレイヤーの座標セット
	void SetTargetPos(float tx, float ty) { m_TargetPosX = tx; m_TargetPosY = ty; }

	int GetBossMotionNo() { return m_Motion.GetMotionNo(); }

	CRectangle GetBossBottomRect() { return CRectangle(m_SrcRect.Left, m_SrcRect.Bottom - 1, m_SrcRect.Right, m_SrcRect.Bottom); }
	CRectangle GetBossSideRect() 
	{
		CRectangle hr = GetRect();
		return CRectangle(hr.Left - 10, (hr.Top + 100), hr.Right + 10, (hr.Bottom - 100));
	}
	//ボスのフロントRect
	CRectangle GetBossFrontRect()
	{
		if (!m_bReverse)
		{
			return CRectangle(m_Pos.x + BOSS1_RECT_WIDTH_DECREASE, m_Pos.y + BOSS1_RECT_HEIGHT_DECREASE, m_Pos.x +  + BOSS1_RECT_WIDTH_DECREASE + ENEMY_BOSS_FRONTDEF_DIRECTION, m_Pos.y + m_SrcRect.GetHeight());
		}
		else
		{
			return CRectangle((m_Pos.x + m_SrcRect.GetWidth() - ENEMY_BOSS_FRONTDEF_DIRECTION - BOSS1_RECT_WIDTH_DECREASE), m_Pos.y + BOSS1_RECT_HEIGHT_DECREASE, m_Pos.x + m_SrcRect.GetWidth() - BOSS1_RECT_WIDTH_DECREASE, m_Pos.y + m_SrcRect.GetHeight());
		}
	}
	void SetReverse(bool reverse) { m_bReverse = reverse; }
	bool GetReverse() { return m_bReverse; }
	bool IsJump()
	{
		if (m_Move.y <= 0)
			return true;
		else
			return false;
	}
	void SetTouchGround(bool flg) { m_bTouchGround = flg; }
	void SetJumpAttackEnd()
	{
		m_bJump = false;
		m_Motion.ChangeMotion(MOTION_FALL);
	}

	//ボススラッシュ攻撃の判定
	bool isCollisionBossAttack(CRectangle prec);
	//ボス討伐判定
	bool isBossEliminated() { return m_bEliminated; }

	void DeffenceProc(int dmg, int deff) override;

	//発生位置
	inline Vector2 SetStartPos() {
		return Vector2(m_Pos.x + m_SrcRect.GetWidth() * 0.5f, m_Pos.y + m_SrcRect.GetHeight() * 0.5f);
	}


	//TODO: どうにかしよう
	void Initialize(float px, float py, int type) {};
	void Update(float wx) {};

};

