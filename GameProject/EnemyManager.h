#pragma once
#include<vector>
#include<list>
#include"DxLib.h"

using namespace std;

//クラスのプロトタイプ宣言
class Player;
class Map;
class EasyEnemy;
class LeftShotEnemy;
class BaseEnemy;



/// <summary>
/// エネミーの処理やインスタンスをまとめたもの
/// </summary>
class EnemyManager
{
public:
	//定数群
    static constexpr int EASY_NUM = 2;              //一番弱い敵の数
    static constexpr int LEFT_SHOT_ENEMY_NUM = 2;   //横に撃つ敵の数
	//初期座標(１マップチップ0.725の値で計算)
	static constexpr float EASY1_FIRST_X = 32.625f;	
	static constexpr float EASY1_FIRST_Y = 9.425f;
    static constexpr float EASY2_FIRST_X = 36.975f;
    static constexpr float EASY2_FIRST_Y = 5.075f;
    static constexpr float LEFT1_FIRST_X = 52.2f;
    static constexpr float LEFT1_FIRST_Y = 7.25f;
    static constexpr float LEFT2_FIRST_X = 55.1f;
    static constexpr float LEFT2_FIRST_Y = 10.15f;
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
	void Update(const Map&map, const VECTOR& cameraPos, ShotManager& shotManager);
	/// <summary>
	/// エネミーの描画
	/// </summary>
	void Draw();
    /// <summary>
    /// 体力が0になったらインスタンスを削除する
    /// </summary>
    void DeleteEnemy(vector<BaseEnemy*>&enemy);
    /// <summary>
    /// エネミーインスタンスのメモリ解放
    /// </summary>
    /// <param name="enemy">エネミーのインスタンス</param>
    void ReleaseMemory(vector<BaseEnemy*>& enemy);
    /// <summary>
    /// for文を毎回呼ばないでいいように用意したエネミーの種類毎のアップデート
    /// </summary>
    /// <param name="enemy">エネミーの種類毎のvector</param>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="cameraPos">カメラの座標</param>
    /// <param name="shotManager">ショットの管理クラス</param>
    void SingleUpdate(vector<BaseEnemy*> enemy, const Map& map, const VECTOR& cameraPos, ShotManager& shotManager);
    /// <summary>
    /// for文を毎回呼ばないでいいように用意したエネミーの種類毎の描画
    /// </summary>
    /// <param name="enemy">エネミーの種類毎のvector</param>
    void SingleDraw(vector<BaseEnemy*>enemy);
private:
	vector<BaseEnemy*> easyEnemy;	    //一番弱い敵
    vector<BaseEnemy*> leftShotEnemy;   //左にショットを撃ち続ける敵
};
