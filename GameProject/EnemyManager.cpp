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
/// エネミー全体の更新処理
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="cameraPos">カメラの座標</param>
void EnemyManager::Update(const Map& map, const VECTOR& cameraPos)
{

	easyEnemy[0]->Update(map,cameraPos);
}
/// <summary>
/// 描画
/// </summary>
void EnemyManager::Draw()
{
	easyEnemy[0]->Draw();
}
