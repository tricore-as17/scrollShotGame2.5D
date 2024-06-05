#include"Player.h"
#include"Colision.h"
#include"Utility.h"

// 静的定数
// 速度（1=1m、60fps固定として、時速10km）
// 10000m ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
const float Player::SPEED = static_cast<float>(17000.0 / 60.0 / 60.0 / 60.0);

//コンストラクタ
Player::Player():isHitTop(false),isGround(false)
{
	//座標の初期化
	pos = VGet(10, 8, 0);
	dir = VGet(0, 0, 1);
	fallSpeed = 0;
	playTime = 0.0f;
	//モデルハンドルに代入
	modelHandle = MV1LoadModel("mv1/Player/playerModel.mv1");
	//モデルのサイズを設定
	MV1SetScale(modelHandle, VGet(SCALE, SCALE, SCALE));
	//モデルの回転値を設定(y軸に90度回転させる);
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, -110.0f * DX_PI_F / 180.0f, 0.0f));
	//3Dモデルの1番目のアニメーションをアタッチする
	attachIndex = MV1AttachAnim(modelHandle, IDLE, -1, FALSE);
	//アタッチしたアニメションの総再生時間を取得
	totalAnimeTime = MV1GetAttachAnimTotalTime(modelHandle, attachIndex);
}
//デストラクタ
Player::~Player()
{
	MV1DeleteModel(modelHandle);
}

/// <summary>
/// ゲーム開始時の初期化
/// </summary>
void Player::Init()
{
	//座標の初期化と移動方向の初期化
	pos = VGet(10,8, 0);
	dir = VGet(0, 0, 0);
	fallSpeed = 0;
	isHitTop, isGround = false;
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
void Player::Update(bool keyStop,const Map &map)
{
	// 入力状態を更新
	// パッド１とキーボードから入力を得る
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// プレイヤーの移動処理
	// 左右の移動方向を出す
	dir = VGet(0, 0, 0);
	if (input & PAD_INPUT_LEFT && keyStop == false)
	{
		dir = VAdd(dir, VGet(-1, 0, 0));
	}
	if (input & PAD_INPUT_RIGHT && keyStop == false)
	{
		dir = VAdd(dir, VGet(1, 0, 0));
	}

	// 正規化
	if (VSquareSize(dir) > 0)		//dirのサイズを2乗にして返す(二乗にすることでdirに値が入っていればifに入る
	{
		dir = VNorm(dir);			//各成分のサイズを１にする
	}

	// 移動量を出す
	velocity = VScale(dir, SPEED);		//dirの各成分にspeedを掛ける

	fallSpeed -= Utility::GRAVITY;


	// HACK: 先に設定判定をすることでfallSpeed修正＋接地フラグ更新
	PlayerColision::CheckIsGround(*this, map);
	PlayerColision::CheckIsTopHit(*this, map);

	//// 落下速度を更新

	// 地に足が着いている場合のみジャンプボタン(ボタン１ or Ｚキー)を見る
	if (((isGround && !isHitTop)) && (input & PAD_INPUT_A) && keyStop == false)
	{
		fallSpeed = JUMP_POWER;	// ジャンプボタンを押したら即座に上方向の力に代わる
		isGround = false;			//接地判定を切る
	}

	// 落下速度を移動量に加える
	auto fallVelocity = VGet(0, fallSpeed, 0);	// 落下をベクトルに。y座標しか変化しないので最後にベクトルにする
	velocity = VAdd(velocity, fallVelocity);

	// 当たり判定をして、壁にめり込まないようにvelocityを操作する
	velocity = PlayerColision::CheckPlayerHitWithMap(*this, map, velocity);
	
	//FIXME:マップをスクロールするために使用しているがその使用は辞めたので
	//出た値を保存する
	keepVelocity = velocity;

	// 移動
	pos = VAdd(pos, velocity);

	//そのまま位置を設定するとモデルの位置がぶれるので微調整
	VECTOR playerOffset = VGet(0, -PLAYER_H*0.5, 0);
	pos = VAdd(pos, playerOffset);

	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, pos);

	//微調整した後はポジションを戻す
	pos = VSub(pos, playerOffset);



	
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


