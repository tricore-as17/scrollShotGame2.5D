#include"Player.h"
#include"Colision.h"
#include"ShotManager.h"
#include"Shot.h"
#include"EnemyManager.h"
#include"BaseEnemy.h"
#include"EasyEnemy.h"
#include"Utility.h"

// 静的定数
// 速度（1=1m、60fps固定として、時速10km）
// 10000m ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
const float Player::SPEED = Utility::CalculationSpeed(17000.0f);
//拡大率の設定
const MATRIX Player::SCALE_MATRIX = MGetScale(VGet(SCALE, SCALE, SCALE));

//コンストラクタ
Player::Player():isHitTop(false),isGround(false),rotaModelY(-90.0f)
{
	//座標の初期化
	position = VGet(0, 0, 0);
	direction = VGet(0, 0, 1);
	fallSpeed = 0;
	playTime = 0.0f;
	//モデルハンドルに代入
	modelHandle = MV1LoadModel("mv1/Player/playerModel.mv1");
	//3Dモデルの1番目のアニメーションをアタッチする
	attachIndex = MV1AttachAnim(modelHandle, IDLE, -1, FALSE);
	//アタッチしたアニメションの総再生時間を取得
	totalAnimeTime = MV1GetAttachAnimTotalTime(modelHandle, attachIndex);
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
    life = INITIALIZE_LIFE;           //体力を初期値に
    canShotFlag = true;         //ショットを撃てるかどうかのフラグ
    shotIntervalCount = 0;      //ショットの弾を撃つ間隔をカウント
	//回転率の初期設定(左向きにさせる)
	rotaVector = VGet(20.0f, rotaModelY, 0.0f);
	//アニメーション関連の初期化
	playTime = 0.0f;
	for (int i = 0; i < ANIME_STATE_SUM; i++)
	{
		if (i == IDLE)
		{
			animeState[i] = true;
		}
		animeState[i] = false;
	}

}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update(const Map &map, ShotManager& shotManager)
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
	if (VSquareSize(direction) > 0)		//directionのサイズを2乗にして返す(二乗にすることでdirectionに値が入っていればifに入る
	{
		direction = VNorm(direction);			//各成分のサイズを１にする
	}

	// 移動量を出す
	velocity = VScale(direction, SPEED);		//directionの各成分にspeedを掛ける

	fallSpeed -= Utility::GRAVITY;


	// HACK: 先に設定判定をすることでfallSpeed修正＋接地フラグ更新
	isGround = Colision::IsGround(map,position,PLAYER_WIDTH,PLAYER_HEIGHT,fallSpeed);
    isHitTop = Colision::IsTopHit(map, position, PLAYER_WIDTH, PLAYER_HEIGHT, fallSpeed);



	// 地に足が着いている場合のみジャンプボタン(ボタン１ or Ｚキー)を見る
	if (((isGround && !isHitTop)) && (input & PAD_INPUT_A))
	{
		fallSpeed = JUMP_POWER;	// ジャンプボタンを押したら即座に上方向の力に代わる
		isGround = false;			//接地判定を切る
	}

	// 落下速度を移動量に加える
	auto fallVelocity = VGet(0, fallSpeed, 0);	// 落下をベクトルに。y座標しか変化しないので最後にベクトルにする
	velocity = VAdd(velocity, fallVelocity);

	// 当たり判定をして、壁にめり込まないようにvelocityを操作する
	velocity = Colision::IsHitMapAdjustmentVector(map,velocity,position,PLAYER_WIDTH,PLAYER_HEIGHT);

	
	//FIXME:マップをスクロールするために使用しているがその使用は辞めたので
	//出た値を保存する
	keepVelocity = velocity;


	// 移動
	position = VAdd(position, velocity);

	//そのまま位置を設定するとモデルの位置がぶれるので微調整
	VECTOR playerOffset = VGet(0, -PLAYER_HEIGHT*0.5, 0);
	VECTOR addPosition = VAdd(position, playerOffset);




	if (velocity.x > 0)
	{
        rotaModelY = -90.0f;
	}
	else if (velocity.x < 0)
	{
        rotaModelY = 90.0f;
	}
    //右回転の行列を設定;
    rotaVector = VGet(rotaVector.x, rotaModelY, rotaVector.z);
	//モデルに拡大率、座標移動、回転率を与えるための行列を作成して反映させる
	MATRIX modelMatrix = CalculationModelMatrixYXZ(SCALE_MATRIX, addPosition, rotaVector);
	MV1SetMatrix(modelHandle, modelMatrix);


	//アニメーションの更新
	//左右どちらかに動いていたら走りのアニメーションを有効にする
	if (velocity.x != 0.0f)
	{
		AnimeSet(RUN);
	}
	//動いていないので待機アニメーションを有効にする
	else
	{
		AnimeSet(IDLE);
	}

	//アニメーションカウントの更新(１回の再生時間を超えたらリセット)
	playTime += ANIMETION_SPEED;
	if (playTime >= totalAnimeTime)
	{
		playTime = 0.0f;
	}
	//再生時間のセット
	MV1SetAttachAnimTime(modelHandle, attachIndex, playTime);

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
    if (!canShotFlag)
    {
        shotIntervalCount++;
        if (shotIntervalCount >= INTERVAL_RIMIT)
        {
            canShotFlag = true;
            shotIntervalCount = 0;
        }
    }

    //弾を撃つ処理
    if (input & PAD_INPUT_10)
    {
        if (canShotFlag)
        {
            shotManager.CreateShot(position, shotDirction, PLAYER_USUALLY,SHOT_DAMAGE);
            canShotFlag = false;
        }
    }





	
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	//プレイヤーモデルの描画
	MV1DrawModel(modelHandle);

}

/// <summary>
/// アニメーションフラグを全てfalseに
/// </summary>
void Player::ResetAnimeFlag()
{
	for (int i = 0; i < ANIME_STATE_SUM; i++)
	{
		animeState[i] = false;
	}
}

/// <summary>
/// アニメーションのセット
/// </summary>
/// <param name="setState">セットするステート</param>
void Player::AnimeSet(int setState)
{
	//現在そのアニメーションが再生されていなければセット
	if (animeState[setState]!= true)
	{
		MV1DetachAnim(modelHandle, attachIndex);
		//3Dモデルの1番目のアニメーションをアタッチする
		attachIndex = MV1AttachAnim(modelHandle, setState, -1, FALSE);
		//アタッチしたアニメションの総再生時間を取得
		totalAnimeTime = MV1GetAttachAnimTotalTime(modelHandle, attachIndex);
		playTime = 0.0f;
		//一度アニメーションフラグをリセット
		ResetAnimeFlag();
		animeState[setState] = true;
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
            damageFlag = false;
        }
    }
}


