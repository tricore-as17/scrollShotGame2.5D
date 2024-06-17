#include "ShooterEnemy.h"


/// <summary>
/// コンストラクタ
/// </summary>
ShooterEnemy::ShooterEnemy()
    :countShotInterval(0)
    ,canShot(false)
{

}

/// <summary>
/// デストラクタ
/// </summary>
ShooterEnemy::~ShooterEnemy()
{
    //処理なし
}




/// <summary>
/// 弾を撃てるようになるまでの間隔の設定
/// </summary>
/// <param name="INTERVAL_RIMIT">間隔の大きさ</param>
void ShooterEnemy::CountShotInterval()
{
    //弾のインターバルが残っている場合はカウントが間隔を超えるまで増やす
    //超えたら撃てるフラグを立てる
    if (!canShot)
    {
        countShotInterval++;
        if (countShotInterval >= rimitShotInterval)
        {
            canShot = true;
            countShotInterval = 0;
        }
    }
}

