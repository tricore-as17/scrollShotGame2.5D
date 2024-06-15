#include "SceneManager.h"
#include"SceneBase.h"
#include"TitleScene.h"
#include"Game.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneManager::SceneManager()
    :nowScene(NULL)
{
    //最初はタイトルなのでタイトルシーンを作成してnowSceneに代入
    nowScene = new TitleScene();

    game = new Game();
    //TODO
    //ゲームから無理やり読んでいるのでフレームレート処理用のクラスを作る
    game->InitializeFrameRate();

}


/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
    delete nowScene;
}

/// <summary>
/// ゲームループをまわす処理
/// </summary>
void SceneManager::GameLoop()
{
    //ゲームを終了するフラグが来ない限り続ける
    while (IsContinueGame())
    {
        ClearDrawScreen();
        //ToDo
        //ゲームを無理やり呼び出してフレームレートを調整しているのでそこを修正
        game->UpdateFrameRate();
        nowScene->Update();
        //更新処理の後次のループでのシーンを代入する
        nextScene = nowScene->GetNextScene();
        nowScene->Draw();
        ScreenFlip();
        //TODO
        //ここも別のフレームレート処理用のクラスを作る
        game->ControlFrameRate();
        //次のループのシーンと現在のシーンが違う場合は移行処理を行う
        if (nowScene != nextScene)
        {
            SceneChange();
        }
        

    }
}

/// <summary>
/// ゲームを継続するかの判断
/// </summary>
/// <returns>継続するかのフラグ</returns>
bool SceneManager::IsContinueGame()
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
    //TODO
    //他に終了する条件をここに追加する
    return isContinue;
    
}

/// <summary>
/// シーンの移行処理
/// </summary>
void SceneManager::SceneChange()
{
    delete nowScene;
    nowScene = nextScene;
    nextScene = NULL;
}
