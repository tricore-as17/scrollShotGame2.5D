#pragma once
#include"DxLib.h"

//クラスのプロトタイプ宣言
class Map;
class Player;

/// <summary>
/// カメラ
/// </summary>
class Camera
{
public:
    //コンストラクタ
    //デストラクタ
    Camera();
    ~Camera();
    /// <summary>
    /// ゲーム開始ごとの初期化
    /// </summary>
    void Init();
    void Update(const Map& map, const Player& player);
    //ポジションのgetter/setter
    const VECTOR& GetPos() const { return pos; }
private:
    VECTOR firstPos;
    VECTOR pos;
    VECTOR modelVector;
    MATRIX yRota;
};
