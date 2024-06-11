#pragma once
#include"DxLib.h"
#include"GameObject.h"

class Map;

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
    virtual void Init(const VECTOR& initPos )abstract;
    /// <summary>
    /// ゲーム中の更新処理
    /// </summary>
    virtual void Update()abstract;
    /// <summary>
    /// ゲーム中の描画
    /// </summary>
    virtual void Draw()abstract;
	/// <summary>
	/// 当たり判定などの更新処理のなかでの共通処理をまとめたもの
	/// </summary>
	/// <param name="map">マップのインスタンス</param>
	/// <param name="speed">エネミーのスピード</param>
	virtual void Move(const Map& map, const float& speed);
    /// <summary>
    /// エネミーのスクロールを始めるかのチェック(画面に入ったかでチェック)
    /// </summary>
    /// <param name="cameraPos">カメラのポジション</param>
    /// <returns>入っていたら(true)入ってなかったら(false)</returns>
    virtual bool CheckStartMove(const VECTOR& cameraPos);
	//ゲッターセッター
	bool GetIsGround()const { return isGround; }		//接地判定の取得
    void SetIsGround(const bool inIsGroound) { isGround = inIsGroound; }	//接地判定の設定
	bool GetIsHitTop()const { return isHitTop; }		//頭上判定の取得
	void SetIsHitTop(const bool inIsHitTop) { isHitTop = inIsHitTop; }	//頭上判定の設定
    int GetLife()const { return life; }                 //体力の値を返す
    



protected:
	int** graph;		//画像
	bool moveStartFlag;	//移動を開始させるフラグ
	bool isGround;		//接地しているか
	bool isHitTop;		//天井にぶつかっているか
	int firstX;			//初期X座標
    int life;           //体力
    int kind;           //自分の番号(エネミーかプレイヤーかを判断するための変数)


};

