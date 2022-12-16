#pragma once
#include	"Mof.h"
#include	"EffectManager.h"
#include	"EnemyShot.h"

//当たり判定減衰幅
#define			ENEMY_RECTDECREALSE		20

class CEnemy_2{
private:
	//fallFlg : TRUE 落下する : FALSE 落下しない
	bool					m_bFallFlg;
	//ShotTarget : TRUE 弾の軌道がまっすぐ	FALSE : 弾の軌道がプレイヤーに向かって
	bool					m_bShotTarget;
	//false : 左向き	true : 右向き
	bool					m_bReverse;

	CTexture*				m_pTexture;
	CSpriteMotionController m_Motion;
	CRectangle				m_SrcRect;
	
	int m_Type;
	int m_HP;
	int m_DamageWait;

	Vector2		m_Pos;
	Vector2		m_Move;

	bool		m_bShow;
	//TRUE : 画面内		FALSE : 画面外
	bool		m_bWidthOut;

	CEffectManager* m_pEffectManager;

	//弾用変数
	CEnemyShot				m_ShotArray[ENEMY_SHOT_COUNT];
	int						m_ShotWait;

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

	//弾のShow・Rectangleを返す
	bool		ShotArrayBool(int i) { return m_ShotArray[i].GetShow(); }
	CRectangle  ShotArrayRect(int i) { return m_ShotArray[i].GetRect(); }

	//弾のShowをセットする
	void		SetShotShow(bool flg, int i) { m_ShotArray[i].SetShow(flg); }
	//弾のShowを返す
	bool		GetShotShow(int i) { return m_ShotArray[i].GetShow(); }
	//弾のRectを返す
	CRectangle	GetShotRect(int i) { return m_ShotArray[i].GetRect(); }
	//弾のポジションを返す
	Vector2		GetShotPos(int i) { return m_ShotArray[i].GetPos(); }

	void		SetFallFlg(bool flg) { m_bFallFlg = flg; }
};

