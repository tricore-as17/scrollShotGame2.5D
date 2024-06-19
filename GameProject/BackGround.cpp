#include "BackGround.h"


/// <summary>
/// コンストラクタ
/// </summary>
BackGround::BackGround()
{
    //モデルハンドルの読み込み
    domeModelHandle = MV1LoadModel("mv1/NightDome.pmx");
    //ポジションの固定
    MV1SetPosition(domeModelHandle, VGet(0, -200, -100));
}

/// <summary>
/// デストラクタ
/// </summary>
BackGround::~BackGround()
{
    //モデルの削除
    MV1DeleteModel(domeModelHandle);
}

/// <summary>
/// 描画
/// </summary>
void BackGround::Draw()
{
    MV1DrawModel(domeModelHandle);
}
