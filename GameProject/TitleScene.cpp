﻿#include"DxLib.h"
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
    //処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
TitleScene::~TitleScene()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="inputManager">入力管理クラス</param>
void TitleScene::Update(InputManager* inputManager)
{
    //スペースキーが押されたかのチェック
    bool isKeyRelease = inputManager->IsReleaseKey(PAD_INPUT_10);

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
