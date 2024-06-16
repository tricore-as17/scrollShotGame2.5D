#pragma once

/// <summary>
/// フレームレートをコントロールするためのクラス
/// </summary>
class FrameRate
{
public:
    //コンストラクタ
    FrameRate();
    //デストラクタ
    ~FrameRate();
    /// <summary>
    /// フレームレートの計算のためのカウントなどを計算
    /// </summary>
    void Update();
    /// <summary>
    /// 計算した値から処理をまつ
    /// </summary>
    void Control();
private:
    static constexpr int AVERAGE_FRAME = 60;        //調節するフレームレートの値

    int startTime;          //ループ開始時の時間
    int roopCount;          //ループの回数

};

