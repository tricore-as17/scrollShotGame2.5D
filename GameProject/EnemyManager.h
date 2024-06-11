#pragma once
#include<vector>
#include<list>
#include"DxLib.h"

using namespace std;

//クラスのプロトタイプ宣言
class Player;
class Map;
class EasyEnemy;
class BaseEnemy;

/// <summary>
/// エネミーの処理やインスタンスをまとめたもの
/// </summary>
class EnemyManager
{
public:
	//定数群
	//初期座標(１マップチップ0.725の値で計算)
	static constexpr float EAZY1_FIRST_X = 32.625f;	
	static constexpr int EAZY1_FIRST_Y = 9.425f;
    //getter,setter
    vector<BaseEnemy*> GetEasyEnemy()const { return easyEnemy; }
	EnemyManager();		//コンストラクタ
	~EnemyManager();	//デストラクタ
	/// <summary>
	/// ゲーム開始ごとの初期化
	/// </summary>
	void Init();
    /// <summary>
    /// エネミー全体の更新処理
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="cameraPos">カメラの座標</param>
	void Update(const Map&map, const VECTOR& cameraPos, const ShotManager& shotManager);
	/// <summary>
	/// エネミーの描画
	/// </summary>
	void Draw();
    void DeleteEnemy();
private:
	vector<BaseEnemy*> easyEnemy;	//一番弱い敵
};
