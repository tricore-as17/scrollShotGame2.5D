#include"Shot.h"
#include"Utility.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="initPos">ショットの初期座標</param>
/// <param name="initDir">ショットの方向</param>
/// <param name="speed">ショットのスピード</param>
/// <param name="initRadius">ショットの半径</param>
Shot::Shot(const VECTOR& initPos, const VECTOR& initDir, const float& initSpeed, const float& initRadius,const int initKinds)
    :speed(initSpeed),radius(initRadius),kinds(initKinds)
{
    //座標と方向の初期化
    pos = initPos;
    dir = initDir;
}

/// <summary>
/// デストラクタ
/// </summary>
Shot::~Shot()
{
    //処理なし
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
