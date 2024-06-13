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
    if (VSquareSize(direction) > 0)		//directionのサイズを2乗にして返す(二乗にすることでdirectionに値が入っていればifに入る
    {
        direction = VNorm(direction);			//各成分のサイズを１にする
    }

    //移動量を出す
    VECTOR velocity = VScale(direction, speed);

    //重力の値だけ落下させる
    fallSpeed -= Utility::GRAVITY;

    // HACK: 先に設定判定をすることでfallSpeed修正＋接地フラグ更新
    Colision::IsGround(map,position,w,h,fallSpeed);
    Colision::IsTopHit(map, position,w,h,fallSpeed);

    // 落下速度を移動量に加える
    VECTOR fallVelocity = VGet(0, fallSpeed, 0);	// 落下をベクトルに。y座標しか変化しないので最後にベクトルにする
    velocity = VAdd(velocity, fallVelocity);

    // 当たり判定をして、壁にめり込まないようにvelocityを操作する
    velocity = Colision::IsHitMapAdjustmentVector(map,velocity,position,w,h);

    // 移動
    position = VAdd(position, velocity);
        
}

/// <summary>
/// エネミーのスクロールを始めるかのチェック(画面に入ったかでチェック)
/// </summary>
/// <param name="cameraPosition">カメラの座標</param>
bool BaseEnemy::CanStartMove(const VECTOR& cameraPosition)
{
    //座標が入っているかのチェック用フラグ
    bool isInScreen;
    //画面右端の座標
    float RightLimit = cameraPosition.x +Utility::WORLD_SCREEN_W_SIZE * 0.5;
    //画面左端の座標
    float LeftLimit = cameraPosition.x - Utility::WORLD_SCREEN_W_SIZE * 0.5;
    //画面内に座標があるかのチェック
    if (position.x < RightLimit && LeftLimit < position.x)
    {
        isInScreen = true;
    }
    else
    {
        isInScreen = false;
    }
    return isInScreen;
}

/// <summary>
/// 弾を撃てるようになるまでの間隔の設定
/// </summary>
/// <param name="INTERVAL_RIMIT">間隔の大きさ</param>
void BaseEnemy::CountShotInterval(const int INTERVAL_RIMIT)
{
    //撃てる準備がまだできていないなら
    if (!readyShotFlag)
    {
        shotIntervalCount++;
        if (shotIntervalCount>=INTERVAL_RIMIT)
        {
            readyShotFlag = true;
            shotIntervalCount = 0;
        }

    }
}

/// <summary>
/// 描画
/// </summary>
void BaseEnemy::Draw()
{
    //テスト用
    //当たり判定の描画
    Utility::DrawSquareCollisionDetection(position, w, h);
}


