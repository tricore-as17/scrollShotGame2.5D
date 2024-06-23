#pragma once
#pragma once
#include"BaseEnemy.h"

//クラスのプロトタイプ宣言
struct EnemyInformation;
class ShotManager;
class ShooterEnemy;

/// <summary>
/// ボスのクラス
/// </summary>
class BossEnemy :public BaseEnemy
{
public:
    //定数群
    static constexpr float WIDTH = 2.175f;    //幅
    static constexpr float HEIGHT = 2.175f;    //高さ
    static constexpr int   MAX_LIFE = 5;         //体力の最大値
    static constexpr int   INITIALIZE_DAMAGE = 1;         //接触時の与えるダメージ
    //コンストラクタ
    BossEnemy(EnemyInformation* enemyInformation);
    //デストラクタ
    ~BossEnemy();


    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="cameraPosition">カメラの座標</param>
    /// <param name="shotManager">弾の管理クラス</param>
    /// <param name="playerPosition">プレイヤーの座標</param>
    void Update(const Map& map, const VECTOR& cameraPosition, ShotManager& shotManager, const VECTOR& playerPosition)override;

    void ShootAtThePlayer(const VECTOR& playerPosition, ShotManager& shotManager);

private:
    //定数
    static constexpr float ADJUST_RIGHT_LIMIT = -4.0f;
    static constexpr int SHOT_INTERVAL_RIMIT = 80;      //弾を撃つ間隔
    //メンバ変数
    bool isInAction;             //ボスが何かしらの行動中か
    ShooterEnemy* shooterEnemy;  //弾を撃つためのクラス




};

