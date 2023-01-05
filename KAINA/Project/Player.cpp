#include	"Player.h"

// 特殊な呼び出しがされる処理
#pragma region 特殊関数

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
m_NextBossScene(false){}

#pragma endregion


//読み込み処理
#pragma region Load関数

bool CPlayer::Load(){
	//テクスチャの読み込み
	if (!m_Texture.Load("Player/chara_ren.png"))				{		return false;	}

	if (!m_FrameTexture.Load("Player/Frame.png"))				{		return false;	}

	if (!m_HPTexture.Load("Player/HP.png"))						{		return false;	}

	if (!m_HPBarTexture.Load("Player/HPBAR.png"))				{		return false;	}	
	
	if (!m_SPTexture.Load("Player/SP.png"))						{		return false;	}

	if (!m_SPBarTexture.Load("Player/SPBAR.png"))				{		return false;	}

	if (!m_ShotHealTex.Load("Player/healammo.png"))				{		return false;	}

	if (!m_ShotHeavyTex.Load("Player/heavyammo.png"))			{		return false;	}

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
			0,640,
			128,128,
			TRUE,
			{		
					{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},
					{5,6,0},{5,7,0},{5,8,0},{5,9,0},{5,10,0},{5,11,0},
					{5,12,0},{5,13,0},{5,14,0},{5,15,0},{5,16,0},{5,17,0},
					{5,18,0},{5,19,0},{5,20,0},{5,21,0},{5,22,0},{5,23,0},
					{5,24,0},{5,25,0},{5,26,0},{5,27,0},{5,28,0},{5,29,0}
			}
		},
		{
			"移動",
			0,0,
			128,128,
			TRUE,
			{		
					{5,0,0},{5,1,0},{5,2,0},{5,3,0},{5,4,0},{5,5,0},
					{5,6,0},{5,7,0},{5,8,0},{5,9,0},{5,10,0},{5,11,0},
					{5,12,0},{5,13,0},{5,14,0},{5,15,0},{5,16,0},{5,17,0},
					{5,18,0},{5,19,0},{5,20,0},{5,21,0},{5,22,0},{5,23,0},
					{5,24,0},{5,25,0},{5,26,0},{5,27,0},{5,28,0},{5,29,0}
			}
		},
		{
			"ジャンプ移動",
			0,1408,
			128,128,
			FALSE,
			{
					{5,0,0},{5,1,0},{5,2,0},
			}
		},
		{
			"ジャンプ終了",
			256,1408,
			128,128,
			FALSE,
			{
					{2,0,0},{2,1,0},{2,2,0},{2,3,0},
			}
		},
		{
			"攻撃",
			0,640,
			128,128,
			FALSE,
			{
					{5,24,0},{5,24,1},{5,24,2},{5,24,3}
			}
		},
		{
			"通常弾の銃口上げる",
			0,0,
			128,128,
			FALSE,
			{
					{2,0,0},{2,1,0},{2,2,0},{2,3,0},
			}
		},
		{
			"通常弾の銃口下げる",
			0,0,
			128,128,
			FALSE,
			{
					{2,0,0},{2,1,0},{2,2,0},{2,3,0},
			}
		},
		{
			"レーザーの銃口上げる",
			0,0,
			128,128,
			FALSE,
			{
					{2,0,0},{2,1,0},{2,2,0},{2,3,0},
			}
		},
		{
			"レーザーの銃口下げる",
			0,0,
			128,128,
			FALSE,
			{
					{2,0,0},{2,1,0},{2,2,0},{2,3,0},
			}
		},
		{
			"ダメージ",
			0,1280,
			128,128,
			FALSE,
			{
					{5,29,0}
			}
		},
	};
	m_Motion.Create(anim, MOTION_COUNT);
	
	return true;
}

#pragma endregion


//初期化処理
#pragma region Initialize関数


void CPlayer::Initialize(){
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


#pragma endregion


//更新
#pragma region Update関数

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
	/*else if (m_Motion.GetMotionNo() == MOTION_NORMAL_MUZZLETOP || m_Motion.GetMotionNo() == MOTION_NORMAL_MUZZLEBOTTOM
			|| m_Motion.GetMotionNo() == MOTION_LASER_MUZZLETOP || m_Motion.GetMotionNo() == MOTION_LASER_MUZZLEBOTTOM) {

		if (m_Motion.IsEndMotion())
		{
			m_Motion.ChangeMotion(MOTION_WAIT);
		}
	}//*/
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


void CPlayer::UpdateShot() {
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		m_Laser[i].Update();
		m_PlShotAry[i].Update();
	}
}


