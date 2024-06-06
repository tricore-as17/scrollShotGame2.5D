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
	static constexpr float SPEED = 2.5f;		//スピード
	static constexpr float W = 64.0f;			//幅
	static constexpr float H = 64.0f;			//高さ
	//メソッド
	EasyEnemy(int inFirstX);			//コンストラクタ	
	~EasyEnemy();						//デストラクタ
	/// <summary>
	/// ゲーム開始時の初期化
	/// </summary>
	/// <param name="initPos">初期化用の座標</param>
	void Init(VECTOR initPos);				
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="map">マップの情報が入ったインスタンス</param>
	/// <param name="playerVec">プレイヤーのベクトルをもってくる</param>
	void Update(const Map& map,const VECTOR& playerVec);	
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();							

};
