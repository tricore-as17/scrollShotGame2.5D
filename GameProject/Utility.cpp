#include"Utility.h"
#include"DxLib.h"


//静的定数の設定
const float Utility::CONVERSION_RADIAN = DX_PI_F / 180.0f;  //ラジアン変換を作る


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
/// <param name="position">描画したいものの座標</param>
/// <param name="w">幅</param>
/// <param name="h">高さ</param>
void Utility::DrawSquareCollisionDetection(const VECTOR& position, const float& width, const float& height)
{
    //左上座標
    VECTOR leftUpPosition = VGet(position.x - width * 0.5f, position.y + height * 0.5f, 0.0f);
    //左下座標
    VECTOR leftDownPosition = VGet(position.x - width * 0.5f, position.y - height * 0.5f, 0.0f);
    //右上座標
    VECTOR rightUpPosition = VGet(position.x + width * 0.5f, position.y + height * 0.5f, 0.0f);
    //右下座標
    VECTOR rightDownPosition = VGet(position.x + width * 0.5f, position.y - height * 0.5f, 0.0f);
    //左の線の描画
    DrawLine3D(leftUpPosition, leftDownPosition,WHITE);
    //上の線の描画
    DrawLine3D(leftUpPosition, rightUpPosition, WHITE);
    //右の線の描画
    DrawLine3D(rightUpPosition, rightDownPosition, WHITE);
    //下の線の描画
    DrawLine3D(leftDownPosition, rightDownPosition, WHITE);

    
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
