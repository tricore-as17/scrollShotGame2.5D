#pragma once
#include"DxLib.h"
#include"GameObject.h"

/// <summary>
/// �G�l�~�[�̋��ʂ��镔�����܂Ƃ߂����N���X
/// </summary>
class BaseEnemy:public GameObject
{
public:
	//�R���X�g���N�^�f�X�g���N�^
	BaseEnemy();
	virtual ~BaseEnemy();
	/// <summary>
	/// �G�l�~�[�̋��ʂ���X�N���[������(�}�b�v�̃X�N���[���ɍ��킹�ăG�l�~�[���ړ�)
	/// </summary>
	virtual void ScrollProcess();
	//�Q�b�^�[�Z�b�^�[
	virtual VECTOR GetPos()const { return pos; }				//���W�̎擾
	virtual void SetPos(const VECTOR inPos) { pos = inPos; }	//���W��ݒ�
	virtual float GetW()const { return w; }						//���̎擾
	virtual float GetH()const { return h; }						//�����̎擾
	virtual float GetFallSpeed()const { return fallSpeed; }		//�������x�̎擾
	virtual void SetFallSpeed(const float inFallSpeed) { fallSpeed = inFallSpeed; }	//�������x�̐ݒ�
	virtual bool GetIsGround()const { return isGround; }		//�ڒn����̎擾
	virtual void SetIsGround(const bool inIsGroound) { isGround = inIsGroound; }	//�ڒn����̐ݒ�
	virtual bool GetIsHitTop()const { return isHitTop; }		//���㔻��̎擾
	virtual void SetIsHitTop(const bool inIsHitTop) { isHitTop = inIsHitTop; }	//���㔻��̐ݒ�



protected:
	int** graph;		//�摜
	bool moveStartFlag;	//�ړ����J�n������t���O
	bool isGround;		//�ڒn���Ă��邩
	bool isHitTop;		//�V��ɂԂ����Ă��邩
	int firstX;			//����X���W


};

