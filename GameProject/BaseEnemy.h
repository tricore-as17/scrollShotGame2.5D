#pragma once
#include"DxLib.h"
#include"GameObject.h"

//クラスや構造体のプロトタイプ宣言
class Map;
class ShotManager;
struct EnemyInformation;

/// <summary>
/// エネミーの共通する部分をまとめた基底クラス
/// </summary>
class BaseEnemy abstract :public GameObject 
{
public:
    //コンストラクタデストラクタ
    BaseEnemy(EnemyInformation* enemyInformation, const int adjustRightLimit = 0);
    virtual ~BaseEnemy();

    /// <summary>
    /// ゲーム中の更新処理
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="cameraPosition">カメラの座標</param>
    /// <param name="shotManager">ショットの管理クラス</param>
    virtual void Update(const Map& map, const VECTOR& cameraPosition, ShotManager& shotManager,const VECTOR& playerPosition)abstract;
    /// <summary>
    /// ゲーム中の描画
    /// </summary>
    virtual void Draw();
    /// <summary>
    /// 当たり判定などの更新処理のなかでの共通処理をまとめたもの
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="speed">エネミーのスピード</param>
    virtual void Move(const Map& map, const float& speed);
    /// <summary>
    /// エネミーのスクロールを始めるかのチェック(画面に入ったかでチェック)
    /// </summary>
    /// <param name="cameraPosition">カメラのポジション</param>
    /// <returns>入っていたら(true)入ってなかったら(false)</returns>
    virtual bool CanStartMove(const VECTOR& cameraPosition);
    /// <summary>
    /// アニメーションの更新処理
    /// </summary>
    void UpdateAnimetion();

    ///// <summary>
    /// 弾が当たった際のアニメーション切り替え処理
    /// </summary>
    /// <param name="hitAnimetionState">ヒット時のアニメーションの添え字</param>
    /// <param name="shotManager">ショット管理クラス</param>
    void ChangeHitAnimetion(const int hitAnimetionState, const ShotManager& shotManager);

    /// <summary>
    /// ヒット時のアニメーションの更新
    /// </summary>
    /// <param name="hitAnimetionState">ヒット時のアニメーションの添え字</param>
    /// <param name="roopAnimetionState">ループアニメーションの添え字</param>
    virtual void HitAnimetion(const int hitAnimetionState, const int roopAnimetionState);



    //ゲッターセッター
    bool GetIsGround()const { return isGround; }                            //接地判定の取得
    void SetIsGround(const bool inIsGroound) { isGround = inIsGroound; }    //接地判定の設定
    bool GetIsHitTop()const { return isHitTop; }                            //頭上判定の取得
    void SetIsHitTop(const bool inIsHitTop) { isHitTop = inIsHitTop; }      //頭上判定の設定
    int GetLife()const { return life; }                                     //体力の値を返す
    int GetDamage()const { return damage; }                                 //ダメージの値を返す
    const int GetType()const { return type; }                               //タイプを返す
    const bool GetIsMoveStart()const { return isMoveStart; }                //移動を開始するかを返す
    const bool GetIsDead()const { return isDead; }                          //撃破されたかを返す

protected:
    int  type;              //自身のタイプ
    bool isMoveStart;       //移動を開始させるフラグ
    bool isGround;          //接地しているか
    bool isHitTop;          //天井にぶつかっているか
    int firstX;             //初期X座標
    int life;               //体力
    int kind;               //自分の番号(エネミーかプレイヤーかを判断するための変数)
    int damage;             //敵に当たった時のダメージ
    float adjustRightLimit; //スクリーンに入る際の調節用
    int** image;            //画像ハンドル
    float chipSize;           //画像のチップサイズ
    float imageRotationRate;  //画像の回転率  
    int *animetionCouut;     //アニメーションカウント
    int *animetionCountLimit;//アニメーションの上限値
    bool *isRoopAnimetion;   //ループするアニメーション判断
    bool *isEndAnimetion;    //ループしないアニメーションの再生が終了したフラグ
    int animetionState;      //現在のアニメーションの状態
    int animetionSpeed;      //アニメーションを切り替えるスピード
    bool isTurn;             //ターンするかのフラグ
    bool isDead;            //撃破フラグ
};

