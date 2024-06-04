#include"EasyEnemy.h"
#include"Colision.h"
#include"Map.h"
#include"Utility.h"


/// <summary>
/// コンストラクタ
/// </summary>
EasyEnemy::EasyEnemy(int inFirstX)
{
	firstX = inFirstX;
	//座標の初期化
	pos = VGet(0, 0, 0);
	//幅と高さの取得
	w = W;
	h = H;
	//画像の読み込み
	//LoadDivGraph();
	

}
/// <summary>
/// デストラクタ
/// </summary>
EasyEnemy::~EasyEnemy()
{
	//処理なし
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="initPos">初期化用の座標</param>
void EasyEnemy::Init(VECTOR initPos)
{
	//座標の代入
	pos = initPos;
	//移動を開始するフラグの初期化
	moveStartFlag = false;
	//画像の読み込み
	//LoadDivGraph()
	
}

/// <summary>
/// 更新処理
/// </summary>
void EasyEnemy::Update(const Map& map,const VECTOR& playerVec)
{
	//エネミー共通のスクロール処理
	ScrollProcess();
	//移動開始フラグがたっていたら移動させる
	if (moveStartFlag)
	{
		dir = VAdd(dir, VGet(-1, 0, 0));
	}
	// 正規化
	if (VSquareSize(dir) > 0)		//dirのサイズを2乗にして返す(二乗にすることでdirに値が入っていればifに入る
	{
		dir = VNorm(dir);			//各成分のサイズを１にする
	}

	//移動量を出す
	VECTOR velocity = VScale(dir, SPEED);

	//落下させる
	fallSpeed += Utility::GRAVITY;

	// HACK: 先に設定判定をすることでfallSpeed修正＋接地フラグ更新
	EnemyColision::CheckIsGround(*this, map);
	EnemyColision::CheckIsTopHit(*this, map);

	// 落下速度を移動量に加える
	VECTOR fallVelocity = VGet(0, fallSpeed, 0);	// 落下をベクトルに。y座標しか変化しないので最後にベクトルにする
	velocity = VAdd(velocity, fallVelocity);

	// 当たり判定をして、壁にめり込まないようにvelocityを操作する
	velocity = EnemyColision::CheckEnemyHitWithMap(*this, map, velocity);

	// 移動
	pos = VAdd(pos, velocity);
}

/// <summary>
/// 描画
/// </summary>
void EasyEnemy::Draw()
{
	//スクリーン内に入ったら描画する
	//if (pos.x <= SCREEN_W + w)
	//{
		//テスト用の描画
		DrawBox(pos.x - w*0.5, pos.y - h*0.5, pos.x + w*0.5, pos.y + h*0.5, WHITE, TRUE);

	//}
}