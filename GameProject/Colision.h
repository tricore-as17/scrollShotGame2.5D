#pragma once
#include"DxLib.h"

//クラスのプロトタイプ宣言
class Map;
class Player;
class BaseEnemy;


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

