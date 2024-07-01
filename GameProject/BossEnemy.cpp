#include"BossEnemy.h"
#include"EnemyInformation.h"
#include"Utility.h"
#include"Colision.h"
#include"ShooterEnemy.h"
#include"Map.h"
#include"ShotManager.h"

//スピードの計算
const float BossEnemy::SPEED = Utility::CalculationSpeed(17000.0f);
//エネミーの行動パターンを出す際の基準となる距離
const float BossEnemy::REFERENCE_DISTANCE = Utility::WORLD_SCREEN_WIDTH_SIZE / 4;

/// <summary>
/// コンストラクタ
/// </summary>
BossEnemy::BossEnemy(EnemyInformation* enemyInformation)
    :BaseEnemy(enemyInformation, ADJUST_RIGHT_LIMIT)
    ,isInAction(false)
    ,isHIt(false)
    ,isInSideMove(false)
    ,switchDirectionCount(0)
    ,switchDirection(0)
    ,sideMoveCount(0)
    ,isInShoot(false)
    ,shotCount(0)
    ,isInJump(false)
    ,jumpEndCount(0)
    ,startPlayerPosition(VGet(0,0,0))
    ,jumpVertex(VGet(0,0,0))
    ,jumpStartPosition(VGet(0,0,0))
    ,coefficient(0)
    ,isDraw(true)
    ,blinkingCount(0)
{
    shooterEnemy = new ShooterEnemy();
    //幅と高さの代入
    width = WIDTH;
    height = HEIGHT;
    //体力の初期化
    life = MAX_LIFE;
    //ダメージの値を初期化
    damage = INITIALIZE_DAMAGE;

    //インターバルをセット
    //TODO
    //もともとSetterを使うようなコードで書いていたため
    //ここでセッターを使う形にしてしまいました。
    //時間があれば修正します。
    shooterEnemy->SetRimitShotInterval(SHOT_INTERVAL_RIMIT);

    //アニメーションの種類と種類ごとの分割数で確保する
    image               = new int* [ANIMETION_NUM];
    image[START]        = new int  [START_SPLIT_NUM];
    image[RUN]          = new int  [RUN_SPLIT_NUM];
    image[ATTACK]       = new int  [ATTACK_SPLIT_NUM];
    image[DEAD]         = new int  [DEAD_SPLIT_NUM];
    isRoopAnimetion     = new bool [ANIMETION_NUM];
    animetionCouut      = new int  [ANIMETION_NUM];
    animetionCountLimit = new int  [ANIMETION_NUM];
    isEndAnimetion      = new bool [ANIMETION_NUM];
    //アニメーション関連の初期化
    animetionSpeed    = 7;
    animetionState    = START;
    imageRotationRate = 0;
    //アニメーションカウントの限界値の設定
    animetionCountLimit[START]  = START_SPLIT_NUM * animetionSpeed;
    animetionCountLimit[RUN]    = RUN_SPLIT_NUM * animetionSpeed;
    animetionCountLimit[ATTACK] = ATTACK_SPLIT_NUM * animetionSpeed;
    animetionCountLimit[DEAD]   = DEAD_SPLIT_NUM * animetionSpeed;
    //ループさせるアニメーションかを入力
    isRoopAnimetion[START]  = false;
    isRoopAnimetion[RUN]    = true;
    isRoopAnimetion[ATTACK] = false;
    isRoopAnimetion[DEAD]   = false;
    chipSize = Map::ONE_PIXEL_SIZE * DRAW_SIZE;
    for (int i = 0; i < ANIMETION_NUM; i++)
    {
        animetionCouut[i] = 0;
        isEndAnimetion[i] = false;
    }
    //BOSSエネミーだけ最初に右側を向かせる
    isTurn = true;


    //画像の読み込み
    LoadDivGraph("img/Enemy/boss/start.png", START_SPLIT_NUM, START_SPLIT_NUM, 1, CHIP_SIZE, CHIP_SIZE, image[START]);
    LoadDivGraph("img/Enemy/boss/Run.png", RUN_SPLIT_NUM, RUN_SPLIT_NUM, 1, CHIP_SIZE, CHIP_SIZE, image[RUN]);
    LoadDivGraph("img/Enemy/boss/Attack.png", ATTACK_SPLIT_NUM, ATTACK_SPLIT_NUM, 1, CHIP_SIZE, CHIP_SIZE, image[ATTACK]);
    LoadDivGraph("img/Enemy/boss/dead.png", DEAD_SPLIT_NUM, DEAD_SPLIT_NUM, 1, CHIP_SIZE, CHIP_SIZE, image[DEAD]);


}

