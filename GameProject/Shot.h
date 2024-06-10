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
    float GetRadius()const { return radius; }           //半径を返す
    int GetSurvivalFlag()const { return survivalFlag; } //この弾が生きているかを返す
    void SetSurvivalFlag(const bool inFlag) { survivalFlag = inFlag; }  //弾が生きているフラグを設定する
    int Getkinds()const { return kinds; }               //弾の種類を返す
    int GetDamage()const { return damage; }             //弾のダメージを返す
    //コンスタラクタ
    Shot(const VECTOR& initPos, const VECTOR& initDir, const float& initSpeed,const float& initRadius,const int kinds
        , const int inDamage);
    //デストラクタ
    ~Shot();
    void Update();
    void Draw();
private:
    float speed;        //弾のスピード
    float radius;       //半径
    int kinds;          //弾の種類
    int damage;         //弾のダメージ
    bool survivalFlag;  //弾が生きているかの確認フラグ(誰にも当たっていないか)
};
