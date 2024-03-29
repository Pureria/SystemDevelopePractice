#include	"Item.h"

/**
 * コンストラクタ
 *
 */
CItem::CItem() :
m_pTexture(NULL) ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_MoveX(0.0f) ,
m_MoveY(0.0f) ,
m_bShow(false) ,
m_SrcRect(),
m_bBossEliminated(false){
}

/**
 * デストラクタ
 *
 */
CItem::~CItem(){
	//delete[] で解放されるようにReleaseをデストラクタで実行する
	Release();
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 *
 * 引数
 * [in]			px					X座標
 * [in]			py					Y座標
 * [in]			type				敵タイプ
 */
void CItem::Initialize(float px,float py,int type){
	m_Type = type;
	m_PosX = px;
	m_PosY = py;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bShow = true;
	m_bBossEliminated = false;
	//アニメーションを作成
	if (m_Type == BOSS_DOOR)
	{
		SpriteAnimationCreate anim = {
		"ドア",
		0,0,
		128,256,
		FALSE,{{30,0,0},{30,1,0},{30,2,0},{30,3,0},{30,4,0}}
		};
		m_Motion.Create(anim);
	}
	else
	{
		SpriteAnimationCreate anim = {
			"アイテム",
			0,0,
			64,64,
			TRUE,{{5,0,0}}
		};
		m_Motion.Create(anim);
	}
}

/**
 * 更新
 *
 */
void CItem::Update(void){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//重力により下に少しずつ下がる
	if (m_Type != ITEM_SPIDERWEB && m_Type != BOSS_DOOR)
	{
		m_MoveY += GRAVITY;
		if (m_MoveY >= 20.0f)
		{
			m_MoveY = 20.0f;
		}
		//実際に座標を移動させる
		m_PosX += m_MoveX;
		m_PosY += m_MoveY;
		//アニメーションの更新
		m_Motion.AddTimer(CUtilities::GetFrameSecond());
	}

	m_SrcRect = m_Motion.GetSrcRect();
}

void CItem::Effect(bool jump, bool& BScene,float& PMoveX,float& PMoveY) {
	switch (GetType())
	{
	case BOSS_DOOR:
		if (g_pInput->IsKeyPush(MOFKEY_P) && jump && m_bBossEliminated)
			BScene = true;
		break;
	case ITEM_SPIDERWEB:
		PMoveX *= 0.8f;
		PMoveY *= 0.5f;
		break;
	}
}

void CItem::StartDoorAnimation()
{
	if (m_Type != BOSS_DOOR)
		return;

	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

bool CItem::IsEndDoorAnimation()
{
	return m_Motion.IsEndMotion();
}

/**
 * ステージとの当たり
 *
 * 引数
 * [in]			ox					X埋まり量
 * [in]			oy					Y埋まり量
 */
void CItem::CollisionStage(float ox,float oy){
	m_PosX += ox;
	m_PosY += oy;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if(oy < 0 && m_MoveY > 0)
	{
		m_MoveY = 0;
	}
	else if(oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する。
	if(ox < 0 && m_MoveX > 0)
	{
		m_MoveX = 0;
	}
	else if(ox > 0 && m_MoveX < 0)
	{
		m_MoveX = 0;
	}
}

/**
 * 描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CItem::Render(float wx,float wy){
	//非表示
	if(!m_bShow)
	{
		return;
	}

	if (m_Type == BOSS_DOOR)
	{
		if (m_bBossEliminated)
			m_pTexture->Render(m_PosX - wx, m_PosY - wy, m_SrcRect);
	}
	else
	{
		//テクスチャの描画
		m_pTexture->Render(m_PosX - wx,m_PosY - wy,m_SrcRect);
	}
}

/**
 * デバッグ描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CItem::RenderDebug(float wx,float wy){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx,hr.Top - wy,hr.Right - wx,hr.Bottom - wy,MOF_XRGB(255,0,0));
}

/**
 * 解放
 *
 */
void CItem::Release(void){
	m_Motion.Release();
}
