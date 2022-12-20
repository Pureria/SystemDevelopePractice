#include	"Enemy.h"

/**
 * コンストラクタ
 *
 */
CEnemy::CEnemy(){}

/**
 * デストラクタ
 *
 */
CEnemy::~CEnemy(){
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
void CEnemy::Initialize(float px,float py,int type){
	m_Type = type;
	m_Pos.x = px;
	m_Pos.y = py;
	m_bShow = true;
	m_bWidthOut = true;
	m_EnemyType = Turret;

	//弾用変数のInitialize
	m_ShotWait = ENEMY_SHOT_WAIT;


	//アニメーションを作成
	SpriteAnimationCreate anim[ ] = {
		{
			"待機状態",
			0,0,256,128,TRUE,
			{ { 5,0,0 },{ 5,1,0 },{ 5,2,0 },{ 5,3,0 }, }
		},
	};
	m_Motion.Create( anim, MOTION_COUNT );
}

/**
 * 更新
 *
 */
void CEnemy::Update(float wx){
	if (m_Pos.x - wx + m_pTexture->GetWidth() <= 0 || m_Pos.x - wx > g_pGraphics->GetTargetWidth())
		m_bWidthOut = false;
	else
		m_bWidthOut = true;

	//弾の更新
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
		m_ShotArray[i].Update(wx);

	//if (!m_WidthOut)
		//return;

	//非表示
	if(!m_bShow)
	{
		return;
	}

	//重力により下に少しずつ下がる
	m_Move.y += GRAVITY;
	if ( m_Move.y >= 20.0f ) { m_Move.y = 20.0f; }

	m_Pos.y += m_Move.y;

	//アニメーションの更新
	m_Motion.AddTimer( CUtilities::GetFrameSecond( ) );
	m_SrcRect = m_Motion.GetSrcRect( );

	//弾の発射
	if (m_ShotWait <= 0)
	{
		for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
		{
			if (m_ShotArray[i].GetShow())
				continue;

			m_ShotArray[i].Fire(m_Pos.x, m_Pos.y + 20, -5, 0);
			m_ShotWait = ENEMY_SHOT_WAIT;
			break;
		}
	}
	else
	{
		m_ShotWait--;
	}


}

/**
 * ステージとの当たり
 *
 * 引数
 * [in]			ox					X埋まり量
 * [in]			oy					Y埋まり量
 */
void CEnemy::CollisionStage(float ox,float oy){
	m_Pos.x += ox;
	m_Pos.y += oy;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する。
	if(oy < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
	}
	else if(oy > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
}

void CEnemy::Damage(float dmg)
{
	return;
}

/**
 * 描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CEnemy::Render(float wx,float wy){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//弾の描画
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
		m_ShotArray[i].Render(wx,wy);

	//描画矩形
	CRectangle dr = m_SrcRect;
	//テクスチャの描画
	m_pTexture->Render(m_Pos.x - wx,m_Pos.y - wy,dr);


}

/**
 * デバッグ描画
 *
 * 引数
 * [in]			wx					ワールドの変化
 * [in]			wy					ワールドの変化
 */
void CEnemy::RenderDebug(float wx,float wy){
	//非表示
	if(!m_bShow)
	{
		return;
	}
	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx,hr.Top - wy,hr.Right - wx,hr.Bottom - wy,MOF_XRGB(255,0,0));

	//弾の描画
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
		m_ShotArray[i].RenderDebug(wx, wy);

	//PosX,PosY確認用
	CGraphicsUtilities::RenderCircle(m_Pos.x - wx, m_Pos.y - wy, 2, MOF_XRGB(255, 0, 0));
	//CGraphicsUtilities::RenderCircle(m_TargetPosX - wx, m_TargetPosY - wy, 2, MOF_XRGB(255, 0, 0));
}

void CEnemy::SetTexture(CTexture* pt, CTexture* st)
{
	m_pTexture = pt;
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++) { m_ShotArray[i].SetTexture(st); }
}

/**
 * 解放
 *
 */
void CEnemy::Release(void){
	m_Motion.Release();
}
