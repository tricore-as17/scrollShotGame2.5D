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
    /// <summary>
    /// カメラのポジションなどの更新(プレイヤーを追従
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="player">プレイヤーのインスタンス</param>
    void Update(const Map& map, const Player& player);
    //ポジションのgetter/setter
    const VECTOR& GetPos() const { return pos; }
private:   
    VECTOR pos;         //座標
};
