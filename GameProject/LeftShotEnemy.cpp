#include"LeftShotEnemy.h"
#include"ShooterEnemy.h"
#include"Shot.h"
#include"ShotManager.h"
#include"EnemyInformation.h"
#include"Map.h"
#include"Colision.h"
#include"Utility.h"

/// <summary>
/// コンストラクタ
/// </summary>
LeftShotEnemy::LeftShotEnemy(EnemyInformation* enemyInformation):BaseEnemy(enemyInformation)
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
    shooterEnemy->SetRimitShotInterval(SHOT_INTERVAL_RIMIT);
}

/// <summary>
/// デストラクタ
/// </summary>
LeftShotEnemy::~LeftShotEnemy()
{
    delete shooterEnemy;
}


/// <summary>
/// ゲーム中の更新処理
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="cameraPosition">カメラの座標</param>
/// <param name="shotManager">ショットを管理するクラス</param>
void LeftShotEnemy::Update(const Map& map, const VECTOR& cameraPosition, ShotManager& shotManager)
{
    //画面内に入ったかのチェック
    moveStartFlag = CanStartMove(cameraPosition);

    //画面内に入ったフラグが立っていれば撃つ
    if (moveStartFlag)
    {
        //前撃ってから一定の間隔が経っていれば撃つ
        shooterEnemy->CountShotInterval();
        if (shooterEnemy->GetIsAbleShot())
        {
            shotManager.CreateShot(position, VGet(SHOT_DIRCTION, 0, 0), LEFT_ENEMY_SHOT, damage);
            shooterEnemy->SetIsAbleShot(false);
        }
    }
    //弾と当たっているかを判定して体力などを減らす処理
    Colision::ColisionShot(shotManager.GetShot(), position, width, height, life, kind);
}




