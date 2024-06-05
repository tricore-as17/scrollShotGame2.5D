#include"Utility.h"
#include"DxLib.h"

//static変数の初期化
float Utility::fps = 0;
int Utility::startTime = GetNowCount();
int Utility::roopCount = 0;

/// <summary>
/// フレームレートの調整をする変数などの初期化
/// </summary>
void Utility::FpsInit()
{
    //ゲーム開始時点の時間を取得
    startTime = GetNowCount();
    roopCount = 0;
    fps = 0;
}
/// <summary>
/// フレームレートの計算のためにカウントなどを取得
/// </summary>
void Utility::FpsUpdate()
{
    //1フレーム目なら
    if (roopCount == 0)
    {
        startTime = GetNowCount();
    }
    //60フレーム目なら
    if (roopCount == AVERAGE_FLAME)
    {
        //現在の値を代入
        int tmp = GetNowCount();
        //表示するFPSの値を代入
        fps = 1000.f / ((tmp - startTime) / (float)AVERAGE_FLAME);
        //ループカウントの初期化
        roopCount = 0;
        startTime = tmp;
    }
    roopCount++;
}
/// <summary>
/// 取得したカウントを使用し実際にフレームレートを調節する
/// </summary>
void Utility::FpsControll()
{
    int tookTime = GetNowCount() - startTime;                   //現在のフレームの経過から1フレーム目で計算した値を引く
    int waitTime = roopCount * 1000 / 60 - tookTime;            //tookTimeの値が大きいと１フレーム辺りにかかる時間が長いので処理が遅いことになる

    if (waitTime > 0)
    {
        Sleep(waitTime);
    }
}

/// <summary>
/// ゲームに使用するスクロールスピードやカウントなどを初期化
/// </summary>
void Utility::StartInit()
{
    //ゲーム開始時間を記録
    gameStartTime = GetNowCount();
    elapsedTime = 0;
    endElapsedTime = 0;
    loadFlag = false;
}

/// <summary>
/// 配列へのポインタをもらってベクタを作成する
/// </summary>
/// <param name="targetData">ベクタ内に入れる配列のデータ</param>
/// <param name="num">作成するベクタの数</param>
/// <returns></returns>
vector<int> Utility::CreateArrayVector(const int targetData[], int num)
{
    std::vector<int> newVector;
    for (int i = 0; i < num; i++)
    {
        newVector.push_back(targetData[i]);
    }
    return newVector;
}

/// <summary>
/// カウントなどの更新処理
/// </summary>
void Utility::Update()
{
    //処理なし
}