#pragma once
#include<vector>
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
	EnemyManager();		//コンストラクタ
	~EnemyManager();	//デストラクタ
	/// <summary>
	/// ゲーム開始ごとの初期化
	/// </summary>
	void Init();
	/// <summary>
	/// エネミーの更新処理をまとめたもの
	/// </summary>
	/// <param name="map">マップのインスタンス</param>
	/// <param name="player">プレイヤーのインスタンス</param>
	void Update(const Map&map,const Player&player);
	void Draw();
private:
	vector<EasyEnemy*> easyEnemy;	//一番弱い敵
};
