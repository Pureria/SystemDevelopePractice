#include	"Player.h"

/**
 * コンストラクタ
 *
 */
CPlayer::CPlayer() :
m_Texture() ,
m_Motion() ,
m_PosX(0.0f) ,
m_PosY(0.0f) ,
m_bMove(false) ,
m_MoveX(0.0f) ,
m_MoveY(0.0f) ,
m_bJump(false) ,
m_bDead(false),
m_bReverse(false) ,
m_SrcRect(),
m_pEffectManager(),
m_pEndEffect(),
m_DamageWait(0),
m_ShotWait(0),
m_bTop(false),
m_bBottom(false),
m_ShotType(NORMAL),
m_NatuType(FIRE),
m_DrcType(RIGHT),
m_HP(0),
m_SP(0),
m_bGoal(false),
m_PlShotAry(),
m_NextBossScene(false){
}

/**
 * 読み込み
 * 利用するテクスチャを読み込む。
 */
bool CPlayer::Load(void){
	//テクスチャの読み込み
	if (!m_Texture.Load("player.png"))				{		return false;	}

	if (!m_FrameTexture.Load("Frame.png"))			{		return false;	}

	if (!m_HPTexture.Load("HP.png"))				{		return false;	}

	if (!m_HPBarTexture.Load("HPBAR.png"))			{		return false;	}	
	
	if (!m_SPTexture.Load("SP.png"))				{		return false;	}

	if (!m_SPBarTexture.Load("SPBAR.png"))			{		return false;	}

	if (!m_ShotHealTex.Load("P_missile.png"))		{		return false;	}

	if (!m_ShotHeavyTex.Load("HeavyAmmo.png"))		{		return false;	}

	//if (!m_LaserTex.Load("Shot.png")) { return false; }

	//TODO: Fire関数に移動
	for (int i = 0; i < PLAYERSHOT_COUNT; i++) {
		m_PlShotAry[i].SetHealTexture(&m_ShotHealTex); 
	}

	//for (int i = 0; i < PLAYERSHOT_COUNT; i++) { m_Laser[i].SetTexture(&m_LaserTex); }

	//アニメーションを作成
	SpriteAnimationCreate anim[] = {
		{
			"待機",
			0,0,
			120,128,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},{5,6,0},{5,7,0}}
		},
		{
			"移動",
			0,70,
			120,128,
			TRUE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0}}
		},
		{
			"ジャンプ移動",
			0,140,
			120,128,
			FALSE,{{5,0,0},{5,1,0},{5,2,0},{5,3,0}}
		},
		{
			"ジャンプ終了",
			240,140,
			120,128,
			FALSE,{{2,0,0},{2,1,0}}
		},
		{
			"攻撃",
			0,350,
			120,128,
			FALSE,{{2,0,0},{2,1,0},{2,2,0},{2,3,0},{2,4,0},{2,5,0},{2,6,0}}
		},
		{
			"ダメージ",
			480,0,
			120,128,
			FALSE,{{20,0,0}}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);
	
	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 * プレイヤーの位置など状態を初期化したいときに実行する。
 */
void CPlayer::Initialize(void){
	m_PosX = 200;
	m_PosY = 0;
	m_bMove = false;
	m_MoveX = 0.0f;
	m_MoveY = 0.0f;
	m_bReverse = false;
	m_bJump = false;
	m_HP = 100;
	m_DamageWait = 0;
	m_Motion.ChangeMotion(MOTION_WAIT);
	m_bDead = false;
	m_pEndEffect = NULL;
	m_bGoal = false;
	m_bTop = false;
	m_bBottom = false;
	m_ShotType = NORMAL;
	m_NatuType = NULL;
	m_DrcType = NULL;
	//プレイヤーの素材読み込み
	Load();
	m_NextBossScene = false;
}

/**
 * 更新
 *
 */
