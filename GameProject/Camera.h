#pragma once
#include"DxLib.h"

//�N���X�̃v���g�^�C�v�錾
class Map;
class Player;

/// <summary>
/// �J����
/// </summary>
class Camera
{
public:
    //�R���X�g���N�^
    //�f�X�g���N�^
    Camera();
    ~Camera();
    /// <summary>
    /// �Q�[���J�n���Ƃ̏�����
    /// </summary>
    void Init();
    void Update(const Map& map, const Player& player);
    //�|�W�V������getter/setter
    const VECTOR& GetPos() const { return pos; }
private:
    VECTOR firstPos;
    VECTOR pos;
    VECTOR modelVector;
    MATRIX yRota;
};
