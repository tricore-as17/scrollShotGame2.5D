#include"EasyEnemy.h"
#include"Colision.h"
#include"Map.h"
#include"Utility.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
EasyEnemy::EasyEnemy(int inFirstX)
{
	firstX = inFirstX;
	//���W�̏�����
	pos = VGet(0, 0, 0);
	//���ƍ����̎擾
	w = W;
	h = H;
	//�摜�̓ǂݍ���
	//LoadDivGraph();
	

}
/// <summary>
/// �f�X�g���N�^
/// </summary>
EasyEnemy::~EasyEnemy()
{
	//�����Ȃ�
}

/// <summary>
/// ������
/// </summary>
/// <param name="initPos">�������p�̍��W</param>
void EasyEnemy::Init(VECTOR initPos)
{
	//���W�̑��
	pos = initPos;
	//�ړ����J�n����t���O�̏�����
	moveStartFlag = false;
	//�摜�̓ǂݍ���
	//LoadDivGraph()
	
}

/// <summary>
/// �X�V����
/// </summary>
void EasyEnemy::Update(const Map& map,const VECTOR& playerVec)
{
	//�G�l�~�[���ʂ̃X�N���[������
	ScrollProcess();
	//�ړ��J�n�t���O�������Ă�����ړ�������
	if (moveStartFlag)
	{
		dir = VAdd(dir, VGet(-1, 0, 0));
	}
	// ���K��
	if (VSquareSize(dir) > 0)		//dir�̃T�C�Y��2��ɂ��ĕԂ�(���ɂ��邱�Ƃ�dir�ɒl�������Ă����if�ɓ���
	{
		dir = VNorm(dir);			//�e�����̃T�C�Y���P�ɂ���
	}

	//�ړ��ʂ��o��
	VECTOR velocity = VScale(dir, SPEED);

	//����������
	fallSpeed += Utility::GRAVITY;

	// HACK: ��ɐݒ蔻������邱�Ƃ�fallSpeed�C���{�ڒn�t���O�X�V
	EnemyColision::CheckIsGround(*this, map);
	EnemyColision::CheckIsTopHit(*this, map);

	// �������x���ړ��ʂɉ�����
	VECTOR fallVelocity = VGet(0, fallSpeed, 0);	// �������x�N�g���ɁBy���W�����ω����Ȃ��̂ōŌ�Ƀx�N�g���ɂ���
	velocity = VAdd(velocity, fallVelocity);

	// �����蔻������āA�ǂɂ߂荞�܂Ȃ��悤��velocity�𑀍삷��
	velocity = EnemyColision::CheckEnemyHitWithMap(*this, map, velocity);

	// �ړ�
	pos = VAdd(pos, velocity);
}

/// <summary>
/// �`��
/// </summary>
void EasyEnemy::Draw()
{
	//�X�N���[�����ɓ�������`�悷��
	//if (pos.x <= SCREEN_W + w)
	//{
		//�e�X�g�p�̕`��
		DrawBox(pos.x - w*0.5, pos.y - h*0.5, pos.x + w*0.5, pos.y + h*0.5, WHITE, TRUE);

	//}
}