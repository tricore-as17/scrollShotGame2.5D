#include"Utility.h"
#include"DxLib.h"

//static変数の初期化
float Utility::fps = 0;
int Utility::startTime = GetNowCount();
int Utility::roopCount = 0;

//静的定数の設定
const float Utility::CONVERSION_RADIAN = DX_PI_F / 180.0f;  //ラジアン変換を作る

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
/// 四角の当たり判定の描画
/// </summary>
/// <param name="pos">描画したいものの座標</param>
/// <param name="w">幅</param>
/// <param name="h">高さ</param>
void Utility::DrawSquareCollisionDetection(const VECTOR& pos, const float& w, const float& h)
{
    //左上座標
    VECTOR leftUpPos = VGet(pos.x - w * 0.5f, pos.y + h * 0.5f, 0.0f);
    //左下座標
    VECTOR leftDownPos = VGet(pos.x - w * 0.5f, pos.y - h * 0.5f, 0.0f);
    //右上座標
    VECTOR rightUpPos = VGet(pos.x + w * 0.5f, pos.y + h * 0.5f, 0.0f);
    //右下座標
    VECTOR rightDownPos = VGet(pos.x + w * 0.5f, pos.y - h * 0.5f, 0.0f);
    //左の線の描画
    DrawLine3D(leftUpPos, leftDownPos,WHITE);
    //上の線の描画
    DrawLine3D(leftUpPos, rightUpPos, WHITE);
    //右の線の描画
    DrawLine3D(rightUpPos, rightDownPos, WHITE);
    //下の線の描画
    DrawLine3D(leftDownPos, rightDownPos, WHITE);

    
}
/// <summary>
/// フレームレートに合わせたスピードの値を計算する処理
/// </summary>
/// <param name="setSpeed">代入するスピード</param>
float Utility::CalculationSpeed(const float setSpeed)
{
    return setSpeed / 60.0f / 60.0f / 60.0f;
}

/// <summary>
/// カウントなどの更新処理
/// </summary>
void Utility::Update()
{
    //処理なし
}
