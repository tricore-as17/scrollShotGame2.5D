#include"DxLib.h"
#include"SceneBase.h"
#include "TitleScene.h"
#include"GameScene.h"
#include"InputManager.h"
#include"Utility.h"


/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
{
    inputManager = new InputManager();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
    delete inputManager;
}

/// <summary>
/// 更新処理
/// </summary>
void TitleScene::Update()
{
    //スペースキーが押されたかのチェック
    bool isKeyRelease = inputManager->InputKeyOnlyOne(PAD_INPUT_10);

    //スペースキーが押されていればゲームを始める
    if (isKeyRelease)
    {
        inputScene = new GameScene();
    }
    else
    {
        inputScene = this;
    }
}

/// <summary>
/// 描画処理
/// </summary>
void TitleScene::Draw()
{
    //TODO
    //テスト用の描画(タイトルを実装していないためわかりやすく描画)
    DrawString(500, 500, "タイトル", WHITE);
}
