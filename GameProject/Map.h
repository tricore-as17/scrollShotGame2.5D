#pragma once
#include"DxLib.h"
//#include"GameObject.h"

class GameObject;


class Map : public GameObject
{
public:
	Map(VECTOR initPos);
	~Map();
	//ゲットセット
	int getMapXNum() const{ return mapXNum; }		//横チップの数を返す
	int getMapYNum() const { return mapYNum; }		//縦チップの数を返す
	int** getMapData() const{ return mapData; }		//マップデータを返す
	VECTOR getMapPos() const{ return pos; }			//座標を返す

	void Init();
	void Update(const VECTOR& playerVec);
	void Draw();

	void LoadMapChip(const char* mapCSVFileName);		//マップチップの読み込み関数

	//定数群
	static constexpr int CHIP_SIZE = 32;		//マップチップ一つのサイズ
	static constexpr int TILE_DIV_W = 22;		//マップタイルの横方向分割数
	static constexpr int TILE_DIV_H = 11;		//マップタイルの縦方向分割数


private:
	int tileGraph[TILE_DIV_W * TILE_DIV_H];			//マップチップ画像
	int **mapData;										//マップデータ(CSVで管理)
	int mapXNum;									//横方向のマップチップの数
	int mapYNum;									//縦方向のマップチップの数


};
