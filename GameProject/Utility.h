#pragma once
#include<vector>
#include"DxLib.h"

using namespace std;

//スクリーンサイズ
const int SCREEN_W = 1280;
const int SCREEN_H = 800;

//色
const int WHITE = GetColor(255, 255, 255);


const int AVERAGE_FLAME = 60;			//カウントするフレーム数
const int SETTING_FPS = 60;				//目標FPS値
const int FIRST_SCROLL_SPEED = -5;		//最初のスクロールスピード
const int SECOND_SCROLL_SPEED = -6;		//二回目のスクロールスピード
const int THIRD_SCROLL_SPEED = -7;		//３回目のスクロールスピード
const int FORCE_SCROLL_SPEED = -8;		//4回目のスクロールスピード
const int FIFTH_SCROLL_SPEED = -9;		//5回目のスクロールスピード


// ゲームの状態.
enum STATE
{
	STATE_TITLE,		// タイトル
	STATE_GAME,			// ゲーム中
	STATE_GAMECLEAR,	//クリア
	STATE_GAMEOVER,		// ゲームオーバー
};


class Utility
{
public:
	//定数群
	static constexpr float GRAVITY = 0.5f;			//重力の値

	//ゲッターセッター
	//経過時間のゲッター
	int getElapsedTime()const { return elapsedTime; }
	int getEndElapsedTime()const { return endElapsedTime; }
	void setEndElapsedTime(int inEndElapsedTime) { endElapsedTime = inEndElapsedTime; }
	bool GetLoadFlag() const { return loadFlag; }
	void SetLoadFlag(const bool inLoadFlag) { loadFlag = inLoadFlag; }
	//ゲームのステータスのげったーせったー
	int getGameState() { return gameState; }
	int getScrollSpeed() { return scrollSpeed; }
	void setGameState(int inputState) { gameState = inputState; }
	int GetNowScreenX()const { return nowScreenX; }		//スクリーンX座標の取得
	int GetNowScreenY()const { return nowScreenY; }		//スクリーンY座標の取得
	int SetNowScreenX(int inX) { nowScreenX = inX; }	//スクリーンX座標の更新
	int SetNowScreenY(int inY) { nowScreenY = inY; }	//スクリーンY座標の更新
	//フレームレート関連の初期化
	static void FpsInit();
	//1フレーム目と60フレーム目で更新
	static void FpsUpdate();
	//計算した値でフレームレートを調節
	static void FpsControll();
	//ゲーム開始時ごとの初期化処理
	void StartInit();
	/// <summary>
	/// 配列へのポインタをもらってベクタを作成する
	/// </summary>
	/// <param name="targetData">ベクタ内に入れる配列のデータ</param>
	/// <param name="num">作成するベクタの数</param>
	/// <returns></returns>
	vector<int> CreateArrayVector(const int targetData[], int num);
	//更新処理
	void Update();
private:
	//fps処理に関する変数
	static int startTime;			//ループ開始時点の時間
	static int roopCount;			//何回目のループか60になったら0に戻る
	static float fps;				//表示するfps値
	//ゲームの経過時間関連
	int gameStartTime = 0;				//ゲーム開始時の時間を保存
	int elapsedTime = 0;				//ゲームの経過時間
	int endElapsedTime;
	bool loadFlag;						//ゲームオーバー時の経過時間を既に読み込んだかのフラグ
	//ゲームの状態
	int gameState = STATE_GAME;
	int scrollSpeed = FIRST_SCROLL_SPEED;
	int nowScreenX = 0;		//スクリーンの現在の座標
	int nowScreenY = 0;		//スクリーンの現在の座標





};



