#pragma once
#include"DxLib.h"
#include"BaseEnemy.h"

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
	EasyEnemy(int inFirstX);//コンストラクタ	
	~EasyEnemy();			//デストラクタ
	void Init(VECTOR initPos);				//初期化
	void Update(const Map& map,const VECTOR& playerVec);	//更新
	void Draw();							//描画

};
