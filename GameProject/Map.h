#pragma once
#include"DxLib.h"
//#include"GameObject.h"

class GameObject;


class Map : public GameObject
{
public:
	Map(VECTOR initPos);
	~Map();
	//�Q�b�g�Z�b�g
	int getMapXNum() const{ return mapXNum; }		//���`�b�v�̐���Ԃ�
	int getMapYNum() const { return mapYNum; }		//�c�`�b�v�̐���Ԃ�
	int** getMapData() const{ return mapData; }		//�}�b�v�f�[�^��Ԃ�
	VECTOR getMapPos() const{ return pos; }			//���W��Ԃ�

	void Init();
	void Update(const VECTOR& playerVec);
	void Draw();

	void LoadMapChip(const char* mapCSVFileName);		//�}�b�v�`�b�v�̓ǂݍ��݊֐�

	//�萔�Q
	static constexpr int CHIP_SIZE = 32;		//�}�b�v�`�b�v��̃T�C�Y
	static constexpr int TILE_DIV_W = 22;		//�}�b�v�^�C���̉�����������
	static constexpr int TILE_DIV_H = 11;		//�}�b�v�^�C���̏c����������


private:
	int tileGraph[TILE_DIV_W * TILE_DIV_H];			//�}�b�v�`�b�v�摜
	int **mapData;										//�}�b�v�f�[�^(CSV�ŊǗ�)
	int mapXNum;									//�������̃}�b�v�`�b�v�̐�
	int mapYNum;									//�c�����̃}�b�v�`�b�v�̐�


};
