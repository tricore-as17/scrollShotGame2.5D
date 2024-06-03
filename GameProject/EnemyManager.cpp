#include"EasyEnemy.h"
#include"EnemyManager.h"
#include"Map.h"
#include"Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
EnemyManager::EnemyManager()
{
	//��Ԏア�G���C���X�^���X��
	easyEnemy.emplace_back(new EasyEnemy(EAZY1_FIRST_X));	//1�̖�
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyManager::~EnemyManager()
{
	//�������̊J��
	easyEnemy.clear();
}

/// <summary>
/// �Q�[���J�n���̏�����
/// </summary>
void EnemyManager::Init()
{
	easyEnemy[0]->Init(VGet(EAZY1_FIRST_X, EAZY1_FIRST_Y, 0));
}
/// <summary>
/// �X�V����
/// </summary>
/// <param name="map">�}�b�v�̃C���X�^���X</param>
/// <param name="player">�v���C���[�̃C���X�^���X</param>
void EnemyManager::Update(const Map& map, const Player& player)
{
	//�v���C���[�̈ړ������̎擾
	VECTOR playerVec = player.GetKeepVelocity();
	easyEnemy[0]->Update(map, playerVec);
}
/// <summary>
/// �`��
/// </summary>
void EnemyManager::Draw()
{
	easyEnemy[0]->Draw();
}