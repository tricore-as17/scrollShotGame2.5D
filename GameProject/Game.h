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

	//定数
	static constexpr int CLEAR_EFFECT_NUM = 4;		//クリア時のエフェクトの数
	//コンストラクタ・デストラクタ
	Game();
	~Game();
	void GameStateChange();		//ゲームステータスを移行する際の処理
	void Initialize();			//初期化
	//メイン描画の後にサブの処理をする必要があるので別々にする
	void Update();				//メイン画面の更新処理
	void Draw();				//メイン画面の描画
private:
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

};
