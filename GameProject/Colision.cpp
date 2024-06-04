#include"DxLib.h"
#include"Colision.h"
#include"GameObject.h"
#include"Player.h"
#include"EasyEnemy.h"
#include"Map.h"

VECTOR PlayerColision::CheckPlayerHitWithMap(Player& player, const Map& map, const VECTOR& velocity)
{
	// サイズが最初から0なら動かさず早期return
	if (VSize(velocity) == 0)		//VSizeでベクトルのサイズをとっている0なら動いてないなのでここで返す
	{
		return velocity;
	}
	//ゲッターで数値を変数に代入
	//横と縦のマップチップの数を持ってくる
	int mapXNum = map.getMapXNum();
	int mapYNum = map.getMapYNum();
	//プレイヤーの座標を持ってくる
	VECTOR playerPos = player.GetPos();
	//マップデータを持ってくる
	int** mapData = map.getMapData();
	VECTOR mapPos = map.getMapPos();



	VECTOR ret = velocity;

	// 当たらなくなるまで繰り返す
	bool loop = true;
	bool isFirstHit = true;	// 初回で当たったか
	while (loop)
	{
		loop = false;

		// 未来のプレイヤーのポジションをまず出す
		VECTOR futurePos = VAdd(playerPos, ret);

		// 全マップチップ分繰り返す
		for (int hIndex = 0; hIndex <mapYNum; hIndex++)
		{
			bool isHit = false;
			for (int wIndex = 0; wIndex < mapXNum; wIndex++)
			{
				//マップのx座標を
				VECTOR mapPos = map.getMapPos();
				//マップチップそれぞれの座標を取得
				VECTOR mapChipPos = VGet(Map::CHIP_SIZE * wIndex+mapPos.x, Map::CHIP_SIZE * hIndex, 0);
				//マップチップとプレイヤーの当たり判定をみる
				isHit = IsHitPlayerWithMapChip(player, futurePos, mapData[hIndex][wIndex],mapChipPos);

				// 初回に当たったとき
				if (isHit && isFirstHit)
				{
					// 今後当たり判定でポジションやvelocityの補正をするとき、小数点以下の誤差が産まれる
					// 雑に1ドットずつ減らす、数学計算をしないマッシブ当たり判定には邪魔なので初回に丸めてしまい、
					// 以降改めて当たり判定
					// posもVelocityも丸める
					playerPos.x = floorf(playerPos.x);		//floorfは小数点を丸める
					playerPos.y = floorf(playerPos.y);
					player.SetPos(playerPos);
					ret.x = floorf(ret.x);
					ret.y = floorf(ret.y);
					isFirstHit = false;
					loop = true;	// ループ継続
				}

				// 当たった時点でマップチップのループからぬけるが、当たらなくなるまで繰り返すループは継続
				if (isHit && !isFirstHit)
				{
					// HACK: 当たっていた場合にvelocityを1ドットずつ縮めていき、当たらなくなるまで繰り返す
					// そのまま縮めてしまうと、斜めのベクトルのとき（例えば壁に向かってジャンプしたとき）にジャンプの勢いも縮めてしまう
					// これを防ぐために、
					// 横成分から縮めていくことで、問題を回避する
					float absX = fabsf(ret.x);	// velocityのx成分の絶対値
					float absY = fabsf(ret.y);	// velocityのy成分の絶対値

					// x成分を縮め切っていなければx成分を縮める
					bool shrinkX = (absX != 0.0f);	// x成分を縮めるかどうか

					if (shrinkX)
					{
						if (ret.x > 0.0f)
						{
							ret.x -= 1.0f;
						}
						else
						{
							ret.x += 1.0f;
						}

						// 縮め切ったら消す
						if (fabs(ret.x) < 1.0f)
						{
							ret.x = 0.0f;
						}
						loop = true;
					}
					else
					{
						if (ret.y > 0.0f)
						{
							ret.y -= 1.0f;
						}
						else
						{
							ret.y += 1.0f;
						}

						// 縮め切ったら消す
						if (fabs(ret.y) < 1.0f)
						{
							ret.y = 0.0f;
						}
						loop = true;
					}
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
	}

	// MEMO: 超高速で移動してマップ突き抜けた場合は考慮していない
	// MEMO: 処理負荷を少しでも減らすために、マップチップとプレイヤーの距離でいったん計算除外するとか、色々するのはアリ

	return ret;
}

/// <summary>
/// プレイヤーとマップが当たったかのチェック
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="futurePos">移動後を計算した後の座標</param>
/// <param name="mapData">どんなマップチップか</param>
/// <returns>当たったかのフラグ</returns>
bool PlayerColision::IsHitPlayerWithMapChip(const Player& player, const  VECTOR& futurePos, int mapData,VECTOR mapChipPos)
{
	// マップチップが当たらない種類なら早期return
	if (mapData == -1)
	{
		return false;
	}

	// 当たっているかどうか調べる
	//幅と高さを半分にして中心座標を求める
	float futurePosLeft = futurePos.x - Player::PLAYER_W * 0.5f;
	float futurePosRight = futurePos.x + Player::PLAYER_W * 0.5f;
	float futurePosTop = futurePos.y - Player::PLAYER_H * 0.5f;
	float futurePosBottom = futurePos.y + Player::PLAYER_H * 0.5f;
	float targetLeft = mapChipPos.x - Map::CHIP_SIZE * 0.5f;
	float targetRight = mapChipPos.x + Map::CHIP_SIZE * 0.5f;
	float targetTop = mapChipPos.y - Map::CHIP_SIZE * 0.5f;
	float targetBottom = mapChipPos.y + Map::CHIP_SIZE * 0.5f;
	// 矩形同士の当たり判定
	if (((targetLeft <= futurePosLeft && futurePosLeft < targetRight) ||
		(targetLeft > futurePosLeft && targetLeft < futurePosRight)) &&
		((targetTop <= futurePosTop && futurePosTop < targetBottom) ||
			(targetTop > futurePosTop && targetTop < futurePosBottom)))
	{
		return true;
	}
	return false;
}

/// <summary>
/// 接地いた場合の処理
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="map">マップ</param>
void PlayerColision::CheckIsGround(Player& player, const  Map& map)
{
	//ゲッターで必要な値を持ってくる
	VECTOR playerPos = player.GetPos();
	//横と縦のマップチップの数を持ってくる
	int mapXnum = map.getMapXNum();
	int mapYNum = map.getMapYNum();
	//マップデータを持ってくる
	int** mapData = map.getMapData();
	VECTOR mapPos = map.getMapPos();


	// 1ドット下にずらして当たれば地面に足がぶつかっている （小数点無視）
	auto checkPos = VGet(playerPos.x, floorf(playerPos.y) + 1.0f, playerPos.z);
	bool isHit;
	// 全マップチップ分繰り返す
	for (int hIndex = 0; hIndex < mapYNum; hIndex++)
	{
		for (int wIndex = 0; wIndex < mapXnum; wIndex++)
		{
			//マップチップそれぞれの座標を取得
			VECTOR mapChipPos = VGet(Map::CHIP_SIZE * wIndex+ mapPos.x, Map::CHIP_SIZE * hIndex, 0);
			//if (isHit == false)
			//{
			isHit = IsHitPlayerWithMapChip(player, checkPos, mapData[hIndex][wIndex],mapChipPos);
			//}
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			break;
		}
	}
	if (isHit)
	{
		//接地判定をtrueにする
		player.SetIsGround(true);
		// fallSpeedをゼロにし、急激な落下を防ぐ
		player.SetFallSpeed(0.0f);

		// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
		playerPos.y = floorf(playerPos.y);	// ちょうど地面に付く位置に
	}
	else
	{
		player.SetIsGround(false);
	}
}

/// <summary>
/// 天井に当たっていた場合の処理
/// </summary>
/// <param name="player">プレイヤー</param>
/// <param name="map">マップ</param>
void PlayerColision::CheckIsTopHit(Player& player, const  Map& map)
{
	//ゲッターで必要な値を持ってくる
	VECTOR playerPos = player.GetPos();
	//横と縦のマップチップの数を持ってくる
	int mapXnum = map.getMapXNum();
	int mapYNum = map.getMapYNum();
	//マップデータを持ってくる
	int** mapData = map.getMapData();
	VECTOR mapPos = map.getMapPos();


	// 1ドット上にずらして当たれば頭上がぶつかっている （小数点無視）
	auto checkPos = VGet(playerPos.x, floorf(playerPos.y) - 1.0f, playerPos.z);
	bool isHit;
	//マップのx座標を
	for (int hIndex = 0; hIndex < mapYNum; hIndex++)
	{
		for (int wIndex = 0; wIndex < mapXnum; wIndex++)
		{
			//マップチップそれぞれの座標を取得
			VECTOR mapChipPos = VGet(Map::CHIP_SIZE * wIndex+mapPos.x, Map::CHIP_SIZE * hIndex, 0);
			isHit = IsHitPlayerWithMapChip(player, checkPos, mapData[hIndex][wIndex], mapChipPos);
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			break;
		}
	}
	if (isHit)
	{
		//天井にぶつかっていたかのフラグを持ってくる
		bool inIsHitTop = player.GetIsHitTop();
		// 以前ぶつかっていないのにぶつかるならfallSpeedをゼロにし、即落下するように
		if (!inIsHitTop)
		{
			player.SetIsHitTop(true);
			player.SetFallSpeed(0.0f);

			// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
			playerPos.y = floorf(playerPos.y);
		}
	}
	else
	{
		player.SetIsHitTop(false);
	}
}



/// <summary>
/// エネミーの当たり判定をとった後の押し戻し処理
/// </summary>
/// <param name="enemy">エネミーのインスタンス</param>
/// <param name="map">マップのインスタンス</param>
/// <param name="velocity">エネミーの移動方向</param>
/// <returns>押し戻した際の移動量</returns>
VECTOR EnemyColision::CheckEnemyHitWithMap(BaseEnemy& enemy, const Map& map, const VECTOR& velocity)
{
	// サイズが最初から0なら動かさず早期return
	if (VSize(velocity) == 0)		//VSizeでベクトルのサイズをとっている0なら動いてないなのでここで返す
	{
		return velocity;
	}
	//ゲッターで数値を変数に代入
	//横と縦のマップチップの数を持ってくる
	int mapXNum = map.getMapXNum();
	int mapYNum = map.getMapYNum();
	//エネミーの座標を持ってくる
	VECTOR enemyPos = enemy.GetPos();
	//マップデータを持ってくる
	int** mapData = map.getMapData();
	VECTOR mapPos = map.getMapPos();



	VECTOR ret = velocity;

	// 当たらなくなるまで繰り返す
	bool loop = true;
	bool isFirstHit = true;	// 初回で当たったか
	while (loop)
	{
		loop = false;

		// 未来のプレイヤーのポジションをまず出す
		VECTOR futurePos = VAdd(enemyPos, ret);

		// 全マップチップ分繰り返す
		for (int hIndex = 0; hIndex < mapYNum; hIndex++)
		{
			bool isHit = false;
			for (int wIndex = 0; wIndex < mapXNum; wIndex++)
			{
				//マップのx座標を
				VECTOR mapPos = map.getMapPos();
				//マップチップそれぞれの座標を取得
				VECTOR mapChipPos = VGet(Map::CHIP_SIZE * wIndex + mapPos.x, Map::CHIP_SIZE * hIndex, 0);
				//マップチップとプレイヤーの当たり判定をみる
				isHit = IsHitEnemyWithMapChip(enemy, futurePos, mapData[hIndex][wIndex], mapChipPos);

				// 初回に当たったとき
				if (isHit && isFirstHit)
				{
					// 今後当たり判定でポジションやvelocityの補正をするとき、小数点以下の誤差が産まれる
					// 雑に1ドットずつ減らす、数学計算をしないマッシブ当たり判定には邪魔なので初回に丸めてしまい、
					// 以降改めて当たり判定
					// posもVelocityも丸める
					enemyPos.x = floorf(enemyPos.x);		//floorfは小数点を丸める
					enemyPos.y = floorf(enemyPos.y);
					enemy.SetPos(enemyPos);
					ret.x = floorf(ret.x);
					ret.y = floorf(ret.y);
					isFirstHit = false;
					loop = true;	// ループ継続
				}

				// 当たった時点でマップチップのループからぬけるが、当たらなくなるまで繰り返すループは継続
				if (isHit && !isFirstHit)
				{
					// HACK: 当たっていた場合にvelocityを1ドットずつ縮めていき、当たらなくなるまで繰り返す
					// そのまま縮めてしまうと、斜めのベクトルのとき（例えば壁に向かってジャンプしたとき）にジャンプの勢いも縮めてしまう
					// これを防ぐために、
					// 横成分から縮めていくことで、問題を回避する
					float absX = fabsf(ret.x);	// velocityのx成分の絶対値
					float absY = fabsf(ret.y);	// velocityのy成分の絶対値

					// x成分を縮め切っていなければx成分を縮める
					bool shrinkX = (absX != 0.0f);	// x成分を縮めるかどうか

					if (shrinkX)
					{
						if (ret.x > 0.0f)
						{
							ret.x -= 1.0f;
						}
						else
						{
							ret.x += 1.0f;
						}

						// 縮め切ったら消す
						if (fabs(ret.x) < 1.0f)
						{
							ret.x = 0.0f;
						}
						loop = true;
					}
					else
					{
						if (ret.y > 0.0f)
						{
							ret.y -= 1.0f;
						}
						else
						{
							ret.y += 1.0f;
						}

						// 縮め切ったら消す
						if (fabs(ret.y) < 1.0f)
						{
							ret.y = 0.0f;
						}
						loop = true;
					}
					break;
				}
			}
			if (isHit)
			{
				break;
			}
		}
	}

	// MEMO: 超高速で移動してマップ突き抜けた場合は考慮していない
	// MEMO: 処理負荷を少しでも減らすために、マップチップとプレイヤーの距離でいったん計算除外するとか、色々するのはアリ

	return ret;
}

bool EnemyColision::IsHitEnemyWithMapChip(const BaseEnemy& enemy, const  VECTOR& futurePos, int mapData, VECTOR mapChipPos)
{
	// マップチップが当たらない種類なら早期return
	if (mapData == -1)
	{
		return false;
	}
	//幅と高さの取得
	float enemyW = enemy.GetW();
	float enemyH = enemy.GetH();

	// 当たっているかどうか調べる
	//幅と高さを半分にして中心座標を求める
	float futurePosLeft = futurePos.x - enemyW * 0.5f;
	float futurePosRight = futurePos.x + enemyW * 0.5f;
	float futurePosTop = futurePos.y -  enemyH* 0.5f;
	float futurePosBottom = futurePos.y + enemyH * 0.5f;
	float targetLeft = mapChipPos.x - Map::CHIP_SIZE * 0.5f;
	float targetRight = mapChipPos.x + Map::CHIP_SIZE * 0.5f;
	float targetTop = mapChipPos.y - Map::CHIP_SIZE * 0.5f;
	float targetBottom = mapChipPos.y + Map::CHIP_SIZE * 0.5f;
	// 矩形同士の当たり判定
	if (((targetLeft <= futurePosLeft && futurePosLeft < targetRight) ||
		(targetLeft > futurePosLeft && targetLeft < futurePosRight)) &&
		((targetTop <= futurePosTop && futurePosTop < targetBottom) ||
			(targetTop > futurePosTop && targetTop < futurePosBottom)))
	{
		return true;
	}
	return false;
}

void EnemyColision::CheckIsGround(BaseEnemy& enemy, const  Map& map)
{
	//ゲッターで必要な値を持ってくる
	VECTOR enemyPos = enemy.GetPos();
	//横と縦のマップチップの数を持ってくる
	int mapXnum = map.getMapXNum();
	int mapYNum = map.getMapYNum();
	//マップデータを持ってくる
	int** mapData = map.getMapData();
	VECTOR mapPos = map.getMapPos();


	// 1ドット下にずらして当たれば地面に足がぶつかっている （小数点無視）
	auto checkPos = VGet(enemyPos.x, floorf(enemyPos.y) + 1.0f, enemyPos.z);
	bool isHit;
	// 全マップチップ分繰り返す
	for (int hIndex = 0; hIndex < mapYNum; hIndex++)
	{
		for (int wIndex = 0; wIndex < mapXnum; wIndex++)
		{
			//マップチップそれぞれの座標を取得
			VECTOR mapChipPos = VGet(Map::CHIP_SIZE * wIndex + mapPos.x, Map::CHIP_SIZE * hIndex, 0);
			//if (isHit == false)
			//{
			isHit = IsHitEnemyWithMapChip(enemy, checkPos, mapData[hIndex][wIndex], mapChipPos);
			//}
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			break;
		}
	}
	if (isHit)
	{
		//接地判定をtrueに
		enemy.SetIsGround(true);
		// fallSpeedをゼロにし、急激な落下を防ぐ
		enemy.SetFallSpeed(0.0f);

		// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
		enemyPos.y = floorf(enemyPos.y);	// ちょうど地面に付く位置に
	}
	else
	{
		enemy.SetIsGround(false);
	}
}

void EnemyColision::CheckIsTopHit(BaseEnemy& enemy, const  Map& map)
{
	//ゲッターで必要な値を持ってくる
	VECTOR enemyPos = enemy.GetPos();
	//横と縦のマップチップの数を持ってくる
	int mapXnum = map.getMapXNum();
	int mapYNum = map.getMapYNum();
	//マップデータを持ってくる
	int** mapData = map.getMapData();
	VECTOR mapPos = map.getMapPos();


	// 1ドット上にずらして当たれば頭上がぶつかっている （小数点無視）
	auto checkPos = VGet(enemyPos.x, floorf(enemyPos.y) - 1.0f, enemyPos.z);
	bool isHit;
	//マップのx座標を
	for (int hIndex = 0; hIndex < mapYNum; hIndex++)
	{
		for (int wIndex = 0; wIndex < mapXnum; wIndex++)
		{
			//マップチップそれぞれの座標を取得
			VECTOR mapChipPos = VGet(Map::CHIP_SIZE * wIndex + mapPos.x, Map::CHIP_SIZE * hIndex, 0);
			isHit = IsHitEnemyWithMapChip(enemy, checkPos, mapData[hIndex][wIndex], mapChipPos);
			if (isHit)
			{
				break;
			}
		}
		if (isHit)
		{
			break;
		}
	}
	if (isHit)
	{
		//天井にぶつかっていたかのフラグを持ってくる
		bool inIsHitTop = enemy.GetIsHitTop();
		// 以前ぶつかっていないのにぶつかるならfallSpeedをゼロにし、即落下するように
		if (!inIsHitTop)
		{
			enemy.SetIsHitTop(true);
			enemy.SetFallSpeed(0.0f);

			// 後々の雑計算に響くので、y座標の小数点を消し飛ばす
			enemyPos.y = floorf(enemyPos.y);
		}
	}
	else
	{
		enemy.SetIsHitTop(false);
	}
}














