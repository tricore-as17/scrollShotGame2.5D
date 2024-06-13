#include"LeftShotEnemy.h"
#include"Shot.h"
#include"ShotManager.h"
#include"Map.h"
#include"Colision.h"
#include"Utility.h"

/// <summary>
/// コンストラクタ
/// </summary>
LeftShotEnemy::LeftShotEnemy()
{
    //処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
LeftShotEnemy::~LeftShotEnemy()
{
    //処理なし
}

/// <summary>
/// ゲーム開始時の初期化
/// </summary>
/// <param name="initPosition">初期座標</param>
void LeftShotEnemy::Initialize(const VECTOR& initializePosition)
{
    //座標の代入
    position = initializePosition;
    //撃ち始めるフラグ
    moveStartFlag = false;
    fallSpeed = 0;
    //幅と高さの代入
    w = W;
    h = H;
    //体力の初期化
    life = MAX_LIFE;
    //ダメージの値を初期化
    damage = INITIALIZE_DAMAGE;

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
        CountShotInterval(SHOT_INTERVAL_RIMIT);
        if (readyShotFlag)
        {
            shotManager.CreateShot(position, VGet(SHOT_DIRCTION, 0, 0), LEFT_ENEMY_SHOT, damage);
            readyShotFlag = false;
        }
    }
    //弾と当たっているかを判定して体力などを減らす処理
    Colision::ColisionShot(shotManager.GetShot(), position, w, h, life, kind);
}



