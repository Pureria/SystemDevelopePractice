#include	"BaseStage.h"
#include	<sys/stat.h>

/**
 * コンストラクタ
 *
 */
CStage::CStage() :
m_ChipTexture() ,
m_BackTexture() ,
m_ChipSize(0) ,
m_XCount(0) ,
m_YCount(0) ,
m_pChipData(NULL) ,
m_ScrollX(0) ,
m_ScrollY(0),
m_EnemyTextureCount(0),
m_pEnemyTexture(NULL),
m_EnemyCount(0),
m_ItemTextureCount(0),
m_pItemTexture(NULL),
m_ItemCount(0),
m_IniPlayerPos(Vector2(0,0)) {
}

/**
 * デストラクタ
 *
 */
CStage::~CStage(){
}

/**
 * 読み込み
 * 利用するテクスチャとステージファイルを読み込む。
 *
 * 引数
 * [in]			pName				ステージファイルの名前
 */
bool CStage::Load(char* pName , int nowscene){
	//テキストファイルを開く
	FILE* fp = fopen(pName, "rt");
	if (fp == NULL)
	{
		return false;
	}
	//ファイルの全容量を調べる
	fseek(fp, 0, SEEK_END);
	long fSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	//ファイルサイズ分だけのメモリを確保する
	char* pBuffer = (char*)malloc(fSize + 1);
	//ファイルをすべてバッファに読み込む
	fSize = fread(pBuffer, 1, fSize, fp);
	pBuffer[fSize] = '\0';
	char* pstr;

	//strtok : 引数1の文字列から、引数2のトークンが見つかるまでの文字を取得
	//　strtok (pBuffer, ",") : pBufferの文字列から , が見つかるまでの文字を取得
	//テクスチャの読み込み
	pstr = strtok(pBuffer, ",");
	if (!m_BackTexture.Load(pstr))
	{
		return false;
	}

	//strtok : 2回目以降は文字の指定がない場合は前の指定した文字の続きから取得
	//strtok(NULL, ",") : 先ほど取得したpBufferの続きから , が見つかるまでの文字を取得
	pstr = strtok(NULL, ",");
	if (!m_ChipTexture.Load(pstr))
	{
		return false;
	}

	//プレイヤーの初期位置
	m_IniPlayerPos.x = atoi(strtok(NULL, ","));
	m_IniPlayerPos.y = atoi(strtok(NULL, ","));

	//チップサイズ
	//atof : 引数の文字列をfloat(実数型)の値に変換する
	//float.Parse : atof
	m_ChipSize = atof(strtok(NULL, ","));

	//マップのチップ数
	//atof : 引数の文字列をint(整数型)の値に変換する
	//int.Parse : atof
	m_XCount = atoi(strtok(NULL, ","));
	m_YCount = atoi(strtok(NULL, ","));

	//マップチップ用のメモリ確保
	m_pChipData = (char*)malloc(m_XCount * m_YCount);
	//上も下も同じ意味
	//m_pChipData = new char[(m_XCount * m_YCount)];

	//チップデータの読み込み
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			m_pChipData[y * m_XCount + x] = atoi(strtok(NULL, ","));
		}
	}

	if (nowscene == SCENENO_GAME_STAGE1)
	{
		//敵のテクスチャ読み込み
		pstr = strtok(NULL, ",");
		m_EnemyTextureCount = atoi(pstr);
		m_pEnemyTexture = new CTexture[m_EnemyTextureCount];
		for (int i = 0; i < m_EnemyTextureCount; i++)
		{
			pstr = strtok(NULL, ",");
			if (!m_pEnemyTexture[i].Load(pstr))
			{
				return false;
			}
		}

		//敵の弾のテクスチャ読み込み
		pstr = strtok(NULL, ",");
		m_pEnemyShotTexture = new CTexture[m_EnemyTextureCount * ENEMY_SHOT_COUNT];
		for (int i = 0; i < m_EnemyTextureCount * ENEMY_SHOT_COUNT; i++)
		{
			if (!m_pEnemyShotTexture[i].Load(pstr))
				return false;
		}
		//配置データの読み込み
		m_pEnemyData = (char*)malloc(m_XCount * m_YCount);
		m_EnemyCount = 0;
		for (int y = 0; y < m_YCount; y++)
		{
			for (int x = 0; x < m_XCount; x++)
			{
				m_pEnemyData[y * m_XCount + x] = atoi(strtok(NULL, ","));
				if (m_pEnemyData[y * m_XCount + x] > 0)
				{
					m_EnemyCount++;
				}
			}
		}

		//敵2のテクスチャ読み込み
	}
	else if (nowscene == SCENENO_GAME_STAGE1_BOSS)
	{

	}

	//アイテムのテクスチャ読み込み
	pstr = strtok(NULL, ",");
	m_ItemTextureCount = atoi(pstr);
	m_pItemTexture = new CTexture[m_ItemTextureCount];
	for (int i = 0; i < m_ItemTextureCount; i++)
	{
		pstr = strtok(NULL, ",");
		if (!m_pItemTexture[i].Load(pstr))
		{
			return false;
		}
	}

	//配置データの読み込み
	m_pItemData = (char*)malloc(m_XCount * m_YCount);
	m_ItemCount = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			pstr = strtok(NULL, ",");
			m_pItemData[y * m_XCount + x] = atoi(pstr);
			if (m_pItemData[y * m_XCount + x] > 0)
			{
				m_ItemCount++;
			}
		}
	}

	//ファイルを閉じる
	fclose(fp);
	free(pBuffer);
	return true;
}