void CPlayer::Update() {
	UpdateShot();
	//TODO: ゲームパッド使用時
	//g_pInput->GetGamePad(m_GamePadCnt);

	//HPが無くなると爆発の終了を待機して終了
	PlayerEnd();

	//移動フラグ、このフレームでの移動があったかを保存
	m_bMove = false;
	//攻撃中、着地の場合の動作
	if (m_Motion.GetMotionNo() == MOTION_ATTACK || m_Motion.GetMotionNo() == MOTION_JUMPEND)
	{
		//終了で待機に戻す
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	else if(m_Motion.GetMotionNo() == MOTION_DAMAGE)
	{
		//終了で待機に戻す
		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	else
	{
		//キー入力による動作
		UpdateKey();
		//TODO: ゲームパッドの接続確認
	/*if (m_pGamePad != nullptr) {
		UpdatePadKey(m_pGamePad);//ゲームパッドによる動作
	}//*/
	}

	//移動更新
	UpdateMove();
	//実際に座標を移動させる
	m_PosX += m_MoveX;
	m_PosY += m_MoveY;

	Fall();
	
	//アニメーションの更新
	m_Motion.AddTimer(CUtilities::GetFrameSecond());
	m_SrcRect = m_Motion.GetSrcRect();

	if (m_HP >= 100) {
		m_HP = 100;
	}

	//ダメージのインターバルを減らす
	if (m_DamageWait > 0)
	{
		m_DamageWait--;
	}

}

/**
 * キー入力による動作更新
 *
 */
void CPlayer::UpdateKey( void ) {
	//キーボードでの移動処理
	MoveKey();

	//弾の特性切り替え
	BulletChange();

	//銃口の向く処理
	DirecTpBtm();

	//弾の特性変化の処理
	NatuChange();

	//SPACEキーで攻撃
	ShotManager();

}

//プレイヤーの動きの制限
void CPlayer::MoveKey() {
	//入力で直接座標を動かすのではなく、速度を変化させる
	//攻撃中は移動できないようにする
	if (g_pInput->IsKeyHold(MOFKEY_A))
	{
		m_MoveX -= PLAYER_SPEED;
		m_bReverse = true;
		m_bMove = true;
		if (m_MoveX < -PLAYER_MAXSPEED)
		{
			m_MoveX = -PLAYER_MAXSPEED;
		}
		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}

	else if (g_pInput->IsKeyHold(MOFKEY_D))
	{
		m_MoveX += PLAYER_SPEED;
		m_bReverse = false;
		m_bMove = true;
		if (m_MoveX > PLAYER_MAXSPEED)
		{
			m_MoveX = PLAYER_MAXSPEED;
		}
		if (m_Motion.GetMotionNo() == MOTION_WAIT)
		{
			m_Motion.ChangeMotion(MOTION_MOVE);
		}
	}

	//Eキーでジャンプ
	if (g_pInput->IsKeyHold(MOFKEY_SPACE) && !m_bJump)
	{
		m_bJump = true;
		m_MoveY = PLAYER_JUMP;
		m_Motion.ChangeMotion(MOTION_JUMPSTART);
	}
}

//弾の種類を変える処理
void CPlayer::BulletChange() {
	if (g_pInput->IsKeyPush(MOFKEY_I)) {
		Change();
	}
}

void CPlayer::Change() {
	if (m_ShotType == NORMAL) {
		m_ShotType = LASER;
		m_NatuType = FIRE;
	}
	else {
		m_ShotType = NORMAL;
		m_NatuType = HEAL;
	}
}

//弾の特性を変える処理
void CPlayer::NatuChange() {
	if (g_pInput->IsKeyPush(MOFKEY_O)) {
		switch (m_NatuType)
		{
		case FIRE:
			m_NatuType = FROST;
			break;
		case FROST:
			m_NatuType = FIRE;
			break;
		case HEAL:
			m_NatuType = HEAVY;
			break;
		case HEAVY:
			m_NatuType = HEAL;
			break;
		}
	}
}

void CPlayer::ShotManager() {
	if (IsLaser()) {
		FireShotLaser();
	}
	else {
		FireShot();
	}
}

//弾の方向を変える処理
void CPlayer::DirecTpBtm() {
	if (g_pInput->IsKeyPush(MOFKEY_W) && !m_bTop) {
		m_bTop = true;
		m_bBottom = false;

	}
	else if (g_pInput->IsKeyPush(MOFKEY_W) && m_bTop) {
		m_bTop = false;//銃口を元に戻す
	}
	if (g_pInput->IsKeyPush(MOFKEY_S) && !m_bBottom) {
		m_bBottom = true;
		m_bTop = false;
	}
	else if (g_pInput->IsKeyPush(MOFKEY_S) && m_bBottom) {
		m_bBottom = false;
	}
}

//弾を撃つ処理
void CPlayer::FireShot() {
	//弾の発射

	if (m_ShotWait <= 0)
	{
		if (g_pInput->IsKeyPush(MOFKEY_P))
		{
			m_Motion.ChangeMotion(MOTION_ATTACK);

			for (int i = 0; i < PLAYERSHOT_COUNT; i++) {
				if (m_PlShotAry[i].GetShow())
				{
					continue;
				}
				m_ShotWait = PLAYERSHOT_WAIT;

				ShotRev(i);
				break;
			}
		}
	}
	else
	{
		m_ShotWait--;
	}
}

//弾の向きを撃つ瞬間にセット
void CPlayer::ShotRev(int i) {
	if (!m_bReverse) {
		if (m_bTop) {
			m_PlShotAry[i].Fire(SetStartPos(), RIGHTTOP, m_NatuType);
		}
		else if (m_bBottom) {
			m_PlShotAry[i].Fire(SetStartPos(), RIGHTBOTTOM, m_NatuType);
		}
		else {
			m_PlShotAry[i].Fire(SetStartPos(), RIGHT, m_NatuType);
		}
	}
	else {
		if (m_bTop) {
			m_PlShotAry[i].Fire(SetStartPos(), LEFTTOP, m_NatuType);
		}
		else if (m_bBottom) {
			m_PlShotAry[i].Fire(SetStartPos(), LEFTBOTTOM, m_NatuType);
		}
		else {
			m_PlShotAry[i].Fire(SetStartPos(), LEFT, m_NatuType);
		}
	}
}

void CPlayer::FireShotLaser() {
	//弾の発射

	if (m_ShotWait <= 0)
	{
		if (g_pInput->IsKeyPush(MOFKEY_P))
		{
			m_Motion.ChangeMotion(MOTION_ATTACK);

			for (int i = 0; i < PLAYERSHOT_COUNT; i++) {
				if (m_Laser[i].GetShow()) { continue; }
				m_ShotWait = PLAYERSHOT_WAIT;
				ShotRevLaser(i);
				break;
			}
		}
	}
	else
	{
		m_ShotWait--;
	}
}

//弾の向きを撃つ瞬間にセット
void CPlayer::ShotRevLaser(int i) {
	if (!m_bReverse) {
		if (m_bTop) {
			m_Laser[i].Fire(SetStartPos(), RIGHTTOP, m_NatuType);
		}
		else if (m_bBottom) {
			m_Laser[i].Fire(SetStartPos(), RIGHTBOTTOM, m_NatuType);
		}
		else {
			m_Laser[i].Fire(SetStartPos(), RIGHT, m_NatuType);
		}
	}
	else {
		if (m_bTop) {
			m_Laser[i].Fire(SetStartPos(), LEFTTOP, m_NatuType);
		}
		else if (m_bBottom) {
			m_Laser[i].Fire(SetStartPos(), LEFTBOTTOM, m_NatuType);
		}
		else {
			m_Laser[i].Fire(SetStartPos(), LEFT, m_NatuType);
		}
	}
}


//弾の更新
void CPlayer::UpdateShot() {
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_Laser[i].Update();
		m_PlShotAry[i].Update();
	}
}

/**
 * 移動更新
 *
 */
void CPlayer::UpdateMove(void){
	//このフレームでの移動入力がなければ減速処理を実行する
	if (!m_bMove)
	{
		if (m_MoveX > 0)
		{
			m_MoveX -= PLAYER_SPEED;
			if (m_MoveX <= 0)
			{
				m_MoveX = 0;
			}
		}
		else if (m_MoveX < 0)
		{
			m_MoveX += PLAYER_SPEED;
			if (m_MoveX >= 0)
			{
				m_MoveX = 0;
			}
		}
		else if (m_Motion.GetMotionNo() == MOTION_MOVE)
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}
	//重力により少しずつ下がる
	if (IsJump())
	{
		m_MoveY += GRAVITY;
	}
	else
	{
		m_MoveY += GRAVITY + 0.2f;
	}

	if (m_MoveY >= 20.0f)
	{
		m_MoveY = 20.0f;
	}
}

void CPlayer::PlayerDamage(bool flg,float damage)
{
	//HPが無くなると当たり判定しない
	if (m_HP <= 0)
		return;


	//ダメージ中のため当たり判定を行わない
	if (m_DamageWait > 0)
		return;

	m_HP -= damage;
	m_DamageWait = 60;
	if (flg)
	{
		m_MoveX = -5.0f;
		m_bReverse = false;
	}
	else
	{
		m_MoveX = 5.0f;
		m_bReverse = true;
	}

	if (m_HP <= 0)
	{
		//爆発エフェクトを発生させる
		m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
	}
	else
	{
		//ダメージエフェクトを発生させる
		m_pEffectManager->Start(SetStartPos(), EFC_DAMAGE);
	}

}

bool CPlayer::CollisionEnemy_1(CEnemy& ene) {
	if (!ene.GetShow()) 
		return false;
	
	//HPが無くなると当たり判定しない
	if (m_HP <= 0)
		return false;


	//ダメージ中のため当たり判定を行わない
	if (m_DamageWait > 0) 
		return false;

	//敵の短径と自分の短径でダメージ
	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();

	//砲台との当たり判定
	/*
	if (prec.CollisionRect(erec))
	{
		m_HP -= 5;
		m_DamageWait = 60;
		if (prec.Left < erec.Left)
		{
			m_MoveX = -5.0f;
			m_bReverse = false;
		}
		else
		{
			m_MoveX = 5.0f;
			m_bReverse = true;
		}
		m_Motion.ChangeMotion(MOTION_DAMAGE);

		if (m_HP <= 0)
		{
			//爆発エフェクトを発生させる
			m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
		}
		else
		{
			//ダメージエフェクトを発生させる
			m_pEffectManager->Start(SetStartPos(), EFC_DAMAGE);
		}
		return true;
	}
	*/

	//敵の弾との当たり判定
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
	{
		if (!ene.ShotArrayBool(i))
			continue;
		CRectangle esrec = ene.ShotArrayRect(i);
		if (prec.CollisionRect(esrec))
		{
			m_HP -= 5;
			m_DamageWait = 60;
			if (prec.Left < erec.Left)
			{
				m_MoveX = -5.0f;
				m_bReverse = false;
			}
			else
			{
				m_MoveX = 5.0f;
				m_bReverse = true;
			}
			m_Motion.ChangeMotion(MOTION_DAMAGE);

			if (m_HP <= 0)
			{
				//爆発エフェクトを発生させる
				m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
			}
			else
			{
				//ダメージエフェクトを発生させる
				m_pEffectManager->Start(SetStartPos(), EFC_DAMAGE);
			}
		}

	}


	//敵と弾の当たり判定
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!IsLaser()) {
			if (!m_PlShotAry[i].GetShow()) { continue; }
			CRectangle srec = m_PlShotAry[i].GetRect();
			if (srec.CollisionRect(erec))
			{
				switch (m_PlShotAry[i].GetNatu())
				{
				case HEAL:
					m_HP += HEAL_POWER;
					break;

				case HEAVY:
					ene.SetShotShow(false, i);
					break;
				}
				m_PlShotAry[i].SetShow(false);
				break;
			}
		}
		else {
			if (!m_Laser[i].GetShow()) { continue; }
			CRectangle lrec = m_Laser[i].GetRect();
			
			if (lrec.CollisionRect(erec))
			{
				break;
			}
		}
	}

	//プレイヤーと敵の弾同士の当たり判定
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_PlShotAry[i].GetShow()) { continue; }

		CRectangle srec = m_PlShotAry[i].GetRect();
		for (int j = 0; j < ENEMY_SHOT_COUNT; j++) {
			CRectangle esrec = ene.ShotArrayRect(j);
			if (srec.CollisionRect(esrec))
			{
				switch (m_PlShotAry[i].GetNatu())
				{
				case HEAL:
					m_PlShotAry[i].SetShow(false);
					ene.SetShotShow(false, j);
					break;

				case HEAVY:
					ene.SetShotShow(false, j);
					break;
				}
				break;
			}
		}
	}


	return false;

}