/// <summary>
/// デストラクタ
/// </summary>
BossEnemy::~BossEnemy()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="cameraPosition">カメラの座標</param>
/// <param name="shotManager">ショットの管理クラス</param>
/// <param name="playerPosition">プレイヤーの座標</param>
void BossEnemy::Update(const Map& map, const VECTOR& cameraPosition, ShotManager& shotManager, const VECTOR& playerPosition)
{
    if (!isMoveStart)
    {
        //画面内に入ったかのチェック
        isMoveStart = CanStartMove(cameraPosition);
    }

    //行動を開始したら
    if (isMoveStart)
    {

        if (isEndAnimetion[START])
        {
            isEndAnimetion[START] = false;
            animetionState = RUN;
            animetionCouut[START] = 0;
        }
        if(animetionState!= START)
        {
            //ランダムで行動を決める
            SelectAction();
            //選択された行動を開始する
            VECTOR velocity = StartAction(playerPosition, shotManager);

            //ジャンプ中じゃなければ重力を落下速度に足す
            if (!isInJump)
            {
                fallSpeed -= Utility::GRAVITY;
            }
            else
            {
                fallSpeed = 0.0f;
            }


            //接地判定を行う
            Colision::IsGround(map, position, width, height, fallSpeed);

            // 落下速度を移動量に加える
            VECTOR fallVelocity = VGet(0, fallSpeed, 0);        // 落下をベクトルに。y座標しか変化しないので最後にベクトルにする
            velocity = VAdd(velocity, fallVelocity);

            // 当たり判定をして、壁にめり込まないようにvelocityを操作する
            velocity = Colision::IsHitMapAdjustmentVector(map, velocity, position, width, height);
            //壁との当たり判定をとる
            velocity = Colision::IsHitWallAdjustmentVector(cameraPosition, velocity, position, width, height);
            // 移動
            position = VAdd(position, velocity);

            //向きを変える
            if (velocity.x < 0)
            {
                isTurn = true;
            }
            else if (velocity.x > 0)
            {
                isTurn = false;
            }

            if (!isHIt)
            {
                //弾と当たっているかを判定して体力などを減らす処理
                isHIt = Colision::ColisionShot(shotManager.GetShot(), position, width, height, life, kind);
            }

            //点滅描画
            BlinkingDraw();

        }


        //アニメーションの更新
        UpdateAnimetion();

        //攻撃アニメーションが終了した際の処理
        EndAttackAnimetion();

        //ボスの体力が0になった際の処理
        DeadBoss();

    }

}

/// <summary>
/// ボスの行動パターンをランダムで決定
/// </summary>
void BossEnemy::SelectAction()
{
    //既に行動中なら早期return
    if (isInAction)
    {
        return;
    }
    else
    {
        //ランダムで敵の行動パターンを決める
        //ランダムで決めたらそれぞれの行動のフラグをたてる
        int randAction = GetRand(2);
        switch (randAction)
        {
        case SIDE_MOVE:
            isInSideMove = true;
            break;
        case SHOOT:
            isInShoot = true;
            break;
        case JUMP:
            isInJump = true;
            break;
        default:
            break;
        }
        //行動開始のフラグを立てる
        isInAction = true;
    }
}

/// <summary>
/// 決まった行動に合わせて動かす
/// </summary>
/// <param name="playerPosition">プレイヤーの座標</param>
/// <param name="shotManager">弾の管理クラス</param>
/// <returns>行動によって決まった移動量</returns>
VECTOR BossEnemy::StartAction(const VECTOR& playerPosition, ShotManager& shotManager)
{
    VECTOR velocity = VGet(0, 0, 0);
    //横移動に関する処理
    if (isInSideMove)
    {
        velocity = MoveSide();
        if (sideMoveCount == SIDE_MOVE_END_COUNT)
        {
            sideMoveCount = 0;
            direction = VGet(0, 0, 0);
            isInSideMove = false;
        }

    }
    //プレイヤーに向かって弾を撃つ処理
    else if (isInShoot)
    {
        ShootAtThePlayer(playerPosition, shotManager);
        if (shotCount == SINGLE_ACTION_SHOT_NUM)
        {
            shotCount = 0;
            isInShoot = false;
        }
    }
    //プレイヤーに向かってジャンプする処理
    else if (isInJump)
    {
        velocity = JumpTowadsPlayer(playerPosition);
        if (jumpEndCount >= 1)
        {
            jumpEndCount = 0;
            isInJump = false;
        }
    }
    //全ての行動が終わっていたら
    if (!isInSideMove && !isInShoot && !isInJump)
    {
        isInAction = false;
    }
    return velocity;
}

/// <summary>
/// 左右移動の行動パターンの処理
/// </summary>
/// <returns>方向を出した後のの移動量</returns>
VECTOR BossEnemy::MoveSide()
{
    switchDirectionCount++;
    //一定のカウントがたまったら向きを切り替える
    if (switchDirectionCount >=SWITCH_DIRCTION_INTERVAL)
    {
        //どの向きにするかをランダムで決める
        switchDirection = GetRand(1);
        switchDirectionCount = 0;
    }
    direction = VGet(0, 0, 0);
    if (switchDirection)
    {
        direction = VGet(-1, 0, 0);
    }
    else
    {
        direction = VGet(1, 0, 0);
    }
    // 正規化
    direction = VNorm(direction);            //各成分のサイズを１にする

    //移動量を出す
    VECTOR velocity = VScale(direction, SPEED);
    sideMoveCount++;

    return velocity;
}



