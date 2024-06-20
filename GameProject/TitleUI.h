#pragma once
#include"DxLib.h"
#include"BaseUI.h"

class Font;

/// <summary>
/// タイトルのUIをまとめたクラス
/// </summary>
class TitleUI:public BaseUI
{
public:

    //コンストラクタ
    TitleUI();
    //デストラクタ
    ~TitleUI();
    /// <summary>
    /// 更新処理
    /// </summary>
    void Update() override;
    //描画
    void Draw(Font* font) override;

private:
    int backGroundGraph;        //背景画像

};

