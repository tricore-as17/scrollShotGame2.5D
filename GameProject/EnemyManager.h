#pragma once
#include<vector>
#include"DxLib.h"

using namespace std;

class Player;
class Map;
class EasyEnemy;
class BaseEnemy;

class EnemyManager
{
public:
	//定数群
	//初期座標
	static constexpr int EAZY1_FIRST_X = 1440;	
	static constexpr int EAZY1_FIRST_Y = 352;
	EnemyManager();		//コンストラクタ
	~EnemyManager();	//デストラクタ
	void Init();
	void Update(const Map&map,const Player&player);
	void Draw();
private:
	vector<EasyEnemy*> easyEnemy;	//一番弱い敵
};
