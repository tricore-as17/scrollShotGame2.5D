#pragma once
#include<vector>

//クラスのプロトタイプ宣言
class Player;
class Map;
class Gimmick;
class Utility;
class UI;
class BgModel;
class BG;
class Cloud;
class Player3DDraw;
class Gimmick3D;
class GroundDraw3D;
class Effect;
class EnemyManager;
class ShotManager;

/// <summary>
/// ゲーム全体のインスタンスなどをまとめたクラス
/// </summary>
class Game
{
public:
    // ゲームの状態.
    enum STATE
    {
        STATE_TITLE,		// タイトル
        STATE_GAME,			// ゲーム中
        STATE_GAMECLEAR,	//クリア
        STATE_GAMEOVER,		// ゲームオーバー
    };
	//コンストラクタ・デストラクタ
	Game();
	~Game();
	void GameStateChange();		//ゲームステータスを移行する際の処理
	void Initialize();			//初期化
	//メイン描画の後にサブの処理をする必要があるので別々にする
	void Update();				//メイン画面の更新処理
	void Draw();				//メイン画面の描画
    /// <summary>
    /// フレームレートの調整をする変数などの初期化
    /// </summary>
    void InitializeFrameRate();
    /// <summary>
    /// フレームレートの計算のためにカウントなどを取得
    /// </summary>
    void UpdateFrameRate();
    /// <summary>
    /// 取得したカウントを使用し実際にフレームレートを調節する
    /// </summary>
    void ControlFrameRate();
private:
    //static変数
    //FPSコントロール用
    int startTime;           //ループ開始時の時間
    int roopCount;           //ループ回数

	//プレイヤーやマップなどのクラスをまとめる
	Player* player;
	Utility* utility;
	UI* ui;
	Camera* camera;
	Map* map;
	EnemyManager* enemyManager;
    ShotManager* shotManager;
	//ゲームのステータス関連（スクロールスピードなど)
	
	bool keyRelease = false;
	bool keyOn = false;
	bool prevKeyOn = false;
	int effectPlayCount = 0;
	bool keyStop = false;
    //ゲームの状態
    int gameState = STATE_GAME;			//ゲームステート（タイトル、ゲーム中など)



};
