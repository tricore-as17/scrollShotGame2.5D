#include"EasyEnemy.h"
#include"EnemyManager.h"
#include"Map.h"
#include"Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
EnemyManager::EnemyManager()
{
	//一番弱い敵をインスタンス化
	easyEnemy.emplace_back(new EasyEnemy());	//1体目
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyManager::~EnemyManager()
{
	//メモリの開放
	easyEnemy.clear();
}

/// <summary>
/// ゲーム開始時の初期化
/// </summary>
void EnemyManager::Init()
{
	easyEnemy[0]->Init(VGet(EAZY1_FIRST_X, EAZY1_FIRST_Y, 0));
}
/// <summary>
/// 更新処理
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="player">プレイヤーのインスタンス</param>
void EnemyManager::Update(const Map& map, const Player& player)
{
	//プレイヤーの移動方向の取得
	VECTOR playerVec = player.GetKeepVelocity();
	easyEnemy[0]->Update(map);
}
/// <summary>
/// 描画
/// </summary>
void EnemyManager::Draw()
{
	easyEnemy[0]->Draw();
}
