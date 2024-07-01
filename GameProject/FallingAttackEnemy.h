#pragma once
#include"BaseEnemy.h"

class Player;
class Map;
class ShotManager;


/// <summary>
/// 下降しながら攻撃してくる敵
/// </summary>
class FallingAttackEnemy :public BaseEnemy
{
public:
    //エネミーの状態
    enum STATE
    {
        FLY = 0,
        HIT = 1,
    };
    //コンストラクタ
    FallingAttackEnemy(EnemyInformation* enemyInformation);
    //デストラクタ
    ~FallingAttackEnemy();

    static constexpr float COUNT_SPEED       = 0.005f;    //エネミーの移動速度
    static constexpr float WIDTH             = 1.45f;     //幅
    static constexpr float HEIGHT            = 1.45;      //高さ
    static constexpr int   MAX_LIFE          = 1;         //体力
    static constexpr int   INITIALIZE_DAMAGE = 1;         //与えるダメージ
    //アニメーション関連
    static constexpr int CHIP_SIZE = 64;          //チップの大きさ
    static constexpr int ANIMETION_NUM = 2;       //アニメーションの種類
    //分割数
    static constexpr int FLY_SPLIT_NUM = 9;       //飛行時
    static constexpr int HIT_SPLIT_NUM = 5;       //被弾時

    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="cameraPosition">カメラの座標</param>
    /// <param name="shotManager">ショット管理クラス</param>
    void Update(const Map& map, const VECTOR& cameraPosition, ShotManager& shotManager, const VECTOR& playerPosition)override;
private:
    //定数
    static constexpr float MOVE_END_COUNT = 1.4;    //エネミーの動きを止めるカウント(endCountがこの値になったら止まる)
    //メンバ変数
    VECTOR startPosition;                   //移動開始時の座標を格納する変数
    float  parabolaEndX;                    //放物線の終点となるX座標 
    VECTOR startPlayerPosition;             //エネミーが移動を始めた時にプレイヤーがいた位置
    float  endCount;                        //移動している時間のカウント(線形補間などの移動に使う)
    float  coefficient;                     //放物線係数
};

