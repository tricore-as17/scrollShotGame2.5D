#include"Camera.h"

void Camera::Init(const VECTOR& modelPos)
{
    pos = VGet(0, 0, -10);

    SetCameraPositionAndTarget_UpVecY(pos, VGet(0, 0, 0));

    ////モデル座標の上の部分をカメラが見ることにするので座標を修正
    //VECTOR drawPos = VGet(modelPos.x, modelPos.y , 0.1f);
    //VECTOR modifyModelPos = ConvScreenPosToWorldPos(drawPos);
    //SetCameraPositionAndTarget_UpVecY(modifyModelPos,pos );

    yRota = MGetRotY(DX_PI_F / -10000.0f);

}

void Camera::Update(const VECTOR& modelPos)
{
    ////モデル座標の上の部分をカメラが見ることにするので座標を修正

    
}