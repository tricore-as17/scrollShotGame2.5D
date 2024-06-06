#include"EasyEnemy.h"
#include"Colision.h"
#include"Map.h"
#include"Utility.h"

// 静的定数
// 速度（1=1m、60fps固定として、時速10km）
// 設定したい速さ ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
const float EasyEnemy::SPEED = static_cast<float>(17000.0 / 60.0 / 60.0 / 60.0);

/// <summary>
/// コンストラクタ
/// </summary>
EasyEnemy::EasyEnemy()
{
	//座標の初期化
	pos = VGet(0, 0, 0);

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
void EasyEnemy::Init(const VECTOR& initPos)
{
	//座標の代入
	pos = initPos;
	//移動を開始するフラグの初期化
	moveStartFlag = false;
    fallSpeed = 0;
    //幅と高さの代入
    w = W;
    h = H;

	
}

/// <summary>
/// 更新処理(当たり判定などの処理はプレイヤーとほぼ同じ)
/// </summary>
/// <param name="map">マップのインスタンス</param>
void EasyEnemy::Update(const Map& map)
{
    
	//移動開始フラグがたっていたら移動させる
	if (moveStartFlag)
	{
		dir = VAdd(dir, VGet(-1, 0, 0));
	}
    //当たり判定や移動処理などのエネミー共通処理を呼ぶ
    MoveProcess(map, SPEED);
    
}

/// <summary>
/// 描画
/// </summary>
void EasyEnemy::Draw()
{
	//テスト用
    //当たり判定の描画
    Utility::DrawSquareCollisionDetection(pos, W, H);

}
