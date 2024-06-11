#include"EasyEnemy.h"
#include"EnemyManager.h"
#include"ShotManager.h"
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
    //中の要素の削除
    for (auto it : easyEnemy)
    {
        delete it;
    }
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
/// <param name="shotManager">ショットを管理するクラス</param>
void EnemyManager::Update(const Map& map, const VECTOR& cameraPos, const ShotManager& shotManager)
{
    for (int i = 0; i < easyEnemy.size(); i++)
    {
	    easyEnemy[i]->Update(map,cameraPos,shotManager);
    }
    DeleteEnemy();

}
/// <summary>
/// 描画
/// </summary>
void EnemyManager::Draw()
{
    for (int i = 0; i < easyEnemy.size(); i++)
    {
        easyEnemy[i]->Draw();
    }
}

/// <summary>
/// 体力が0になったらインスタンスを削除する
/// </summary>
void EnemyManager::DeleteEnemy()
{
    for (auto it = easyEnemy.begin(); it != easyEnemy.end();)
    {
        if ((*it)->GetLife() <= 0)
        {
            it = easyEnemy.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