/**
 * 初期化
 * パラメーターや座標を初期化する。
 */
void CStage::Initialize(CEnemy* pEnemy,CItem* pItem){
	m_ScrollX = 0;
	m_ScrollY = 0;
	ButtonCount = 0;
	NextBlockDel = 0;

	int n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//配置番号
			//番号0は配置しない
			char on = m_pEnemyData[y * m_XCount + x] - 1;
			if (on < 0)
			{
				continue;
			}
			pEnemy[n].SetTexture(&m_pEnemyTexture[on],&m_pEnemyShotTexture[on]);
			pEnemy[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}

	n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//配置番号
			//番号0は位置しない
			char on = m_pItemData[y * m_XCount + x] - 1;
			if (on < 0)
				continue;
			pItem[n].SetTexture(&m_pItemTexture[on]);
			pItem[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}

	
}

void CStage::Initialize(CItem* pItem)
{
	m_ScrollX = 0;
	m_ScrollY = 0;
	ButtonCount = 0;
	NextBlockDel = 0;

	int n = 0;
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//配置番号
			//番号0は位置しない
			char on = m_pItemData[y * m_XCount + x] - 1;
			if (on < 0)
				continue;
			pItem[n].SetTexture(&m_pItemTexture[on]);
			pItem[n++].Initialize(x * m_ChipSize, y * m_ChipSize, on);
		}
	}
}

/**
 * 更新
 *
 * 引数
 * [in]			pl					プレイヤー、スクロールの判定に使用
 */
