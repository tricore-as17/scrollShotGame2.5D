#pragma once


class Font
{
public:
	//�萔
	static constexpr int TITLE_GAMELOGO_SIZE = 150;		//�^�C�g�����S�̃T�C�Y
	static constexpr int TITLE_EXPLANETION_SIZE = 50;	//�^�C�g����ʂł̃{�^�������T�C�Y
	static constexpr int GAME_DISTANCE_SIZE = 70;		//�Q�[�����̌o�ߋ����̃T�C�Y
	static constexpr int GAME_ANNOUNCE_SIZE = 50;		//�Q�[���A�i�E���X�̃T�C�Y
	static constexpr int COMPLIMENT_SIZE = 30;			//��Q�����щz�������̗_�ߌ��t
	static constexpr int CLEAREND_TITLE_SIZE = 150;		//�Q�[���N���A�ƃQ�[���I�[�o�[��ʂ̃^�C�g���T�C�Y
	static constexpr int END_TIME_SIZE = 100;			//�Q�[���I�[�o�[���ɕ\������o�ߎ��Ԃ̃T�C�Y
	//�R���X�g���N�^�E�f�X�g���N�^
	Font();
	virtual ~Font();
	//�`��
	//���ꂼ��̃n���h�����Q�b�^�[
	int GetTitleLogoHandle()const { return titleLogoHandle; }
	int GetTitleExplanetionHandle()const { return titleExplanetionHandle; }
	int GetgameDistanceHandle()const { return gameDistanceHandle; }
	int GetGameAnnouceHandle() const { return gameAnnounceHandle; }
	int GetComplimentHandle()const { return complimentHandle; }
	int GetClearEndTitleHandle() const{ return clearEndTitleHandle; }
	int GetEndTimeHandle() const { return endTimeHandle; }

private:
	//�n���h���f�[�^
	int titleLogoHandle;
	int titleExplanetionHandle;
	int gameDistanceHandle;
	int gameAnnounceHandle;
	int complimentHandle;
	int clearEndTitleHandle;
	int endTimeHandle;

};
