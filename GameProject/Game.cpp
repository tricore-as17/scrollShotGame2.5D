#include<vector>
#include"DxLib.h"
#include"Player.h"
#include"Map.h"
#include"Utility.h"
#include"Camera.h"
#include"Effect.h"
#include"EnemyManager.h"
#include"ShotManager.h"
#include"Shot.h"
#include"Game.h"

//static変数の初期化
int Game::startTime = GetNowCount();
int Game::roopCount = 0;

//コンストラクタ
Game::Game()
{
	//クラスのインスタンスの作成
	player = new Player();
	utility = new Utility();
	camera = new Camera();
	map = new Map();
	enemyManager = new EnemyManager();
    shotManager = new ShotManager();	
}
//デストラクタ
Game::~Game()
{
	//メモリの解放
    delete player;
    delete utility;
    delete ui;
    delete camera;
    delete map;
    delete enemyManager;
    delete shotManager;
    //ヌルポインターの代入
    player = nullptr;
    utility = nullptr;
    ui = nullptr;
    camera = nullptr;
    map = nullptr;
    enemyManager = nullptr;
    shotManager = nullptr;
    
}

/// <summary>
/// タイトルからゲームなどの以降の際に行う処理のまとめ
/// </summary>
void Game::GameStateChange()
{

	//プレイヤー座標の取得
	switch (gameState)
	{
	case STATE_TITLE:
		//プレイヤーとギミックの位置は毎回リセット
		//player->Init();
		break;
	case STATE_GAME:
		player->Initialize();
		map->Initialize();
		enemyManager->Initialize();
        shotManager->Initialize();
		break;
	case STATE_GAMECLEAR:

		break;
	case STATE_GAMEOVER:
		//プレイヤーとギミックの位置は毎回リセット
		player->Initialize();
		break;
	default:
		break;
	}




}

/// <summary>
/// プログラムが始まる際に行う初期化
/// </summary>
void Game::Initialize()
{
	player->Initialize();
	map->Initialize();
	camera->Initialize();
	enemyManager->Initialize();
}

/// <summary>
/// ゲーム全体の更新処理をまとめたもの
/// </summary>
void Game::Update()
{
	//ローカル変数の宣言
	bool inGameOverFlag = false;//ゲームオーバーフラグ
	bool inGameClearFlag = false;//ゲームクリアフラグ
	//キー入力
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);


	keyRelease = false;
		// キー離した瞬間を取る.
		if (keyOn)
		{
			//
			if (!(input & PAD_INPUT_10))
			{
				keyOn = false;
				keyRelease = true;
			}
		}
		else if (prevKeyOn == false && (input & PAD_INPUT_10))	//キーが最初に押されたタイミング
		{
			keyRelease = false;
			keyOn = true;
		}
		if ((input & PAD_INPUT_10))	//押し続けられている時の処理
		{
			prevKeyOn = true;
		}
		else
		{
			prevKeyOn = false;
		}


	switch (gameState)
	{
	case STATE_TITLE:


		break;
	case STATE_GAME:
		map->Update(player->GetKeepVelocity());
		player->Update(keyStop, *map,*shotManager);
		enemyManager->Update(*map, camera->GetPosition(),*shotManager);
        //弾の移動など
        shotManager->Update();
        player->IsReceiveDamage(enemyManager->GetEasyEnemy(),shotManager->GetShot());
        //画面外に出た弾を消す処理
        shotManager->DeleteShot(camera->GetPosition());
		camera->Update(*map,*player);
		break;
	case STATE_GAMEOVER:

		break;
	case STATE_GAMECLEAR:

		break;
	default:
		break;
	}

}
/// <summary>
/// ゲーム中の描画処理をまとめたもの
/// </summary>
void Game::Draw()
{

	switch (gameState)
	{
	case STATE_TITLE:
		break;
	case STATE_GAME:
		map->Draw();
		player->Draw();
        shotManager->Draw();
		enemyManager->Draw();

		break;
	case STATE_GAMECLEAR:

		break;
	case STATE_GAMEOVER:

		break;
	default:
		break;
	}
	

	
}

/// <summary>
/// フレームレートの調整をする変数などの初期化
/// </summary>
void Game::InitializeFrameRate()
{
    //ゲーム開始時点の時間を取得
    startTime = GetNowCount();
    roopCount = 0;
}

/// <summary>
/// フレームレートの計算のためにカウントなどを取得
/// </summary>
void Game::UpdateFrameRate()
{
    //1フレーム目なら
    if (roopCount == 0)
    {
        startTime = GetNowCount();
    }
    //60フレーム目なら
    if (roopCount == AVERAGE_FLAME)
    {
        //現在の値を代入
        int tmp = GetNowCount();
        //ループカウントの初期化
        roopCount = 0;
        startTime = tmp;
    }
    roopCount++;
}

/// <summary>
/// 取得したカウントを使用し実際にフレームレートを調節する
/// </summary>
void Game::ControlFrameRate()
{
    int tookTime = GetNowCount() - startTime;                   //現在のフレームの経過から1フレーム目で計算した値を引く
    int waitTime = roopCount * 1000 / 60 - tookTime;            //tookTimeの値が大きいと１フレーム辺りにかかる時間が長いので処理が遅いことになる

    if (waitTime > 0)
    {
        Sleep(waitTime);
    }
}