void CStage::Update(CPlayer& pl){
	//プレイヤーの短径取得
	CRectangle prec = pl.GetRect();
	//スクリーンの幅
	float sw = CGraphicsUtilities::GetGraphics()->GetTargetWidth();
	float sh = CGraphicsUtilities::GetGraphics()->GetTargetHeight();
	//ステージ全体の幅
	float stgw = m_ChipSize * m_XCount;
	float stgh = m_ChipSize * m_YCount;
	//座標が画面端によっている（各端から200pixel）場合スクロールを行って補正する
	if (prec.Left - m_ScrollX < 800)
	{
		m_ScrollX -= 800 - (prec.Left - m_ScrollX);
		if (m_ScrollX <= 0)
		{
			m_ScrollX = 0;
		}
	}
	else if (prec.Right - m_ScrollX > sw - 800)
	{
		m_ScrollX += (prec.Right - m_ScrollX) - (sw - 800);
		if (m_ScrollX >= stgw - sw)
		{
			m_ScrollX = stgw - sw;
		}
	}

	if (prec.Top - m_ScrollY < 100)
	{
		m_ScrollY -= 100 - (prec.Top - m_ScrollY);
		if (m_ScrollY <= 0)
		{
			m_ScrollY = 0;
		}
	}
	else if (prec.Bottom - m_ScrollY > sh - 100)
	{
		m_ScrollY += (prec.Bottom - m_ScrollY) - (sh - 100);
		if (m_ScrollY >= stgh - sh)
		{
			m_ScrollY = stgh - sh;
		}
	}

	/*
	if (prec.Left - m_ScrollX < g_pGraphics->GetTargetWidth() / 2 - 100)
	{
		m_ScrollX -= (g_pGraphics->GetTargetWidth() / 2 - 100) - (prec.Left - m_ScrollX);
		if (m_ScrollX <= 0)
		{
			m_ScrollX = 0;
		}
	}
	else if (prec.Right - m_ScrollX > sw - (g_pGraphics->GetTargetWidth() / 2 + 100))
	{
		m_ScrollX += (prec.Right - m_ScrollX) - (sw - (g_pGraphics->GetTargetWidth() / 2 + 100));
		if (m_ScrollX >= stgw - sw)
		{
			m_ScrollX = stgw - sw;
		}
	}

	if (prec.Top - m_ScrollY < 100)
	{
		m_ScrollY -= 100 - (prec.Top - m_ScrollY);
		if (m_ScrollY <= 0)
		{
			m_ScrollY = 0;
		}
	}
	else if (prec.Bottom - m_ScrollY > sh - 100)
	{
		m_ScrollY += (prec.Bottom - m_ScrollY) - (sh - 100);
		if (m_ScrollY >= stgh - sh)
		{
			m_ScrollY = stgh - sh;
		}
	}
	*/

	if (ButtonCount == 2 && NextBlockDel == 0)
	{
		ButtonGimmic(4);
	}

	if (ButtonCount == 3 && NextBlockDel == 1)
	{
		ButtonGimmic(1);
	}

	if (ButtonCount == 4 && NextBlockDel == 2)
	{
		ButtonGimmic(2);
	}
}

void CStage::ButtonGimmic(int DelBlockCnt)
{
	for (int x = 0; x < m_XCount; x++)
	{
		for (int y = 0; y < m_YCount; y++)
		{
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (DelBlockCnt > 0)
			{
				if (cn == 7)
				{
					m_pChipData[y * m_XCount + x] = 0;
					DelBlockCnt -= 1;
				}
			}
		}
	}
	NextBlockDel += 1;
}

/**
 * 描画
 *
 */
void CStage::Render(void){
	//遠景の描画
	int scw = g_pGraphics->GetTargetWidth();
	int sch = g_pGraphics->GetTargetHeight();
	int wn = m_BackTexture.GetWidth();
	int hn = m_BackTexture.GetHeight();
	for (float y = ((int)-m_ScrollY % hn) - hn; y < scw; y += hn)
	{
		for (float x = ((int)-m_ScrollX % wn) - wn; x < scw; x += wn)
		{
			m_BackTexture.Render(x, y);
		}
	}

	//テクスチャの横幅からマップチップの縦オフセットを求める
	int tcx = m_ChipTexture.GetWidth() / m_ChipSize;
	//マップチップの描画
	for (int y = 0; y < m_YCount; y++)
	{
		for (int x = 0; x < m_XCount; x++)
		{
			//描画するチップ番号
			//チップ番号0は描画しない
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}
			//マップチップの短径
			CRectangle cr(m_ChipSize * (cn % tcx), m_ChipSize * (cn / tcx), m_ChipSize * (cn % tcx + 1), m_ChipSize * (cn / tcx + 1));
			//マップチップの描画
			m_ChipTexture.Render(-m_ScrollX + x * m_ChipSize, -m_ScrollY + y * m_ChipSize, cr);
		}
	}
}

