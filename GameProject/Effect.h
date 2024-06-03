#pragma once
#include"DxLib.h"

class Player;

class Effect
{
public:
	//コンストラクタ・デストラクタ
	Effect(const char* fileName);
	virtual ~Effect();
	//ゲッター
	bool GetPlayFlag()const { return playFlag; }	//再生中かのフラグを返す
	static int Setting();
	//void Init();
	//bool Update(Player* player, const VECTOR playerPos);
	//bool ClearUpdate(VECTOR inPos);
	//bool ClearUpdate(Player* player, const VECTOR playerPos);
	//void Draw();
private:
	int handle;		//エフェクトのハンドル
	int playHandle;	//プレイ中のエフェクトハンドル
	int playTime;			//再生時間
	bool playFlag;			//再生中か確認するフラグ
	bool playEndFlag;		//再生終了のフラグ
	VECTOR pos;				//座標
};
