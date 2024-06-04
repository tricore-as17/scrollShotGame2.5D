#pragma once
#include<vector>
#include"DxLib.h"

using namespace std;

//�X�N���[���T�C�Y
const int SCREEN_W = 1280;
const int SCREEN_H = 800;

//�F
const int WHITE = GetColor(255, 255, 255);


const int AVERAGE_FLAME = 60;			//�J�E���g����t���[����
const int SETTING_FPS = 60;				//�ڕWFPS�l
const int FIRST_SCROLL_SPEED = -5;		//�ŏ��̃X�N���[���X�s�[�h
const int SECOND_SCROLL_SPEED = -6;		//���ڂ̃X�N���[���X�s�[�h
const int THIRD_SCROLL_SPEED = -7;		//�R��ڂ̃X�N���[���X�s�[�h
const int FORCE_SCROLL_SPEED = -8;		//4��ڂ̃X�N���[���X�s�[�h
const int FIFTH_SCROLL_SPEED = -9;		//5��ڂ̃X�N���[���X�s�[�h


// �Q�[���̏��.
enum STATE
{
	STATE_TITLE,		// �^�C�g��
	STATE_GAME,			// �Q�[����
	STATE_GAMECLEAR,	//�N���A
	STATE_GAMEOVER,		// �Q�[���I�[�o�[
};


class Utility
{
public:
	//�萔�Q
	static constexpr float GRAVITY = 0.5f;			//�d�͂̒l

	//�Q�b�^�[�Z�b�^�[
	//�o�ߎ��Ԃ̃Q�b�^�[
	int getElapsedTime()const { return elapsedTime; }
	int getEndElapsedTime()const { return endElapsedTime; }
	void setEndElapsedTime(int inEndElapsedTime) { endElapsedTime = inEndElapsedTime; }
	bool GetLoadFlag() const { return loadFlag; }
	void SetLoadFlag(const bool inLoadFlag) { loadFlag = inLoadFlag; }
	//�Q�[���̃X�e�[�^�X�̂������[�������[
	int getGameState() { return gameState; }
	int getScrollSpeed() { return scrollSpeed; }
	void setGameState(int inputState) { gameState = inputState; }
	int GetNowScreenX()const { return nowScreenX; }		//�X�N���[��X���W�̎擾
	int GetNowScreenY()const { return nowScreenY; }		//�X�N���[��Y���W�̎擾
	int SetNowScreenX(int inX) { nowScreenX = inX; }	//�X�N���[��X���W�̍X�V
	int SetNowScreenY(int inY) { nowScreenY = inY; }	//�X�N���[��Y���W�̍X�V
	//�t���[�����[�g�֘A�̏�����
	static void FpsInit();
	//1�t���[���ڂ�60�t���[���ڂōX�V
	static void FpsUpdate();
	//�v�Z�����l�Ńt���[�����[�g�𒲐�
	static void FpsControll();
	//�Q�[���J�n�����Ƃ̏���������
	void StartInit();
	/// <summary>
	/// �z��ւ̃|�C���^��������ăx�N�^���쐬����
	/// </summary>
	/// <param name="targetData">�x�N�^���ɓ����z��̃f�[�^</param>
	/// <param name="num">�쐬����x�N�^�̐�</param>
	/// <returns></returns>
	vector<int> CreateArrayVector(const int targetData[], int num);
	//�X�V����
	void Update();
private:
	//fps�����Ɋւ���ϐ�
	static int startTime;			//���[�v�J�n���_�̎���
	static int roopCount;			//����ڂ̃��[�v��60�ɂȂ�����0�ɖ߂�
	static float fps;				//�\������fps�l
	//�Q�[���̌o�ߎ��Ԋ֘A
	int gameStartTime = 0;				//�Q�[���J�n���̎��Ԃ�ۑ�
	int elapsedTime = 0;				//�Q�[���̌o�ߎ���
	int endElapsedTime;
	bool loadFlag;						//�Q�[���I�[�o�[���̌o�ߎ��Ԃ����ɓǂݍ��񂾂��̃t���O
	//�Q�[���̏��
	int gameState = STATE_GAME;
	int scrollSpeed = FIRST_SCROLL_SPEED;
	int nowScreenX = 0;		//�X�N���[���̌��݂̍��W
	int nowScreenY = 0;		//�X�N���[���̌��݂̍��W





};



