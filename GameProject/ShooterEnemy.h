#pragma once

/// <summary>
/// 弾を撃つエネミーの基底クラス
/// </summary>
class ShooterEnemy
{
public:
    //getter,setter
    void SetRimitShotInterval(const int rimitShotInterval) { this->rimitShotInterval = rimitShotInterval; }
    const bool GetCanShot()const { return canShot; }
    void SetCanShot(const bool isAbleShot) { this->canShot = isAbleShot; }
    //コンストラクタ
    ShooterEnemy();
    //デストラクタ
    virtual ~ShooterEnemy();
    /// <summary>
    /// 弾を撃てるようになるまでの間隔の設定
    /// </summary>
    /// <param name="INTERVAL_RIMIT">間隔の大きさ</param>
    virtual void CountShotInterval();

private:
    //メンバ変数
    int  countShotInterval;              //ショットを撃った後の待ち時間のカウント用
    bool canShot;                     //弾を撃てるようになっているか
    int rimitShotInterval;

};

