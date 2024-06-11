#include"Map.h"
#include"ShotManager.h"
#include"Shot.h"
#include"Utility.h"

// 静的定数

// 速度（1=1m、60fps固定として、時速10km）
// 10000m ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
//プレイヤーの通常弾の速度
const float ShotManager::SHOT_SPEED[SHOT_KINDS_NUM] = { Utility::CalculationSpeed(35000.0f),
//敵の弾の通常速度
Utility::CalculationSpeed(25000.0f)};

//プレイヤーの通常弾の半径(マップチップのサイズの4分の一)
const float ShotManager::SHOT_RADIUS[SHOT_KINDS_NUM] = { Map::CHIP_SIZE / 4,
//敵の通常弾の半径(マップチップのサイズの4分の一)
Map::CHIP_SIZE/4};

//静的変数の初期化
bool ShotManager::readyFlag[SHOT_KINDS_NUM];
int ShotManager::intervalCount[SHOT_KINDS_NUM] = { 0 };

list<Shot*> ShotManager::activeShot;
list<Shot*> ShotManager::inactiveShot;


/// <summary>
/// コンスタラクタ
/// </summary>
ShotManager::ShotManager()
{
    for (int i = 0; i < INACTIVE_SHOT_NUM; i++)
    {
        inactiveShot.emplace_back(new Shot());
    }
}

//NOTE
//staticを辞めたらコンストラクタで行うので消す
void ShotManager::Init()
{
    for (int i = 0; i < INACTIVE_SHOT_NUM; i++)
    {
        inactiveShot.emplace_back(new Shot());
    }
}


/// <summary>
/// 弾の移動などの更新処理
/// </summary>
void ShotManager::Update()
{
    //弾を撃てるようになるまでの間隔のカウントをする
    for (int i = 0; i < SHOT_KINDS_NUM; i++)
    {
        if (!readyFlag[i])
        {
            intervalCount[i] ++;
            if (intervalCount[i] >= INTERVAL[i])
            {
                readyFlag[i] = true;
                intervalCount[i] = 0;
            }
        }
    }

    //弾の移動処理
    for (auto it = activeShot.begin(); it !=activeShot.end(); ++it)
    {
        (*it)->Update();
    }
}

/// <summary>
/// 弾の生成(敵の弾も味方の弾もすべて生成する)
/// </summary>
/// <param name="pos">弾を撃った座標</param>
/// <param name="dir">弾の方向</param>
/// <param name="shotKinds">どの弾を撃ったか</param>
/// <param name="shotDamage">弾のダメージ</param>
void ShotManager::CreateShot(const VECTOR& pos, const VECTOR& dir,const int shotKinds,const int shotDamage)
{
    //インターバルをチェックして撃てるかの確認撃てるなら弾を作成
    if ( readyFlag[shotKinds])
    {
        //インターバルを0にして弾の作成
        readyFlag[shotKinds] = false;
        //オブジェクトプールを使ってactivShotを有効か
        activeShot.splice(activeShot.end(), inactiveShot, inactiveShot.begin());
        //差し込んだ位置のイテレータを用意してそこで初期化する
        auto it = prev(activeShot.end());    
        (*it)->Init(pos, dir, SHOT_SPEED[shotKinds], SHOT_RADIUS[shotKinds], shotKinds, shotDamage);
    }
}

/// <summary>
/// 弾の削除(画面外に出るか当たっていたら削除)
/// </summary>
/// <param name="cameraPos">カメラの座標</param>
void ShotManager::DeleteShot(const VECTOR& cameraPos)
{
    //現在あるショットの数だけまわす
    for (auto it = activeShot.begin(); it != activeShot.end();)
    {
        //座標の取得
        VECTOR shotPos = (*it)->GetPos();
        //接触した後かスクリーン外に出た際にアクティブからインアクティブに
        if (!(*it)->GetSurvivalFlag() || CheckScreenOut(cameraPos, shotPos))
        {
            //渡す用のイテレータを用意
            auto switchShot = it;
            ++it;
            //最初の位置に差し込む
            inactiveShot.splice(inactiveShot.begin(), activeShot, switchShot);
        }
        else
        {
            ++it;
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
    for (auto it = activeShot.begin(); it != activeShot.end(); ++it)
    {
        (*it)->Draw();
    }
}

/// <summary>
/// 全ての弾の削除
/// </summary>
void ShotManager::DeleteAllShot()
{
    //リストポインタの指しているオブジェクトの解放
    for ( auto ptr : inactiveShot)
    {
        delete ptr;
    }
    for (auto ptr : activeShot)
    {
        delete ptr;
    }
    //ポインタも解放する
    inactiveShot.clear();
    activeShot.clear();
}



