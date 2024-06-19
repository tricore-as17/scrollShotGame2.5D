#include "TitleUI.h"
#include"Font.h"


/// <summary>
/// コンストラクタ
/// </summary>
TitleUI::TitleUI()
{
    //タイトルで使う画像のロード
    BackGroundGraph = LoadGraph("img/BG/TitleBG.png");
}

/// <summary>
/// デストラクタ
/// </summary>
TitleUI::~TitleUI()
{
    //読み込んだ画像の解放
    DeleteGraph(BackGroundGraph);
}

/// <summary>
/// 更新処理
/// </summary>
void TitleUI::Update()
{
    //点滅させるためのカウント計算
    CountBlinkingString();
}

/// <summary>
/// 描画
/// </summary>
void TitleUI::Draw(Font* font)
{
    //背景画像の描画
    DrawGraph(0, 0, BackGroundGraph, TRUE);
    //タイトルでの説明文の追加
    if (isDisplay)
    {
        DrawStringToHandle(300, 500, "SPACEボタンでスタート！", Font::FONT_COLOR_GRAY, font->GetTitleExplanetionHandle());
    }
}




