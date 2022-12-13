#include	"Enemy.h"

/**
 * コンストラクタ
 *
 */
CEnemy::CEnemy() :
m_pTexture(NULL) ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_MoveY(0.0f) ,
m_bShow(false) ,
m_SrcRect(){
}

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
	m_PosX = px;
	m_PosY = py;
	m_bShow = true;
	m_HP = 10;
	m_DamageWait = 0;
	m_WidthOut = true;

	//弾用変数のInitialize
	m_ShotWait = ENEMY_SHOT_WAIT;


	//アニメーションを作成
	SpriteAnimationCreate anim[ ] = {
		{
			"移動",
			0,0,120,128,TRUE,
			{ { 5,0,0 },{ 5,1,0 },{ 5,2,0 },{ 5,3,0 }, }
		},
		{
			"ダメージ",
			0,210,
			120,128,
			FALSE,{{20,0,0}}
		},
	};
	m_Motion.Create( anim, MOTION_COUNT );
}

/**
 * 更新
 *
 */
void CEnemy::Update(float wx){
	if (m_PosX - wx + m_pTexture->GetWidth() <= 0 || m_PosX - wx > g_pGraphics->GetTargetWidth())
		m_WidthOut = false;
	else
		m_WidthOut = true;

	//弾の更新
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
		m_ShotArray[i].Update(wx);

	if (!m_WidthOut)
		return;

	//非表示
	if(!m_bShow)
	{
		return;
	}
	//ダメージ中の動作
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		m_ShotWait = ENEMY_SHOT_WAIT;

		//終了で待機に戻す
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
			if (m_HP <= 0)
			{
				m_bShow = false;
				//爆発エフェクトを発生させる
				m_pEffectManager->Start(m_PosX + m_SrcRect.GetWidth() * 0.5f, m_PosY + m_SrcRect.GetHeight() * 0.5f, EFC_EXPLOSION01);
			}
			//m_MoveX = ((m_bReverse) ? -3.0f : 3.0f);
		}
		/*
		else
		{
			if (m_MoveX > 0)
			{
				m_MoveX -= 0.2f;
				if (m_MoveX <= 0)
				{
					m_MoveX = 0;
				}
			}
			else if (m_MoveX < 0)
			{
				m_MoveX += 0.2f;
				if (m_MoveX >= 0)
				{
					m_MoveX = 0;
				}
			}
		}
		*/
	}

	//重力により下に少しずつ下がる
	m_MoveY += GRAVITY;
	if ( m_MoveY >= 20.0f ) { m_MoveY = 20.0f; }

	m_PosY += m_MoveY;

	//アニメーションの更新
	m_Motion.AddTimer( CUtilities::GetFrameSecond( ) );
	m_SrcRect = m_Motion.GetSrcRect( );

	//ダメージのインターバルを減らす
	if ((m_DamageWait > 0))
	{
		m_DamageWait--;
	}

	//弾の発射
	if (m_ShotWait <= 0)
	{
		for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
		{
			if (m_PosX > m_TargetPos.x)
			{
				if (m_ShotArray[i].GetShow())
					continue;
				m_ShotWait = ENEMY_SHOT_WAIT;
				Vector2 cv = m_SrcRect.GetCenter();
				//弾の発射位置
				float stx = m_PosX + 30;
				float sty = m_PosY + 30;
				//目標地点に向かうための方向
				float dx = m_TargetPosX - stx;
				float dy = m_TargetPosY - sty;
				//目標地点までの距離を求める
				float d = sqrt(dx * dx + dy * dy);
				//距離が0以下 = 完全に同じ位置の場合は発射しない
				if (d <= 0)
					break;
				//方向を正規化
				dx /= d;
				dy /= d;
				m_ShotArray[i].Fire(stx, sty, dx * 5, dy * 5);
				break;
			}
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

	//インターバル2フレームごとに描画をしない
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}

	//描画矩形
	CRectangle dr = m_SrcRect;
	//テクスチャの描画
	m_pTexture->Render(m_PosX - wx,m_PosY - wy,dr);


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
	CGraphicsUtilities::RenderCircle(m_PosX - wx, m_PosY - wy, 2, MOF_XRGB(255, 0, 0));
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