void CPlayer::UpdateMove(){
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


void CPlayer::UpdateKey() {

	MoveKey();

	BulletChange();

	DirecTpBtmChange();

	NatuChange();

	ShotManager();

}


#pragma endregion


//キー入力による動作更新/
#pragma region Move関数


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


#pragma endregion


//変える処理
#pragma region Change関数

void CPlayer::BulletChange() {
	if (g_pInput->IsKeyPush(MOFKEY_I)) {
		TypeChange();
	}
}

void CPlayer::TypeChange() {
	if (m_ShotType == NORMAL) {
		m_ShotType = LASER;
		m_NatuType = FIRE;
	}
	else {
		m_ShotType = NORMAL;
		m_NatuType = HEAL;
	}
}

void CPlayer::NatuChange() {
	if (g_pInput->IsKeyPush(MOFKEY_O)) {
		switch (m_NatuType)
		{
		case HEAL:
			m_NatuType = HEAVY;
			break;
		case HEAVY:
			m_NatuType = HEAL;
			break;
		case FIRE:
			m_NatuType = FROST;
			break;
		case FROST:
			m_NatuType = FIRE;
			break;
		}
	}
}

void CPlayer::DirecTpBtmChange() {

	if (g_pInput->IsKeyPush(MOFKEY_W) && !m_bTop) {
		m_bTop = true;
		m_bBottom = false;
		if (IsLaser()) {
			m_Motion.ChangeMotion(MOTION_LASER_MUZZLETOP);
		}
		else {
			m_Motion.ChangeMotion(MOTION_NORMAL_MUZZLETOP);
		}
	}
	else if (g_pInput->IsKeyPush(MOFKEY_W) && (m_bTop || m_bBottom)) {
		m_bTop = false;
		m_bBottom = false;
		m_Motion.ChangeMotion(MOTION_WAIT);
	}
	if (g_pInput->IsKeyPush(MOFKEY_S) && !m_bBottom) {
		m_bBottom = true;
		m_bTop = false;
		if (IsLaser()) {
			m_Motion.ChangeMotion(MOTION_LASER_MUZZLEBOTTOM);
		}
		else {
			m_Motion.ChangeMotion(MOTION_NORMAL_MUZZLEBOTTOM);
		}
	}
	else if (g_pInput->IsKeyPush(MOFKEY_S) && (m_bTop || m_bBottom)) {
		m_bBottom = false;
		m_bTop = false;
		m_Motion.ChangeMotion(MOTION_WAIT);
	}
}

void CPlayer::DirecMotionChange() {
	if (GetDirec() == RIGHTTOP || GetDirec() == LEFTTOP) {
		if (IsLaser()) {
			m_Motion.ChangeMotion(MOTION_LASER_MUZZLETOP);
		}
		else {
			m_Motion.ChangeMotion(MOTION_NORMAL_MUZZLETOP);
		}
	}
	else if (GetDirec() == RIGHTBOTTOM || GetDirec() == LEFTBOTTOM) {
		if (IsLaser()) {
			m_Motion.ChangeMotion(MOTION_LASER_MUZZLEBOTTOM);
		}
		else {
			m_Motion.ChangeMotion(MOTION_NORMAL_MUZZLEBOTTOM);
		}
	}
	else {
		m_Motion.ChangeMotion(MOTION_ATTACK);
	}
}

#pragma endregion


//処理の管理
#pragma region Manager処理

void CPlayer::ShotManager() {
	if (IsLaser()) {
		FireShotLaser();
	}
	else {
		FireShot();
	}
}

#pragma endregion


//反射弾の処理
#pragma region Shot関数


//弾を撃つ処理
void CPlayer::FireShot() {
	//弾の発射

	if (m_ShotWait <= 0)
	{
		if (g_pInput->IsKeyPush(MOFKEY_P))
		{
			m_Motion.ChangeMotion(MOTION_ATTACK);
			//DirecMotionChange();
			for (int i = 0; i < PLAYERSHOT_COUNT; i++) {

				if (m_PlShotAry[i].GetShow())	{		continue;		}
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
			return;
		}
		else if (m_bBottom) {
			m_PlShotAry[i].Fire(SetStartPos(), RIGHTBOTTOM, m_NatuType);
			return;
		}
		else {
			m_PlShotAry[i].Fire(SetStartPos(), RIGHT, m_NatuType);
			return;
		}
	}
	else {
		if (m_bTop) {
			m_PlShotAry[i].Fire(SetStartPos(), LEFTTOP, m_NatuType);
			return;
		}
		else if (m_bBottom) {
			m_PlShotAry[i].Fire(SetStartPos(), LEFTBOTTOM, m_NatuType);
			return;
		}
		else {
			m_PlShotAry[i].Fire(SetStartPos(), LEFT, m_NatuType);
			return;
		}
	}
	/*switch (GetDirec())
	{
		case RIGHT:
			m_PlShotAry[i].Fire(SetStartPos(), RIGHT, m_NatuType);
			break;
		case RIGHTTOP:
			m_PlShotAry[i].Fire(SetStartPos(), RIGHTTOP, m_NatuType);
			break;
		case RIGHTBOTTOM:
			m_PlShotAry[i].Fire(SetStartPos(), RIGHTBOTTOM, m_NatuType);
			break;

		case LEFT:
			m_PlShotAry[i].Fire(SetStartPos(), LEFT, m_NatuType);
			break;
		case LEFTTOP:
			m_PlShotAry[i].Fire(SetStartPos(), LEFTTOP, m_NatuType);
			break;
		case LEFTBOTTOM:
			m_PlShotAry[i].Fire(SetStartPos(), LEFTBOTTOM, m_NatuType);
			break;
	}//*/
}

#pragma endregion

//レーザーの処理
#pragma region Laser関数

void CPlayer::FireShotLaser() {
	//弾の発射

	if (m_ShotWait <= 0)
	{
		if (g_pInput->IsKeyPush(MOFKEY_P))
		{
			DirecMotionChange();

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

#pragma endregion


//Playerに影響を与える関数
#pragma region Player関数

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

#pragma endregion


//当たり判定の関数
#pragma region Collision関数


bool CPlayer::CollisionEnemy(CEnemyBase_Shot& ene, int eneType) {
	bool flg = false;

	if (!ene.GetShow()) 
		return flg;
	
	//HPが無くなると当たり判定しない
	if (m_HP <= 0)
		return flg;
	
	//敵の短径と自分の短径でダメージ
	CRectangle prec = GetRect();
	CRectangle erec = ene.GetRect();

	//敵と弾の当たり判定
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_PlShotAry[i].GetShow()) { continue; }
		CRectangle srec = m_PlShotAry[i].GetRect();
		if (srec.CollisionRect(erec))
		{
			if (eneType != Turret)
			{
				if (m_PlShotAry[i].GetNatu() == HEAL)
				{
					//TODO::回復弾の回復量
					m_HP += HEAL_POWER;
					//TODO::ダメージ量
					ene.Damage(10);
				}
				else if (m_PlShotAry[i].GetNatu() == HEAVY)
				{
					//TODO::ダメージ量
					ene.Damage(12);
				}
			}
			m_PlShotAry[i].SetShow(false);
		}

	}

	//敵とレーザーの当たり判定
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_Laser[i].GetShow()) { continue; }

		CRectangle srec = m_Laser[i].GetRect();
		if (srec.CollisionRect(erec))
		{
			if (eneType == Turret)
				continue;

			//TODO::レーザーのダメージ
			if (m_Laser[i].GetNatu() == FIRE) {
				ene.Damage(10);
			}
			else if (m_Laser[i].GetNatu() == FROST) {
				ene.Damage(12);
			}
		}
	}

	//ダメージ中のため当たり判定を行わない
	if (m_DamageWait > 0) 
		return flg;


	//敵との当たり判定
	if (eneType != Turret)
	{
		if (prec.CollisionRect(erec))
		{
			m_HP -= 5;
			m_DamageWait = DAMAGE_WAIT;
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
			flg = true;
		}
	}

	//敵の弾との当たり判定
	for (int i = 0; i < ENEMY_SHOT_COUNT; i++)
	{
		if (!ene.ShotArrayBool(i))
			continue;
		CRectangle esrec = ene.ShotArrayRect(i);
		if (prec.CollisionRect(esrec))
		{
			m_HP -= 5;
			m_DamageWait = DAMAGE_WAIT;
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



	//プレイヤーと敵の弾同士の当たり判定
	for (int i = 0; i < PLAYERSHOT_COUNT; i++)
	{
		if (!m_PlShotAry[i].GetShow()) { continue; }

		CRectangle srec = m_PlShotAry[i].GetRect();
		for (int j = 0; j < ENEMY_SHOT_COUNT; j++) {
			if (!ene.ShotArrayBool(i))
				continue;
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


	return flg;

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
		m_HP -= ENEMY_ATTAK_POWER;
		m_DamageWait = DAMAGE_WAIT;
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

	return false;

}

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


#pragma endregion


//期待値を返す関数
#pragma region Is関数

bool CPlayer::IsJump()
{
	if (m_MoveY < 0)
		return true;
	else
		return false;
}

#pragma endregion


//描画
#pragma region Render関数

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

void CPlayer::RenderStatus() {
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

#pragma endregion


//解放
#pragma region Release関数

void CPlayer::Release(){
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

#pragma endregion


//その他の関数
#pragma region Other関数


void CPlayer::Fall() {
	//画面外で落下としてHPを0にする
	if (m_PosY >= g_pGraphics->GetTargetHeight() && m_HP > 0)
	{
		m_HP = 0;
		//爆発エフェクトを発生させる
		m_pEndEffect = m_pEffectManager->Start(SetStartPos(), EFC_EXPLOSION02);
	}
}


#pragma endregion