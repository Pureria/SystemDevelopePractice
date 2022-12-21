#pragma once

#include	"EnemyShot.h"
#include	"CEnemyBase_Shot.h"

//当たり判定減衰幅
#define			ENEMY_RECTDECREALSE		10

class CEnemy_2 : public CEnemyBase_Shot{
private:
	//fallFlg : TRUE 落下する : FALSE 落下しない
	bool					m_bFallFlg;
	//ShotTarget : TRUE 弾の軌道がまっすぐ	FALSE : 弾の軌道がプレイヤーに向かって
	bool					m_bShotTarget;
	//KnockBack : TRUE ノックバック中 : FALSE : ノックバック無し
	bool					m_bKnockback;


	float					m_TargetPosX;
	float					m_TargetPosY;


	//モーション種類定義
	enum tag_Motion {
		MOTION_MOVE,
		MOTION_DAMAGE,
		
		MOTION_COUNT,
	};
public:
	CEnemy_2();
	~CEnemy_2();

	void Initialize(float px, float py, int type);
	void Update(float wx);
	void CollisionStage(float ox, float oy);
	void Render(float wx, float wy);
	void RenderDebug(float wx, float wy);
	void Release();
	void SetEffectManager(CEffectManager* pmng) { m_pEffectManager = pmng; }

	void SetTexture(CTexture* pt, CTexture* st);

	bool		GetShow() { return m_bShow; }

	CRectangle  GetRect() { return CRectangle(m_Pos.x + ENEMY_RECTDECREALSE, m_Pos.y + ENEMY_RECTDECREALSE, m_Pos.x + m_SrcRect.GetWidth() - ENEMY_RECTDECREALSE, m_Pos.y + m_SrcRect.GetHeight()); }
	Vector2		GetPos() { return m_Pos; }

	//プレイヤーの座標セット
	void		SetTargetPos(float tx, float ty) { m_TargetPosX = tx; m_TargetPosY = ty; }
	bool		ShotTarget(int i);

	//弾のShowを返す
	bool		GetShotShow(int i) { return m_ShotArray[i].GetShow(); }
	//弾のRectを返す
	CRectangle	GetShotRect(int i) { return m_ShotArray[i].GetRect(); }
	//弾のポジションを返す
	Vector2		GetShotPos(int i) { return m_ShotArray[i].GetPos(); }

	//崖判定用Rectを返す
	CRectangle	GetLedgeCheckRect();
	void		Flip() { m_bReverse = !m_bReverse; }
	bool		GetFallFlg() { return m_bFallFlg; }

	void		SetFallFlg(bool flg) { m_bFallFlg = flg; }

	void Damage(float dmg) override;
	void KnockBack() override;
};

