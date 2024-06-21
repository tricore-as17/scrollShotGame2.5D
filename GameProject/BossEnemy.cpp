#include"BossEnemy.h"
#include"EnemyInformation.h"
#include"Utility.h"
#include"ShotManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
BossEnemy::BossEnemy(EnemyInformation* enemyInformation)
    :BaseEnemy(enemyInformation)
{
    //幅と高さの代入
    width = WIDTH;
    height = HEIGHT;
    //体力の初期化
    life = MAX_LIFE;
    //ダメージの値を初期化
    damage = INITIALIZE_DAMAGE;
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
        
    }

}
