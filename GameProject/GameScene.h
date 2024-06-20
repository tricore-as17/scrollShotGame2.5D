#pragma once
#include"SceneBase.h"

//クラスのプロトタイプ宣言
class Player;
class Camera;
class Map;
class EnemyManager;
class ShotManager;
class InputManager;
class BackGround;
class GameSceneUI;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene:public SceneBase
{
public:
    GameScene();
    ~GameScene();

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="inputManager">入力管理クラス</param>
    void Update(InputManager* inputManager)override;

    /// <summary>
    /// 描画
    /// </summary>
    void Draw(Font* font) override;
private:
    Player*       player;         //プレイヤー
    Camera*       camera;         //カメラ
    Map*          map;            //マップ
    BackGround*   backGround;     //背景         
    EnemyManager* enemyManager;   //エネミーマネージャー
    ShotManager*  shotManager;    //ショットマネージャー
    GameSceneUI*  gameSceneUI;    //ゲームシーンのUI      
    

};

