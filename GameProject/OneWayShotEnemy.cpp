#include "OneWayShotEnemy.h"
#include"ShooterEnemy.h"
#include"EnemyInformation.h"
#include"ShotManager.h"
#include"Map.h"
#include"Colision.h"
#include"Utility.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="enemyInformation">エネミーの初期化情報をまとめたもの</param>
OneWayShotEnemy::OneWayShotEnemy(EnemyInformation* enemyInformation) : BaseEnemy(enemyInformation)
{
    shooterEnemy = new ShooterEnemy();
    //幅と高さの代入
    width = WIDTH;
    height = HEIGHT;
    //体力の初期化
    life = MAX_LIFE;
    //ダメージの値を初期化
    damage = INITIALIZE_DAMAGE;
    //弾の方向を代入
    dirctionX = enemyInformation->shotDirectionX;
    dirctionY = enemyInformation->shotDirectionY;
    //インターバルをセット
    shooterEnemy->SetRimitShotInterval(SHOT_INTERVAL_RIMIT);
    //アニメーションの種類と種類ごとの分割数で確保する
    image               = new int* [ANIMETION_NUM];
    image[IDLE]         = new int  [IDLE_SPLIT_NUM];
    image[ATTACK]       = new int  [ATTACK_SPLIT_NUM];
    image[HIT]          = new int  [HIT_SPLIT_NUM];
    animetionCouut      = new int  [ANIMETION_NUM];
    animetionCountLimit = new int  [ANIMETION_NUM];
    isRoopAnimetion     = new bool [ANIMETION_NUM];
    isEndAnimetion      = new bool [ANIMETION_NUM];
    //アニメーション関連の初期化
    animetionSpeed = 7;
    animetionState = IDLE;
    //角度をラジアンに変換して代入
    imageRotationRate = Utility::ConversionRadian(enemyInformation->imageRotationRate);
    //アニメーションカウントの限界値の設定
    animetionCountLimit[IDLE]   = IDLE_SPLIT_NUM   * animetionSpeed;
    animetionCountLimit[ATTACK] = ATTACK_SPLIT_NUM * animetionSpeed;
    animetionCountLimit[HIT]    = HIT_SPLIT_NUM    * animetionSpeed;
    //ループするアニメーションかどうかを入力
    isRoopAnimetion[IDLE]   = true;
    isRoopAnimetion[ATTACK] = false;
    isRoopAnimetion[HIT]    = false;
    chipSize = Map::ONE_PIXEL_SIZE * 70;
    for (int i = 0; i < ANIMETION_NUM; i++)
    {
        animetionCouut[i] = 0;
        isEndAnimetion[i] = false;
    }

    //画像の読み込み
    LoadDivGraph("img/Enemy/shot/Idle (44x44).png", IDLE_SPLIT_NUM, IDLE_SPLIT_NUM, 1, CHIP_SIZE, CHIP_SIZE, image[IDLE]);
    LoadDivGraph("img/Enemy/shot/Attack (44x44).png", ATTACK_SPLIT_NUM, ATTACK_SPLIT_NUM, 1, CHIP_SIZE, CHIP_SIZE, image[ATTACK]);
    LoadDivGraph("img/Enemy/shot/Hit (44x44).png", HIT_SPLIT_NUM, HIT_SPLIT_NUM, 1, CHIP_SIZE, CHIP_SIZE, image[HIT]);

}

/// <summary>
/// デストラクタ
/// </summary>
OneWayShotEnemy::~OneWayShotEnemy()
{
    delete shooterEnemy;
}

/// <summary>
/// ゲーム中の更新処理
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="cameraPosition">カメラの座標</param>
/// <param name="shotManager">ショットを管理するクラス</param>
void OneWayShotEnemy::Update(const Map& map, const VECTOR& cameraPosition, ShotManager& shotManager, const VECTOR& playerPosition)
{
    //画面内に入ったかのチェック
    isMoveStart = CanStartMove(cameraPosition);

    //画面内に入ったフラグが立っていれば撃つ
    if (isMoveStart && life > 0)
    {
        //前撃ってから一定の間隔が経っていれば撃つ
        shooterEnemy->CountShotInterval();
        if (shooterEnemy->GetCanShot())
        {
            //アニメーションの状態を撃っているように
            animetionState = ATTACK;
        }
    }

    //ヒット時のアニメーション切り替え処理
    ChangeHitAnimetion(HIT, shotManager);
    //アニメーションの更新
    UpdateAnimetion();

    //ヒット時の処理
    HitAnimetion(HIT, IDLE);

    //アニメーションが撃つタイミングになった瞬間
    //アニメーションの中間に撃っているモーションが入っているためここで調節している
    if (animetionCouut[ATTACK] ==  SHOT_ANIMETION_MOMENT * animetionSpeed)
    {
        shotManager.CreateShot(position, VGet(dirctionX, dirctionY, 0), LEFT_ENEMY_SHOT, damage, kind);
        shooterEnemy->SetCanShot(false);
    }

    //攻撃アニメーションが終了した際の処理
    //アニメーションを待機に戻してATTACkで使っていたものを初期化
    if (isEndAnimetion[ATTACK])
    {
        animetionState = IDLE;
        animetionCouut[ATTACK] = 0;
        isEndAnimetion[ATTACK] = false;
    }
}
