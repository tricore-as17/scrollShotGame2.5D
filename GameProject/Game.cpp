#include "Game.h"
#include"FrameRate.h"
#include"InputManager.h"
#include"SceneBase.h"
#include"TitleScene.h"
#include"Game.h"

/// <summary>
/// コンストラクタ
/// </summary>
Game::Game()
    :nowScene(NULL)
{
    //最初はタイトルなのでタイトルシーンを作成してnowSceneに代入
    nowScene = new TitleScene();

    frameRate = new FrameRate();
    inputManager = new InputManager();

}


/// <summary>
/// デストラクタ
/// </summary>
Game::~Game()
{
    //解放処理
    delete nowScene;
    delete frameRate;
    delete inputManager;
}

/// <summary>
/// ゲームループをまわす処理
/// </summary>
void Game::Update()
{
    //ゲームを終了するフラグが来ない限り続ける
    while (IsContinueGame())
    {
        ClearDrawScreen();
        //フレームレートを調整するための計算
        frameRate->Update();
        nowScene->Update(inputManager);
        //更新処理の後次のループでのシーンを代入する
        nextScene = nowScene->GetNextScene();
        nowScene->Draw();
        ScreenFlip();
        //フレームレートを設定した値に同期させる
        frameRate->Sync();
        //次のループのシーンと現在のシーンが違う場合は移行処理を行う
        if (nowScene != nextScene)
        {
            ChangeScene();
        }


    }
}

/// <summary>
/// ゲームを継続するかの判断
/// </summary>
/// <returns>継続するかのフラグ</returns>
bool Game::IsContinueGame()
{
    //継続するか判断するフラグ
    bool isContinue = true;
    if (ProcessMessage())
    {
        isContinue = false;
    }
    if (CheckHitKey(KEY_INPUT_ESCAPE))
    {
        isContinue = false;
    }
    return isContinue;

}

/// <summary>
/// シーンの移行処理
/// </summary>
void Game::ChangeScene()
{
    delete nowScene;
    nowScene = nextScene;
    nextScene = NULL;
}
