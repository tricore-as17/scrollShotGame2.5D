#pragma once
#include<vector>
#include"DxLib.h"
#include"GameObject.h"

const int PLAYER_X = 150;					//プレイヤーのX座標(動かないので定数)
const int PLAYER_STATE_NUM = 4;				//プレイヤーの状態の数
const int PLAYER_CHIP_SIZE = 64;			//プレイヤーチップのサイズ
const int PLAYER_CHIP_DIV_YNUM = 1;			//プレイヤーチップの縦方向の分割数
const int STATE_RUN_DIV_NUM = 12;			//走っている時の分割数
const int STATE_JUMP_DIV_NUM = 1;			//ジャンプの時の分割数
const int STATE_FALL_DIV_NUM = 1;			//落下中の時の分割数
const int STATE_HIT_DIV_NUM = 7;




class Map;
class Gimmick;


class Player:public GameObject
{
public:
	Player();
	~Player();
	//基本メソッド
	void Init();								//初期化
	void Update(bool keyStop,const Map& map);	//更新
	void Draw();								//描画
	//ゲッターセッター
	VECTOR GetPos()const { return pos; }			//座標を返す
	VECTOR GetDrawPos()const { return drawPos; }	//draw座標を返す
	VECTOR GetKeepVelocity()const { return keepVelocity; }
	bool GetIsHitTop()const { return isHitTop; }	//天井へ当たっているかのフラグを返す
	void SetIsHitTop(const bool inIsHitTop) { isHitTop = inIsHitTop; }		//天井へ当たっているかのセット
	void SetFallSpeed(const float inFallSpeed) { fallSpeed = inFallSpeed; }	//落下スピードのセット
	void SetIsGround(const bool inIsGround) { isGround = inIsGround; }		//接地判定の設定
	void SetPos(const VECTOR inPos) { pos = inPos; }						//座標のセット
	
	//アニメーションの状態の定数
	static enum ANIME_STATE
	{
		//1から開始
		IDLE = 1, MAGIC, RUN
	};
	//定数群
	static constexpr int FIRST_X = 100;			//初期X座標
	static constexpr int FIRST_Y = 450;			//初期Y座標
	static constexpr int PLAYER_W = 32;			//プレイヤー横サイズ
	static constexpr int PLAYER_H = 96;			//プレイヤーの縦サイズ
	static constexpr float JUMP_POWER = 15.0f;  //キャラのジャンプ力
	static constexpr float SPEED = 5.0f;		//キャラの移動スピード
	static constexpr int ANIME_STATE_SUM = 4;	//合計アニメーションの数

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
	VECTOR pos3D;						//3Dモデルの座標
	VECTOR drawPos;
	VECTOR keepVelocity;				//プレイヤーの移動量の保存用

	bool hitFlag;
	bool isGround;						//接地判定
	bool isHitTop;						//天井に当たっているかの判定


	


};


