#include"Utility.h"
#include"DxLib.h"

//static変数の初期化
float Utility::fps = 0;
int Utility::startTime = GetNowCount();
int Utility::roopCount = 0;

//初期化
void Utility::FpsInit()
{
    //ゲーム開始時点の時間を取得
    startTime = GetNowCount();
    roopCount = 0;
    fps = 0;
}
//更新処理
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
//コントロール
void Utility::FpsControll()
{
    int tookTime = GetNowCount() - startTime;                   //現在のフレームの経過から1フレーム目で計算した値を引く
    int waitTime = roopCount * 1000 / 60 - tookTime;            //tookTimeの値が大きいと１フレーム辺りにかかる時間が長いので処理が遅いことになる

    if (waitTime > 0)
    {
        Sleep(waitTime);
    }
}

//ゲーム開始時ごとの初期化
void Utility::StartInit()
{
    //ゲーム開始時間を記録
    gameStartTime = GetNowCount();
    elapsedTime = 0;
    scrollSpeed = FIRST_SCROLL_SPEED;
    endElapsedTime = 0;
    loadFlag = false;
}

//更新処理
void Utility::Update()
{
    int nowTime = GetNowCount();
    //現在の時間からゲームスタート時の時間を引いて経過時間を出す
    elapsedTime = nowTime - gameStartTime;   
    if (elapsedTime > 20000 && elapsedTime <=40000)
    {
        scrollSpeed = SECOND_SCROLL_SPEED;
    }
    else if (elapsedTime >40000 && elapsedTime <=60000)
    {
        scrollSpeed = THIRD_SCROLL_SPEED;
    }
    else if (elapsedTime > 60000 && elapsedTime <= 80000)
    {
        scrollSpeed = FORCE_SCROLL_SPEED;
    }
    else if (elapsedTime > 80000 && elapsedTime <= 90000)
    {
        scrollSpeed = FIFTH_SCROLL_SPEED;
    }
}