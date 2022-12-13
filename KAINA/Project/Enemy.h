#pragma once

#include	"GameDefine.h"
#include	"EffectManager.h"
#include	"EnemyShot.h"


//当たり判定減衰幅
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

	//敵が画面内にいるかの判定
	//TRUE :　画面内	FALSE : 画面外
	bool					m_WidthOut;
	
	//モーション種類定義
	enum tag_MOTION {
		MOTION_MOVE,
		MOTION_DAMAGE,
		MOTION_COUNT,
	};

	//弾用変数
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

	//プレイヤーの座標セット
	void SetTargetPos(float tx, float ty) { m_TargetPosX = tx; m_TargetPosY = ty; }

	//弾のShow・Rectangleを返す
	bool	   ShotArrayBool(int i) { return m_ShotArray[i].GetShow(); }
	CRectangle ShotArrayRect(int i) { return m_ShotArray[i].GetRect(); }

	//弾のShowをセットする
	void	   SetShotShow(bool flg, int i) { m_ShotArray[i].SetShow(flg); }

	//プレイヤーの座標をセットする
	void	   SetPlayerPos(Vector2 ppos) { m_TargetPos = ppos; }

};