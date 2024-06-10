#pragma once
#include<vector>
#include"DxLib.h"

using namespace std;

//クラスのプロトタイプ宣言
class Map;
class Shot;


/// <summary>
/// 当たり判定をまとめたもの
/// </summary>
class Colision
{
public:
    /// <summary>
    /// 矩形同士の当たり判定
    /// </summary>
    /// <param name="pos1">矩形１の座標</param>
    /// <param name="w1">矩形１の幅</param>
    /// <param name="h1">矩形１の高さ</param>
    /// <param name="pos2">矩形２の座標</param>
    /// <param name="w2">矩形２の幅</param>
    /// <param name="h2">矩形２の高さ</param>
    /// <returns>当たったかの判定結果</returns>
    static bool IsHitRectangles(const VECTOR& pos1, float w1, float h1, const VECTOR& pos2, float w2, float h2);

    /// <summary>
    /// 矩形と円の当たり判定
    /// </summary>
    /// <param name="rectPos">矩形の座標</param>
    /// <param name="rectW">矩形の幅</param>
    /// <param name="rectH">矩形の高さ</param>
    /// <param name="circlePos">円の中心座標</param>
    /// <param name="circleR">円の半径</param>
    /// <returns>当たったかの判定結果</returns>
    static bool IsHitCircleWithRectangles(const VECTOR& rectPos, const float rectW, const float rectH, const VECTOR& circlePos, const float circleR);


    /// <summary>
    /// マップとプレイヤーやエネミーの当たり判定
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="velocity">プレイヤーなどのベクトル</param>
    /// <param name="pos">動かす前の座標</param>
    /// <param name="w">オブジェクトの幅</param>
    /// <param name="h">オブジェクトの高さ</param>
    /// <returns>調節したベクトル</returns>
    static VECTOR CheckHitMapAdjustmentVector(const Map& map, VECTOR velocity, const VECTOR& pos,const float w, const float h);

    /// <summary>
    /// オブジェクトが接地しているかの判定
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="objectPos">調べるオブジェクトの座標</param>
    /// <param name="objectW">オブジェクトの幅</param>
    /// <param name="objectH">オブジェクトの高さ</param>
    /// <returns>接地しているか</returns>
    static bool IsGround(const Map& map, const VECTOR& objectPos, const float objectW, const float objectH, float& fallSpeed);

    /// <summary>
    /// 天井に頭がぶつかっているか
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="objectPos">調べるオブジェクトの座標</param>
    /// <param name="objectW">オブジェクトの幅</param>
    /// <param name="objectH">オブジェクトの高さ</param>
    /// <param name="fallSpeed">オブジェクトの落下速度</param>
    /// <returns>当たっているか</returns>
    static bool IsTopHit(const Map& map, const VECTOR& objectPos, const float objectW, const float objectH, float& fallSpeed);

    /// <summary>
    /// 二点間の距離を2乗した値を計算
    /// </summary>
    /// <param name="x1">点１のx</param>
    /// <param name="y1">点１のｙ</param>
    /// <param name="x2">点２のｘ</param>
    /// <param name="y2">点２のｙ</param>
    /// <returns>距離を2乗した値</returns>
    static float DistanceSquare(const float x1, const float y1, const float x2, const float y2);

    /// <summary>
    /// 弾とオブジェクトとの接触判定(オブジェクトはプレイヤーやエネミー)
    /// </summary>
    /// <param name="shot">弾のベクター配列</param>
    /// <param name="objectPos">オブジェクトの座標</param>
    /// <param name="objectW">オブジェクトの幅</param>
    /// <param name="objectH">オブジェクトの高さ</param>
    /// <param name="objectLife">オブジェクトの体力</param>
    /// <param name="objectKind">オブジェクトの種類(誰が発射した弾か)</param>
    static void ColisionShot(vector<Shot*> shot, const VECTOR& objectPos, const float objectW, const float objectH, int& objectLife, const int objectKind);


};


