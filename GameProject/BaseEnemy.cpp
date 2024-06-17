#include"BaseEnemy.h"
#include"EnemyInformation.h"
#include"Colision.h"
#include"Utility.h"
#include"Map.h"

/// <summary>
/// コンストラクタ
/// </summary>
BaseEnemy::BaseEnemy(EnemyInformation* enemyInformation)
    :moveStartFlag(false)
    ,kind(Utility::KIND_ENEMY)
{
    //座標の初期化
    position.x = enemyInformation->initializeX;
    position.y = enemyInformation->initializeY;
    position.z = 0;
    //落下速度の初期化
    fallSpeed = 0;
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

    Colision::IsGround(map,position,width,height,fallSpeed);
    Colision::IsTopHit(map, position,width,height,fallSpeed);


    // 落下速度を移動量に加える
    VECTOR fallVelocity = VGet(0, fallSpeed, 0);	// 落下をベクトルに。y座標しか変化しないので最後にベクトルにする
    velocity = VAdd(velocity, fallVelocity);

    // 当たり判定をして、壁にめり込まないようにvelocityを操作する
    velocity = Colision::IsHitMapAdjustmentVector(map,velocity,position,width,height);


    // 移動
    position = VAdd(position, velocity);
        
}

/// <summary>
/// エネミーが行動を始めるかのチェック(画面に入ったかでチェック)
/// </summary>
/// <param name="cameraPosition">カメラの座標</param>
bool BaseEnemy::CanStartMove(const VECTOR& cameraPosition)
{
    //座標が入っているかのチェック用フラグ
    bool isInScreen;
    //画面右端の座標
    float RightLimit = cameraPosition.x +Utility::WORLD_SCREEN_WIDTH_SIZE * 0.5;
    //画面左端の座標
    float LeftLimit = cameraPosition.x - Utility::WORLD_SCREEN_WIDTH_SIZE * 0.5;
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
/// 描画
/// </summary>
void BaseEnemy::Draw()
{
    //テスト用
    //当たり判定の描画
    Utility::DrawSquareCollisionDetection(position, width, height);

}


