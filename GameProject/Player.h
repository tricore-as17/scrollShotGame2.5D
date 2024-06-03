#pragma once
#include<vector>
#include"DxLib.h"
#include"GameObject.h"

const int PLAYER_X = 150;					//�v���C���[��X���W(�����Ȃ��̂Œ萔)
const int PLAYER_STATE_NUM = 4;				//�v���C���[�̏�Ԃ̐�
const int PLAYER_CHIP_SIZE = 64;			//�v���C���[�`�b�v�̃T�C�Y
const int PLAYER_CHIP_DIV_YNUM = 1;			//�v���C���[�`�b�v�̏c�����̕�����
const int STATE_RUN_DIV_NUM = 12;			//�����Ă��鎞�̕�����
const int STATE_JUMP_DIV_NUM = 1;			//�W�����v�̎��̕�����
const int STATE_FALL_DIV_NUM = 1;			//�������̎��̕�����
const int STATE_HIT_DIV_NUM = 7;




class Map;
class Gimmick;


class Player:public GameObject
{
public:
	Player();
	~Player();
	//��{���\�b�h
	void Init();								//������
	void Update(bool keyStop,const Map& map);	//�X�V
	void Draw();								//�`��
	//�Q�b�^�[�Z�b�^�[
	VECTOR GetPos()const { return pos; }			//���W��Ԃ�
	VECTOR GetDrawPos()const { return drawPos; }	//draw���W��Ԃ�
	VECTOR GetKeepVelocity()const { return keepVelocity; }
	bool GetIsHitTop()const { return isHitTop; }	//�V��֓������Ă��邩�̃t���O��Ԃ�
	void SetIsHitTop(const bool inIsHitTop) { isHitTop = inIsHitTop; }		//�V��֓������Ă��邩�̃Z�b�g
	void SetFallSpeed(const float inFallSpeed) { fallSpeed = inFallSpeed; }	//�����X�s�[�h�̃Z�b�g
	void SetIsGround(const bool inIsGround) { isGround = inIsGround; }		//�ڒn����̐ݒ�
	void SetPos(const VECTOR inPos) { pos = inPos; }						//���W�̃Z�b�g
	
	//�A�j���[�V�����̏�Ԃ̒萔
	static enum ANIME_STATE
	{
		//1����J�n
		IDLE = 1, MAGIC, RUN
	};
	//�萔�Q
	static constexpr int FIRST_X = 100;			//����X���W
	static constexpr int FIRST_Y = 450;			//����Y���W
	static constexpr int PLAYER_W = 32;			//�v���C���[���T�C�Y
	static constexpr int PLAYER_H = 96;			//�v���C���[�̏c�T�C�Y
	static constexpr float JUMP_POWER = 15.0f;  //�L�����̃W�����v��
	static constexpr float SPEED = 5.0f;		//�L�����̈ړ��X�s�[�h
	static constexpr int ANIME_STATE_SUM = 4;	//���v�A�j���[�V�����̐�

private:
	//�A�j���[�V�����t���O��S�ă��Z�b�g
	void ResetAnimeFlag();
	//�A�j���V�����̃Z�b�g
	void AnimeSet(int setState);
	int modelHandle;					//�L�����̃��f���n���h��
	int attachIndex;					//�A�j���[�V�����A�^�b�`�p�C���f�b�N�X
	float totalAnimeTime;				//�A�j���[�V�����̃g�[�^���Đ�����
	float playTime;						//�A�j���[�V�����̌��݂̍Đ�����
	bool animeState[ANIME_STATE_SUM];	//�A�j���[�V�����̏��
	VECTOR pos3D;						//3D���f���̍��W
	VECTOR drawPos;
	VECTOR keepVelocity;				//�v���C���[�̈ړ��ʂ̕ۑ��p

	bool hitFlag;
	bool isGround;						//�ڒn����
	bool isHitTop;						//�V��ɓ������Ă��邩�̔���


	


};


