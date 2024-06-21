#include "GameScene.h"
#include"Player.h"
#include"Camera.h"
#include"Map.h"
#include"EnemyManager.h"
#include"ShotManager.h"
#include"InputManager.h"
#include"GameSceneUI.h"
#include"ResultScene.h"


//コンストラクタ
GameScene::GameScene()
{
    player       = new Player();
    camera       = new Camera();
    map          = new Map();
    enemyManager = new EnemyManager();
    shotManager  = new ShotManager();
    gameSceneUI  = new GameSceneUI();

    player->Initialize();
    camera->Initialize();
    map->Initialize();
    shotManager->Initialize();

    //背景モデルのロード
    backGroundModel = MV1LoadModel("mv1/NightDome.pmx");
    //モデル位置の固定
    MV1SetPosition(backGroundModel, VGet(0, -200, -100));

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
    delete gameSceneUI;
    player       = NULL;
    camera       = NULL;
    map          = NULL;
    enemyManager = NULL;
    shotManager  = NULL;
    gameSceneUI  = NULL;
    //背景モデルも削除
    MV1DeleteModel(backGroundModel);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="inputManager">入力管理クラス</param>
void GameScene::Update(InputManager* inputManager)
{

    player->Update(*map, *shotManager,camera->GetPosition());
    enemyManager->Update(*map, camera->GetPosition(),*shotManager,player->GetPosition());
    shotManager->Update();
    player->IsReceiveDamage(enemyManager->GetEnemy(), shotManager->GetShot());
    shotManager->DeleteShot(camera->GetPosition());
    //ボスが移動を始めたらカメラの移動を止める
    if (enemyManager->GetIsBossActive())
    {
        camera->StopCameraMove();
    }
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
    //背景モデルの描画
    MV1DrawModel(backGroundModel);
    //それぞれのクラスの描画処理
    map->Draw();
    player->Draw();
    shotManager->Draw();
    enemyManager->Draw();
    gameSceneUI->Draw(player->GetLife());
}
