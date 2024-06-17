﻿#pragma once
#include<vector>
#include<list>
#include"DxLib.h"
#include"GameObject.h"


const int PLAYER_STATE_NUM = 4;				//プレイヤーの状態の数

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
	void Initialize();								        //初期化
	void Update(const Map& map, ShotManager& shotManager);	//更新
	void Draw();								            //描画

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
	//ゲッターセッター
	VECTOR GetKeepVelocity()const { return keepVelocity; }					//プレイヤーの移動方向を保存
	bool GetIsHitTop()const { return isHitTop; }							//天井へ当たっているかのフラグを返す
	void SetIsHitTop(const bool inIsHitTop) { isHitTop = inIsHitTop; }		//天井へ当たっているかのセット
	void SetFallSpeed(const float inFallSpeed) { fallSpeed = inFallSpeed; }	//落下スピードのセット
	void SetIsGround(const bool inIsGround) { isGround = inIsGround; }		//接地判定の設定
    const int GetLife() const { return life; }                              //プレイヤーの体力を返す
	
	//アニメーションの状態の定数
	static enum ANIME_STATE
	{
		//1から開始
		IDLE = 1, MAGIC, RUN
	};
	//定数群	
	static constexpr float PLAYER_WIDTH = 0.725f;			//プレイヤー横サイズ
	static constexpr float PLAYER_HEIGHT = 2.175f;			//プレイヤーの縦サイズ
    static constexpr float ANIMETION_SPEED = 0.7f;      //プレイヤーのアニメーションの速度
	static constexpr float JUMP_POWER = 0.25f;			//キャラのジャンプ力
	static constexpr int ANIME_STATE_SUM = 4;			//合計アニメーションの数
	static const MATRIX SCALE_MATRIX;					//キャラの拡大率を設定するための行列
    static constexpr int INITIALIZE_LIFE = 5;                 //ゲーム開始時の体力
    static constexpr int INVINCIBLE_TIME = 50;          //無敵時間の長さ
    static constexpr int INTERVAL_RIMIT = 50;           //弾を撃てるようになるまでの間隔

private:

	//アニメーションフラグを全てリセット
	void ResetAnimeFlag();
	//アニメションのセット
	void AnimeSet(int setState);
    int modelHandle;					//キャラのモデルハンドル
	int attachIndex;					//アニメーションアタッチ用インデックス
	float totalAnimeTime;				//アニメーションのトータル再生時間
	float playTime;						//アニメーションの現在の再生時間
	bool animeState[ANIME_STATE_SUM];	//アニメーションの状態
	

	VECTOR velocity;					//移動量
	VECTOR keepVelocity;				//プレイヤーの移動量の保存用
	VECTOR rotaVector;					//回転率を保存するためのベクトル
    float rotaModelY;                   //プレイヤーの向きの角度
	bool hitFlag;
	bool isGround;						//接地判定
	bool isHitTop;						//天井に当たっているかの判定
    bool damageFlag;                    //ダメージを受けた際のフラグ
    int invincibleCount;               //無敵時間のカウント
    int life;                           //体力
    int shotIntervalCount;              //弾を撃つ間隔をカウントする変数
    bool canShotFlag;                   //弾を撃つ準備が出来たか確認フラグ

	//静的定数
	static constexpr float SCALE = 0.01f;	//プレイヤーの大きさ
	static const float SPEED;				//プレイヤーの速度
    static constexpr int SHOT_DAMAGE = 1;   //弾のダメージ


	


};