//当たり判定
bool CStage::Collision(CRectangle r) {
	//当たり判定する短径の左上と右下のチップ位置を求める
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;

	//ステージの範囲外にはならないようにする
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	//当たり判定以外をする短径の左上から右下の範囲のみ当たり判定を行う
	//それ以外の番号は当たることはないので判定が必要ない
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//描画するチップ番号
			//チップ番号0は当たり判定しない
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}

			//リフトの当たり判定
			if (cn == LIFT)
				continue;

			//マップチップの短径
			CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
			if (cr.CollisionRect(r))
			{
				return true;
			}
		}
	}
	return false;
}

bool CStage::Collision(CRectangle r, float& ox, float& oy) {
	bool re = false;

	//当たり判定する短径の左上と右下のチップ位置を求める
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;

	//ステージの範囲外にはならないようにする
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	//当たり判定以外をする短径の左上から右下の範囲のみ当たり判定を行う
	//それ以外の番号は当たることはないので判定が必要ない
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//描画するチップ番号
			//チップ番号0は当たり判定しない
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
			{
				continue;
			}

			//水の当たり判定
			if (cn == WATER)
			{
				continue;
			}

			//ボタンの当たり判定
			if (cn == BUTTON)
			{
				continue;
			}
			
			//リフトの当たり判定
			if (cn == LIFT)
				continue;
			
			//マップチップの短径
			CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
			//当たり判定用のキャラクタ短径
			//下で範囲を限定した専用の短径を作成する
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;		//下の短径は上側をしたと同じ値にする
			brec.Expansion(-6, 0);			//横の範囲を少し狭める
			//下と当たり判定
			if (cr.CollisionRect(brec))
			{
				re = true;
				//チップが斜面の場合自分の立ち位置から高さの割合を求める
				if (cn == LEFTSLOPE)
				{
					float sp = (brec.Right - cr.Left) / cr.GetWidth();
					if		(sp < 0.0f)		{ sp = 0.0f; }
					else if (sp > 1.0f)		{ sp = 1.0f; }
					//斜面の上の位置を求める
					float cTop = cr.Bottom - cr.GetHeight() * sp;
					//求めた上辺より上にある場合は埋まっていない
					if (brec.Bottom < cTop) { continue; }
					//下の埋まりなので坂上端から短径の下端の値を引いた値が埋まりの値
					oy += cTop - brec.Bottom;
					r.Top += cTop - brec.Bottom;
					r.Bottom += cTop - brec.Bottom;
				}
				else if (cn == RIGHTSLOPE)
				{
					float sp = ((brec.Left - cr.Right) / cr.GetWidth()) * -1;
					if		(sp < 0.0f)	{ sp = 0.0f; }
					else if (sp > 1.0f) { sp = 1.0f; }
					float cTop = cr.Bottom - cr.GetHeight() * sp;
					if (brec.Bottom < cTop) { continue; }
					oy += cTop - brec.Bottom;
					r.Top += cTop - brec.Bottom;
					r.Bottom += cTop - brec.Bottom;
				}
				else
				{
					//下の埋まりなのでチップ上端から短径の下端の値を引いた値が埋まりの値
					oy += cr.Top - brec.Bottom;
					r.Top += cr.Top - brec.Bottom;
					r.Bottom += cr.Top - brec.Bottom;
				}
			}

			//上で範囲を限定した専用の短径を作成する。
			CRectangle trec = r;
			trec.Bottom = trec.Top + 1;	//上の短径は下側を上と同じ値にする
			trec.Expansion(-12, 0);		//横の範囲を少し狭める
			//上と当たり判定
			if (cr.CollisionRect(trec))
			{
				re = true;
				//上の埋まりなのでチップした端から短径の上端の値を引いた値が埋まりの値
				oy += cr.Bottom - trec.Top;
				r.Top += cr.Bottom - trec.Top;
				r.Bottom += cr.Bottom - trec.Top;
			}

			//チップが斜面の場合壁・天井としての当たり判定を行わない
			if (cn == LEFTSLOPE) { continue; }
			if (cn == RIGHTSLOPE) { continue; }

			//当たり判定用のキャラクタ短径
			//左、右、それぞれで範囲を限定した専用の短径を作成する
			CRectangle lrec = r;
			lrec.Right = lrec.Left + 1;
			lrec.Expansion(0, -12);
			CRectangle rrec = r;
			rrec.Left = rrec.Right - 1;
			rrec.Expansion(0, -12);
			//左と当たり判定
			if (cr.CollisionRect(lrec))
			{
				re = true;
				//左の埋まりなのでチップ右端から短径の左端の値を引いた値が埋まりの値
				ox		+= cr.Right - lrec.Left;
				r.Left	+= cr.Right - lrec.Left;
				r.Right += cr.Right - lrec.Left;
			}
			//右と当たり判定
			else if (cr.CollisionRect(rrec))
			{
				re = true;
				//右の埋まりなのでチップ左端から短径の右端の値を引いた値が埋まりの値
				ox		+= cr.Left - rrec.Right;
				r.Left	+= cr.Left - rrec.Right;
				r.Right += cr.Left - rrec.Right;
			}
			//当たり判定用のキャラクタ短径
		}
	}
	return re;
}

