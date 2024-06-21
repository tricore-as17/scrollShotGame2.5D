#pragma once
#include"DxLib.h"

//クラスのプロトタイプ宣言
class Font;
class BlinkingString;

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
    /// 描画
    /// </summary>
    void Draw();

private:
    int             backGroundGraph;//背景画像
    BlinkingString* blinkingString; //文字の点滅表示用のクラス
    Font*           font;           //フォントハンドルの格納クラス              

};

