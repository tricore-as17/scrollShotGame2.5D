#include"EasyEnemy.h"
#include"EnemyInformation.h"
#include"Colision.h"
#include"ShotManager.h"
#include"Map.h"
#include"Utility.h"

// 静的定数
// 速度（1=1m、60fps固定として、時速10km）
// 設定したい速さ ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
const float EasyEnemy::SPEED = Utility::CalculationSpeed(17000.0f);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="enemyInformation">ベースのコンストラクタを呼ぶ</param>
EasyEnemy::EasyEnemy(EnemyInformation* enemyInformation):BaseEnemy(enemyInformation)
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
EasyEnemy::~EasyEnemy()
{
	//処理なし
}


/// <summary>
/// 初期エネミーの更新処理
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="cameraPosition">カメラの座標</param>
/// <param name="shotManager">ショットを管理するクラス</param>
void EasyEnemy::Update(const Map& map,const VECTOR& cameraPosition,ShotManager& shotManager, const VECTOR& playerPosition)
{

    //画面内に入ったかのチェック
    isMoveStart = CanStartMove(cameraPosition,0,0);
    
	//移動開始フラグがたっていたら移動させる
	if (isMoveStart)
	{
		direction = VAdd(direction, VGet(-1, 0, 0));
	}
    //当たり判定や移動処理などのエネミー共通処理を呼ぶ
    Move(map, SPEED);

    //弾と当たっているかを判定して体力などを減らす処理
    Colision::ColisionShot(shotManager.GetShot(), position, width, height, life, kind);

}


