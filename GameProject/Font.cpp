#include"DxLib.h"
#include"Font.h"

const int Font::FONT_COLOR_GRAY = GetColor(210, 210, 210);

//コンストラクタ
Font::Font()
{
    //フォントのロード
    AddFontResourceEx("Font/k8x12.ttf", FR_PRIVATE, NULL);
    AddFontResourceEx("Font/minamoji04.ttf", FR_PRIVATE, NULL);
    LPCSTR DotFontName = "k8x12";
    LPCSTR SuimenjiFontName = "水面字04";

    //フォントハンドルの設定
    titleExplanationHandle = CreateFontToHandle(SuimenjiFontName, TITLE_EXPLANETION_SIZE, 9, DX_FONTTYPE_NORMAL);
    playerLifeHandle       = CreateFontToHandle(SuimenjiFontName, PLAYER_LIFE_SIZE, 9, DX_FONTTYPE_NORMAL);
}
//デストラクト
//フォントデータを解放するようになったら使用(ゲームの途中で破棄しないなら使わない)
Font::~Font(){ }



