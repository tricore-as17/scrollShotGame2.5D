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
    //エネミーの状態
    enum STATE
    {
        IDLE   = 0,
        ATTACK = 1,
        HIT    = 2
    };
    //定数群
    static constexpr float WIDTH  = 1.45f;          //幅
    static constexpr float HEIGHT = 1.45f;          //高さ
    static constexpr int MAX_LIFE = 2;              //体力の最大値
    static constexpr int INITIALIZE_DAMAGE   = 1;   //与えるダメージ量
    static constexpr int SHOT_INTERVAL_RIMIT = 120; //弾を撃つ間隔
    //アニメーション関連
    static constexpr int CHIP_SIZE     = 44;        //チップサイズ
    static constexpr int ANIMETION_NUM = 3;         //アニメーションの種類
    static constexpr int DRAW_SIZE     = 70;        //描画する時のサイズ
    static constexpr int SHOT_ANIMETION_MOMENT = 4; //アニメーションの中で実際に撃っている瞬間の画像番号
    //分割数
    static constexpr int IDLE_SPLIT_NUM   = 11;     //待機 
    static constexpr int ATTACK_SPLIT_NUM = 8;      //攻撃
    static constexpr int HIT_SPLIT_NUM    = 5;      //被弾時


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
    void Update(const Map& map, const VECTOR& cameraPosition, ShotManager& shotManager, const VECTOR& playerPosition)override;
private:
    int           dirctionX;         //弾のX方向
    int           dirctionY;         //弾のY方向
    ShooterEnemy* shooterEnemy;      //ショットを撃つためのクラス
};

