#include "FallingAttackEnemy.h"
#include"ShotManager.h"
#include"Colision.h"
#include"EnemyInformation.h"
#include"Player.h"
#include"Utility.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="enemyInformation">初期化情報の入った構造体</param>
FallingAttackEnemy::FallingAttackEnemy(EnemyInformation* enemyInformation)
    :BaseEnemy(enemyInformation)
    , endCount(0)
{
    //幅と高さの代入
    width = WIDTH;
    height = HEIGHT;
    //体力の初期化
    life = MAX_LIFE;
    //ダメージの値を初期化
    damage = INITIALIZE_DAMAGE;
    //初期座標を代入
    startPosition  = position;
}

/// <summary>
/// デストラクタ
/// </summary>
FallingAttackEnemy::~FallingAttackEnemy()
{
    //処理なし
}

/// <summary>
/// 下降しながらプレイヤーに近づいてくる敵
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="cameraPosition">カメラの座標</param>
/// <param name="shotManager">ショットの管理クラス</param>
void FallingAttackEnemy::Update(const Map& map, const VECTOR& cameraPosition, ShotManager& shotManager, const VECTOR& playerPosition)
{

    if (!isMoveStart)
    {
        //画面内に入ったかのチェック
        isMoveStart = CanStartMove(cameraPosition,0,0);
    }
    //一度画面内に入ったら動き続ける
    if (isMoveStart)
    {
        //0.0fの処理は最初だけ行う
        if (endCount == 0.0f)
        {
            //放物線の終点X座標を画面の位置の幅の場所にする
            parabolaEndX = startPosition.x - Utility::WORLD_SCREEN_WIDTH_SIZE;
            //移動開始時にプレイヤーの座標を代入して持っておく
            startPlayerPosition = playerPosition;
            //動かす前にプレイヤーの位置と自分の位置から放射線の係数を計算する
            coefficient = (startPosition.y - startPlayerPosition.y) / powf(startPosition.x - startPlayerPosition.x, 2);
        }
        endCount += COUNT_SPEED;
        if (endCount > 0 && endCount <= MOVE_END_COUNT)
        {
            //X座標の更新(始点から終点までの移動)
            position.x = (1 - endCount) * startPosition.x + endCount * parabolaEndX;

            //放物線の方程式からY座標を計算
            position.y = coefficient * powf(position.x - startPlayerPosition.x, 2) + startPlayerPosition.y;

        }
    }

    //弾と当たっているかを判定して体力などを減らす処理
    Colision::ColisionShot(shotManager.GetShot(), position, width, height, life, kind);

}
