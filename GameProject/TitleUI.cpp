#include "TitleUI.h"
#include"BlinkingDrawString.h"
#include"Font.h"


/// <summary>
/// コンストラクタ
/// </summary>
TitleUI::TitleUI()
{
    //メモリの確保
    blinkingString = new BlinkingString();
    font = new Font();
    //タイトルで使う画像のロード
    backGroundGraph = LoadGraph("img/BG/TitleBG.png");
}

/// <summary>
/// デストラクタ
/// </summary>
TitleUI::~TitleUI()
{
    //読み込んだ画像の解放
    DeleteGraph(backGroundGraph);
    //メモリの開放
    delete blinkingString;
    delete font;
    //NULL代入
    blinkingString = NULL;
    font           = NULL;

}


/// <summary>
/// 描画
/// </summary>
void TitleUI::Draw()
{
    //背景画像の描画
    DrawGraph(0, 0, backGroundGraph, TRUE);
    //点滅文字の座標取得
    VECTOR blinkingStringPosition = VGet(200, 500, 0);
    //タイトルでの説明文の追加
    blinkingString->BlinkingStringDraw(blinkingStringPosition, "SPACEボタンでスタート！", Font::FONT_COLOR_GRAY, font->GetTitleExplanetionHandle());
    
}




