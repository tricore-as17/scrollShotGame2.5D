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
	//�萔�Q
	//�������W
	static constexpr int EAZY1_FIRST_X = 1440;	
	static constexpr int EAZY1_FIRST_Y = 352;
	EnemyManager();		//�R���X�g���N�^
	~EnemyManager();	//�f�X�g���N�^
	void Init();
	void Update(const Map&map,const Player&player);
	void Draw();
private:
	vector<EasyEnemy*> easyEnemy;	//��Ԏア�G
};
