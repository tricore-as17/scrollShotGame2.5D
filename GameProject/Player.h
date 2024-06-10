#pragma once
#include<vector>
#include"DxLib.h"
#include"GameObject.h"


const int PLAYER_STATE_NUM = 4;				//プレイヤーの状態の数

//クラスのプロトタイプ宣言
class Map;
class Gimmick;

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
	void Init();								//初期化
	void Update(bool keyStop,const Map& map);	//更新
	void Draw();								//描画

	/// <summary>
	/// プレイヤーモデルの座標移動、拡大、YXZの順で回転させる
	/// </summary>
	/// <param name="scale">拡大率</param>
	/// <param name="translate">移動させたい座標</param>
	/// <param name="rota">それぞれの回転を代入したVECTOR</param>
	/// <returns>計算した行列</returns>
	MATRIX CalculationModelMatrixYXZ(const MATRIX& scale, const VECTOR& translate, const VECTOR& rota);
	//ゲッターセッター
	VECTOR GetKeepVelocity()const { return keepVelocity; }					//プレイヤーの移動方向を保存
	bool GetIsHitTop()const { return isHitTop; }							//天井へ当たっているかのフラグを返す
	void SetIsHitTop(const bool inIsHitTop) { isHitTop = inIsHitTop; }		//天井へ当たっているかのセット
	void SetFallSpeed(const float inFallSpeed) { fallSpeed = inFallSpeed; }	//落下スピードのセット
	void SetIsGround(const bool inIsGround) { isGround = inIsGround; }		//接地判定の設定
	
	//アニメーションの状態の定数
	static enum ANIME_STATE
	{
		//1から開始
		IDLE = 1, MAGIC, RUN
	};
	//定数群	
	static constexpr float PLAYER_W = 0.725f;			//プレイヤー横サイズ
	static constexpr float PLAYER_H = 2.175f;			//プレイヤーの縦サイズ
    static constexpr float ANIMETION_SPEED = 0.7f;      //プレイヤーのアニメーションの速度
	static constexpr float JUMP_POWER = 0.25f;			//キャラのジャンプ力
	static constexpr int ANIME_STATE_SUM = 4;			//合計アニメーションの数
	static const MATRIX SCALE_MATRIX;					//キャラの拡大率を設定するための行列

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

	//静的定数
	static constexpr float SCALE = 0.01f;	//プレイヤーの大きさ
	static const float SPEED;				//プレイヤーの速度


	


};


