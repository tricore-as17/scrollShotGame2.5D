#include"BaseEnemy.h"
#include"Colision.h"
#include"Utility.h"
#include"Map.h"

/// <summary>
/// コンストラクタ
/// </summary>
BaseEnemy::BaseEnemy() :moveStartFlag(false),kind(Utility::KIND_ENEMY)
{
    //処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
BaseEnemy::~BaseEnemy() {/*処理なし*/ }

/// <summary>
/// 当たり判定などの更新処理のなかでの共通処理をまとめたもの
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="speed">エネミーのスピード</param>
void BaseEnemy::Move(const Map& map,const float& speed)
{
    // 正規化
    if (VSquareSize(dir) > 0)		//dirのサイズを2乗にして返す(二乗にすることでdirに値が入っていればifに入る
    {
        dir = VNorm(dir);			//各成分のサイズを１にする
    }

    //移動量を出す
    VECTOR velocity = VScale(dir, speed);

    //重力の値だけ落下させる
    fallSpeed -= Utility::GRAVITY;

    // HACK: 先に設定判定をすることでfallSpeed修正＋接地フラグ更新
    Colision::IsGround(map,pos,w,h,fallSpeed);
    Colision::IsTopHit(map, pos,w,h,fallSpeed);

    // 落下速度を移動量に加える
    VECTOR fallVelocity = VGet(0, fallSpeed, 0);	// 落下をベクトルに。y座標しか変化しないので最後にベクトルにする
    velocity = VAdd(velocity, fallVelocity);

    // 当たり判定をして、壁にめり込まないようにvelocityを操作する
    velocity = Colision::CheckHitMapAdjustmentVector(map,velocity,pos,w,h);

    // 移動
    pos = VAdd(pos, velocity);
        
}

/// <summary>
/// エネミーのスクロールを始めるかのチェック(画面に入ったかでチェック)
/// </summary>
/// <param name="cameraPos">カメラの座標</param>
bool BaseEnemy::CheckStartMove(const VECTOR& cameraPos)
{
    //座標が入っているかのチェック用フラグ
    bool checkFlag;
    //画面右端の座標
    float RightLimit = cameraPos.x +Utility::WORLD_SCREEN_W_SIZE * 0.5;
    //画面左端の座標
    float LeftLimit = cameraPos.x - Utility::WORLD_SCREEN_W_SIZE * 0.5;
    //画面内に座標があるかのチェック
    if (pos.x < RightLimit && LeftLimit < pos.x)
    {
        checkFlag = true;
    }
    else
    {
        checkFlag = false;
    }
    return checkFlag;
}


