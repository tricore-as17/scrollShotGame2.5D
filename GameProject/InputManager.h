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
    /// キー１度だけ押す処理(押し続けても入力されないように)
    /// </summary>
    /// <param name="inputKey">入力されたキーの値</param>
    /// <param name="compareKey">チェックしたい入力キー</param>
    void InputKeyOnlyOne(const int inputKey,const int compareKey);

private:
    bool releaseKey;        //キーが離されたか
    bool onKey;             //キーが押されたか
    bool onPrevKey;         //キーが押され続けているか
    
};

