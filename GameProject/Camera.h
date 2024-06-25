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
    void Initialize();
    /// <summary>
    /// カメラのポジションなどの更新(プレイヤーを追従
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="player">プレイヤーのインスタンス</param>
    void Update(const Map& map, const Player& player);

    /// <summary>
    /// カメラの移動を止める
    /// </summary>
    void StopCameraMove();
    //ポジションのgetter/setter
    const VECTOR& GetPosition() const { return position; }
private:   
    VECTOR position;         //座標
    bool  isMoveStop;       //カメラの移動を止めるかのフラグ
};
