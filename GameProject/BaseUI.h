#pragma once

class Font;

class BaseUI abstract
{
public:
    //コンストラクタ
    BaseUI();
    //デストラクタ
    virtual ~BaseUI();
    virtual void Update() abstract;
    virtual void Draw(Font* font) abstract;

    /// <summary>
    /// 文字の点滅表示のカウント
    /// </summary>
    void CountBlinkingString();
protected:
    //定数
    static constexpr int DISPLAY_TIME = 15;     //描画する時間
    static constexpr int INVISIBLE_TIME = 30;   //消している時間

    int BackGroundGraph;        //背景画像
    int blinkingCount;           //点滅させるカウント
    bool isDisplay;              //表示させるかのフラグ
};
