#include "Enemy_2.h"

CEnemy_2::CEnemy_2() :
	m_bFallFlg(false),
	m_pEndEffect(),
	m_pSEManager()
{}

CEnemy_2::~CEnemy_2(){}

//TODO::Enemy_2の処理

void CEnemy_2::Initialize(float px, float py, int type)
{
	m_Type = type;
	m_Pos.x = px;
	m_Pos.y = py;
	m_Move.x = 0;
	m_Move.y = 0;
	m_bShow = true;
	m_DamageWait = 0;
	m_bWidthOut = true;
	m_EnemyType = Bike;
	m_CurrentMove = m_Move;
	m_bKnockback = false;
	m_KnockbackTime = 0;

	m_bShotTarget = m_bFallFlg;
	m_pEndEffect = NULL;

	if (m_bFallFlg)
		m_HP = ENEMY_2_1_HP;
	else
		m_HP = ENEMY_2_2_HP;

	//弾用変数のInitialize
	m_ShotWait = ENEMY_SHOT_WAIT;

	//アニメーションを作成
	SpriteAnimationCreate anim[] = {
		{
			"移動",
			0,0,192,64,TRUE,
			{{5,0,0}}
		},
		{
			"ダメージ",
			0,0,192,64,FALSE,
			{{5,0,0}}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);
}

/**
*更新
*
* [in] wx:スクリーン座標
**/
void CEnemy_2::Update(float wx)
{
	ReturnWaitStates();
	if (m_Pos.x - wx + m_pTexture->GetWidth() <= 0 || m_Pos.x - wx > g_pGraphics->GetTargetWidth())
	{
		m_bWidthOut = false;
	}
	else
	{
		m_bWidthOut = true;
	}

	//弾の更新
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
	{
		m_ShotArray[i].Update(wx);
	}

	if (m_bReverse)
	{
		m_Move.x = 5.0f;
	}
	else
	{
		m_Move.x = -5.0f;
	}

	if (!m_bWidthOut)
		return;

	if (!m_bShow)
		return;

	if (m_bKnockback)
	{
		//TODO::ノックバック中の処理
		KnockBack();
		return;
	}
	else if (m_pEndEffect)
		return;

	//ダメージ中の動作
	if (m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		m_ShotWait = ENEMY_SHOT_WAIT;

		//ダメージモーション終了で元に戻す
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
			if (m_HP <= 0)
			{
				m_bShow = false;
				//爆発エフェクトを発生させる
				m_pEffectManager->Start(m_Pos.x + m_SrcRect.GetWidth() * 0.5f, m_Pos.y + m_SrcRect.GetHeight() * 0.5f, EFC_EXPLOSION01);
			}
		}
		//TODO::余裕があればダメージ中のノックバック
	}

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
			if (m_ShotArray[i].GetShow())
				continue;

			m_ShotWait = ENEMY_SHOT_WAIT;

			if (m_bShotTarget)
			{
				if (m_bReverse)
				{
					if (m_Pos.x < m_TargetPosX)
					{
						m_ShotArray[i].Fire(m_Pos.x + m_SrcRect.GetWidth(), m_Pos.y + 30, 8, 0);
					}
				}
				else
				{
					if (m_Pos.x > m_TargetPosX)
					{
						m_ShotArray[i].Fire(m_Pos.x + 30, m_Pos.y + 30, -8, 0);
					}
				}
				break;
			}
			else
			{
				if (m_bReverse)
				{
					if (m_Pos.x < m_TargetPosX)
					{
						if (!ShotTarget(i))
							break;
					}
				}
				else
				{
					if (m_Pos.x > m_TargetPosX)
					{
						if (!ShotTarget(i))
							break;
					}
				}
				break;
			}
		}
	}
	else
	{
		m_ShotWait--;
	}

	AbStateMoveDec();

	//重力
	m_Move.y += GRAVITY;
	if (m_Move.y >= 20.0f) { m_Move.y = 20.0f; }


	m_CurrentMove = m_Move;
	//m_Pos.y += m_Move.y;
	m_Pos += m_Move;

	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();
}

bool CEnemy_2::ShotTarget(int i)
{
	//弾の発射位置
	float stx = m_Pos.x + 30;
	float sty = m_Pos.y + 30;
	//目標地点に向かうための方向
	float dx = m_TargetPosX - stx;
	float dy = m_TargetPosY - sty;
	//目標地点までの距離を求める
	float d = sqrt(dx * dx + dy * dy);
	//距離が0以下 = 完全に同じ位置の場合は発射しない
	if (d <= 0)
		return false;
	//方向を正規化
	dx /= d;
	dy /= d;
	m_ShotArray[i].Fire(stx, sty, dx * 5, dy * 5);
	return true;
}

/**
*ステージとの当たり
*
*引数
*[in]		ox		x埋まり量
*[in]		oy		y埋まり量
*/

