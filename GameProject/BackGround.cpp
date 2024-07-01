#include"DxLib.h"
#include"BackGround.h"
#include"Utility.h"


/// <summary>
/// コンストラクタ
/// </summary>
BackGround::BackGround()
{
    //画像を読み込む
    cloudImage      = LoadGraph("img/BG/cloud.png");
    anderCloudImage = LoadGraph("img/BG/anderCloud.png");
    woodImage       = LoadGraph("img/BG/wood.png");
    forestImage     = LoadGraph("img/BG/forest.png");
    skyImage        = LoadGraph("img/BG/sky.png");

    //座標の初期化
    skyPosition = VGet(120, 0, 100);
    anderCloudPosition = VGet(120, 5, 90);
    cloudPoaition = VGet(100, 20, 70);
    forestPosition = VGet(120, 4, 45);
    woodPosition = VGet(120, 9, 20);
    
}

/// <summary>
/// デストラクタ
/// </summary>
BackGround::~BackGround()
{
    //読み込んだ画像の削除
    DeleteGraph(cloudImage);
    DeleteGraph(anderCloudImage);
    DeleteGraph(woodImage);
    DeleteGraph(forestImage);
    DeleteGraph(skyImage);
}

/// <summary>
/// 描画
/// </summary>
void BackGround::Draw()
{
    //それぞれの画像を背景の空間に描画
    DrawBillboard3D(skyPosition, 0.5f, 0.5f, SKY_IMAGE_SIZE, 0, skyImage, TRUE);
    DrawBillboard3D(anderCloudPosition, 0.5f, 0.5f, SKY_IMAGE_SIZE, 0, anderCloudImage, TRUE);
    DrawBillboard3D(cloudPoaition, 0.5f, 0.5f, CLOUD_SIZE, 0, cloudImage, TRUE);
    DrawBillboard3D(forestPosition, 0.5f, 0.5f, FOREST_SIZE, 0, forestImage, TRUE);
    DrawBillboard3D(woodPosition, 0.5f, 0.5f, WOOD_SIZE, 0, woodImage, TRUE);
}
