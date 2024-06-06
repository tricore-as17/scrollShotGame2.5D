#include"Shot.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="initPos">ショットの初期座標</param>
/// <param name="initDir">ショットの方向</param>
/// <param name="speed">ショットのスピード</param>
Shot::Shot(const VECTOR& initPos,const VECTOR& initDir,const float& initSpeed):speed(initSpeed)
{
    //座標と方向の初期化
    pos = initPos;
    dir = initDir;
}

/// <summary>
/// 弾の移動などの更新処理
/// </summary>
void Shot::Update()
{
    //移動量を出す
    VECTOR velocity = VScale(dir, speed);

}

/// <summary>
/// 弾の描画
/// </summary>
void Shot::Draw()
{

}
