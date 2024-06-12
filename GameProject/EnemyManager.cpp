#include"LeftShotEnemy.h"
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
	//一番弱い敵をインスタンス化(作る数だけ)
    for (int i = 0; i < EAZY_NUM;i++)
    {
	    easyEnemy.emplace_back(new EasyEnemy());	
    }
    for (int i = 0; i < LEFT_SHOT_ENEMY_NUM; i++)
    {
        leftShotEnemy.emplace_back(new LeftShotEnemy());
    }
    
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyManager::~EnemyManager()
{
    //中の要素の削除
    ReleaseMemory(easyEnemy);
    ReleaseMemory(leftShotEnemy);
}

/// <summary>
/// ゲーム開始時の初期化
/// </summary>
void EnemyManager::Init()
{
    //それぞれの敵の座標を代入していく
	easyEnemy[0]->Init(VGet(EAZY1_FIRST_X, EAZY1_FIRST_Y, 0));
    easyEnemy[1]->Init(VGet(EAZY2_FIRST_X, EAZY1_FIRST_Y, 0));
    leftShotEnemy[0]->Init(VGet(LEFT1_FIRST_X,LEFT1_FIRST_Y,0));
    leftShotEnemy[1]->Init(VGet(LEFT2_FIRST_X, LEFT2_FIRST_Y, 0));


    
}
/// <summary>
/// エネミー全体の更新処理
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="cameraPos">カメラの座標</param>
/// <param name="shotManager">ショットを管理するクラス</param>
void EnemyManager::Update(const Map& map, const VECTOR& cameraPos, ShotManager& shotManager)
{
    //for文を何個もかかないでいいようにエネミーの種類によってアップデートを呼ぶ
    SingleUpdate(easyEnemy, map, cameraPos, shotManager);
    SingleUpdate(leftShotEnemy, map, cameraPos, shotManager);
    //体力の値によって削除する
    DeleteEnemy(easyEnemy);
    DeleteEnemy(leftShotEnemy);

}
/// <summary>
/// 描画
/// </summary>
void EnemyManager::Draw()
{
    //for文を何個もかかないでいいようにエネミーの種類によって描画を呼ぶ
    SingleDraw(easyEnemy);
    SingleDraw(leftShotEnemy);
}

/// <summary>
/// 体力が0になったらインスタンスを削除する(削除するので参照渡し)
/// </summary>
void EnemyManager::DeleteEnemy(vector<BaseEnemy*>&enemy)
{
    for (auto it = enemy.begin(); it != enemy.end();)
    {
        if ((*it)->GetLife() <= 0)
        {
            it = enemy.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

/// <summary>
/// エネミーインスタンスのメモリ解放
/// </summary>
/// <param name="enemy">エネミーのインスタンス</param>
void EnemyManager::ReleaseMemory(vector<BaseEnemy*>& enemy)
{
    //中の要素の削除
    for (auto it : enemy)
    {
        delete it;
    }
    enemy.clear();
}

/// <summary>
/// for文を毎回呼ばないでいいように用意したエネミーの種類毎のアップデート
/// </summary>
/// <param name="enemy">エネミーの種類毎のvector</param>
/// <param name="map">マップのインスタンス</param>
/// <param name="cameraPos">カメラの座標</param>
/// <param name="shotManager">ショットの管理クラス</param>
void EnemyManager::SingleUpdate(vector<BaseEnemy*> enemy, const Map& map, const VECTOR& cameraPos, ShotManager& shotManager)
{
    for (int i = 0; i < enemy.size(); i++)
    {
        enemy[i]->Update(map, cameraPos, shotManager);
    }
}

/// <summary>
/// for文を毎回呼ばないでいいように用意したエネミーの種類毎の描画
/// </summary>
/// <param name="enemy">エネミーの種類毎のvector</param>
void EnemyManager::SingleDraw(vector<BaseEnemy*>enemy)
{
    for (int i = 0; i < enemy.size(); i++)
    {
        enemy[i]->Draw();
    }
}