void CStage::StageAttackCollision(CRectangle r)
{
	int lc = m_ScrollX / m_ChipSize;
	int rc = (g_pGraphics->GetTargetWidth() + m_ScrollX) / m_ChipSize;
	int tc = m_ScrollY / m_ChipSize;
	int bc = (g_pGraphics->GetTargetHeight() + m_ScrollY) / m_ChipSize;

	//ステージの範囲外にはならないようにする
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	//当たり判定以外をする短径の左上から右下の範囲のみ当たり判定を行う
	//それ以外の番号は当たることはないので判定が必要ない
	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			//描画するチップ番号
			//チップ番号0は当たり判定しない
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn < 0)
				continue;

			//ボタンギミック用
			if (cn == BUTTON)
			{
				CRectangle cr(x * m_ChipSize, y * m_ChipSize, x * m_ChipSize + m_ChipSize, y * m_ChipSize + m_ChipSize);
				if (cr.CollisionRect(r))
				{
					ButtonCount += 1;
					m_pChipData[y * m_XCount + x] = 0;
				}
			}
		}
	}
}


void CStage::CollisionFreezeWater(CRectangle r)
{
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;

	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn == WATER)
			{
				m_pChipData[y * m_XCount + x] = 12;

				//左の水
				if (m_pChipData[y * m_XCount + (x - 1)] - 1 == WATER)
				{
					m_pChipData[y * m_XCount + (x - 1)] = 12;
				}

				//右の水
				if (m_pChipData[y * m_XCount + (x + 1)] - 1 == WATER)
				{
					m_pChipData[y * m_XCount + (x + 1)] = 12;
				}

				//上の水
				if (m_pChipData[(y - 1) * m_XCount + x] - 1 == WATER)
				{
					m_pChipData[(y - 1) * m_XCount + x] = 12;
				}

				//下の水
				if (m_pChipData[(y + 1) * m_XCount + x] - 1 == WATER)
				{
					m_pChipData[(y + 1) * m_XCount + x] = 12;
				}
			}
		}
	}
}


void CStage::CollisionIceFroe(CRectangle r)
{
	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;

	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn == ICE)
			{
				m_pChipData[y * m_XCount + x] = 13;
			}
		}
	}
}

bool CStage::CollisionLift(CRectangle r, float& ox, float& oy)
{
	bool re = false;

	int lc = r.Left / m_ChipSize;
	int rc = r.Right / m_ChipSize;
	int tc = r.Top / m_ChipSize;
	int bc = r.Bottom / m_ChipSize;

	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	for (int y = tc; y <= bc; y++)
	{
		for (int x = lc; x <= rc; x++)
		{
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn != LIFT)
				continue;
			CRectangle cr(x * m_ChipSize + 10, y * m_ChipSize, x * m_ChipSize + m_ChipSize - 10, y * m_ChipSize + 20);
			CRectangle brec = r;
			brec.Top = brec.Bottom - 1;
			brec.Expansion(-6, 0);
			if (cr.CollisionRect(brec))
			{
				re = true;
				oy += cr.Top - brec.Bottom;
				r.Top += cr.Top - brec.Bottom;
				r.Bottom += cr.Top - brec.Bottom;
			}
		}
	}
	return re;
}

