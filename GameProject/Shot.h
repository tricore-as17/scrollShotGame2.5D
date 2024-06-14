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
    /// <summary>
    /// 引数として値を受け取って初期化
    /// </summary>
    /// <param name="initializePosition">座標</param>
    /// <param name="initializeDirection">方向</param>
    /// <param name="initializeSpeed">スピード</param>
    /// <param name="initializeRadius">半径</param>
    /// <param name="initializeKinds">種類</param>
    /// <param name="initializeDamage">ダメージ</param>
    void Initialize(const VECTOR& initializePosition, const VECTOR& initializeDirection, const float& initializeSpeed, const float& initializeRadius, const int initializeKinds, const int initializeDamage);
    void Update();
    void Draw();
private:
    float speed;        //弾のスピード
    float radius;       //半径
    int kinds;          //弾の種類
    int damage;         //弾のダメージ
    bool survivalFlag;  //弾が生きているかの確認フラグ(誰にも当たっていないか)
};
