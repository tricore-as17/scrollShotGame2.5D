#pragma once
#include"DxLib.h"

/// <summary>
/// フォントのに関するクラス
/// </summary>
class Font
{
public:
	//定数
    static const int FONT_COLOR_GRAY;                   //フォントのカラー
	static constexpr int TITLE_EXPLANETION_SIZE = 80;	//タイトル画面でのボタン説明サイズ
    static constexpr int PLAYER_LIFE_SIZE       = 40;   //プレイヤーライフのフォントサイズ

	Font();
	virtual ~Font();
	//描画
	//それぞれのハンドルをゲッター
	const int GetTitleExplanetionHandle()const { return titleExplanationHandle; }
    const int GetPlayerLifeHandle()      const { return playerLifeHandle; }


private:
	//ハンドルデータ
	int titleExplanationHandle;
    int playerLifeHandle;


};
