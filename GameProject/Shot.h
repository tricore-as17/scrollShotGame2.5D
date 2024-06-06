#pragma once
#include"GameObject.h"
#include"DxLib.h"

/// <summary>
/// プレイヤーやエネミーが撃つ弾のクラス
/// </summary>
class Shot :public GameObject
{
public:
    //コンスタラクタ
    Shot(const VECTOR& initPos, const VECTOR& initDir, const float& speed);
    //デストラクタ
    ~Shot();
    void Update();
    void Draw();
private:
    float speed;        //弾のスピード
    float radius;       //半径
};
