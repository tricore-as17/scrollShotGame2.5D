#include"Utility.h"
#include"DxLib.h"

//static�ϐ��̏�����
float Utility::fps = 0;
int Utility::startTime = GetNowCount();
int Utility::roopCount = 0;

/// <summary>
/// �t���[�����[�g�̒���������ϐ��Ȃǂ̏�����
/// </summary>
void Utility::FpsInit()
{
    //�Q�[���J�n���_�̎��Ԃ��擾
    startTime = GetNowCount();
    roopCount = 0;
    fps = 0;
}
/// <summary>
/// �t���[�����[�g�̌v�Z�̂��߂ɃJ�E���g�Ȃǂ��擾
/// </summary>
void Utility::FpsUpdate()
{
    //1�t���[���ڂȂ�
    if (roopCount == 0)
    {
        startTime = GetNowCount();
    }
    //60�t���[���ڂȂ�
    if (roopCount == AVERAGE_FLAME)
    {
        //���݂̒l����
        int tmp = GetNowCount();
        //�\������FPS�̒l����
        fps = 1000.f / ((tmp - startTime) / (float)AVERAGE_FLAME);
        //���[�v�J�E���g�̏�����
        roopCount = 0;
        startTime = tmp;
    }
    roopCount++;
}
/// <summary>
/// �擾�����J�E���g���g�p�����ۂɃt���[�����[�g�𒲐߂���
/// </summary>
void Utility::FpsControll()
{
    int tookTime = GetNowCount() - startTime;                   //���݂̃t���[���̌o�߂���1�t���[���ڂŌv�Z�����l������
    int waitTime = roopCount * 1000 / 60 - tookTime;            //tookTime�̒l���傫���ƂP�t���[���ӂ�ɂ����鎞�Ԃ������̂ŏ������x�����ƂɂȂ�

    if (waitTime > 0)
    {
        Sleep(waitTime);
    }
}

/// <summary>
/// �Q�[���Ɏg�p����X�N���[���X�s�[�h��J�E���g�Ȃǂ�������
/// </summary>
void Utility::StartInit()
{
    //�Q�[���J�n���Ԃ��L�^
    gameStartTime = GetNowCount();
    elapsedTime = 0;
    endElapsedTime = 0;
    loadFlag = false;
}

/// <summary>
/// �z��ւ̃|�C���^��������ăx�N�^���쐬����
/// </summary>
/// <param name="targetData">�x�N�^���ɓ����z��̃f�[�^</param>
/// <param name="num">�쐬����x�N�^�̐�</param>
/// <returns></returns>
vector<int> Utility::CreateArrayVector(const int targetData[], int num)
{
    std::vector<int> newVector;
    for (int i = 0; i < num; i++)
    {
        newVector.push_back(targetData[i]);
    }
    return newVector;
}

/// <summary>
/// �J�E���g�Ȃǂ̍X�V����
/// </summary>
void Utility::Update()
{
    //�����Ȃ�
}