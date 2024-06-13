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
	/// <summary>
	/// エフェクトを表示する時の初期設定
	/// </summary>
	/// <returns>初期化が成功したかの判定</returns>
	static int Setting();

private:
	int handle;				//エフェクトのハンドル
	int playHandle;			//プレイ中のエフェクトハンドル
	int playTime;			//再生時間
	bool playFlag;			//再生中か確認するフラグ
	bool playEndFlag;		//再生終了のフラグ
	VECTOR position;				//座標
};
