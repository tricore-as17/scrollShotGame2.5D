#pragma once
#include"DxLib.h"

class Player;

class Effect
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	Effect(const char* fileName);
	virtual ~Effect();
	//�Q�b�^�[
	bool GetPlayFlag()const { return playFlag; }	//�Đ������̃t���O��Ԃ�
	static int Setting();
	//void Init();
	//bool Update(Player* player, const VECTOR playerPos);
	//bool ClearUpdate(VECTOR inPos);
	//bool ClearUpdate(Player* player, const VECTOR playerPos);
	//void Draw();
private:
	int handle;		//�G�t�F�N�g�̃n���h��
	int playHandle;	//�v���C���̃G�t�F�N�g�n���h��
	int playTime;			//�Đ�����
	bool playFlag;			//�Đ������m�F����t���O
	bool playEndFlag;		//�Đ��I���̃t���O
	VECTOR pos;				//���W
};
