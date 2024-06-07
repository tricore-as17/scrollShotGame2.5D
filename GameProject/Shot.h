#pragma once
#include"GameObject.h"
#include"DxLib.h"

/// <summary>
/// プレイヤーやエネミーが撃つ弾のクラス
/// </summary>
class Shot :public GameObject
{
public:
    //getter,setter
    VECTOR GetPos()const { return pos; }    //座標のgetter
    //コンスタラクタ
    Shot(const VECTOR& initPos, const VECTOR& initDir, const float& initSpeed,const float& initRadius,const int kinds);
    //デストラクタ
    ~Shot();
    void Update();
    void Draw();
private:
    float speed;        //弾のスピード
    float radius;       //半径
    int kinds;          //弾の種類
};
