#pragma once

class Font;

class BaseUI abstract
{
public:
    //コンストラクタ
    BaseUI();
    //デストラクタ
    virtual ~BaseUI();
    /// <summary>
    /// 更新処理
    /// </summary>
    virtual void Update() abstract;
    /// <summary>
    /// 描画処理
    /// </summary>
    /// <param name="font">フォントの格納クラス</param>
    virtual void Draw(Font* font) {}

    /// <summary>
    /// 文字の点滅表示のカウント
    /// </summary>
    void CountBlinkingString();
protected:
    //定数
    static constexpr int DISPLAY_TIME = 15;     //描画する時間
    static constexpr int INVISIBLE_TIME = 30;   //消している時間

    int blinkingCount;           //点滅させるカウント
    bool isDisplay;              //表示させるかのフラグ
};
