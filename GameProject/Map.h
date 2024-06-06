#pragma once
#include<vector>
#include"DxLib.h"
#include"GameObject.h"


using namespace std;
//クラスのプロトタイプ宣言
class GameObject;
class WorldSprite;

/// <summary>
/// ゲームマップのクラスワールドスプライトを使用して作成
/// </summary>
class Map : public GameObject
{
public:
	Map();
	~Map();
	//ゲットセット
	const int getMapXNum() const{ return mapXNum; }					//横チップの数を返す
	const int getMapYNum() const { return mapYNum; }				//縦チップの数を返す
	int** getMapData()const{ return  mapData; }				//マップデータを返す
	const VECTOR GetChipLeftPos() const { return chipLeftTopPos; }	//マップの左上の座標

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
	static constexpr float CHIP_SIZE = 0.725f;		//ワールド座標での32ピクセルのサイズ
	static const float ONE_PIXEL_SIZE;				//ワールド座標での1ピクセルのサイズ
	static constexpr int TILE_DIV_W = 22;			//マップタイルの横方向分割数
	static constexpr int TILE_DIV_H = 11;			//マップタイルの縦方向分割数
    static constexpr int BLANK_CHIP_NUMBER = 48;    //マップタイルの中の空白になっている番号
    static const VECTOR CHIP_HALF_OFFSET;             //マップチップを左下に下げるためのベクトル


private:
	int tileGraph = -1;								//マップチップデータの画像
	int **mapData;									//マップデータ(CSVで管理)
	int mapXNum;									//横方向のマップチップの数
	int mapYNum;									//縦方向のマップチップの数
	VECTOR chipLeftTopPos;							//ワールドスプライトの左上座標
	vector<WorldSprite*> sprites;					//ワールドスプライトのインスタンス


};
