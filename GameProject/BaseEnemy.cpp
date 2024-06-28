#include"BaseEnemy.h"
#include"EnemyInformation.h"
#include"ShotManager.h"
#include"Colision.h"
#include"Utility.h"
#include"Map.h"

/// <summary>
/// コンストラクタ
/// </summary>
BaseEnemy::BaseEnemy(EnemyInformation* enemyInformation, int adjustRightLimit )
    :isMoveStart(false)
    , adjustRightLimit(adjustRightLimit)
    ,kind(Utility::KIND_ENEMY)
    ,isDead(false)
    ,isTurn(false)
{
    //エネミーのタイプを判断
    type = enemyInformation->type;
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
    Colision::IsTopHit(map, position,width,height,fallSpeed,isHitTop);


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
    float RightLimit = (cameraPosition.x +Utility::WORLD_SCREEN_WIDTH_SIZE * 0.5)+adjustRightLimit;
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
    //NULLチェック
    if (animetionCouut!=NULL && image[animetionState] != NULL && image!=NULL)
    {
        //描画
        DrawBillboard3D(position, 0.5f, 0.5f, chipSize, imageRotationRate, image[animetionState][animetionCouut[animetionState] / animetionSpeed], TRUE,isTurn);
    }
}
/// <summary>
/// 弾が当たった際のアニメーション切り替え処理
/// </summary>
/// <param name="hitAnimetionState">ヒット時のアニメーションの添え字</param>
/// <param name="shotManager">ショット管理クラス</param>
void BaseEnemy::ChangeHitAnimetion(const int hitAnimetionState,const ShotManager& shotManager)
{
    bool isHit = false;
    //弾と当たっているかを判定して体力などを減らす処理
    isHit = Colision::ColisionShot(shotManager.GetShot(), position, width, height, life, kind);
    if (isHit)
    {
        animetionState = hitAnimetionState;
    }
}

/// <summary>
/// アニメーションの更新処理
/// </summary>
void BaseEnemy::UpdateAnimetion()
{
    //NULLチェック
    if (animetionCountLimit!=NULL && animetionCouut != NULL && isRoopAnimetion != NULL && isEndAnimetion != NULL)
    {
        //アニメーションのカウントを進める
        animetionCouut[animetionState]++;
        //ループアニメーションの処理
        if (animetionCouut[animetionState] >= animetionCountLimit[animetionState] && isRoopAnimetion[animetionState])
        {
            animetionCouut[animetionState] = 0;
        }
        //ループしないアニメーションの処理
        else if (animetionCouut[animetionState] >= animetionCountLimit[animetionState] && !isRoopAnimetion[animetionState])
        {
            animetionCouut[animetionState] = 0;
            isEndAnimetion[animetionState] = true;
        }
    }

}

/// <summary>
/// ヒット時のアニメーションの更新
/// </summary>
/// <param name="hitAnimetionState">ヒット時のアニメーションの添え字</param>
/// <param name="roopAnimetionState">ループアニメーションの添え字</param>
void BaseEnemy::HitAnimetion(const int hitAnimetionState, const int roopAnimetionState)
{
    //被弾時のアニメーションが終了した際の処理
    if (isEndAnimetion[hitAnimetionState])
    {
        //体力が0になっていれば撃破フラグをたてる
        if (life <= 0)
        {
            isDead = true;
        }
        //体力が余っていればアニメーションを変更
        else
        {
            animetionState = roopAnimetionState;
            animetionCouut[hitAnimetionState] = 0;
            isEndAnimetion[hitAnimetionState] = false;
        }
    }
}






