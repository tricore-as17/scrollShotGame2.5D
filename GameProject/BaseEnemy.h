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
	BaseEnemy(EnemyInformation* enemyInformation);
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
	//ゲッターセッター
	bool GetIsGround()const { return isGround; }		//接地判定の取得
    void SetIsGround(const bool inIsGroound) { isGround = inIsGroound; }	//接地判定の設定
	bool GetIsHitTop()const { return isHitTop; }		//頭上判定の取得
	void SetIsHitTop(const bool inIsHitTop) { isHitTop = inIsHitTop; }	//頭上判定の設定
    int GetLife()const { return life; }                 //体力の値を返す
    int GetDamage()const { return damage; }             //ダメージの値を返す
    



protected:
	bool moveStartFlag;	    //移動を開始させるフラグ
	bool isGround;		    //接地しているか
	bool isHitTop;		    //天井にぶつかっているか
	int firstX;			    //初期X座標
    int life;               //体力
    int kind;               //自分の番号(エネミーかプレイヤーかを判断するための変数)
    int damage;             //敵に当たった時のダメージ


};

