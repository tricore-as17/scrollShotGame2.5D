#pragma once
#include<vector>
#include<list>
#include<string>
#include"DxLib.h"

using namespace std;

//クラスのプロトタイプ宣言
class Player;
class Map;
class EasyEnemy;
class LeftShotEnemy;
class BaseEnemy;
struct EnemyInformation;



/// <summary>
/// エネミーの処理やインスタンスをまとめたもの
/// </summary>
class EnemyManager
{
public:
    /// <summary>
    /// エネミーの種類
    /// </summary>
    enum ENEMY_TYPE
    {
        EASY = 0,
        ONE_WAY_SHOT = 1
    };
    //getter,setter
    vector<BaseEnemy*> GetEnemy()const { return enemy; }
	EnemyManager();		//コンストラクタ
	~EnemyManager();	//デストラクタ
    /// <summary>
    /// エネミー全体の更新処理
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="cameraPosition">カメラの座標</param>
	void Update(const Map&map, const VECTOR& cameraPosition, ShotManager& shotManager);
	/// <summary>
	/// エネミーの描画
	/// </summary>
	void Draw();

    /// <summary>
    /// CSVファイルからエネミーのデータを読み込む
    /// </summary>
    /// <param name="fileName">ファイル名</param>
    vector<EnemyInformation*> LoadEnemyInformation(const string& fileName);

private:
    vector<BaseEnemy*>        enemy;            //敵のインスタンスをまとめたもの
};
