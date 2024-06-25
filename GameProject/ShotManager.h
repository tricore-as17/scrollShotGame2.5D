#pragma once
#include<vector>
#include<list>
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
    LEFT_ENEMY_SHOT,
    BOSS_SHOT,
    //ショットの合計数(新しい種類を追加する際はこの上に追加)
    SHOT_KINDS_NUM
};



/// <summary>
/// 弾の発射やインターバルを管理するクラス
/// </summary>
class ShotManager
{
public:
    //コンストラクタ
    ShotManager();
    //デストラクタ
    ~ShotManager();
    //getter,setter
    list<Shot*> GetShot()const { return activeShot; }
    /// <summary>
    /// 弾の移動などの更新処理
    /// </summary>
    void Update();
    /// <summary>
    /// 弾の生成(敵の弾も味方の弾もすべて生成する)
    /// </summary>
    /// <param name="position">弾を撃った座標</param>
    /// <param name="direction">弾の方向</param>
    /// <param name="shotKinds">どの弾を撃ったか</param>
    /// <param name="shotDamage">弾のダメージ</param>
    /// <param name="shooterKinds">弾を撃ったキャラの種類</param>
    void CreateShot(const VECTOR& position,const VECTOR& direction, const int shotKinds, const int shotDamage,const int shooterKinds);
    /// <summary>
    /// 弾の削除(画面外に出たら削除)
    /// </summary>
    /// <param name="cameraPosition">カメラの座標</param>
    void DeleteShot(const VECTOR& cameraPosition);
    /// <summary>
    /// 画面外に出たかのチェック
    /// </summary>
    /// <param name="cameraPosition">カメラの座標</param>
    /// <param name="objectPosition"></param>
    /// <returns></returns>
    bool IsScreenOut(const VECTOR& cameraPosition,const VECTOR objectPosition);
    /// <summary>
    /// 弾の描画
    /// </summary>
    void Draw();
    /// <summary>
    /// 全ての弾の削除
    /// </summary>
    void DeleteAllShot();
    //定数
    static const float SHOT_SPEED[SHOT_KINDS_NUM];                  //それぞれの弾のスピード
    static const float SHOT_RADIUS[SHOT_KINDS_NUM];                 //それぞれの弾の半径
    static constexpr int INACTIVE_SHOT_NUM = 20;                    //最初に用意するショットのインスタンスの数
    
private:
    list<Shot*> inactiveShot;                             //弾を格納する配列（未使用)
    list<Shot*> activeShot;                              //弾を格納する配列(使用中)
};
