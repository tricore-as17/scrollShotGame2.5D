#pragma once

/// <summary>
/// 敵の初期化情報をまとめた構造体
/// </summary>
struct EnemyInformation
{
    int   type;             //敵の種類
    float initializeX;      //初期X座標
    float initializeY;      //初期Y座標
    int   shotDirectionX;   //ショットのX方向（弾を撃ってる奴だけがもらう)
    int   shotDirectionY;   //ショットのY方向
    float imageRotationRate;//画像の回転率
};
