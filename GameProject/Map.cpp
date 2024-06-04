#include"GameObject.h"
#include"Map.h"
#include"Utility.h"
#pragma warning(disable:4996)
//コンストラクタ
Map::Map(VECTOR initPos)
{
	//マップタイルと配置のcsvファイルの読み込み

	//テスト用
	///////////////////////////////////////////////////
	LoadDivGraph("img/MapTile/Terrain (32x32).png", TILE_DIV_W * TILE_DIV_H, TILE_DIV_W, TILE_DIV_H
		, CHIP_SIZE, CHIP_SIZE, tileGraph);
	LoadMapChip("Map/stage1.csv");
	///////////////////////////////////////////////////
	pos = initPos;
}
//デストラクタ
Map::~Map()
{
	//マップデータのメモリ解放
	for (int i = 0; i < mapXNum; i++)
	{
		delete[] mapData[i];
	}
}
void Map::Init(){}



void Map::Update(const VECTOR& playerVec)
{
	if (pos.x - playerVec.x < 0)
	{
		//マップをスクロールさせる
		pos.x = pos.x - playerVec.x;

	}
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
	//ファイルを開く
	FILE* fp;
	fp = fopen(mapCSVFileName, "rt");
	//読み込めなかった場合の処理
	if (!fp)
	{
		DebugBreak();
	}
	//ファイルを１行分から読みし、１行のデータを数える
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
	//１データ 16bit最大値 "65535,"(6文字)として文字列入ってきたときの１行サイズ
	int bufferLen = mapXNum * 6 + 1;
	//一行分のバッファを確保
	char* buf = new char[bufferLen];
	char* ptmp = buf;
	//ファイルポインタを先頭に戻し行数を読む
	fseek(fp, 0, SEEK_SET);
	bool firstRow = true;
	while (fgets(buf, bufferLen - 1, fp) != NULL)
	{
		mapYNum++;
	}
	//２次元配列を動的確保する map[row][col]として動的確保する
	mapData = new int * [mapYNum];
	int ix, iy;
	for (iy = 0; iy < mapYNum; iy++)
	{
		mapData[iy] = new int[mapXNum];
	}
	//ファイルポインタを先頭に戻す
	fseek(fp, 0, SEEK_SET);
	//ファイルからデータを配列に移す
	char* readPoint;		//読み込み中のポイント
	char* firstPoint;		//最初の読み込みポイント
	for (iy = 0; iy < mapYNum; iy++)
	{
		//１行取り込み
		fgets(buf, bufferLen - 1, fp);
		readPoint = firstPoint = buf;
		for (ix = 0; ix < mapXNum; ix++)
		{
			//カンマまでreadPointの位置を進める
			while (',' != *readPoint && '\n' != *readPoint)
			{
				readPoint++;
			}
			//カンマをNULL文字に置き換え
			*readPoint = '\0';
			//この時点でfirstPoint -readPoint間で文字列が完成するので数値に変換
			mapData[iy][ix] = atoi(firstPoint);
			//次のデータ読み取り位置まで進める
			readPoint++;
			firstPoint = readPoint;
		}
	}
	fclose(fp);
	//バッファ開放
	delete[]buf;

}