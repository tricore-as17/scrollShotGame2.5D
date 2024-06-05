#include"GameObject.h"
#include"Map.h"
#include"WorldSprite.h"
#include"Utility.h"
#pragma warning(disable:4996)

//�ÓI�ϐ�
//���[���h���W�ł�32�s�N�Z���̃T�C�Y����1�s�N�Z�����v�Z���ďo��
const float Map::ONE_PIXEL_SIZE = Map::CHIP_SIZE / 32;

//�R���X�g���N�^
Map::Map()
{
	//�}�b�v�^�C���Ɣz�u��csv�t�@�C���̓ǂݍ���

	tileGraph =LoadGraph("img/MapTile/Terrain (32x32).png");
	LoadMapChip("Map/stage1.csv");
}
//�f�X�g���N�^
Map::~Map()
{
	//�}�b�v�f�[�^�̃��������
	for (int i = 0; i < mapXNum; i++)
	{
		delete[] mapData[i];
	}
}
/// <summary>
/// �}�b�v�̈ʒu�̏�����
/// </summary>
void Map::Init()
{
	//���[���h�X�v���C�g�̍�����W��ݒ�
	chipLeftTopPos = VGet(0, mapYNum * CHIP_SIZE,0);
	for (int yIndex = 0; yIndex < mapYNum; yIndex++)
	{
		for (int xIndex = 0; xIndex < mapXNum; xIndex++)
		{
			auto sprite = new WorldSprite();
			//�摜�A�`�b�v�̃T�C�Y32,���݂̔z��f�[�^
			sprite->Initialize(tileGraph, CHIP_PIXEL_SIZE, mapData[yIndex][xIndex]);
			//chipHalfOffset�̓`�b�v�������ɂ��炷
			VECTOR chipHalfOffset = VGet(-CHIP_SIZE * 0.5f, -CHIP_SIZE * 0.5f, 0);					// �}�b�v�`�b�v�̔����T�C�Y�����ɂ��炷�I�t�Z�b�g
			VECTOR chipPos = VAdd(VGet(xIndex * CHIP_SIZE, (-yIndex - 1) * CHIP_SIZE, 0), chipHalfOffset);	// �^�񒆃s�{�b�g�Ȃ̂Ń}�b�v�`�b�v�����T�C�Y���炷+�n�ʂȂ̂ň����
			chipPos = VAdd(chipPos, chipLeftTopPos);	//�s�̐��������W����ɂ����Ă���
			sprite->SetTransform(chipPos, CHIP_SIZE);
			sprites.push_back(sprite);
		}
	}

}


/// <summary>
/// ���W�ړ��Ȃǂ̍X�V����
/// </summary>
/// <param name="playerVec"></param>
void Map::Update(const VECTOR& playerVec)
{

}

/// <summary>
/// ���[���h�X�v���C�g���g�����`��
/// </summary>
void Map::Draw()
{
	for (const auto& sprite : sprites)
	{
		sprite->Draw();
	}
}


/// <summary>
/// csv�t�@�C������}�b�v�`�b�v�̃f�[�^��ǂݍ���
/// </summary>
/// <param name="mapCSVFileName">csv�t�@�C���l�[��</param>
void Map::LoadMapChip(const char* mapCSVFileName)
{
	mapData = NULL;
	mapXNum = 0;
	mapYNum = 0;
	//�t�@�C�����J��
	FILE* fp;
	fp = fopen(mapCSVFileName, "rt");
	//�ǂݍ��߂Ȃ������ꍇ�̏���
	if (!fp)
	{
		DebugBreak();
	}
	//�t�@�C�����P�s������ǂ݂��A�P�s�̃f�[�^�𐔂���
	char c = 0;
	while (c != '\n')
	{
		c = fgetc(fp);
		if (',' == c)
		{
			mapXNum++;
		}
	}
	mapXNum++;
	//�P�f�[�^ 16bit�ő�l "65535,"(6����)�Ƃ��ĕ���������Ă����Ƃ��̂P�s�T�C�Y
	int bufferLen = mapXNum * 6 + 1;
	//��s���̃o�b�t�@���m��
	char* buf = new char[bufferLen];
	char* ptmp = buf;
	//�t�@�C���|�C���^��擪�ɖ߂��s����ǂ�
	fseek(fp, 0, SEEK_SET);
	bool firstRow = true;
	while (fgets(buf, bufferLen - 1, fp) != NULL)
	{
		mapYNum++;
	}
	//�Q�����z��𓮓I�m�ۂ��� map[row][col]�Ƃ��ē��I�m�ۂ���
	mapData = new int * [mapYNum];
	int ix, iy;
	for (iy = 0; iy < mapYNum; iy++)
	{
		mapData[iy] = new int[mapXNum];
	}
	//�t�@�C���|�C���^��擪�ɖ߂�
	fseek(fp, 0, SEEK_SET);
	//�t�@�C������f�[�^��z��Ɉڂ�
	char* readPoint;		//�ǂݍ��ݒ��̃|�C���g
	char* firstPoint;		//�ŏ��̓ǂݍ��݃|�C���g
	for (iy = 0; iy < mapYNum; iy++)
	{
		//�P�s��荞��
		fgets(buf, bufferLen - 1, fp);
		readPoint = firstPoint = buf;
		for (ix = 0; ix < mapXNum; ix++)
		{
			//�J���}�܂�readPoint�̈ʒu��i�߂�
			while (',' != *readPoint && '\n' != *readPoint)
			{
				readPoint++;
			}
			//�J���}��NULL�����ɒu������
			*readPoint = '\0';
			//���̎��_��firstPoint -readPoint�Ԃŕ����񂪊�������̂Ő��l�ɕϊ�
			mapData[iy][ix] = atoi(firstPoint);
			//���̃f�[�^�ǂݎ��ʒu�܂Ői�߂�
			readPoint++;
			firstPoint = readPoint;
		}
	}
	fclose(fp);
	//�o�b�t�@�J��
	delete[]buf;

}