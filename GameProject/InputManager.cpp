#include"DxLib.h"
#include "InputManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
InputManager::InputManager()
    :releaseKey(false)
    ,onKey(false)
    ,onPrevKey(false)
{
    //処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
InputManager::~InputManager()
{
    //処理なし
}


/// <summary>
/// キーを離した瞬間をとる
/// </summary>
/// <param name="compareKey">チェックしたい入力キー</param>
/// <returns>キーを離したか</returns>
bool InputManager::IsReleaseKey(const int compareKey)
{
    //キー入力
    auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);


    releaseKey = false;
    // キー離した瞬間を取る.
    if (onKey)
    {
        //
        if (!(input & PAD_INPUT_10))
        {
            onKey = false;
            releaseKey = true;
        }
    }
    else if (onPrevKey == false && (input & PAD_INPUT_10))	//キーが最初に押されたタイミング
    {
        releaseKey = false;
        onKey = true;
    }
    if ((input & PAD_INPUT_10))	//押し続けられている時の処理
    {
        onPrevKey = true;
    }
    else
    {
        onPrevKey = false;
    }
    return releaseKey;
}
