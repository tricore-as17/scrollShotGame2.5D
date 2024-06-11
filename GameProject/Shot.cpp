#include"Shot.h"
#include"Utility.h"


/// <summary>
/// 引数として値を受け取って初期化
/// </summary>
/// <param name="initPos">座標</param>
/// <param name="initDir">方向</param>
/// <param name="initSpeed">スピード</param>
/// <param name="initRadius">半径</param>
/// <param name="initKinds">種類</param>
/// <param name="initDamage">ダメージ</param>
void Shot::Init(const VECTOR& initPos, const VECTOR& initDir, const float& initSpeed, const float& initRadius, const int initKinds, const int initDamage)
{
    survivalFlag = true;
    pos = initPos;
    dir = initDir;
    speed = initSpeed;
    radius = initRadius;
    kinds = initKinds;
    damage = initDamage;
}

/// <summary>
/// 弾の移動などの更新処理
/// </summary>
void Shot::Update()
{
    //移動量を出す
    VECTOR velocity = VScale(dir, speed);
    pos = VAdd(pos, velocity);
}

/// <summary>
/// 弾の描画
/// </summary>
void Shot::Draw()
{
    //テスト用の描画のちのちは別の画像を使用
    DrawSphere3D(pos, radius, 32, GetColor(255, 0, 0), WHITE, TRUE);
}
