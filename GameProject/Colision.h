#pragma once
#include"DxLib.h"

//クラスのプロトタイプ宣言
class Map;


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
    static bool CheckIsGround(const Map& map, const VECTOR& objectPos, const float objectW, const float objectH, float& fallSpeed);

    /// <summary>
    /// 天井に頭がぶつかっているか
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="objectPos">調べるオブジェクトの座標</param>
    /// <param name="objectW">オブジェクトの幅</param>
    /// <param name="objectH">オブジェクトの高さ</param>
    /// <param name="fallSpeed">オブジェクトの落下速度</param>
    /// <returns>当たっているか</returns>
    static bool CheckIsTopHit(const Map& map, const VECTOR& objectPos, const float objectW, const float objectH, float& fallSpeed);


};


