#pragma once

/// <summary>
/// キー入力に関するクラス
/// </summary>
class InputManager
{
public:
    //コンストラクタ
    InputManager();
    //デストラクタ
    ~InputManager();
    /// <summary>
    /// キーを離した瞬間をとる
    /// </summary>
    /// <param name="compareKey">チェックしたい入力キー</param>
    /// <returns>キーを離したか</returns>
    bool IsReleaseKey(const int compareKey);

private:
    bool releaseKey;        //キーが離されたか
    bool onKey;             //キーが押されたか
    bool onPrevKey;         //キーが押され続けているか
    
};