void CEnemy_2::CollisionStage(float ox, float oy)
{
	if (ox != 0 && !m_bKnockback)
	{
		m_bReverse = !m_bReverse;
	}
	m_Pos.x += ox;
	m_Pos.y += oy;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する
	if (oy < 0 && m_Move.y > 0)
	{
		m_Move.y = 0;
	}
	else if (oy > 0 && m_Move.y < 0)
	{
		m_Move.y = 0;
	}
}

/**
*崖判定用Rectを返す
*
*/

CRectangle CEnemy_2::GetLedgeCheckRect()
{
	if (!m_bReverse)
	{
		return CRectangle(m_Pos.x - 10, m_Pos.y + m_SrcRect.GetHeight(), m_Pos.x, m_Pos.y + m_SrcRect.GetHeight() + 64);
	}
	else
	{
		return CRectangle(m_Pos.x + m_SrcRect.GetWidth(), m_Pos.y + m_SrcRect.GetHeight(), m_Pos.x + m_SrcRect.GetWidth() + 10, m_Pos.y + m_SrcRect.GetHeight() + 64);
	}
}

void CEnemy_2::Damage(float dmg)
{
	if (m_bKnockback || m_pEndEffect)
		return;

	DeffenceProc(dmg);

	if (m_HP <= 0 && m_bShow)
	{
		m_pEndEffect = m_pEffectManager->Start(m_Pos.x + (m_SrcRect.GetWidth() * 0.5), m_Pos.y + (m_SrcRect.GetHeight() * 0.5), EFC_EXPLOSION01);
		for (int i = 0; i < SE_COUNT; i++)
		{
			if (m_pSEManager[i].IsPlaySE())
				continue;
			m_pSEManager[i].SEPlayer(SE_ENEMY_DIE);
			break;
		}
		m_bShow = false;
	}
	else if(m_DamageWait <= 0)
	{
		for (int i = 0; i < SE_COUNT; i++)
		{
			if (m_pSEManager[i].IsPlaySE())
				continue;
			m_pSEManager[i].SEPlayer(SE_ENEMY_DAMAGE);
			break;
		}

		m_bKnockback = true;
		Flip();
		m_Move.y = -ENEMY_KNOCKBACK_POWER_Y;
	}
}

void CEnemy_2::KnockBack()
{
	m_KnockbackTime += CUtilities::GetFrameSecond();
	m_Move.y += GRAVITY;
	if (m_Move.y >= 20.0f) { m_Move.y = 20.0f; }
	m_Move.x = m_CurrentMove.x * -1;
	m_Pos += m_Move;

	if (m_KnockbackTime >= ENEMY_KNOCKBACK_TIME)
	{
		m_bKnockback = false;
		m_KnockbackTime = 0;
		m_Move = m_CurrentMove;
	}
}

/**
*描画
*
*引数
*[in]		wx		スクロール値x
*[in]		wy		スクロール値y
*/
void CEnemy_2::Render(float wx, float wy)
{
	//非表示
	if (!m_bShow)
		return;

	//弾の描画
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
	{
		m_ShotArray[i].Render(wx, wy);
	}

	//インターバル2フレームごとに描画をしない
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}

	//描画短径
	CRectangle dr = m_SrcRect;
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
	}

	//テクスチャの描画
	if (m_bFallFlg)
		(GetAbStateNo() == STATE_FROST) ? m_pTexture->Render(m_Pos.x - wx, m_Pos.y - wy, dr, MOF_XRGB(0, 255, 255)) : m_pTexture->Render(m_Pos.x - wx, m_Pos.y - wy, dr);
	else
		(GetAbStateNo() == STATE_FROST) ? m_pTexture->Render(m_Pos.x - wx, m_Pos.y - wy, dr, MOF_XRGB(0, 255, 255)) : m_pTexture->Render(m_Pos.x - wx, m_Pos.y - wy, dr, MOF_XRGB(255, 255, 100));
}

/**
*デバッグ
*
*引数
*[in]		wx		スクロール値x
*[in]		wy		スクロール値y
*/
void CEnemy_2::RenderDebug(float wx, float wy)
{
	if (!m_bShow)
		return;

	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 0, 0));

	//崖チェックのRect
	hr = GetLedgeCheckRect();
	CGraphicsUtilities::RenderFillRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(255, 255, 0));

	//弾の描画
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
		m_ShotArray[i].RenderDebug(wx, wy);
}

void CEnemy_2::SetTexture(CTexture* pt, CTexture* st)
{
	m_pTexture = pt;
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++) { m_ShotArray[i].SetTexture(st); }
}

void CEnemy_2::DeffenceProc(int dmg) {
	if (m_bFallFlg)
		m_Deffence = ENEMY_2_1_DEFFENCE_POWER;
	else
		m_Deffence = ENEMY_2_2_DEFFENCE_POWER;

	float deff = m_Deffence - dmg;

	if (deff < 0) { m_HP += deff; }
}
/**
*解放
*
*/
void CEnemy_2::Release()
{
	m_Motion.Release();
}