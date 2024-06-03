#pragma once
#include"DxLib.h"

//ÉJÉÅÉâ
class Camera
{
public:
    void Init(const VECTOR &inModelPos);
    void Update(const VECTOR &inModelPos);
private:
    VECTOR firstPos;
    VECTOR pos;
    VECTOR modelVector;
    MATRIX yRota;
};
