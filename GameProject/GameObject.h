#pragma once
#include"DxLib.h"

class GameObject
{
protected:
	//使用する座標などの変数
	VECTOR pos;				//座標
	VECTOR dir;				//移動方向
	float w;				//幅
	float h;				//高さ
	float fallSpeed;		//落下速度
};
