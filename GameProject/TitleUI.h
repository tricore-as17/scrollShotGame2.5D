#pragma once
#include"DxLib.h"

class Font;

/// <summary>
/// タイトルのUIをまとめたクラス
/// </summary>
class TitleUI
{
public:

    //コンストラクタ
    TitleUI();
    //デストラクタ
    ~TitleUI();
    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();
    //描画
    void Draw(Font* font);

    /// <summary>
    /// 文字の点滅表示のカウント
    /// </summary>
    void CountBlinkingString();

private:
    //定数
    static constexpr int DISPLAY_TIME = 15;
    static constexpr int INVISIBLE_TIME = 30;

    int BackGroundGraph ;        //背景画像
    int blinkingCount;           //点滅させるカウント
    bool isDisplay;              //表示させるかのフラグ
};

