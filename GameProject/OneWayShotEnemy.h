#pragma once
#include"DxLib.h"
#include"BaseEnemy.h"

//クラスのプロトタイプ宣言
class ShooterEnemy;
class ShotManager;
class Map;
struct EnemyInformation;

/// <summary>
/// 一方通行で弾を撃つエネミーのクラス
/// </summary>
class OneWayShotEnemy :public BaseEnemy
{
public:
    //定数群
    static constexpr float WIDTH = 1.45f;           //幅
    static constexpr float HEIGHT = 1.45f;          //高さ
    static constexpr int MAX_LIFE = 2;              //体力の最大値
    static constexpr int INITIALIZE_DAMAGE = 1;     //与えるダメージ量
    static constexpr int SHOT_INTERVAL_RIMIT = 120;  //弾を撃つ間隔


    //コンストラクタ
    OneWayShotEnemy(EnemyInformation* enemyInformation);
    //デストラクタ
    virtual ~OneWayShotEnemy();
    /// <summary>
    /// ゲーム中の更新処理
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="cameraPosition">カメラの座標</param>
    /// <param name="shotManager">ショットを管理するクラス</param>
    void Update(const Map& map, const VECTOR& cameraPosition, ShotManager& shotManager)override;
private:
    int           dirctionX;         //弾のX方向
    int           dirctionY;         //弾のY方向
    ShooterEnemy* shooterEnemy;     //ショットを撃つためのクラス
};

