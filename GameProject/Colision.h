#pragma once
#include"DxLib.h"

class Map;
class Player;
class BaseEnemy;

//�v���C���[�̓����蔻��
class PlayerColision
{
public:
	//�v���C���[���ǂɂ߂荞�܂Ȃ��ʒu�ɂ��邽�߂̍��W�C���p
	static VECTOR CheckPlayerHitWithMap(Player& player, const Map& map, const VECTOR& velocity);
	//�����������̃`�F�b�N
	static bool IsHitPlayerWithMapChip(const Player& player, const  VECTOR& futurePos,int mapData,VECTOR mapChipPos);
	//�ڒn����̃`�F�b�N
	static void CheckIsGround(Player& player, const  Map& map);
	//���㔻��̃`�F�b�N
	static void CheckIsTopHit(Player& player, const  Map& map);

};

//�G�l�~�[�̓����蔻��
class EnemyColision
{
public:
	static VECTOR CheckEnemyHitWithMap(BaseEnemy& enemy, const Map& map, const VECTOR& velocity);
	//�����������̃`�F�b�N
	static bool IsHitEnemyWithMapChip(const BaseEnemy& enemy, const  VECTOR& futurePos, int mapData, VECTOR mapChipPos);
	//�ڒn����̃`�F�b�N
	static void CheckIsGround(BaseEnemy& enemy, const  Map& map);
	//���㔻��̃`�F�b�N
	static void CheckIsTopHit(BaseEnemy&enemy, const  Map& map);
	//�v���C���[�Ƃ̓����蔻��
	static bool IsHitPlayerWithEnemy(const BaseEnemy& enemy, const Player& player, const VECTOR& futurePos);
};

