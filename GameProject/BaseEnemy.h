#pragma once
#include"DxLib.h"
#include"GameObject.h"

/// <summary>
/// エネミーの共通する部分をまとめた基底クラス
/// </summary>
class BaseEnemy:public GameObject
{
public:
	//コンストラクタデストラクタ
	BaseEnemy();
	virtual ~BaseEnemy();
	/// <summary>
	/// エネミーの共通するスクロール処理(マップのスクロールに合わせてエネミーも移動)
	/// </summary>
	virtual void ScrollProcess();
	//ゲッターセッター
	virtual VECTOR GetPos()const { return pos; }				//座標の取得
	virtual void SetPos(const VECTOR inPos) { pos = inPos; }	//座標を設定
	virtual float GetW()const { return w; }						//幅の取得
	virtual float GetH()const { return h; }						//高さの取得
	virtual float GetFallSpeed()const { return fallSpeed; }		//落下速度の取得
	virtual void SetFallSpeed(const float inFallSpeed) { fallSpeed = inFallSpeed; }	//落下速度の設定
	virtual bool GetIsGround()const { return isGround; }		//接地判定の取得
	virtual void SetIsGround(const bool inIsGroound) { isGround = inIsGroound; }	//接地判定の設定
	virtual bool GetIsHitTop()const { return isHitTop; }		//頭上判定の取得
	virtual void SetIsHitTop(const bool inIsHitTop) { isHitTop = inIsHitTop; }	//頭上判定の設定



protected:
	int** graph;		//画像
	bool moveStartFlag;	//移動を開始させるフラグ
	bool isGround;		//接地しているか
	bool isHitTop;		//天井にぶつかっているか
	int firstX;			//初期X座標


};

