#pragma once
#include<vector>
#include"DxLib.h"

using namespace std;

//スクリーンサイズ
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;

//色
const int WHITE = GetColor(255, 255, 255);


const int AVERAGE_FLAME = 60;			//カウントするフレーム数
const int SETTING_FPS = 60;				//目標FPS値
const int FIRST_SCROLL_SPEED = -5;		//最初のスクロールスピード
const int SECOND_SCROLL_SPEED = -6;		//二回目のスクロールスピード
const int THIRD_SCROLL_SPEED = -7;		//３回目のスクロールスピード
const int FORCE_SCROLL_SPEED = -8;		//4回目のスクロールスピード
const int FIFTH_SCROLL_SPEED = -9;		//5回目のスクロールスピード




/// <summary>
/// FPS処理などのゲーム全体で必要なものをまとめたクラス
/// </summary>
class Utility
{
public:
	//定数群
	static constexpr float GRAVITY = 0.012f;			//重力の値
	static const float CONVERSION_RADIAN ;				//角度をラジアンに変換する際にしようする定数
    static constexpr float WORLD_SCREEN_WIDTH_SIZE = 29.0f;    //ワールド座標に合わせたスクリーンの幅
    static constexpr float WORLD_SCREEN_HEIGHT_SIZE = 18.125f;  //ワールド座標に合わせたスクリーンの高さ
    static constexpr int KIND_PLAYER = 0;                  //プレイヤーを判断するための数字
    static constexpr int KIND_ENEMY = 1;                   //エネミーを判断するための数字



	/// <summary>
	/// 配列へのポインタをもらってベクタを作成する
	/// </summary>
	/// <param name="targetData">ベクタ内に入れる配列のデータ</param>
	/// <param name="num">作成するベクタの数</param>
	/// <returns></returns>
	vector<int> CreateArrayVector(const int targetData[], int num);

    /// <summary>
    /// 四角の当たり判定の描画
    /// </summary>
    /// <param name="position">描画したいものの座標</param>
    /// <param name="width">幅</param>
    /// <param name="height">高さ</param>
    static void DrawSquareCollisionDetection(const VECTOR& position,const float& width,const float& height );
    /// <summary>
    /// フレームレートに合わせたスピードの値を計算する処理
    /// </summary>
    /// <param name="setSpeed">代入するスピード</param>
    static float CalculationSpeed(const float setSpeed);

    /// <summary>
    /// 角度をもらってラジアンに変換する
    /// </summary>
    /// <param name="rotationRate">角度</param>
    /// <returns>変換した値</returns>
    static float ConversionRadian(const float rotationRate);

	//更新処理
	void Update();
private:





};



