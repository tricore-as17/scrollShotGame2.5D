#include "OneWayShotEnemy.h"
#include"ShooterEnemy.h"
#include"EnemyInformation.h"
#include"ShotManager.h"
#include"Map.h"
#include"Colision.h"
#include"Utility.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="enemyInformation">エネミーの初期化情報をまとめたもの</param>
OneWayShotEnemy::OneWayShotEnemy(EnemyInformation* enemyInformation) : BaseEnemy(enemyInformation)
{
    shooterEnemy = new ShooterEnemy();
    //幅と高さの代入
    width = WIDTH;
    height = HEIGHT;
    //体力の初期化
    life = MAX_LIFE;
    //ダメージの値を初期化
    damage = INITIALIZE_DAMAGE;
    //弾の方向を代入
    dirctionX = enemyInformation->shotDirectionX;
    dirctionY = enemyInformation->shotDirectionY;
    //インターバルをセット
    shooterEnemy->SetRimitShotInterval(SHOT_INTERVAL_RIMIT);
}

/// <summary>
/// デストラクタ
/// </summary>
OneWayShotEnemy::~OneWayShotEnemy()
{
    delete shooterEnemy;
}

/// <summary>
/// ゲーム中の更新処理
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="cameraPosition">カメラの座標</param>
/// <param name="shotManager">ショットを管理するクラス</param>
void OneWayShotEnemy::Update(const Map& map, const VECTOR& cameraPosition, ShotManager& shotManager, const VECTOR& playerPosition)
{
    //画面内に入ったかのチェック
    isMoveStart = CanStartMove(cameraPosition);

    //画面内に入ったフラグが立っていれば撃つ
    if (isMoveStart)
    {
        //前撃ってから一定の間隔が経っていれば撃つ
        shooterEnemy->CountShotInterval();
        if (shooterEnemy->GetCanShot())
        {
            shotManager.CreateShot(position, VGet(dirctionX, dirctionY, 0), LEFT_ENEMY_SHOT, damage,kind);
            shooterEnemy->SetCanShot(false);
        }
    }
    //弾と当たっているかを判定して体力などを減らす処理
    Colision::ColisionShot(shotManager.GetShot(), position, width, height, life, kind);
}
