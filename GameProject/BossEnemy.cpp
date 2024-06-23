#include"BossEnemy.h"
#include"EnemyInformation.h"
#include"Utility.h"
#include"ShooterEnemy.h"
#include"ShotManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
BossEnemy::BossEnemy(EnemyInformation* enemyInformation)
    :BaseEnemy(enemyInformation)
    ,isInAction(false)
{
    shooterEnemy = new ShooterEnemy();
    //幅と高さの代入
    width = WIDTH;
    height = HEIGHT;
    //体力の初期化
    life = MAX_LIFE;
    //ダメージの値を初期化
    damage = INITIALIZE_DAMAGE;

    //インターバルをセット
    //TODO
    //もともとSetterを使うようなコードで書いていたため
    //ここでセッターを使う形にしてしまいました。
    //時間があれば修正します。
    shooterEnemy->SetRimitShotInterval(SHOT_INTERVAL_RIMIT);
}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemy::~BossEnemy()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="cameraPosition">カメラの座標</param>
/// <param name="shotManager">ショットの管理クラス</param>
/// <param name="playerPosition">プレイヤーの座標</param>
void BossEnemy::Update(const Map& map, const VECTOR& cameraPosition, ShotManager& shotManager, const VECTOR& playerPosition)
{
    if (!isMoveStart)
    {
        //画面内に入ったかのチェック
        isMoveStart = CanStartMove(cameraPosition, ADJUST_RIGHT_LIMIT, 0);
    }
    if (isMoveStart)
    {
        ShootAtThePlayer(playerPosition, shotManager);
    }

}

/// <summary>
/// プレイヤに向けて弾を撃つ行動
/// </summary>
void BossEnemy::ShootAtThePlayer(const VECTOR& playerPosition,ShotManager& shotManager)
{
    shooterEnemy->CountShotInterval();
    if (shooterEnemy->GetCanShot())
    {
        //プレイヤーの方向へ向かうベクトルを出す
        VECTOR shotDirection = VSub(playerPosition, position);

        shotDirection = VNorm(shotDirection);
        shotManager.CreateShot(position, shotDirection, BOSS_SHOT, damage);
        shooterEnemy->SetCanShot(false);
    }
}
