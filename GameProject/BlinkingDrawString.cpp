#include "BlinkingDrawString.h"

/// <summary>
/// コンストラクタ
/// </summary>
BlinkingString::BlinkingString()
    :isDisplay(true)
    ,blinkingCount(0)
{

}

/// <summary>
/// デストラクタ
/// </summary>
BlinkingString::~BlinkingString()
{
    //処理なし
}

/// <summary>
/// 点滅する文字の描画
/// </summary>
/// <param name="drawPosision">描画する座標</param>
/// <param name="string">文字列</param>
/// <param name="color">色</param>
/// <param name="fontHandle">フォントのハンドル</param>
void BlinkingString::BlinkingStringDraw(VECTOR drawPosision, const char* string,int color, int fontHandle)
{
    blinkingCount++;
    //文字を表示する時間のカウント
    if (blinkingCount <= DISPLAY_TIME)
    {
        isDisplay = true;
    }
    //文字を消す時間のカウント
    else if (blinkingCount > DISPLAY_TIME && blinkingCount <= INVISIBLE_TIME)
    {
        isDisplay = false;
        if (blinkingCount == INVISIBLE_TIME)
        {
            blinkingCount = 0;
        }
    }

    //描画するフラグが立っていれば描画する
    if (isDisplay)
    {
        DrawStringToHandle(drawPosision.x, drawPosision.y, string, color, fontHandle);
    }
}
