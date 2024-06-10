#include"Map.h"
#include"ShotManager.h"
#include"Shot.h"
#include"Utility.h"

// 静的定数

// 速度（1=1m、60fps固定として、時速10km）
// 10000m ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
//プレイヤーの通常弾の速度
const float ShotManager::SHOT_SPEED[SHOT_KINDS_NUM] = { static_cast<float>(35000.0 / 60.0 / 60.0 / 60.0),
//敵の弾の通常速度
static_cast<float>(25000.0 / 60.0 / 60.0 / 60.0) };

//プレイヤーの通常弾の半径(マップチップのサイズの4分の一)
const float ShotManager::SHOT_RADIUS[SHOT_KINDS_NUM] = { Map::CHIP_SIZE / 4,
//敵の通常弾の半径(マップチップのサイズの4分の一)
Map::CHIP_SIZE/4};

//静的変数の初期化
bool ShotManager::readyFlag[SHOT_KINDS_NUM];
int ShotManager::intervalCount[SHOT_KINDS_NUM] = { 0 };
vector<Shot*> ShotManager::shot;


/// <summary>
/// 弾の移動などの更新処理
/// </summary>
void ShotManager::Update()
{
    //弾を撃てるようになるまでの間隔のカウントをする
    for (int i = 0; i < SHOT_KINDS_NUM; i++)
    {
        intervalCount[i] ++;
        if (intervalCount[i] >= INTERVAL[i])
        {
            readyFlag[i] = true;
            intervalCount[i] = 0;
        }
    }

    //弾の移動処理
    for (int i = 0; i<shot.size(); i++)
    {
        shot[i]->Update();
    }
}

/// <summary>
/// 弾の生成(敵の弾も味方の弾もすべて生成する)
/// </summary>
/// <param name="pos">弾を撃った座標</param>
/// <param name="dir">弾の方向</param>
/// <param name="shotKinds">どの弾を撃ったか</param>
void ShotManager::CreateShot(const VECTOR& pos, const VECTOR& dir,const int shotKinds)
{

    //インターバルをチェックして撃てるかの確認撃てるなら弾を作成
    if ( readyFlag[shotKinds] == true)
    {
        //インターバルを0にして弾の作成
        readyFlag[shotKinds] = false;
        shot.emplace_back(new Shot(pos, dir,SHOT_SPEED[shotKinds],SHOT_RADIUS[shotKinds],shotKinds));
    }
}

/// <summary>
/// 弾の削除(画面外に出たら削除)
/// </summary>
/// <param name="cameraPos">カメラの座標</param>
void ShotManager::DeleteShot(const VECTOR& cameraPos)
{
    //現在あるショットの数だけまわす

    for (int i = 0; i< shot.size(); i++)
    {
        //座標の取得
        VECTOR shotPos = shot[i]->GetPos();
        //画面外に出たら要素を削除する
        if (CheckScreenOut(cameraPos,shotPos))
        {
            shot.erase(shot.begin() + i);
        }
    }
}

/// <summary>
/// 画面外に出たかのチェック
/// </summary>
/// <param name="cameraPos">カメラの座標</param>
/// <param name="objectPos"></param>
/// <returns></returns>
bool ShotManager::CheckScreenOut(const VECTOR& cameraPos, const VECTOR objectPos)
{
    //座標が出たかのチェック用フラグ
    bool checkFlag = false;
    //画面右端の座標
    float rightLimit = cameraPos.x + Utility::WORLD_SCREEN_W_SIZE * 0.5f;
    //画面左端の座標
    float leftLimit = cameraPos.x - Utility::WORLD_SCREEN_W_SIZE * 0.5f;
    //画面上端の座標
    float topLimit = cameraPos.y + Utility::WORLD_SCREEN_H_SIZE * 0.5f;
    //画面下端の座標
    float botomLimit = cameraPos.y - Utility::WORLD_SCREEN_H_SIZE * 0.5f;
    //画面内に座標があるかのチェック
    if ((objectPos.x < rightLimit && leftLimit < objectPos.x)&&(objectPos.y < topLimit && objectPos.y > botomLimit))
    {
        checkFlag = false;
    }
    else
    {
        checkFlag = true;
    }
    return checkFlag;
}


/// <summary>
/// 弾の描画
/// </summary>
void ShotManager::Draw()
{
    for (int i = 0; i < shot.size(); i++)
    {
        shot[i]->Draw();
    }
}

/// <summary>
/// 全ての弾の削除
/// </summary>
void ShotManager::DeleteAllShot()
{
    //メモリの解放
    shot.clear();
}



