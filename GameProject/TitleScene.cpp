#include"DxLib.h"
#include"TitleUI.h"
#include"SceneBase.h"
#include "TitleScene.h"
#include"GameScene.h"
#include"InputManager.h"
#include"Font.h"
#include"Utility.h"


/// <summary>
/// コンストラクタ
/// </summary>
TitleScene::TitleScene()
{
    //メモリの確保
    titleUI = new TitleUI();
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
    //処理なし
    delete titleUI;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="inputManager">入力管理クラス</param>
void TitleScene::Update(InputManager* inputManager)
{
    //スペースキーが押されたかのチェック
    bool isKeyRelease = inputManager->IsReleaseKey(PAD_INPUT_10);
    titleUI->Update();

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
void TitleScene::Draw(Font* font)
{
    titleUI->Draw(font);
}
