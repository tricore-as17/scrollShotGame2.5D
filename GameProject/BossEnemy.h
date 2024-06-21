#pragma once
#pragma once
#include"BaseEnemy.h"

//クラスのプロトタイプ宣言
struct EnemyInformation;
class ShotManager;

/// <summary>
/// ボスのクラス
/// </summary>
class BossEnemy :public BaseEnemy
{
public:
    //定数群
    static constexpr float WIDTH = 2.175f;    //幅
    static constexpr float HEIGHT = 2.175f;    //高さ
    static constexpr int   MAX_LIFE = 5;         //体力の最大値
    static constexpr int   INITIALIZE_DAMAGE = 1;         //接触時の与えるダメージ
    //getter,setter
    void SetScreenLeftLimit(const float screenLeftLimit) { this->screenLeftLimit = screenLeftLimit; }
    void SetScreenRightLimit(const float screenRightLimit) { this->screenRightLimit = screenRightLimit; }
    //コンストラクタ
    BossEnemy(EnemyInformation* enemyInformation);
    //デストラクタ
    ~BossEnemy();

    void Update(const Map& map, const VECTOR& cameraPosition, ShotManager& shotManager, const VECTOR& playerPosition)override;

private:

    float screenLeftLimit;              //移動できる左端の限界値
    float screenRightLimit;             //移動できる右端の限界値
    bool isInAction;                    //何らかの行動中か



};

