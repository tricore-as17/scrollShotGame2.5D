#pragma once
#include"DxLib.h"
#include"BaseEnemy.h"

//クラスのプロトタイプ宣言
class Map;

/// <summary>
/// 一番最初に登場する雑魚敵横に移動してくるだけ
/// </summary>
class EasyEnemy :public BaseEnemy
{
public:
	//定数群
	static const float SPEED;		//スピード
	static constexpr float W = 1.45f;			//幅
	static constexpr float H = 1.45f;			//高さ
	//メソッド
	EasyEnemy();			//コンストラクタ	
	~EasyEnemy();						//デストラクタ
	/// <summary>
	/// ゲーム開始時の初期化
	/// </summary>
	/// <param name="initPos">初期化用の座標</param>
	void Init(const VECTOR& initPos)override;
	/// <summary>
	/// 更新処理(当たり判定などの処理はプレイヤーとほぼ同じ)
	/// </summary>
	/// <param name="map">マップのインスタンス</param>
	void Update(const Map& map);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;

    //使用しない純粋仮想関数の定義
    void Update(){}

};
