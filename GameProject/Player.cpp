#include"Player.h"
#include"Colision.h"
#include"ShotManager.h"
#include"Shot.h"
#include"EnemyManager.h"
#include"BaseEnemy.h"
#include"EasyEnemy.h"
#include"Map.h"
#include"Utility.h"

// 静的定数
// 速度（1=1m、60fps固定として、時速10km）
// 10000m ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
const float Player::SPEED = Utility::CalculationSpeed(17000.0f);
//拡大率の設定
const MATRIX Player::INITIAL_SCALE_MATRIX = MGetScale(VGet(SCALE, SCALE, SCALE));

//コンストラクタ
Player::Player()
    :isHitTop(false)
    ,isGround(false)
    ,rotaModelY(-90.0f)
    ,isMoveAnimetionUpY(false)
    ,differencePositionY(0)
    ,modelScale(INITIAL_SCALE_MATRIX)
    ,isShotAnimetionUpY(false)
    ,isShot(false)
    ,shotModelScaleZ(SCALE)
    ,shotModelScaleY(SCALE)
    ,moveModelScaleY(SCALE)
    ,moveModelScaleZ(SCALE)
{
    //座標の初期化
    position = VGet(0, 0, 0);
    direction = VGet(0, 0, 1);
    fallSpeed = 0;
    //モデルハンドルに代入
    modelHandle = MV1LoadModel("mv1/Player/slime.mv1");

    //回転率の初期設定(左向きにさせる)
    rotaVector= VGet(20.0f, rotaModelY, 0.0f);


}
//デストラクタ
Player::~Player()
{
    MV1DeleteModel(modelHandle);
}

