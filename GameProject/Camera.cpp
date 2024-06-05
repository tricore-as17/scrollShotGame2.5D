#include"Camera.h"
#include"Map.h"
#include"Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
{
    //���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
    SetCameraNearFar(0.1f, 1000.0f);
    //���W�̏�����
    pos = VGet(0, 0, 0);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
    //�����Ȃ�
}

/// <summary>
/// �Q�[���J�n���Ƃ̏�����
/// </summary>
void Camera::Init()
{
    //���W�̏�����
    pos = VGet(0, 0, 0);

}

/// <summary>
/// �J�������v���C���[�̈ʒu��}�b�v�̈ʒu�ɍ��킹�čX�V����
/// </summary>
/// <param name="map"></param>
/// <param name="player"></param>
void Camera::Update(const Map& map, const Player& player)
{
    //�v���C���[�ƃ}�b�v�̍��W�������Ă���
    VECTOR playerPos = player.GetPos();
    int mapYNum = map.getMapYNum();

    // �傫��0.5�̃}�b�v�`�b�v���A�}�b�vY�̐������z�u����
    // �v���C���[�̒n�ʂ�Y�ʒu��0�Ƃ������̂ŁA�n�㕔�̃}�b�v�`�b�v�̐��͓���炵���ʒu�Œ���
    // ���̐^�񒆂ɕ\������̂Ŕ������v�Z�ŏo��
    // �v���C���[��X���W�ɂ͒Ǐ]�������̂�player��X���g��
    VECTOR cameraPos = VGet(playerPos.x, Map::CHIP_SIZE * (mapYNum - 2) * 0.5f, playerPos.z - 15.0f);


    // �������鎋�_�́A�J�����ƕ��s�ɂ܂�����z=0�n�_
    VECTOR lookPos = VGet(cameraPos.x, cameraPos.y, 0.0f);

    pos = cameraPos;

    // �J�����Ɉʒu�𔽉f.
    SetCameraPositionAndTarget_UpVecY(pos, lookPos);
    
}