bool CPlayer::Collision_Stage1_Boss(CEnemy_Stage1_Boss& boss) {
	if (!boss.GetShow())
		return false;

	//HPが無くなると当たり判定しない
	if (m_HP <= 0)
		return false;


	//ダメージ中のため当たり判定を行わない
	if (m_DamageWait > 0)
		return false;

	//敵の短径と自分の短径でダメージ
	CRectangle prec = GetRect();
	CRectangle erec = boss.GetRect();

	if (prec.CollisionRect(erec))
	{
		DeffenceProc(5);
		m_DamageWait = 60;
		if (prec.Left < erec.Left)
		{
			m_MoveX = -5.0f;
			m_bReverse = false;
		}
		else
		{
			m_MoveX = 5.0f;
			m_bReverse = true;
		}
		m_Motion.ChangeMotion(MOTION_DAMAGE);

		if (m_HP <= 0)
		{
			//爆発エフェクトを発生させる
			m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
		}
		else
		{
			//ダメージエフェクトを発生させる
			m_pEffectManager->Start(SetStartPos(), EFC_DAMAGE);
		}
		return true;
	}

	//攻撃中の場合のみ攻撃との当たり判定を実行
	if (m_Motion.GetMotionNo() != MOTION_ATTACK)
		return false;

	return false;

}
/**当たり判定
* 引数のアイテムに対して短径同士の当たり判定を実行する
* 当たっていた場合はプレイヤーの状態を変更する
* 
* 引数
* [in]			itm			判定を行うアイテム
* 
* 戻り値
* 当たっている場合はtrue、当たっていなければfalseを返す
* */
bool CPlayer::ColisionItem(CItem& itm)
{
	if (!itm.GetShow())
	{
		return false;
	}

	//アイテムの短径と自分の短径で当たり判定
	CRectangle prec = GetRect();
	CRectangle irec = itm.GetRect();
	if (prec.CollisionRect(irec))
	{
		itm.Effect(m_HP, m_bGoal,IsJump(),m_NextBossScene,m_MoveX,m_MoveY);
		return true;
	}
	return false;
}

