#pragma once
#include"DxLib.h"

//�N���X�̃v���g�^�C�v�錾
class Map;
class Player;
class BaseEnemy;


/// <summary>
/// �v���C���[�̓����蔻�胁�\�b�h���܂Ƃ߂��N���X
/// </summary>
class PlayerColision
{
public:
	/// <summary>
	/// �v���C���[�ƃ}�b�v�̓����蔻����Ƃ��ē�����Ȃ��ʒu�܂ŏC��
	/// </summary>
	/// <param name="player">�v���C���[�̃C���X�^���X</param>
	/// <param name="map">�}�b�v�̃C���X�^���X</param>
	/// <param name="velocity">����̃��[�v�œ��͂��ꂽ�v���C���[�x�N�g���̒l</param>
	/// <returns>�C�������x�N�g��</returns>
	static VECTOR CheckPlayerHitWithMap(Player& player, const Map& map, const VECTOR& velocity);
	/// <summary>
	/// �v���C���[�ƃ}�b�v�������������̃`�F�b�N
	/// </summary>
	/// <param name="player">�v���C���[</param>
	/// <param name="futurePos">�ړ�����v�Z������̍��W</param>
	/// <param name="mapData">�ǂ�ȃ}�b�v�`�b�v��</param>
	/// <returns>�����������̃t���O</returns>
	static bool IsHitPlayerWithMapChip(const Player& player, const  VECTOR& futurePos,int mapData,VECTOR mapChipPos);
	/// <summary>
	/// �ڒn�����ꍇ�̏���
	/// </summary>
	/// <param name="player">�v���C���[</param>
	/// <param name="map">�}�b�v</param>
	static void CheckIsGround(Player& player, const  Map& map);
	/// <summary>
	/// �V��ɓ������Ă����ꍇ�̏���
	/// </summary>
	/// <param name="player">�v���C���[</param>
	/// <param name="map">�}�b�v</param>
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

