#pragma once
#include<vector>
#include"DxLib.h"
#include"GameObject.h"

const int PLAYER_STATE_NUM = 4;				//�v���C���[�̏�Ԃ̐�



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
	static constexpr float PLAYER_W = 0.725f;			//�v���C���[���T�C�Y
	static constexpr float PLAYER_H = 2.175f;			//�v���C���[�̏c�T�C�Y
	static constexpr float JUMP_POWER = 0.25f;  //�L�����̃W�����v��
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
	VECTOR velocity;					//�ړ���
	VECTOR keepVelocity;				//�v���C���[�̈ړ��ʂ̕ۑ��p

	bool hitFlag;
	bool isGround;						//�ڒn����
	bool isHitTop;						//�V��ɓ������Ă��邩�̔���

	//�ÓI�萔
	static constexpr float SCALE = 0.01f;	//�v���C���[�̑傫��
	static const float SPEED;				//�v���C���[�̑��x


	


};