bool CPlayer::CollisionAttackItem(CItem& itm)
{
	//TODO::弾の種類によって処理の実行

	CRectangle irec = itm.GetRect();
	//蜘蛛の巣削除処理

	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_Laser[i].GetShow())
			return false;

		CRectangle srec = m_Laser[i].GetRect();
		if (irec.CollisionRect(srec))
		{
			switch (itm.GetType())
			{
			case ITEM_SPIDERWEB:
				if(m_Laser[i].GetNatu() == FIRE)
					itm.SetShow(false);
				break;
			default:
				break;
			}
			return true;
		}
	}
	return false;
}

/**
 * プレイヤー死亡時の処理
 *
 */
void CPlayer::PlayerEnd() {
	if (m_HP <= 0)
	{
		if (!m_pEndEffect || !m_pEndEffect->GetShow())
		{
			m_bDead = true;
		}
		return;
	}
}

//プレイヤーの落下処理
void CPlayer::Fall() {
	//画面外で落下としてHPを0にする
	if (m_PosY >= g_pGraphics->GetTargetHeight() && m_HP > 0)
	{
		m_HP = 0;
		//爆発エフェクトを発生させる
		m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
	}
}

//ステージとの当たり判定
void CPlayer::CollisionStage(float ox, float oy)
{
	m_PosX += ox;
	m_PosY += oy;
	//落下中の下埋まり、ジャンプ中の上埋まりの場合は移動を初期化する
	if (oy < 0 && m_MoveY >0)
	{
		m_MoveY = 0;
		if (m_bJump)
		{
			m_bJump = false;
			m_Motion.ChangeMotion(MOTION_JUMPEND);
		}
	}
	
	else if (oy > 0 && m_MoveY < 0)
	{
		m_MoveY = 0;
	}
	//左移動中の左埋まり、右移動中の右埋まりの場合は移動を初期化する
	if (ox < 0 && m_MoveX > 0)
	{
		m_MoveX = 0;
	}
	else if (ox > 0 && m_MoveX < 0)
	{
		m_MoveX = 0;
	}
}

