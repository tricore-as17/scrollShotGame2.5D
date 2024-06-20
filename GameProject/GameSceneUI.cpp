#include "GameSceneUI.h"
#include"Font.h"


/// <summary>
/// コンストラクタ
/// </summary>
GameSceneUI::GameSceneUI()
{
    //画像ハンドルの取得
    lifeGraph = LoadGraph("img/UI/life.png");
    
}

/// <summary>
/// デストラクタ
/// </summary>
GameSceneUI::~GameSceneUI()
{
    //画像の削除
    DeleteGraph(lifeGraph);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="font"></param>
void GameSceneUI::Draw(Font* font,const int playerLife)
{
    //Lifeの文字
    DrawStringToHandle(LIFE_STRING_X, LIFE_STRING_Y, "LIFE",Font::FONT_COLOR_GRAY, font->GetPlayerLifeHandle());
    //ライフの数だけ描画
    for (int i = 0; i < playerLife; i++)
    {
        DrawGraph(i * LIFE_DRAW_SPACE + FIRST_X, FIRST_Y,lifeGraph, TRUE);
    }
}
