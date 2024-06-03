#include"DxLib.h"
#include"Font.h"

//コンストラクタ
Font::Font()
{
	//フォントのパスを変数に
	LPCSTR FONT_PATH = "Font/k8x12.ttf";
	//フォントのロード
	AddFontResourceEx(FONT_PATH, FR_PRIVATE, NULL);
	LPCSTR FONT_NAME = "k8x12";
	
	//フォントハンドルの設定
	titleLogoHandle = CreateFontToHandle(FONT_NAME, TITLE_GAMELOGO_SIZE, 1, DX_FONTTYPE_EDGE, 0, 2);
	titleExplanetionHandle = CreateFontToHandle(FONT_NAME, TITLE_EXPLANETION_SIZE, 1, DX_FONTTYPE_EDGE, 0, 1);
	gameDistanceHandle = CreateFontToHandle(FONT_NAME, GAME_DISTANCE_SIZE, 1, DX_FONTTYPE_EDGE, 0, 1);
	gameAnnounceHandle = CreateFontToHandle(FONT_NAME, GAME_ANNOUNCE_SIZE, 1, DX_FONTTYPE_EDGE, 0, 1);
	complimentHandle = CreateFontToHandle(FONT_NAME, COMPLIMENT_SIZE, 1, DX_FONTTYPE_EDGE, 0, 1);
	clearEndTitleHandle = CreateFontToHandle(FONT_NAME, CLEAREND_TITLE_SIZE, 1, DX_FONTTYPE_EDGE, 0, 2);
	endTimeHandle = CreateFontToHandle(FONT_NAME, END_TIME_SIZE, 1, DX_FONTTYPE_EDGE, 0, 2);
}
//デストラクト
//フォントデータを解放するようになったら使用(ゲームの途中で破棄しないなら使わない)
Font::~Font(){ }



