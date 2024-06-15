#pragma once

/// <summary>
/// キー入力に関するクラス
/// </summary>
class InputManager
{
public:
    //getter,setter
    const bool GetIsStopKey()const { return isStopKey; }
    //コンストラクタ
    InputManager();
    //デストラクタ
    ~InputManager();
    /// <summary>
    /// キー１度だけ押す処理(押し続けても入力されないように)
    /// </summary>
    /// <param name="compareKey">チェックしたい入力キー</param>
    /// <returns>入力されたかを返す</returns>
    bool InputKeyOnlyOne(const int compareKey);

private:
    bool releaseKey;        //キーが離されたか
    bool onKey;             //キーが押されたか
    bool onPrevKey;         //キーが押され続けているか
    bool isStopKey;         //キーを押されないようにする
    
};