/// <summary>
/// ゲーム開始時の初期化
/// </summary>
void Player::Initialize()
{
    //座標の初期化と移動方向の初期化
    position = VGet(PLAYER_FIRST_X,PLAYER_FIRST_Y, 0);
    direction = VGet(0, 0, 0);
    fallSpeed = 0;
    isHitTop, isGround = false;
    damageFlag = false;         //ダメージを受けていない状態に
    invincibleCount = 0;        //無敵カウントを0に
    life = INITIALIZE_LIFE;     //体力を初期値に
    canShot = true;         //ショットを撃てるかどうかのフラグ
    shotIntervalCount = 0;      //ショットの弾を撃つ間隔をカウント
    //回転率の初期設定(左向きにさせる)
    rotaVector = VGet(20.0f, rotaModelY, 0.0f);


}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update(const Map &map, ShotManager& shotManager,const VECTOR cameraPosition)
{
    // 入力状態を更新
    // パッド１とキーボードから入力を得る
    auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

    // プレイヤーの移動処理
    // 左右の移動方向を出す
    direction = VGet(0, 0, 0);
    if (input & PAD_INPUT_LEFT)
    {
        direction = VAdd(direction, VGet(-1, 0, 0));
    }
    if (input & PAD_INPUT_RIGHT)
    {
        direction = VAdd(direction, VGet(1, 0, 0));
    }

    // 正規化
    if (VSquareSize(direction) > 0)      //directionのサイズを2乗にして返す(二乗にすることでdirectionに値が入っていればifに入る
    {
        direction = VNorm(direction);    //各成分のサイズを１にする
    }

    // 移動量を出す
    velocity = VScale(direction, SPEED); //directionの各成分にspeedを掛ける

    fallSpeed -= Utility::GRAVITY;


    // HACK: 先に設定判定をすることでfallSpeed修正＋接地フラグ更新
    isGround = Colision::IsGround(map,position,PLAYER_WIDTH,PLAYER_HEIGHT,fallSpeed);
    isHitTop = Colision::IsTopHit(map, position, PLAYER_WIDTH, PLAYER_HEIGHT, fallSpeed,isHitTop);



    // 地に足が着いている場合のみジャンプボタン(ボタン１ or Ｚキー)を見る
    if (((isGround && !isHitTop)) && (input & PAD_INPUT_A))
    {
        fallSpeed = JUMP_POWER; //ジャンプボタンを押したら即座に上方向の力に代わる
        isGround = false;       //接地判定を切る
    }


    // 落下速度を移動量に加える
    auto fallVelocity = VGet(0, fallSpeed, 0);  //落下をベクトルに。y座標しか変化しないので最後にベクトルにする
    velocity = VAdd(velocity, fallVelocity);

    // 当たり判定をして、壁にめり込まないようにvelocityを操作する
    velocity = Colision::IsHitMapAdjustmentVector(map,velocity,position,PLAYER_WIDTH,PLAYER_HEIGHT);

    velocity = Colision::IsHitWallAdjustmentVector(cameraPosition, velocity, position, PLAYER_WIDTH, PLAYER_HEIGHT);


    // 移動
    position = VAdd(position, velocity);

    //そのまま位置を設定するとモデルの位置がぶれるので微調整
    VECTOR playerOffset = VGet(0, -PLAYER_HEIGHT*0.5, 0);
    VECTOR addPosition = VAdd(position, playerOffset);

    //接地していて移動していればアニメーションを流す
    if (isGround && velocity.x != 0 || differencePositionY > 0)
    {
        //移動アニメーションの更新処理
        UpdateMoveAnimetion();
    }

    addPosition.y += differencePositionY;

    //モデルの向いている向きの計算
    if (velocity.x > 0)
    {
        rotaModelY = -90.0f;
    }
    else if (velocity.x < 0)
    {
        rotaModelY = 90.0f;
    }
    //ショットに引数として渡す用の方向変数の宣言
    VECTOR shotDirction;

    //モデルの向いている方向によってショットの撃つ向きを設定
    if (rotaModelY == -90.0f)
    {
        shotDirction = VGet(1.0f, 0.0f, 0.0f);
    }
    else if (rotaModelY == 90.0f)
    {
        shotDirction = VGet(-1.0f, 0.0f, 0.0f);
    }

    //ショットの撃てるタイミングを計算
    if (!canShot)
    {
        shotIntervalCount++;
        if (shotIntervalCount >= INTERVAL_RIMIT)
        {
            canShot = true;
            shotIntervalCount = 0;
        }
    }

    //弾を撃つ処理
    if (input & PAD_INPUT_10)
    {
        if (canShot)
        {
            //弾を撃った際のフラグの変更やや弾の生成処理
            isShot = true;
            isShotAnimetionUpY = true;
            //弾の生成
            shotManager.CreateShot(position, shotDirction, PLAYER_USUALLY, SHOT_DAMAGE, Utility::KIND_PLAYER);
            canShot = false;

        }
    }

    //弾を実際に撃った後のアニメーションの処理
    UpdateShotAnimetion();


    //右回転の行列を設定;
    rotaVector = VGet(rotaVector.x, rotaModelY, rotaVector.z);
    //モデルに拡大率、座標移動、回転率を与えるための行列を作成して反映させる
    MATRIX modelMatrix = CalculationModelMatrixYXZ(modelScale, addPosition, rotaVector);
    MV1SetMatrix(modelHandle, modelMatrix);


}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
    //描画フラグによって描画するかを決める
    if (isDraw)
    {
        MV1DrawModel(modelHandle);
    }

}





/// <summary>
/// プレイヤーモデルの座標移動、拡大、YXZの順で回転させる
/// </summary>
/// <param name="scale">拡大率</param>
/// <param name="translate">移動させたい座標</param>
/// <param name="rota">それぞれの回転を代入したVECTOR</param>
/// <returns>計算した行列</returns>
MATRIX Player::CalculationModelMatrixYXZ(const MATRIX& scale, const VECTOR& translate, const VECTOR& rota)
{
    //マトリックスに移動する値をセット
    MATRIX translateMatrix = MGetTranslate(translate);	
    //YXZの順で回転行列を掛けて回転させる
    MATRIX rotaMatrix = MMult(MMult(MGetRotY(rota.y * Utility::CONVERSION_RADIAN),
        MGetRotX(rota.x * Utility::CONVERSION_RADIAN)), MGetRotZ(rota.z));
    //スケールを追加した状態で計算して返り値にする
    return MMult(MMult(scale, rotaMatrix), translateMatrix);
}

