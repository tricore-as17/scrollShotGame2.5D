#include"DxLib.h"
#include "FrameRate.h"

/// <summary>
/// コンストラクタ
/// </summary>
FrameRate::FrameRate()
    :startTime(GetNowCount())
    ,roopCount(0)
{

}

//デストラクタ
FrameRate::~FrameRate()
{
    //処理なし
}

/// <summary>
/// フレームレートの計算のためのカウントなどを計算
/// </summary>
void FrameRate::Update()
{
    //1フレーム目なら
    if (roopCount == 0)
    {
        startTime = GetNowCount();
    }
    //60フレーム目なら
    if (roopCount == AVERAGE_FRAME)
    {
        //現在の値を代入
        int tmp = GetNowCount();
        //ループカウントの初期化
        roopCount = 0;
        startTime = tmp;
    }
    roopCount++;
}

/// <summary>
/// 計算した値から設定したフレームレートになるように同期させる
/// </summary>
void FrameRate::Sync()
{
    int tookTime = GetNowCount() - startTime;                   //現在のフレームの経過から1フレーム目で計算した値を引く
    int waitTime = roopCount * 1000 / 60 - tookTime;            //tookTimeの値が大きいと１フレーム辺りにかかる時間が長いので処理が遅いことになる

    if (waitTime > 0)
    {
        Sleep(waitTime);
    }
}
