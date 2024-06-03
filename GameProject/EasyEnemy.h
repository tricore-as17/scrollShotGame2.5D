#pragma once
#include"DxLib.h"
#include"BaseEnemy.h"

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
	EasyEnemy(int inFirstX);//�R���X�g���N�^	
	~EasyEnemy();			//�f�X�g���N�^
	void Init(VECTOR initPos);				//������
	void Update(const Map& map,const VECTOR& playerVec);	//�X�V
	void Draw();							//�`��

};
