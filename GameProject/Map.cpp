#include"GameObject.h"
#include"Map.h"
#include"Utility.h"
#pragma warning(disable:4996)
//�R���X�g���N�^
Map::Map(VECTOR initPos)
{
	//�}�b�v�^�C���Ɣz�u��csv�t�@�C���̓ǂݍ���

	//�e�X�g�p
	///////////////////////////////////////////////////
	LoadDivGraph("img/MapTile/Terrain (32x32).png", TILE_DIV_W * TILE_DIV_H, TILE_DIV_W, TILE_DIV_H
		, CHIP_SIZE, CHIP_SIZE, tileGraph);
	LoadMapChip("Map/stage1.csv");
	///////////////////////////////////////////////////
	pos = initPos;
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
void Map::Init(){}



void Map::Update(const VECTOR& playerVec)
{
	//FIXME
	//�}�b�v���X�N���[������ۂɎg�p�����X�N���[���ۂɎg�p����̂ł����g��Ȃ�
	//if (pos.x - playerVec.x < 0)
	//{
	//	//�}�b�v���X�N���[��������
	//	pos.x = pos.x - playerVec.x;

	//}
}

void Map::Draw()
{
	for (int  y= 0; y < mapYNum; y++)
	{
		for (int x = 0; x < mapXNum; x++)
		{
				if (mapData[y][x] == -1)
				{
					continue;
				}
				int graphHandle = tileGraph[mapData[y][x]];
				DrawGraph((x * CHIP_SIZE) + pos.x, y * CHIP_SIZE, graphHandle, TRUE);


		}
	}
}



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