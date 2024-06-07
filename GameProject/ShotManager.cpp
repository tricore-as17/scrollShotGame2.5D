#include"Map.h"
#include"ShotManager.h"
#include"Shot.h"

// 静的定数

// 速度（1=1m、60fps固定として、時速10km）
// 10000m ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
//プレイヤーの通常弾の速度
const float ShotManager::SHOT_SPEED[SHOT_KINDS_NUM] = { static_cast<float>(25000.0 / 60.0 / 60.0 / 60.0),
//敵の弾の通常速度
static_cast<float>(25000.0 / 60.0 / 60.0 / 60.0) };

//プレイヤーの通常弾の半径(マップチップのサイズの4分の一)
const float ShotManager::SHOT_RADIUS[SHOT_KINDS_NUM] = { Map::CHIP_SIZE / 4,
//敵の通常弾の半径(マップチップのサイズの4分の一)
Map::CHIP_SIZE/4};


/// <summary>
/// 弾の生成(敵の弾も味方の弾もすべて生成する)
/// </summary>
/// <param name="pos">弾を撃った座標</param>
/// <param name="dir">弾の方向</param>
/// <param name="shotKinds">どの弾を撃ったか</param>
void ShotManager::CreateShot(const VECTOR& pos, const VECTOR& dir,const int shotKinds)
{
    //インターバルをチェックして撃てるかの確認撃てるなら弾を作成
    if ( intervalCount[shotKinds] > INTERVAL[shotKinds])
    {
        //インターバルを0にして弾の作成
        intervalCount[shotKinds] = 0;
        shot.emplace_back(new Shot(pos, dir,SHOT_SPEED[shotKinds],SHOT_RADIUS[shotKinds],shotKinds));
    }
}

