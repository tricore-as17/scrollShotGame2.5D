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
/// キー１度だけ押す処理(押し続けても入力されないように)
/// </summary>
/// <param name="inputKey">入力されたキーの値</param>
/// <param name="compareKey"></param>
/// <returns></returns>
void InputManager::InputKeyOnlyOne(const int inputKey, const int compareKey)
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
}
