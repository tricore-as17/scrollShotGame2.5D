#pragma once
#include"DxLib.h"

/// <summary>
/// 文字を点滅表示させる機能をもったクラス
/// </summary>
class BlinkingString
{
public:
    //コンストラクタ
    BlinkingString();
    //デストラクタ
    virtual ~BlinkingString();
    /// <summary>
    /// 点滅する文字の描画
    /// </summary>
    /// <param name="drawPosision">描画する座標</param>
    /// <param name="string">文字列</param>
    /// <param name="color">色</param>
    /// <param name="fontHandle">フォントのハンドル</param>
    void BlinkingStringDraw(VECTOR drawPosision,const char* string,int color,int fontHandle);

private:
    static constexpr int DISPLAY_TIME   = 15;     //描画する時間
    static constexpr int INVISIBLE_TIME = 30;     //消している時間

    int blinkingCount;           //点滅させるカウント
    bool isDisplay;              //表示させるかのフラグ
    
};

