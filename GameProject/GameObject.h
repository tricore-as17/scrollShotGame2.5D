#pragma once
#include"DxLib.h"

/// <summary>
/// 座標などをまとめたゲームのオブジェクトに使用する基底クラス
/// </summary>
class GameObject
{
public:
    //getter,setter
    VECTOR GetPosition()const { return position; }                        //座標の取得
    void SetPosition(const VECTOR inPosition) { position = inPosition; }  //座標の設定
    VECTOR GetDir()const { return direction; }                            //方向の取得
    void SetDir(const VECTOR inDirection) { direction = inDirection;  }   //方向の設定
    float GetWidth()const { return width; }                  //幅の取得
    float GetHeight()const { return height; }                //高さの取得
    float GetFallSpeed()const { return fallSpeed; }          //落下速度の取得
    void SetFallSpeed(const float inFallSpeed) { fallSpeed = inFallSpeed; } //落下速度の設定
protected:
    //使用する座標などの変数
    VECTOR position;				//座標
    VECTOR direction;				//移動方向
    float width;		    //幅
    float height;			//高さ
    float fallSpeed;		//落下速度
};
