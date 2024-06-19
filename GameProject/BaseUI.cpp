#include"Font.h"
#include"BaseUI.h"

/// <summary>
/// コンストラクタ
/// </summary>
BaseUI::BaseUI()
    :blinkingCount(0)
    ,isDisplay(true)
{
    //処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
BaseUI::~BaseUI()
{
    //処理なし
}

/// <summary>
/// 文字の点滅表示のカウント
/// </summary>
void BaseUI::CountBlinkingString()
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
}
