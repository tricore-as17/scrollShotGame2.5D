#include "GameScene.h"
#include"Player.h"
#include"Camera.h"
#include"Map.h"
#include"EnemyManager.h"
#include"ShotManager.h"
#include"InputManager.h"
#include"ResultScene.h"


//コンストラクタ
GameScene::GameScene()
{
    //ToDo
    //ゲームで使うクラスのインスタンスを作成する
    //ゲーム開始時点で初期化するものもここに書く
    //クラスのインスタンスの作成
    player       = new Player();
    camera       = new Camera();
    map          = new Map();
    enemyManager = new EnemyManager();
    shotManager  = new ShotManager();
    inputManager = new InputManager();

    player->Initialize();
    camera->Initialize();
    map->Initialize();
    enemyManager->Initialize();
    shotManager->Initialize();
}

//デストラクタ
GameScene::~GameScene()
{
    //ここで使ったクラスのインスタンスなどを解放する
    delete player;
    delete camera;
    delete map;
    delete enemyManager;
    delete shotManager;
    delete inputManager;
    player       = NULL;
    camera       = NULL;
    map          = NULL;
    enemyManager = NULL;
    shotManager  = NULL;
    inputManager = NULL;
}

/// <summary>
/// ゲーム中の更新処理
/// </summary>
void GameScene::Update()
{
    //キー入力を止める必要があるか
    bool isKeyStop = inputManager->GetIsStopKey();

    player->Update(isKeyStop, *map, *shotManager);
    enemyManager->Update(*map, camera->GetPosition(),*shotManager);
    shotManager->Update();
    player->IsReceiveDamage(enemyManager->GetEasyEnemy(), shotManager->GetShot());
    shotManager->DeleteShot(camera->GetPosition());
    camera->Update(*map, *player);
    //次のループへの処理
    //プレイヤーの体力が0以下になったらリザルト画面に移行
    if (player->GetLife() <= 0)
    {
        inputScene = new ResultScene();
    }
    else
    {
        inputScene = this;
    }
}

/// <summary>
/// ゲーム中の描画
/// </summary>
void GameScene::Draw()
{
    //ToDo
    //ゲーム中に行う描画処理をまとめる
    map->Draw();
    player->Draw();
    shotManager->Draw();
    enemyManager->Draw();
}
