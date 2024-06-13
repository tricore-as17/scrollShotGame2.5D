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
	//ゲームステータスの取得
	int inGameState = utility->getGameState();
	//プレイヤー座標の取得
	switch (inGameState)
	{
	case STATE_TITLE:
		//プレイヤーとギミックの位置は毎回リセット
		//player->Init();
		utility->StartInitialize();
		break;
	case STATE_GAME:
		utility->StartInitialize();
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
	//ゲームステータスの取得
	int inGameState = utility->getGameState();
	//ローカル変数の宣言
	bool inGameOverFlag = false;//ゲームオーバーフラグ
	bool inGameClearFlag = false;//ゲームクリアフラグ
	//キー入力
	auto input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	int elapsedTime = utility->getElapsedTime();


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


	switch (inGameState)
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

	//ゲームステータスの取得
	int inGameState = utility->getGameState();
	int inElapsedTime = utility->getElapsedTime();
	switch (inGameState)
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