/// <summary>
/// プレイヤーに向かって弾を撃つ行動の処理
/// </summary>
/// <param name="playerPosition">プレイヤーの座標</param>
/// <param name="shotManager">弾を管理するクラス</param>
void BossEnemy::ShootAtThePlayer(const VECTOR& playerPosition,ShotManager& shotManager)
{
    shooterEnemy->CountShotInterval();
    if (shooterEnemy->GetCanShot())
    {
        //プレイヤーの方向へ向かうベクトルを出す
        VECTOR shotDirection = VSub(playerPosition, position);

        shotDirection = VNorm(shotDirection);
        shotManager.CreateShot(position, shotDirection, BOSS_SHOT, damage,kind);
        shooterEnemy->SetCanShot(false);
        //弾を撃った数を増やす
        shotCount++;
        //弾を撃つアニメーションに変更
        animetionState = ATTACK;
        //アニメーション中に弾を撃ったらリセットされるように処理
        isEndAnimetion[ATTACK] = false;
        animetionCouut[ATTACK] = 0;
    }
}

/// <summary>
/// プレイヤーに向かってジャンプする行動の処理
/// </summary>
/// <param name="playerPosition">プレイヤーの座標</param>
VECTOR BossEnemy::JumpTowadsPlayer(const VECTOR& playerPosition)
{
    //返す用の移動量
    VECTOR velocity = VGet(0, 0, 0);
    if (jumpEndCount == 0.0f)
    {
        jumpStartPosition = position;
        //ジャンプ開始時点でのプレイヤーの座標を代入
        startPlayerPosition = playerPosition;
        //プレイヤーに向かって飛ぶ際の放物線軌道の頂点を計算
        VECTOR vectorToPlayer = VSub(VGet(startPlayerPosition.x,position.y,0), position);
        VECTOR harfVector = VScale(vectorToPlayer, 0.5f);
        jumpVertex = VAdd(position, harfVector);
        //プレイヤーとエネミーとの間の座標から画面高さ半分の位置を頂点にする
        jumpVertex = VAdd(jumpVertex, VGet(0, Utility::WORLD_SCREEN_HEIGHT_SIZE * 0.5f, 0));
        //動かす前にプレイヤーの位置と自分の位置から放射線の係数を計算する
        coefficient = (jumpStartPosition.y - jumpVertex.y) / powf(jumpStartPosition.x - jumpVertex.x, 2);
    }
    jumpEndCount += JUMP_COUNT_SPEED;
    if (jumpEndCount > 0 && jumpEndCount <= 1)
    {
        //未来の座標
        VECTOR futurePosition = VGet(0,0,0);
        //未来の座標の値を計算
        futurePosition.x = (1 - jumpEndCount) * jumpStartPosition.x + jumpEndCount * startPlayerPosition.x;
        futurePosition.y = coefficient * powf(futurePosition.x - jumpVertex.x, 2) + jumpVertex.y;
        //未来の座標と現在の座標から移動量を計算する
        velocity = VSub(futurePosition, position);

    }
    return velocity;


}

/// <summary>
/// 被弾時の点滅表示
/// </summary>
void BossEnemy::BlinkingDraw()
{
    //当たってなければ即return
    if (!isHIt)
    {
        return;
    }
    else
    {
        if (life <= 0)
        {
            return;
        }
        else
        {
            //点滅処理
            blinkingCount++;
            if ((blinkingCount / BLINKING_SPEED) % 2 == 0)
            {
                isDraw = false;
            }
            else
            {
                isDraw = true;
            }
            //点滅させる時間を過ぎたら元の状態に戻す
            if (blinkingCount >= BLINKING_COUNT_LIMIT)
            {
                isDraw = true;
                isHIt = false;
                blinkingCount = 0;
            }
        }
    }
}

/// <summary>
/// 攻撃アニメーションが終了した際の処理
/// </summary>
void BossEnemy::EndAttackAnimetion()
{
    if (isEndAnimetion[ATTACK])
    {
        isEndAnimetion[ATTACK] = false;
        animetionCouut[ATTACK] = 0;
        animetionState = RUN;
    }
}

/// <summary>
/// ボスのライフが0になった際の処理
/// </summary>
void BossEnemy::DeadBoss()
{
    //体力が0でないなら早期return
    if (life > 0)
    {
        return;
    }
    else
    {
         animetionState = DEAD;
        if (isEndAnimetion[DEAD])
        {
            isDead = true;
        }
    }
}

void BossEnemy::Draw()
{
    //描画する状態なら
    if (isDraw)
    {
        //描画
        DrawBillboard3D(position, 0.5f, 0.5f, chipSize, imageRotationRate, image[animetionState][animetionCouut[animetionState] / animetionSpeed], TRUE, isTurn);
    }
}


