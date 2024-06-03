#pragma once
#include"DxLib.h"

class Map;
class Player;
class BaseEnemy;

//プレイヤーの当たり判定
class PlayerColision
{
public:
	//プレイヤーが壁にめり込まない位置にするための座標修正用
	static VECTOR CheckPlayerHitWithMap(Player& player, const Map& map, const VECTOR& velocity);
	//当たったかのチェック
	static bool IsHitPlayerWithMapChip(const Player& player, const  VECTOR& futurePos,int mapData,VECTOR mapChipPos);
	//接地判定のチェック
	static void CheckIsGround(Player& player, const  Map& map);
	//頭上判定のチェック
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

