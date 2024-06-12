﻿#pragma once
#include"DxLib.h"
#include"BaseEnemy.h"

//クラスのプロトタイプ宣言
class ShotManager;
class Map;

/// <summary>
/// 動かずに横向きに弾を撃つエネミー
/// </summary>
class LeftShotEnemy :public BaseEnemy
{
public:
    //定数群
    static constexpr float W = 1.45f;       //幅
    static constexpr float H = 1.45f;       //高さ
    static constexpr int MAX_LIFE = 2;      //体力の最大値
    static constexpr int INIT_DAMAGE = 1;   //与えるダメージ量
    static constexpr int SHOT_DIRCTION = -1;//撃つ弾の方向
    static constexpr int SHOT_INTERVAL_RIMIT = 80;  //弾を撃つ間隔
    //コンストラクタ
    LeftShotEnemy();
    //デストラクタ
    virtual ~LeftShotEnemy();
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="initPos">初期化用の座標</param>
    void Init(const VECTOR& initPos)override;
    /// <summary>
    /// ゲーム中の更新処理
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="cameraPos">カメラの座標</param>
    /// <param name="shotManager">ショットを管理するクラス</param>
    void Update(const Map& map, const VECTOR& cameraPos, ShotManager& shotManager)override;
};