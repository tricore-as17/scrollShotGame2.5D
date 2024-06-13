#pragma once
#include"DxLib.h"
#include"GameObject.h"

class Map;
class ShotManager;

/// <summary>
/// エネミーの共通する部分をまとめた基底クラス
/// </summary>
class BaseEnemy abstract :public GameObject 
{
public:
	//コンストラクタデストラクタ
	BaseEnemy();
	virtual ~BaseEnemy();
    /// <summary>
    /// ゲーム開始時の初期化
    /// </summary>
    virtual void Initialize(const VECTOR& initializePosition )abstract;
    /// <summary>
    /// ゲーム中の更新処理
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="cameraPosition">カメラの座標</param>
    /// <param name="shotManager">ショットの管理クラス</param>
    virtual void Update(const Map& map, const VECTOR& cameraPosition, ShotManager& shotManager)abstract;
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
    /// 弾を撃てるようになるまでの間隔の設定
    /// </summary>
    /// <param name="INTERVAL_RIMIT">間隔の大きさ</param>
    virtual void CountShotInterval(const int INTERVAL_RIMIT);
	//ゲッターセッター
	bool GetIsGround()const { return isGround; }		//接地判定の取得
    void SetIsGround(const bool inIsGroound) { isGround = inIsGroound; }	//接地判定の設定
	bool GetIsHitTop()const { return isHitTop; }		//頭上判定の取得
	void SetIsHitTop(const bool inIsHitTop) { isHitTop = inIsHitTop; }	//頭上判定の設定
    int GetLife()const { return life; }                 //体力の値を返す
    int GetDamage()const { return damage; }             //ダメージの値を返す
    



protected:
	int** graph;		    //画像
	bool moveStartFlag;	    //移動を開始させるフラグ
	bool isGround;		    //接地しているか
	bool isHitTop;		    //天井にぶつかっているか
	int firstX;			    //初期X座標
    int life;               //体力
    int kind;               //自分の番号(エネミーかプレイヤーかを判断するための変数)
    int damage;             //敵に当たった時のダメージ
    int shotIntervalCount;  //弾を撃つ間隔をカウントする変数
    bool readyShotFlag;     //弾を撃つ準備が出来たか確認フラグ


};

