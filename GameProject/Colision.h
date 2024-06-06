#pragma once
#include"DxLib.h"

//クラスのプロトタイプ宣言
class Map;
class Player;
class BaseEnemy;
class Shot;


/// <summary>
/// プレイヤーの当たり判定メソッドをまとめたクラス
/// </summary>
class PlayerColision
{
public:
	/// <summary>
	/// プレイヤーとマップの当たり判定をとって当たらない位置まで修正
	/// </summary>
	/// <param name="player">プレイヤーのインスタンス</param>
	/// <param name="map">マップのインスタンス</param>
	/// <param name="velocity">今回のループで入力されたプレイヤーベクトルの値</param>
	/// <returns>修正したベクトル</returns>
	static VECTOR CheckPlayerHitWithMap(Player& player, const Map& map, const VECTOR& velocity);
	/// <summary>
	/// プレイヤーとマップが当たったかのチェック
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="futurePos">移動後を計算した後の座標</param>
	/// <param name="mapData">どんなマップチップか</param>
	/// <returns>当たったかのフラグ</returns>
	static bool IsHitPlayerWithMapChip(const Player& player, const  VECTOR& futurePos,int mapData,VECTOR mapChipPos);
	/// <summary>
	/// 接地いた場合の処理
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="map">マップ</param>
	static void CheckIsGround(Player& player, const  Map& map);
	/// <summary>
	/// 天井に当たっていた場合の処理
	/// </summary>
	/// <param name="player">プレイヤー</param>
	/// <param name="map">マップ</param>
	static void CheckIsTopHit(Player& player, const  Map& map);

};

//エネミーの当たり判定
class EnemyColision
{
public:
	static VECTOR CheckEnemyHitWithMap(BaseEnemy& enemy, const Map& map, const VECTOR& velocity);
	//当たったかのチェック
	static bool IsHitEnemyWithMapChip(const BaseEnemy& enemy, const  VECTOR& futurePos, int mapData, VECTOR mapChipPos);
	//接地判定のチェック
	static void CheckIsGround(BaseEnemy& enemy, const  Map& map);
	//頭上判定のチェック
	static void CheckIsTopHit(BaseEnemy&enemy, const  Map& map);
	//プレイヤーとの当たり判定
	static bool IsHitPlayerWithEnemy(const BaseEnemy& enemy, const Player& player, const VECTOR& futurePos);
};

/// <summary>
/// 弾の当たり判定
/// </summary>
class ShotColision
{
    /// <summary>
/// 弾とエネミーの当たり判定
/// </summary>
/// <param name="shot">弾のインスタンス</param>
/// <param name="enemy">エネミーのインスタンス</param>
/// <returns>ヒット判定</returns>
    static bool IsHitShotWithEnemy(const Shot& shot, const BaseEnemy& enemy);
};

/// <summary>
/// 当たり判定をまとめたもの
/// </summary>
class Colision
{
    /// <summary>
    /// 矩形同士の当たり判定
    /// </summary>
    /// <param name="pos1">矩形１の座標</param>
    /// <param name="w1">矩形１の幅</param>
    /// <param name="h1">矩形１の高さ</param>
    /// <param name="pos2">矩形２の座標</param>
    /// <param name="w2">矩形２の幅</param>
    /// <param name="h2">矩形２の高さ</param>
    /// <returns>当たったかの判定結果</returns>
    static bool IsHitRectangles(const VECTOR& pos1, float w1, float h1, const VECTOR& pos2, float w2, float h2);


    /// <summary>
    /// マップとプレイヤーやエネミーの当たり判定
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="velocity">プレイヤーなどのベクトル</param>
    /// <param name="pos">動かす前の座標</param>
    /// <returns>調節したベクトル</returns>
    static VECTOR CheckHitMapAdjustmentVector(const Map& map, VECTOR& velocity, const VECTOR& pos,const float w, const float h);

    /// <summary>
    /// オブジェクトが接地しているかの判定
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="objectPos">調べるオブジェクトの座標</param>
    /// <param name="objectW">オブジェクトの幅</param>
    /// <param name="objectH">オブジェクトの高さ</param>
    /// <returns>接地しているか</returns>
    static bool CheckIsGround(const Map& map, const VECTOR& objectPos, const float objectW, const float objectH);


};