bool CPlayer::IsJump()
{
	if (m_MoveY < 0)
		return true;
	else
		return false;
}

/**
 * 描画
 *
 */
void CPlayer::Render(float wx,float wy){
	//弾の描画
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_Laser[i].Render(wx, wy);
		m_PlShotAry[i].Render(wx, wy);
	}

	//インターバル2フレームごとに描画をしない
	if (m_DamageWait % 4 >= 2)
	{
		return;
	}

	//描画短径
	CRectangle dr = m_SrcRect;
	//描画位置
	float px = m_PosX - wx;
	float py = m_PosY - wy;
	//反転フラグがONの場合描画短径を反転させる
	if (m_bReverse)
	{
		float tmp = dr.Right;
		dr.Right = dr.Left;
		dr.Left = tmp;
		if (m_Motion.GetMotionNo() == MOTION_ATTACK)
		{
			px -= PLAYER_ATTACKWIDTH;
		}
	}
	//テクスチャの描画
	m_Texture.Render(px, py, dr);
}

void CPlayer::RenderStatus(void) {
	m_HPTexture.Render(0,0);
	m_SPTexture.Render(0,0);
	//HPに応じて短径の幅を変化させる
	CRectangle hprec(0, 0, 1064 * (m_HP * 0.01f), 64);
	m_HPBarTexture.Render(10, 0, hprec);
	CRectangle sprec(0, 0, 1064 * (m_SP * 0.01f), 64);
	m_SPBarTexture.Render(248, 20, sprec);
	//フレームを上部に描画
	m_FrameTexture.Render(0, 0);
}

