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
    //処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
ResultScene::~ResultScene()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="inputManager">入力管理クラス</param>
void ResultScene::Update(InputManager* inputManager)
{
    bool isKeyRelease = inputManager->IsReleaseKey(PAD_INPUT_10);

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
void ResultScene::Draw(Font* font)
{
    //TODO
    //テスト用の描画(リザルトを実装していないためわかりやすく描画)
    DrawString(500, 500, "リザルト", WHITE);
}
