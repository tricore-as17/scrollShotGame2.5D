#pragma once
#include<vector>
#include"DxLib.h"
//#include"GameObject.h"


using namespace std;
//クラスのプロトタイプ宣言
class GameObject;
class WorldSprite;

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
	/// <summary>
	/// 座標移動などの更新処理
	/// </summary>
	/// <param name="playerVec"></param>
	void Update(const VECTOR& playerVec);
	/// <summary>
	/// ワールドスプライトを使った描画
	/// </summary>
	void Draw();
	/// <summary>
	/// csvファイルからマップチップのデータを読み込み
	/// </summary>
	/// <param name="mapCSVFileName">csvファイルネーム</param>
	void LoadMapChip(const char* mapCSVFileName);		


	//定数群
	static constexpr int CHIP_PIXEL_SIZE = 32;		//マップチップ一つのサイズ
	static constexpr float CHIP_SIZE = 0.725f;		//ワールド座標でのチップのサイズ
	static constexpr int TILE_DIV_W = 22;		//マップタイルの横方向分割数
	static constexpr int TILE_DIV_H = 11;		//マップタイルの縦方向分割数


private:
	int tileGraph = -1;								//マップチップデータの画像
	int **mapData;									//マップデータ(CSVで管理)
	int mapXNum;									//横方向のマップチップの数
	int mapYNum;									//縦方向のマップチップの数
	vector<WorldSprite*> sprites;					//ワールドスプライトのインスタンス


};
