#pragma once
#include"DxLib.h"
#include"BaseEnemy.h"

//クラスのプロトタイプ宣言
class Map;
class ShotManager;

/// <summary>
/// 一番最初に登場する雑魚敵横に移動してくるだけ
/// </summary>
class EasyEnemy :public BaseEnemy
{
public:
	//定数群
	static const float SPEED;		//スピード
	static constexpr float WIDTH  = 1.45f;			//幅
	static constexpr float HEIGHT = 1.45f;			//高さ
    static constexpr int MAX_LIFE = 1;          //体力の上限値
    static constexpr int INIT_DAMAGE = 1;       //当たった時のダメージ
	//メソッド
	EasyEnemy();			            //コンストラクタ	
	~EasyEnemy();						//デストラクタ
	/// <summary>
	/// ゲーム開始時の初期化
	/// </summary>
	/// <param name="initPos">初期化用の座標</param>
	void Initialize(const VECTOR& initPos)override;
    /// <summary>
    /// 初期エネミーの更新処理
    /// </summary>
    /// <param name="map">マップのインスタンス</param>
    /// <param name="cameraPos">カメラの座標</param>
    /// <param name="shotManager">ショットを管理するクラス</param>
	void Update(const Map& map, const VECTOR& cameraPos, ShotManager& shotManager)override;



};
