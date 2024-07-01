#pragma once
#include<vector>
#include<list>
#include"DxLib.h"
#include"GameObject.h"



const int PLAYER_STATE_NUM = 4;             //プレイヤーの状態の数

//クラスのプロトタイプ宣言
class Map;
class Gimmick;
class ShotManager;
class BaseEnemy;
class Shot;
class Utility;

using namespace std;

/// <summary>
/// プレイヤークラス
/// </summary>
class Player:public GameObject
{
public:
    //コンストラクタデストラクタ
    Player();
    ~Player();
    //基本メソッド
    void Initialize();                     //初期化
    void Update(const Map& map, ShotManager& shotManage,const VECTOR cameraPositionr);  //更新
    void Draw();                           //描画

    /// <summary>
    /// プレイヤーモデルの座標移動、拡大、YXZの順で回転させる
    /// </summary>
    /// <param name="scale">拡大率</param>
    /// <param name="translate">移動させたい座標</param>
    /// <param name="rota">それぞれの回転を代入したVECTOR</param>
    /// <returns>計算した行列</returns>
    MATRIX CalculationModelMatrixYXZ(const MATRIX& scale, const VECTOR& translate, const VECTOR& rota);
    /// <summary>
    /// 当たり判定を見てダメージを受けたかのチェック
    /// </summary>
    /// <param name="enemy">調べるエネミーのvector</param>
    /// <param name="shot">画面上に出ている弾のlist</param>
    void IsReceiveDamage(const vector<BaseEnemy*> enemy, list<Shot*> shot);

    /// <summary>
    /// 移動時のアニメーションの更新処理
    /// </summary>
    void UpdateMoveAnimetion();

    /// <summary>
    /// 撃つアニメーションの更新処理
    /// </summary>
    void UpdateShotAnimetion();

    /// <summary>
    /// ダメージを受けた際の点滅表示に関する計算
    /// </summary>
    void modelBlinking();


    //ゲッターセッター
    VECTOR GetKeepVelocity()const { return keepVelocity; }                  //プレイヤーの移動方向を保存
    bool GetIsHitTop()const { return isHitTop; }                            //天井へ当たっているかのフラグを返す
    void SetIsHitTop(const bool inIsHitTop) { isHitTop = inIsHitTop; }      //天井へ当たっているかのセット
    void SetFallSpeed(const float inFallSpeed) { fallSpeed = inFallSpeed; } //落下スピードのセット
    void SetIsGround(const bool inIsGround) { isGround = inIsGround; }      //接地判定の設定
    const int GetLife() const { return life; }                              //プレイヤーの体力を返す
    

    //定数群
    static constexpr float PLAYER_FIRST_X = 13.2f;        //プレイヤーの初期X座標
    static constexpr float PLAYER_FIRST_Y = 4.8f;         //プレイヤーの初期Y座標
    static constexpr float PLAYER_WIDTH   = 1.2f;         //プレイヤー横サイズ
    static constexpr float PLAYER_HEIGHT  = 1.2f;         //プレイヤーの縦サイズ
    static constexpr float JUMP_POWER     = 0.35f;        //キャラのジャンプ力
    static constexpr float ANIMETION_JUMP_POWER = 0.1f;
    static const     MATRIX INITIAL_SCALE_MATRIX;         //キャラの拡大率を設定するための行列
    static constexpr int INITIALIZE_LIFE  = 5;            //ゲーム開始時の体力
    static constexpr int INVINCIBLE_TIME  = 50;           //無敵時間の長さ
    static constexpr int INTERVAL_RIMIT   = 50;           //弾を撃てるようになるまでの間隔

private:
    int modelHandle;                //キャラのモデルハンドル
    VECTOR velocity;                //移動量
    VECTOR keepVelocity;            //プレイヤーの移動量の保存用
    VECTOR rotaVector;              //回転率を保存するためのベクトル
    float differencePositionY;      //モデル用の座標
    float rotaModelY;               //プレイヤーの向きの角度
    bool hitFlag;
    bool isGround;                  //接地判定
    bool isHitTop;                  //天井に当たっているかの判定
    bool damageFlag;                //ダメージを受けた際のフラグ
    int invincibleCount;            //無敵時間のカウント
    int life;                       //体力
    int shotIntervalCount;          //弾を撃つ間隔をカウントする変数
    bool canShot;                   //弾を撃つ準備が出来たか確認フラグ
    bool isShot;                    //実際に撃った場合のフラグ
    bool isMoveAnimetionUpY;        //移動アニメーションでYを加算しているか？
    MATRIX modelScale;              //モデルの大きさ
    bool isShotAnimetionUpY;        //撃つアニメーションでYを加算しているか？
    float moveModelScaleY;          //移動中アニメーションでモデルのYスケール
    float moveModelScaleZ;          //移動中アニメーションでモデルのZスケール
    float shotModelScaleY;          //撃つアニメーションでモデルのYスケール
    float shotModelScaleZ;          //撃つアニメーションでモデルのZスケール
    bool isDraw;                    //描画するか

    //静的定数
    static constexpr float SCALE                       = 0.009f;   //プレイヤーの基本的な大きさ
    static constexpr int   SHOT_DAMAGE                 = 1;        //弾のダメージ
    static constexpr float MOVE_ADDITION_SCALE         = 0.00014f; //移動時に上げるスケールの値 
    static constexpr float MOVE_SUBTRACTION_SCALE      = 0.00025f; //移動時に下げるスケールの値
    static constexpr float MOVE_ADDITION_POSITION_Y    = 0.05f;    //移動時に上げるY座標の値
    static constexpr float MOVE_SUBTRACTION_POSITION_Y = 0.09f;    //移動時に下げるY座標の値
    static constexpr float MOVE_GOAL_DIFFERENCE_SCALE  = 0.002f;   //移動アニメーションのスケールの差の到達値
    static constexpr float SHOT_ADDITION_SCALE         = 0.0005f;  //撃つときに加算させるスケールの値
    static constexpr float SHOT_SUBTRACTION_SCALE      = 0.0005f;  //撃つときに減産させるスケールの値
    static constexpr float SHOT_GOAL_DIFFERENCE_SCALE  = 0.008f;   //撃つアニメーションのスケール差の到達値
    static constexpr int   BLINKING_SPEED = 6;                     //ヒット時に点滅させるスピード
    static const     float SPEED;                                  //プレイヤーの速度

};


