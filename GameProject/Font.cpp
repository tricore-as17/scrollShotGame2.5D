#include"DxLib.h"
#include"Font.h"

//�R���X�g���N�^
Font::Font()
{
	//�t�H���g�̃p�X��ϐ���
	LPCSTR FONT_PATH = "Font/k8x12.ttf";
	//�t�H���g�̃��[�h
	AddFontResourceEx(FONT_PATH, FR_PRIVATE, NULL);
	LPCSTR FONT_NAME = "k8x12";
	
	//�t�H���g�n���h���̐ݒ�
	titleLogoHandle = CreateFontToHandle(FONT_NAME, TITLE_GAMELOGO_SIZE, 1, DX_FONTTYPE_EDGE, 0, 2);
	titleExplanetionHandle = CreateFontToHandle(FONT_NAME, TITLE_EXPLANETION_SIZE, 1, DX_FONTTYPE_EDGE, 0, 1);
	gameDistanceHandle = CreateFontToHandle(FONT_NAME, GAME_DISTANCE_SIZE, 1, DX_FONTTYPE_EDGE, 0, 1);
	gameAnnounceHandle = CreateFontToHandle(FONT_NAME, GAME_ANNOUNCE_SIZE, 1, DX_FONTTYPE_EDGE, 0, 1);
	complimentHandle = CreateFontToHandle(FONT_NAME, COMPLIMENT_SIZE, 1, DX_FONTTYPE_EDGE, 0, 1);
	clearEndTitleHandle = CreateFontToHandle(FONT_NAME, CLEAREND_TITLE_SIZE, 1, DX_FONTTYPE_EDGE, 0, 2);
	endTimeHandle = CreateFontToHandle(FONT_NAME, END_TIME_SIZE, 1, DX_FONTTYPE_EDGE, 0, 2);
}
//�f�X�g���N�g
//�t�H���g�f�[�^���������悤�ɂȂ�����g�p(�Q�[���̓r���Ŕj�����Ȃ��Ȃ�g��Ȃ�)
Font::~Font(){ }



