#include"Camera.h"

void Camera::Init(const VECTOR& modelPos)
{
    pos = VGet(0, 0, -10);

    SetCameraPositionAndTarget_UpVecY(pos, VGet(0, 0, 0));

    ////���f�����W�̏�̕������J���������邱�Ƃɂ���̂ō��W���C��
    //VECTOR drawPos = VGet(modelPos.x, modelPos.y , 0.1f);
    //VECTOR modifyModelPos = ConvScreenPosToWorldPos(drawPos);
    //SetCameraPositionAndTarget_UpVecY(modifyModelPos,pos );

    yRota = MGetRotY(DX_PI_F / -10000.0f);

}

void Camera::Update(const VECTOR& modelPos)
{
    ////���f�����W�̏�̕������J���������邱�Ƃɂ���̂ō��W���C��

    
}