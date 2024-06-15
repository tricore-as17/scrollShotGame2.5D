#include"DxLib.h"
#include"SceneBase.h"
#include "ResultScene.h"
#include"TitleScene.h"
#include"InputManager.h"
#include"Utility.h"

/// <summary>
/// コンストラクタ
/// </summary>
ResultScene::ResultScene()
{
    inputManager = new InputManager();
}

/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene()
{
    delete inputManager;
}

/// <summary>
/// 更新処理
/// </summary>
void ResultScene::Update()
{
    bool isKeyRelease = inputManager->InputKeyOnlyOne(PAD_INPUT_10);

    //スペースキーが押されていればゲームを始める
    if (isKeyRelease)
    {
        inputScene = new TitleScene();
    }
    else
    {
        inputScene = this;
    }
}

/// <summary>
/// 描画処理
/// </summary>
void ResultScene::Draw()
{
    //TODO
    //テスト用の描画(リザルトを実装していないためわかりやすく描画)
    DrawString(500, 500, "リザルト", WHITE);
}
