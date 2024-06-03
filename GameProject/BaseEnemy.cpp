#include"BaseEnemy.h"
#include"Utility.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
BaseEnemy::BaseEnemy() :moveStartFlag(false) {}	//�t���O�̏�����

/// <summary>
/// �f�X�g���N�^
/// </summary>
BaseEnemy::~BaseEnemy() {/*�����Ȃ�*/ }

/// <summary>
/// �G�l�~�[�̋��ʂ���X�N���[������(�}�b�v�̃X�N���[���ɍ��킹�ăG�l�~�[���ړ�)
/// </summary>
/// <param name="playerVec">�v���C���[�̓��͂����x�N�g��</param>
void BaseEnemy::ScrollProcess(const VECTOR& playerVec)
{
	if (pos.x - playerVec.x < firstX)
	{
		//�}�b�v���X�N���[��������
		pos.x = pos.x - playerVec.x;

	}
	//�G�l�~�[����ʓ��ɓ�������X�N���[���t���O�𗧂Ă�
	if (pos.x <= SCREEN_W)
	{
		moveStartFlag = true;
	}
}