/// <summary>
/// 当たり判定を見てダメージを受けたかのチェック
/// </summary>
/// <param name="enemy">調べるエネミーのvector</param>
/// <param name="shot">画面上に出ている弾のlist</param>
void Player::IsReceiveDamage(const vector<BaseEnemy*> enemy,const list<Shot*> shot)
{
    bool isHit = false;
    //ダメージを受けている状態じゃなければ当たり判定をみる
    if (!damageFlag)
    {
        //エネミーの数だけまわして当たり判定をみる
        //当たった瞬間にフラグをたてて抜ける
        for (auto it = enemy.begin(); it != enemy.end(); it++)
        {
           isHit = Colision::IsHitRectangles(position, PLAYER_WIDTH, PLAYER_HEIGHT, (*it)->GetPosition(), (*it)->GetWidth(), (*it)->GetHeight());

           if (isHit)
           {
               life -= (*it)->GetDamage();
               damageFlag = true;
               break;
           }            
        }
        if (!isHit)
        {

            isHit = Colision::ColisionShot(shot, position, PLAYER_WIDTH, PLAYER_HEIGHT, life, Utility::KIND_PLAYER);
            if (isHit)
            {
                damageFlag = true;
            }

        }

    }
    //一度ダメージを受けた状態なら(一定時間無敵状態になる)
    else
    {
        invincibleCount++;
        //無敵時間が終わったらまたダメージを受ける状態に戻す
        if (invincibleCount >= INVINCIBLE_TIME)
        {
            invincibleCount = 0;
            isDraw = true;
            damageFlag = false;
        }
        else
        {
            //無敵時間中にキャラを点滅表示させるためのカウントを計算
            modelBlinking();
        }
    }
}

/// <summary>
/// 移動時のアニメーションの更新処理(ジャンプしながら移動している処理)
/// </summary>
void Player::UpdateMoveAnimetion()
{
    //移動アニメーションの中でジャンプ中なら
    if (isMoveAnimetionUpY)
    {
        //Y座標を上げながら
        //Yのスケールを上げてZスケールを縮めることでジャンプしてるように見せる
        moveModelScaleY += MOVE_ADDITION_SCALE;
        moveModelScaleZ -= MOVE_ADDITION_SCALE;
        differencePositionY += MOVE_ADDITION_POSITION_Y;
        //マップチップ1個分ジャンプしたら(一定の値にして下降する処理に切り替える)
        if (differencePositionY >= Map::CHIP_SIZE)
        {
            isMoveAnimetionUpY = false;
            differencePositionY = Map::CHIP_SIZE;
            moveModelScaleY = SCALE + MOVE_GOAL_DIFFERENCE_SCALE;
            moveModelScaleZ = SCALE - MOVE_GOAL_DIFFERENCE_SCALE;
        }
    }
    //移動アニメーションの下降状態なら
    else
    {
        //Y座標を下げながら
        //Yのスケールを下げてZスケールを上げることで下降してるように見せる
        differencePositionY -= MOVE_SUBTRACTION_POSITION_Y;
        moveModelScaleY -= MOVE_SUBTRACTION_SCALE;
        moveModelScaleZ += MOVE_SUBTRACTION_SCALE;
        //規定値になったらまたジャンプに戻るようにフラグを切り替える
        if (differencePositionY <= 0)
        {
            isMoveAnimetionUpY = true;
            differencePositionY = 0;
            moveModelScaleY = SCALE;
            moveModelScaleZ = SCALE;
        }
    }
    //調整したスケールを反映させる
    modelScale = MGetScale(VGet(SCALE, moveModelScaleY, moveModelScaleZ));
}

/// <summary>
/// 撃つアニメーションの更新処理
/// </summary>
void Player::UpdateShotAnimetion()
{
    if (isShot)
    {
        //弾を打ち出す際のスケールの処理
        if (isShotAnimetionUpY)
        {
            shotModelScaleZ -= SHOT_ADDITION_SCALE;
            shotModelScaleY += SHOT_ADDITION_SCALE;
            if (shotModelScaleZ <= SCALE - SHOT_GOAL_DIFFERENCE_SCALE)
            {
                isShotAnimetionUpY = false;
            }
        }
        //弾を撃ち終わった後の元のスケールに戻す処理
        else
        {
            shotModelScaleZ += SHOT_SUBTRACTION_SCALE;
            shotModelScaleY -= SHOT_SUBTRACTION_SCALE;
            if (shotModelScaleZ >= SCALE)
            {
                shotModelScaleZ = SCALE;
                shotModelScaleY = SCALE;
                isShot = false;
            }
        }
        //調整したモデルのスケールを反映させる
        modelScale = MGetScale(VGet(SCALE, shotModelScaleY, shotModelScaleZ));
    }

}

/// <summary>
/// ダメージを受けた際の点滅表示に関する計算
/// </summary>
void Player::modelBlinking()
{
    if ((invincibleCount / BLINKING_SPEED) % 2 == 0)
    {
        isDraw = false;
    }
    else
    {
        isDraw = true;
    }
}




