#pragma once

class Font;

/// <summary>
/// ゲーム中に表示されるUI
/// </summary>
class GameSceneUI
{
public:
    //コンストラクタ
    GameSceneUI();
    //デストラクタ
    ~GameSceneUI();
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="playerLife">プレイヤーの体力</param>
    void Draw(const int playerLife);
private:
    //定数
    static constexpr int LIFE_DRAW_SPACE = 40;    //ライフを描画する間隔
    static constexpr int FIRST_X         = 350;    //1個目のライフを描画するX座標
    static constexpr int FIRST_Y         = 700;   //1個目のライフを描画するY座標
    static constexpr int LIFE_STRING_X = 250;      //LIFEの文字の描画X座標
    static constexpr int LIFE_STRING_Y = 690;     //LIFEの文字の描画Y座標
    //メンバ変数
    int lifeGraph;      //体力の画像ハンドル
    //メンバクラス
    Font* font;

};

