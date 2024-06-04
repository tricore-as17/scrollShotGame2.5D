#include"BaseEnemy.h"
#include"Utility.h"

/// <summary>
/// コンストラクタ
/// </summary>
BaseEnemy::BaseEnemy() :moveStartFlag(false) {}	//フラグの初期化

/// <summary>
/// デストラクタ
/// </summary>
BaseEnemy::~BaseEnemy() {/*処理なし*/ }

/// <summary>
/// エネミーの共通するスクロール処理(マップのスクロールに合わせてエネミーも移動)
/// </summary>
/// <param name="playerVec">プレイヤーの入力したベクトル</param>
void BaseEnemy::ScrollProcess(const VECTOR& playerVec)
{
	if (pos.x - playerVec.x < firstX)
	{
		//マップをスクロールさせる
		pos.x = pos.x - playerVec.x;

	}
	//エネミーが画面内に入ったらスクロールフラグを立てる
	if (pos.x <= SCREEN_W)
	{
		moveStartFlag = true;
	}
}