//TODO::ファイヤーバーの処理
bool CStage::FireBar(CRectangle prec,bool FireEffect)
{
	int lc = m_ScrollX / m_ChipSize;
	int rc = (g_pGraphics->GetTargetWidth() + m_ScrollX) / m_ChipSize;
	int tc = m_ScrollY / m_ChipSize;
	int bc = (g_pGraphics->GetTargetHeight() + m_ScrollY) / m_ChipSize;

	//ステージの範囲外にはならないようにする
	if (lc < 0) { lc = 0; }
	if (tc < 0) { tc = 0; }
	if (rc >= m_XCount) { rc = m_XCount - 1; }
	if (bc >= m_YCount) { bc = m_YCount - 1; }

	for (int y = tc; y < bc; y++)
	{
		for (int x = lc; x < rc; x++)
		{
			char cn = m_pChipData[y * m_XCount + x] - 1;
			if (cn != BURNER)
				continue;

			//上下確認
			//上方向
			if (m_pChipData[(y - 1) * m_XCount + x] - 1 <= 0)
			{
				CRectangle UpFireRec(-m_ScrollX + x * m_ChipSize, -m_ScrollY + y * m_ChipSize - (m_ChipSize * 2), (-m_ScrollX + x * m_ChipSize) + m_ChipSize, -m_ScrollY + y * m_ChipSize);
				//SetFireRec(UpFireRec);
				if(FireEffect)
					m_pEffectManager->Start(UpFireRec.GetCenter().x + m_ScrollX, UpFireRec.GetCenter().y + m_ScrollY, EFC_FIREBAR);
				if (prec.CollisionRect(UpFireRec))
					return true;
			}
			//下方向
			else
			{
				CRectangle DownFireRec(-m_ScrollX + x * m_ChipSize, -m_ScrollY + y * m_ChipSize + m_ChipSize, (-m_ScrollX + x * m_ChipSize) + m_ChipSize, -m_ScrollY + y * m_ChipSize + (m_ChipSize * 3));
				//SetFireRec(DownFireRec);
				if(FireEffect)
					m_pEffectManager->Start(DownFireRec.GetCenter().x + m_ScrollX, DownFireRec.GetCenter().y + m_ScrollY, EFC_FIREBAR);
				if (prec.CollisionRect(DownFireRec))
					return true;
			}
		}
	}
	return false;
}

/**
 * デバッグ描画
 *
 */
void CStage::RenderDebug(void){
	//位置の描画
	CGraphicsUtilities::RenderString(10,100,"スクロール X : %.0f , Y : %.0f",m_ScrollX,m_ScrollY);
	//CGraphicsUtilities::RenderRect(FireRec, MOF_XRGB(255, 0, 0));
}

/**
 * 解放
 *
 */
void CStage::Release(int nowscene){
	m_ChipTexture.Release();
	m_BackTexture.Release();
	if (m_pChipData)
	{
		free(m_pChipData);
		m_pChipData = NULL;
	}

	if (nowscene == SCENENO_GAME_STAGE1)
	{
		if (m_pEnemyTexture)
		{
			delete[] m_pEnemyTexture;
			m_pEnemyTexture = NULL;
		}
		if (m_pEnemyShotTexture)
		{
			delete[] m_pEnemyShotTexture;
			m_pEnemyShotTexture = NULL;
		}
		if (m_pEnemyData)
		{
			free(m_pEnemyData);
			m_pEnemyData = NULL;
		}
	}

	if (m_pItemData)
	{
		free(m_pItemData);
		m_pItemData = NULL;
	}
	if (m_pItemTexture)
	{
		delete[] m_pItemTexture;
		m_pItemTexture = NULL;
	}
}