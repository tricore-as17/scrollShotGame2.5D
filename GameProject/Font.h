#pragma once
#include"DxLib.h"

/// <summary>
/// フォントのに関するクラス
/// </summary>
class Font
{
public:
	//定数
    static const int FONT_COLOR_GRAY;
	static constexpr int TITLE_EXPLANETION_SIZE = 80;	//タイトル画面でのボタン説明サイズ

	Font();
	virtual ~Font();
	//描画
	//それぞれのハンドルをゲッター
	int GetTitleExplanetionHandle()const { return titleExplanationHandle; }


private:
	//ハンドルデータ
	int titleExplanationHandle;         


};
