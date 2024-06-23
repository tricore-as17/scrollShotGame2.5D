#include"BossEnemy.h"
#include"EnemyInformation.h"
#include"Utility.h"
#include"Colision.h"
#include"ShooterEnemy.h"
#include"ShotManager.h"

//スピードの計算
const float BossEnemy::SPEED = Utility::CalculationSpeed(17000.0f);
//エネミーの行動パターンを出す際の基準となる距離
const float BossEnemy::REFERENCE_DISTANCE = Utility::WORLD_SCREEN_WIDTH_SIZE / 4;

/// <summary>
/// コンストラクタ
/// </summary>
BossEnemy::BossEnemy(EnemyInformation* enemyInformation)
    :BaseEnemy(enemyInformation)
    ,isInAction(false)
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
        isMoveStart = CanStartMove(cameraPosition, ADJUST_RIGHT_LIMIT, 0);
    }
    if (isMoveStart)
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
        VECTOR fallVelocity = VGet(0, fallSpeed, 0);	// 落下をベクトルに。y座標しか変化しないので最後にベクトルにする
        velocity = VAdd(velocity, fallVelocity);

        // 当たり判定をして、壁にめり込まないようにvelocityを操作する
        velocity = Colision::IsHitMapAdjustmentVector(map, velocity, position, width, height);
        //壁との当たり判定をとる
        velocity = Colision::IsHitWallAdjustmentVector(cameraPosition, velocity, position, width, height);

        // 移動
        position = VAdd(position, velocity);     

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
    direction = VNorm(direction);			//各成分のサイズを１にする

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
        shotManager.CreateShot(position, shotDirection, BOSS_SHOT, damage);
        shooterEnemy->SetCanShot(false);
        //弾を撃った数を増やす
        shotCount++;
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


