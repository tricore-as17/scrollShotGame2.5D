#include"GameObject.h"
#include"Map.h"
#include"WorldSprite.h"
#include"Utility.h"
#pragma warning(disable:4996)

//静的変数
//ワールド座標での32ピクセルのサイズから1ピクセルを計算して出す
const float Map::ONE_PIXEL_SIZE = Map::CHIP_SIZE / 32;

//コンストラクタ
Map::Map()
{
	//マップタイルと配置のcsvファイルの読み込み

	tileGraph =LoadGraph("img/MapTile/Terrain (32x32).png");
	LoadMapChip("Map/stage1.csv");
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
/// <summary>
/// マップの位置の初期化
/// </summary>
void Map::Init()
{
	//ワールドスプライトの左上座標を設定
	chipLeftTopPos = VGet(0, mapYNum * CHIP_SIZE,0);
	for (int yIndex = 0; yIndex < mapYNum; yIndex++)
	{
		for (int xIndex = 0; xIndex < mapXNum; xIndex++)
		{
			auto sprite = new WorldSprite();
			//画像、チップのサイズ32,現在の配列データ
			sprite->Initialize(tileGraph, CHIP_PIXEL_SIZE, mapData[yIndex][xIndex]);
			//chipHalfOffsetはチップを左下にずらす
			VECTOR chipHalfOffset = VGet(-CHIP_SIZE * 0.5f, -CHIP_SIZE * 0.5f, 0);					// マップチップの半分サイズ左下にずらすオフセット
			VECTOR chipPos = VAdd(VGet(xIndex * CHIP_SIZE, (-yIndex - 1) * CHIP_SIZE, 0), chipHalfOffset);	// 真ん中ピボットなのでマップチップ半分サイズずらす+地面なので一つ下に
			chipPos = VAdd(chipPos, chipLeftTopPos);	//行の数だけ座標を上にもってくる
			sprite->SetTransform(chipPos, CHIP_SIZE);
			sprites.push_back(sprite);
		}
	}

}


/// <summary>
/// 座標移動などの更新処理
/// </summary>
/// <param name="playerVec"></param>
void Map::Update(const VECTOR& playerVec)
{

}

/// <summary>
/// ワールドスプライトを使った描画
/// </summary>
void Map::Draw()
{
	for (const auto& sprite : sprites)
	{
		sprite->Draw();
	}
}


/// <summary>
/// csvファイルからマップチップのデータを読み込み
/// </summary>
/// <param name="mapCSVFileName">csvファイルネーム</param>
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