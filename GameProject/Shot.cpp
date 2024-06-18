#include"Shot.h"
#include"Utility.h"


/// <summary>
/// 引数として値を受け取って初期化
/// </summary>
/// <param name="position">座標</param>
/// <param name="initializeDirection">方向</param>
/// <param name="initializeSpeed">スピード</param>
/// <param name="initializeRadius">半径</param>
/// <param name="initializeKinds">種類</param>
/// <param name="initializeDamage">ダメージ</param>
void Shot::Initialize(const VECTOR& initializePosition, const VECTOR& initializeDirection, const float& initializeSpeed, const float& initializeRadius, const int initializeKinds, const int initializeDamage)
{
    survivalFlag = true;
    position = initializePosition;
    direction = initializeDirection;
    speed = initializeSpeed;
    radius = initializeRadius;
    kinds = initializeKinds;
    damage = initializeDamage;
}

/// <summary>
/// 弾の移動などの更新処理
/// </summary>
void Shot::Update()
{
    //移動量を出す
    VECTOR velocity = VScale(direction, speed);
    position = VAdd(position, velocity);
}

/// <summary>
/// 弾の描画
/// </summary>
void Shot::Draw()
{
    //テスト用の描画のちのちは別の画像を使用
    DrawSphere3D(position, radius, 16, GetColor(255, 0, 0), WHITE, TRUE);
}
