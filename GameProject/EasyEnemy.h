#pragma once
#include"DxLib.h"
#include"BaseEnemy.h"

//�N���X�̃v���g�^�C�v�錾
class Map;

/// <summary>
/// ��ԍŏ��ɓo�ꂷ��G���G���Ɉړ����Ă��邾��
/// </summary>
class EasyEnemy :public BaseEnemy
{
public:
	//�萔�Q
	static constexpr float SPEED = 2.5f;		//�X�s�[�h
	static constexpr float W = 64.0f;			//��
	static constexpr float H = 64.0f;			//����
	//���\�b�h
	EasyEnemy(int inFirstX);			//�R���X�g���N�^	
	~EasyEnemy();						//�f�X�g���N�^
	/// <summary>
	/// �Q�[���J�n���̏�����
	/// </summary>
	/// <param name="initPos">�������p�̍��W</param>
	void Init(VECTOR initPos);				
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="map">�}�b�v�̏�񂪓������C���X�^���X</param>
	/// <param name="playerVec">�v���C���[�̃x�N�g���������Ă���</param>
	void Update(const Map& map,const VECTOR& playerVec);	
	/// <summary>
	/// �`��
	/// </summary>
	void Draw();							

};
