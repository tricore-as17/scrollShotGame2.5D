#pragma once
#include"SceneBase.h"

//クラスのプロトタイプ宣言
class Player;
class Camera;
class Map;
class EnemyManager;
class ShotManager;
class InputManager;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene:public SceneBase
{
public:
    GameScene();
    ~GameScene();


    void Update()override;

    void Draw() override;
private:
    Player*       player;         //プレイヤー
    Camera*       camera;         //カメラ
    Map*          map;            //マップ
    EnemyManager* enemyManager;   //エネミーマネージャー
    ShotManager*  shotManager;    //ショットマネージャー
    InputManager* inputManager;   //インプトマネージャー
    

};