/**
 * デバッグ描画
 *
 */
void CPlayer::RenderDebug(float wx, float wy){
	//位置の描画
	CGraphicsUtilities::RenderString(10,70,"プレイヤー位置 X : %.0f , Y : %.0f , Move_Y : %.0f",m_PosX,m_PosY,m_MoveY);
	if(m_NextBossScene)
		CGraphicsUtilities::RenderString(10,130, "ボス部屋フラグ : TRUE");
	else
		CGraphicsUtilities::RenderString(10, 130, "ボス部屋フラグ : FALSE");
	//当たり判定の表示
	CRectangle hr = GetRect();
	CGraphicsUtilities::RenderRect(hr.Left - wx, hr.Top - wy, hr.Right - wx, hr.Bottom - wy, MOF_XRGB(0, 255, 0));

	CGraphicsUtilities::RenderCircle(m_PosX - wx + 30,m_PosY - wy + 30, 2, MOF_XRGB(255, 0, 0));
	for (int i = 0; i < PLAYERSHOT_COUNT; i++) {
		m_PlShotAry[i].RenderDebug(wx, wy);
		m_Laser[i].RenderDebug(wx,wy);
	}
}

/**
 * 解放
 *
 */
void CPlayer::Release(void){
	m_Texture.Release();
	m_Motion.Release();
	m_FrameTexture.Release();
	m_HPTexture.Release();
	m_HPBarTexture.Release();
	m_SPTexture.Release();
	m_SPBarTexture.Release();
	m_ShotHealTex.Release();
	m_ShotHeavyTex.Release();
}
