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
    static constexpr float WIDTH = 2.175f;       //幅
    static constexpr float HEIGHT = 2.175f;      //高さ
    static constexpr int   MAX_LIFE = 5;         //体力の最大値
    static constexpr int   INITIALIZE_DAMAGE = 1;//接触時の与えるダメージ

    /// <summary>
    /// エネミーの行動パターン
    /// </summary>
    enum ACTION
    {
        SIDE_MOVE = 0,
        SHOOT     = 1,
        JUMP      = 2
    };
    /// <summary>
    /// アニメーションの状態
    /// </summary>
    enum ANIMETION_STATE
    {
        START  = 0,
        RUN    = 1,
        ATTACK = 2,
        DEAD   = 3,
    };
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

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw()override;

    /// <summary>
    /// ボスの行動パターンをランダムで決定
    /// </summary>
    void SelectAction();

    /// <summary>
    /// 決まった行動に合わせて動かす
    /// </summary>
    /// <param name="playerPosition">プレイヤーの座標</param>
    /// <param name="shotManager">弾の管理クラス</param>
    /// <returns>行動によって決まった移動量</returns>
    VECTOR StartAction(const VECTOR& playerPosition, ShotManager& shotManager);
    /// <summary>
    /// 左右移動の行動パターンの処理
    /// </summary>
    /// <returns>方向を出した後のの移動量</returns>
    VECTOR MoveSide();
    
    /// <summary>
    /// プレイヤーに向かって弾を撃つ行動の処理
    /// </summary>
    /// <param name="playerPosition">プレイヤーの座標</param>
    /// <param name="shotManager">弾を管理するクラス</param>
    void ShootAtThePlayer(const VECTOR& playerPosition, ShotManager& shotManager);

    /// <summary>
    /// プレイヤーに向かってジャンプする行動の処理
    /// </summary>
    /// <param name="playerPosition">プレイヤーの座標</param>
    VECTOR JumpTowadsPlayer(const VECTOR& playerPosition);

    /// <summary>
    /// 攻撃アニメーションが終了した際の処理
    /// </summary>
    void EndAttackAnimetion();

    /// <summary>
    /// ボスのライフが0になった際の処理
    /// </summary>
    void DeadBoss();

    /// <summary>
    /// 被弾時の点滅表示
    /// </summary>
    void BlinkingDraw();

private:
    //定数
    static constexpr float ADJUST_RIGHT_LIMIT       = -4.0f;   //画面の左側の調節 
    static constexpr float JUMP_COUNT_SPEED         = 0.016f;  //ジャンプした際に1フレームですすむカウント
    static constexpr int   SHOT_INTERVAL_RIMIT      = 60;      //弾を撃つ間隔
    static constexpr int   SIDE_MOVE_END_COUNT      = 80;      //横移動を終わるカウント
    static constexpr int   SWITCH_DIRCTION_INTERVAL = 20;      //移動方向が変わるインターバル
    static const float SPEED;                                  //通常移動のスピード
    static const float REFERENCE_DISTANCE;
    static const int   SINGLE_ACTION_SHOT_NUM = 3;        //１回の行動で撃つ弾の数
    static const int   BLINKING_SPEED = 6;                //ダメージを受けた際の点滅のスピード
    static const int   BLINKING_COUNT_LIMIT = 40;         //どれだけの間点滅させるか

    //アニメーション関連
    static constexpr int CHIP_SIZE     = 96;      //チップの大きさ
    static constexpr int ANIMETION_NUM = 4;       //アニメーションの種類
    static constexpr int DRAW_SIZE     = 240;     //描画時のサイズ
    //分割数
    static constexpr int START_SPLIT_NUM  = 6;       //登場時
    static constexpr int RUN_SPLIT_NUM    = 8;       //走り
    static constexpr int ATTACK_SPLIT_NUM = 9;       //攻撃
    static constexpr int DEAD_SPLIT_NUM   = 6;       //撃破時
    //メンバ変数
    bool isInAction;             //ボスが何かしらの行動中か
    bool isHIt;                  //ヒットしたか

    //横移動の行動に関する変数
    bool isInSideMove;           //横移動のアクション中か
    int switchDirectionCount;    //向きを切り替えるまでのカウント
    int switchDirection;         //向きを切り替えるための変数
    int sideMoveCount;           //横移動を辞めるまでのカウント

    //弾を撃つ行動に関する変数
    bool isInShoot;              //ショット中か
    int shotCount;               //ショットを撃った数

    //プレイヤーに向かってジャンプする行動に関する変数
    bool isInJump;               //ジャンプ中か
    VECTOR startPlayerPosition;  //行動開始した時点でのプレイヤー座標
    VECTOR jumpVertex;           //ジャンプした際の放物線軌道の頂点
    VECTOR jumpStartPosition;    //ジャンプを開始した時の座標
    float coefficient;           //放物線係数
    float jumpEndCount;          //ジャンプが終わるまでのカウント

    //弾に当たった際の点滅表示のための変数
    bool isDraw;                //描画するか
    int blinkingCount;          //点滅表示用のカウント


    //メンバクラス
    ShooterEnemy* shooterEnemy;  //弾を撃つためのクラス



};

