#pragma once
#include"DxLib.h"

/// <summary>
/// 座標などをまとめたゲームのオブジェクトに使用する基底クラス
/// </summary>
class GameObject
{
public:
    //getter,setter
    VECTOR GetPos()const { return pos; }                //座標の取得
    void SetPos(const VECTOR inPos) { pos = inPos; }    //座標の設定
    VECTOR GetDir()const { return dir; }                //方向の取得
    void SetDir(const VECTOR inDir) { dir = inDir;  }   //方向の設定
    float GetW()const { return width; }                 //幅の取得
    float GetH()const { return height; }                //高さの取得
    float GetFallSpeed()const { return fallSpeed; }     //落下速度の取得
    void SetFallSpeed(const float inFallSpeed) { fallSpeed = inFallSpeed; } //落下速度の設定
protected:
	//使用する座標などの変数
	VECTOR pos;				//座標
	VECTOR dir;				//移動方向
	float width;		    //幅
	float height;			//高さ
	float fallSpeed;		//落下速度
};
