#include"EasyEnemy.h"
#include"EnemyInformation.h"
#include"Colision.h"
#include"ShotManager.h"
#include"Map.h"
#include"Utility.h"

// 静的定数
// 速度（1=1m、60fps固定として、時速10km）
// 設定したい速さ ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
const float EasyEnemy::SPEED = Utility::CalculationSpeed(17000.0f);

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="enemyInformation">ベースのコンストラクタを呼ぶ</param>
EasyEnemy::EasyEnemy(EnemyInformation* enemyInformation):BaseEnemy(enemyInformation)
{
    //幅と高さの代入
    width = WIDTH;
    height = HEIGHT;
    //体力の初期化
    life = MAX_LIFE;
    //ダメージの値を初期化
    damage = INITIALIZE_DAMAGE;

    //アニメーション関連の変数のメモリ確保
    //アニメーションの種類と種類ごとの分割数で確保する
    image               = new int* [ANIMETION_NUM];
    image[RUN]          = new int  [RUN_SPLIT_NUM];
    image[HIT]          = new int  [HIT_SPLIT_NUM];
    animetionCouut      = new int  [ANIMETION_NUM];
    animetionCountLimit = new int  [ANIMETION_NUM];
    isRoopAnimetion     = new bool [ANIMETION_NUM];
    isEndAnimetion      = new bool [ANIMETION_NUM];
    //アニメーション関連の初期化
    animetionSpeed = 5;           
    animetionState = RUN;
    imageRotationRate = 0;
    animetionCountLimit[RUN] = RUN_SPLIT_NUM * animetionSpeed;
    animetionCountLimit[HIT] = HIT_SPLIT_NUM * animetionSpeed;
    isRoopAnimetion[RUN] = true;
    isRoopAnimetion[HIT] = false;
    chipSize = Map::CHIP_SIZE * 2;
    for (int i = 0; i < ANIMETION_NUM; i++)
    {
        animetionCouut[i] = 0;
        isEndAnimetion[i] = false;
    }
    //画像のロード
    //走りアニメーション
    LoadDivGraph("img/Enemy/eazy/Run (64x64).png", RUN_SPLIT_NUM, RUN_SPLIT_NUM, 1, CHIP_SIZE, CHIP_SIZE, image[RUN]);
    //ヒット時のアニメーション
    LoadDivGraph("img/Enemy/eazy/Hit64.png", HIT_SPLIT_NUM, HIT_SPLIT_NUM, 1, CHIP_SIZE, CHIP_SIZE, image[HIT]);

    
}
/// <summary>
/// デストラクタ
/// </summary>
EasyEnemy::~EasyEnemy()
{
    //メモリの解放
    for (int i = 0; i < ANIMETION_NUM; i++)
    {
        delete[] image;
    }
    delete animetionCouut;
    delete animetionCountLimit;
}


/// <summary>
/// 初期エネミーの更新処理
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="cameraPosition">カメラの座標</param>
/// <param name="shotManager">ショットを管理するクラス</param>
void EasyEnemy::Update(const Map& map,const VECTOR& cameraPosition,ShotManager& shotManager, const VECTOR& playerPosition)
{

    //画面内に入ったかのチェック
    isMoveStart = CanStartMove(cameraPosition);
    
    //移動開始フラグがたっていたら移動させる
    if (isMoveStart && animetionState == RUN)
    {
        direction = VAdd(direction, VGet(-1, 0, 0));
    }
    else
    {
        direction = VGet(0, 0, 0);
    }
    //当たり判定や移動処理などのエネミー共通処理を呼ぶ
    Move(map, SPEED);

    //ヒット時のアニメーション切り替え処理
    ChangeHitAnimetion(HIT, shotManager);

    //アニメーションの更新処理
    UpdateAnimetion();

    //ヒット時のアニメーションの処理
    HitAnimetion(HIT, RUN);



}


