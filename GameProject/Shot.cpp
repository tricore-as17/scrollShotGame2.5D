#include"Shot.h"
#include"Utility.h"

///// <summary>
///// コンストラクタ
///// </summary>
///// <param name="initPos">ショットの初期座標</param>
///// <param name="initDir">ショットの方向</param>
///// <param name="speed">ショットのスピード</param>
///// <param name="initRadius">ショットの半径</param>
///// <param name="initKinds">弾の種類</param>
///// <param name="initDamage">弾のダメージ</param>
//Shot::Shot(const VECTOR& initPos, const VECTOR& initDir, const float& initSpeed, const float& initRadius,const int initKinds,const int initDamage)
//survivalFlag(true)
//{
//    //座標と方向の初期化
//    pos = initPos;
//    dir = initDir;
//}

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
