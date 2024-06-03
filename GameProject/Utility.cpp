#include"Utility.h"
#include"DxLib.h"

//static�ϐ��̏�����
float Utility::fps = 0;
int Utility::startTime = GetNowCount();
int Utility::roopCount = 0;

//������
void Utility::FpsInit()
{
    //�Q�[���J�n���_�̎��Ԃ��擾
    startTime = GetNowCount();
    roopCount = 0;
    fps = 0;
}
//�X�V����
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
//�R���g���[��
void Utility::FpsControll()
{
    int tookTime = GetNowCount() - startTime;                   //���݂̃t���[���̌o�߂���1�t���[���ڂŌv�Z�����l������
    int waitTime = roopCount * 1000 / 60 - tookTime;            //tookTime�̒l���傫���ƂP�t���[���ӂ�ɂ����鎞�Ԃ������̂ŏ������x�����ƂɂȂ�

    if (waitTime > 0)
    {
        Sleep(waitTime);
    }
}

//�Q�[���J�n�����Ƃ̏�����
void Utility::StartInit()
{
    //�Q�[���J�n���Ԃ��L�^
    gameStartTime = GetNowCount();
    elapsedTime = 0;
    scrollSpeed = FIRST_SCROLL_SPEED;
    endElapsedTime = 0;
    loadFlag = false;
}

//�X�V����
void Utility::Update()
{
    int nowTime = GetNowCount();
    //���݂̎��Ԃ���Q�[���X�^�[�g���̎��Ԃ������Čo�ߎ��Ԃ��o��
    elapsedTime = nowTime - gameStartTime;   
    if (elapsedTime > 20000 && elapsedTime <=40000)
    {
        scrollSpeed = SECOND_SCROLL_SPEED;
    }
    else if (elapsedTime >40000 && elapsedTime <=60000)
    {
        scrollSpeed = THIRD_SCROLL_SPEED;
    }
    else if (elapsedTime > 60000 && elapsedTime <= 80000)
    {
        scrollSpeed = FORCE_SCROLL_SPEED;
    }
    else if (elapsedTime > 80000 && elapsedTime <= 90000)
    {
        scrollSpeed = FIFTH_SCROLL_SPEED;
    }
}