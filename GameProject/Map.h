#pragma once
#include<vector>
#include"DxLib.h"
//#include"GameObject.h"


using namespace std;
//�N���X�̃v���g�^�C�v�錾
class GameObject;
class WorldSprite;

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
	/// <summary>
	/// ���W�ړ��Ȃǂ̍X�V����
	/// </summary>
	/// <param name="playerVec"></param>
	void Update(const VECTOR& playerVec);
	/// <summary>
	/// ���[���h�X�v���C�g���g�����`��
	/// </summary>
	void Draw();
	/// <summary>
	/// csv�t�@�C������}�b�v�`�b�v�̃f�[�^��ǂݍ���
	/// </summary>
	/// <param name="mapCSVFileName">csv�t�@�C���l�[��</param>
	void LoadMapChip(const char* mapCSVFileName);		


	//�萔�Q
	static constexpr int CHIP_PIXEL_SIZE = 32;		//�}�b�v�`�b�v��̃T�C�Y
	static constexpr float CHIP_SIZE = 0.725f;		//���[���h���W�ł̃`�b�v�̃T�C�Y
	static constexpr int TILE_DIV_W = 22;		//�}�b�v�^�C���̉�����������
	static constexpr int TILE_DIV_H = 11;		//�}�b�v�^�C���̏c����������


private:
	int tileGraph = -1;								//�}�b�v�`�b�v�f�[�^�̉摜
	int **mapData;									//�}�b�v�f�[�^(CSV�ŊǗ�)
	int mapXNum;									//�������̃}�b�v�`�b�v�̐�
	int mapYNum;									//�c�����̃}�b�v�`�b�v�̐�
	vector<WorldSprite*> sprites;					//���[���h�X�v���C�g�̃C���X�^���X


};
