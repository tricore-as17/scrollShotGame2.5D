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
/// <param name="initPos">初期座標</param>
void LeftShotEnemy::Initialize(const VECTOR& initPos)
{
    //ベースの初期化を呼び出して共通処理をする
    BaseEnemy::Initialize(initPos);
    //幅と高さの代入
    width = WIDTH;
    height = HEIGHT;
    //体力の初期化
    life = MAX_LIFE;
    //ダメージの値を初期化
    damage = INIT_DAMAGE;

}

/// <summary>
/// ゲーム中の更新処理
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="cameraPos">カメラの座標</param>
/// <param name="shotManager">ショットを管理するクラス</param>
void LeftShotEnemy::Update(const Map& map, const VECTOR& cameraPos, ShotManager& shotManager)
{
    //画面内に入ったかのチェック
    moveStartFlag = CheckStartMove(cameraPos);

    //画面内に入ったフラグが立っていれば撃つ
    if (moveStartFlag)
    {
        //前撃ってから一定の間隔が経っていれば撃つ
        CountShotInterval(SHOT_INTERVAL_RIMIT);
        if (readyShotFlag)
        {
            shotManager.CreateShot(pos, VGet(SHOT_DIRCTION, 0, 0), LEFT_ENEMY_SHOT, damage);
            readyShotFlag = false;
        }
    }
    //弾と当たっているかを判定して体力などを減らす処理
    Colision::ColisionShot(shotManager.GetShot(), pos, width, height, life, kind);
}



