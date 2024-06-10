#pragma once
#include<vector>
#include"DxLib.h"

using namespace std;

//クラスのプロトタイプ宣言
class Shot;

/// <summary>
/// 弾の種類を判断する定数
/// </summary>
enum ShotKinds
{
    PLAYER_USUALLY,
    ENEMY_USUALLY,
    //ショットの合計数(新しい種類を追加する際はこの上に追加)
    SHOT_KINDS_NUM
};

/// <summary>
/// 弾の発射やインターバルを管理するクラス
/// </summary>
class ShotManager
{
public:

    /// <summary>
    /// 弾の移動などの更新処理
    /// </summary>
    static void Update();
    /// <summary>
    /// 弾の生成(敵の弾も味方の弾もすべて生成する)
    /// </summary>
    /// <param name="pos">弾を撃った座標</param>
    /// <param name="dir">弾の方向</param>
    /// <param name="shotKinds">どの弾を撃ったか</param>
    static void CreateShot(const VECTOR& playerPos,const VECTOR& playerDir, const int shotKinds);
    /// <summary>
    /// 弾の削除(画面外に出たら削除)
    /// </summary>
    /// <param name="cameraPos">カメラの座標</param>
    static void DeleteShot(const VECTOR& cameraPos);
    /// <summary>
    /// 画面外に出たかのチェック
    /// </summary>
    /// <param name="cameraPos">カメラの座標</param>
    /// <param name="objectPos"></param>
    /// <returns></returns>
    static bool CheckScreenOut(const VECTOR& cameraPos,const VECTOR objectPos);
    /// <summary>
    /// 弾の描画
    /// </summary>
    static void Draw();
    /// <summary>
    /// 全ての弾の削除
    /// </summary>
    static void DeleteAllShot();
    //定数
    static constexpr int INTERVAL[SHOT_KINDS_NUM] = { 50,200 };     //それぞれの弾の発射間隔
    static const float SHOT_SPEED[SHOT_KINDS_NUM];                  //それぞれの弾のスピード
    static const float SHOT_RADIUS[SHOT_KINDS_NUM];                 //それぞれの弾の半径
    
private:
    static bool readyFlag[SHOT_KINDS_NUM];                  //弾を撃てる状態かの判定フラグ
    static int intervalCount[SHOT_KINDS_NUM];              //弾を撃てる間隔を測定するためのカウント(弾の種類だけ作る)
    static vector<Shot*> shot;                             //弾を格納する配列
};
