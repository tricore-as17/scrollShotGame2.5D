#include<vector>
#include"DxLib.h"
#include"Player.h"
#include"Map.h"
#include"Utility.h"
#include"Camera.h"
#include"Effect.h"
#include"EnemyManager.h"
#include"ShotManager.h"
#include"Game.h"

//コンストラクタ
Game::Game()
{
	//クラスのインスタンスの作成
	player = new Player();
	utility = new Utility();
	camera = new Camera();
	gameOverEffect = new Effect("Effect/BreakChara.efkefc");
	clearCharaEffect = new Effect("Effect/clearChara.efkefc");
	map = new Map();
	enemyManager = new EnemyManager();

	//エフェクトの動的確保
	for (int i = 0; i < CLEAR_EFFECT_NUM; i++)
	{
		clearEffect.emplace_back(new Effect("Effect/hitEffect.efkefc"));
	}

	
	
}
//デストラクタ
Game::~Game()
{
	//メモリの解放
	delete player,utility,ui,bgModel,camera,bg,player3D,gameOverEffect,clearCharaEffect,map
		,enemyManager;
    //ヌルポインターの代入
	player ,utility,ui,bgModel,camera,bg,player3D,gameOverEffect,clearCharaEffect,map,enemyManager = nullptr;
    //ベクターのメモリ解放
	gimmick.clear();
	cloud.clear();
	clearEffect.clear();
    //全ての弾のインスタンスを消す
    ShotManager::DeleteAllShot();
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
		utility->StartInit();
		break;
	case STATE_GAME:
		utility->StartInit();
		player->Init();
		map->Init();
		enemyManager->Init();
		break;
	case STATE_GAMECLEAR:

		break;
	case STATE_GAMEOVER:
		//プレイヤーとギミックの位置は毎回リセット
		player->Init();
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
	player->Init();
	map->Init();
	camera->Init();
	enemyManager->Init();
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
	bool inEffectPlayFlag = gameOverEffect->GetPlayFlag();
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
		player->Update(keyStop, *map);
		enemyManager->Update(*map, camera->GetPos());
        //弾の移動など
        ShotManager::Update();
        //画面外に出た弾を消す処理
        ShotManager::DeleteShot(camera->GetPos());
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
        ShotManager::Draw();
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





