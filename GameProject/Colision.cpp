#include"DxLib.h"
#include"Colision.h"
#include"GameObject.h"
#include"Shot.h"
#include"Map.h"



/// <summary>
/// 矩形同士の当たり判定
/// </summary>
/// <param name="pos1">矩形１の座標</param>
/// <param name="w1">矩形１の幅</param>
/// <param name="h1">矩形１の高さ</param>
/// <param name="pos2">矩形２の座標</param>
/// <param name="w2">矩形２の幅</param>
/// <param name="h2">矩形２の高さ</param>
/// <returns>当たったかの判定結果</returns>
bool Colision::IsHitRectangles(const VECTOR& pos1, float w1, float h1, const VECTOR& pos2, float w2, float h2)
{
    bool isHit = false;
        //幅と高さを半分にして中心座標を求める
    float pos1Left = pos1.x - w1 * 0.5f;
    float pos1Right = pos1.x + w1 * 0.5f;
    float pos1Top = pos1.y - h1 * 0.5f;
    float pos1Bottom = pos1.y + h1 * 0.5f;
    float pos2Left = pos2.x - w2 * 0.5f;
    float pos2Right = pos2.x + w2 * 0.5f;
    float pos2Top = pos2.y - h2 * 0.5f;
    float pos2Bottom = pos2.y + h2 * 0.5f;

    // 矩形同士の当たり判定
    if (((pos2Left <= pos1Left && pos1Left < pos2Right) ||
        (pos2Left > pos1Left && pos2Left < pos1Right)) &&
        ((pos2Top <= pos1Top && pos1Top < pos2Bottom) ||
            (pos2Top > pos1Top && pos2Top < pos1Bottom)))
    {
        isHit = true;
    }
    else
    {
        isHit = false;
    }
    return isHit;
    
}

/// <summary>
/// 矩形と円の当たり判定
/// </summary>
/// <param name="rectPos">矩形の座標</param>
/// <param name="rectW">矩形の幅</param>
/// <param name="rectH">矩形の高さ</param>
/// <param name="circlePos">円の中心座標</param>
/// <param name="circleR">円の半径</param>
/// <returns>当たったかの判定結果</returns>
bool Colision::IsHitCircleWithRectangles(const VECTOR& rectPos, const float rectW, const float rectH, const VECTOR& circlePos, const float circleR)
{
    //当たったかのフラグ
    bool isHit = false;
    //矩形の4つの頂点を出す
    float left = rectPos.x - rectW * 0.5f;      //左
    float right = rectPos.x + rectW * 0.5f;     //右
    float top = rectPos.y + rectH * 0.5f;       //上
    float bottom = rectPos.y - rectH * 0.5f;    //下

    //四角形の四辺に対して円の半径分だけ足したとき円が重なっていたら
    //大雑把に当たったかを判定できる
    if ((circlePos.x > left - circleR)&&
        (circlePos.x < right + circleR)&&
        (circlePos.y < top + circleR)&&
        (circlePos.y > bottom - circleR))
    {

        isHit = true;
        //半径を2乗した値を出す(矩形との距離を図るときに平方根を使わないようにするため
        float circleSquareR = circleR * circleR;
        //矩形のそれぞれの頂点と円の中心座標が半径より離れていないか調べて判定する
        if (circlePos.x < left)
        {
            //左上
            if (circlePos.y > top)
            {

                if (DistanceSquare(left,top,circlePos.x,circlePos.y) >= circleSquareR)
                {
                    isHit = false;
                }
            }
            //左下
            else
            {
                if (circlePos.y < bottom)
                {
                    if (DistanceSquare(left, bottom, circlePos.x, circlePos.y) >= circleSquareR)
                    {
                        isHit = false;
                    }
                }
            }
        }
        else
        {
            //右上
            if (circlePos.y > top)
            {

                if (DistanceSquare(right, top, circlePos.x, circlePos.y) >= circleSquareR)
                {
                    isHit = false;
                }
            }
            //左下
            else
            {
                if (circlePos.y < bottom)
                {
                    if (DistanceSquare(right, bottom, circlePos.x, circlePos.y) >= circleSquareR)
                    {
                        isHit = false;
                    }
                }
            }
        }
    }
    return isHit;


}

/// <summary>
/// マップとプレイヤーやエネミーの当たり判定
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="velocity">プレイヤーなどのベクトル</param>
/// <param name="pos">動かす前の座標</param>
/// <param name="w">オブジェクトの幅</param>
/// <param name="h">オブジェクトの高さ</param>
/// <returns>調節したベクトル</returns>
VECTOR Colision::CheckHitMapAdjustmentVector(const Map& map, VECTOR velocity, const VECTOR& pos,const float w,const float h)
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
    //マップデータを持ってくる
    int** mapData = map.getMapData();
    VECTOR mapLeftPos = map.GetChipLeftPos();


    VECTOR ret = velocity;

    // 当たらなくなるまで繰り返す
    bool loop = true;
    bool isFirstHit = true;	// 初回で当たったか
    while (loop)
    {
        loop = false;

        // ベクトルを足した際の未来ポジションをまず出す
        VECTOR futurePos = VAdd(pos, ret);

        // 全マップチップ分繰り返す
        for (int hIndex = 0; hIndex < mapYNum; hIndex++)
        {
            bool isHit = false;
            for (int wIndex = 0; wIndex < mapXNum; wIndex++)
            {
                //マップチップそれぞれの座標を取得
                VECTOR mapChipPos = VAdd(VGet(Map::CHIP_SIZE * wIndex + mapLeftPos.x, Map::CHIP_SIZE * (-hIndex - 1) + mapLeftPos.y, 0), Map::CHIP_HALF_OFFSET);
                if (mapData[hIndex][wIndex] == Map::BLANK_CHIP_NUMBER)
                {
                    isHit = false;
                }
                else
                {
                    //オブジェクトとマップの当たり判定をみる
                    isHit =IsHitRectangles(futurePos, w,h, mapChipPos,Map::CHIP_SIZE,Map::CHIP_SIZE);
                }

                // 初回に当たったとき
                if (isHit && isFirstHit)
                {

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
                            ret.x -= Map::ONE_PIXEL_SIZE;
                        }
                        else
                        {
                            ret.x += Map::ONE_PIXEL_SIZE;
                        }

                        // 縮め切ったら消す
                        if (fabs(ret.x) < Map::ONE_PIXEL_SIZE)
                        {
                            ret.x = 0.0f;
                        }
                        loop = true;
                    }
                    else
                    {
                        if (ret.y > 0.0f)
                        {
                            ret.y -= Map::ONE_PIXEL_SIZE;
                        }
                        else
                        {
                            ret.y += Map::ONE_PIXEL_SIZE;
                        }

                        // 縮め切ったら消す
                        if (fabs(ret.y) < Map::ONE_PIXEL_SIZE)
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

bool Colision::IsGround(const Map& map, const VECTOR& objectPos,const float objectW,const float objectH,float& fallSpeed)
{
    //接地判定用のフラグ
    bool isGround = false;
    //横と縦のマップチップの数を持ってくる
    int mapXnum = map.getMapXNum();
    int mapYNum = map.getMapYNum();
    //マップデータを持ってくる
    int** mapData = map.getMapData();
    VECTOR mapLeftPos = map.GetChipLeftPos();


    // 1ドット下にずらして当たれば地面に足がぶつかっている 
    auto checkPos = VGet(objectPos.x, objectPos.y - Map::ONE_PIXEL_SIZE, objectPos.z);
    bool isHit;
    // 全マップチップ分繰り返す
    for (int hIndex = 0; hIndex < mapYNum; hIndex++)
    {
        for (int wIndex = 0; wIndex < mapXnum; wIndex++)
        {
            //マップチップそれぞれの座標を取得
            VECTOR mapChipPos = VAdd(VGet(Map::CHIP_SIZE * wIndex + mapLeftPos.x, Map::CHIP_SIZE * (-hIndex - 1) + mapLeftPos.y, 0), Map::CHIP_HALF_OFFSET);

            if (mapData[hIndex][wIndex] == Map::BLANK_CHIP_NUMBER)
            {
                isHit = false;
            }
            else
            {
                isHit = IsHitRectangles(checkPos, objectW,objectH, mapChipPos,Map::CHIP_SIZE,Map::CHIP_SIZE);
            }

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
        isGround = true;
        // fallSpeedをゼロにし、急激な落下を防ぐ
        fallSpeed = 0.0f;
    }
    else
    {
        isGround = false;
    }
    return isGround;
}

/// <summary>
/// 天井に頭がぶつかっているか
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="objectPos">調べるオブジェクトの座標</param>
/// <param name="objectW">オブジェクトの幅</param>
/// <param name="objectH">オブジェクトの高さ</param>
/// <param name="fallSpeed">オブジェクトの落下速度</param>
/// <returns>当たっているか</returns>
bool Colision::IsTopHit(const Map& map, const VECTOR& objectPos, const float objectW, const float objectH, float& fallSpeed)
{
    //天井への接触判定用フラグ
    bool isTopHit = false;
    //横と縦のマップチップの数を持ってくる
    int mapXnum = map.getMapXNum();
    int mapYNum = map.getMapYNum();
    //マップデータを持ってくる
    int** mapData = map.getMapData();
    VECTOR mapLeftPos = map.GetChipLeftPos();

    // 1ドット上にずらして当たっていれば天井にぶつかっている
    auto checkPos = VGet(objectPos.x, objectPos.y + Map::ONE_PIXEL_SIZE, objectPos.z);
    bool isHit;
    // 全マップチップ分繰り返す
    for (int hIndex = 0; hIndex < mapYNum; hIndex++)
    {
        for (int wIndex = 0; wIndex < mapXnum; wIndex++)
        {
            //マップチップそれぞれの座標を取得
            VECTOR mapChipPos = VAdd(VGet(Map::CHIP_SIZE * wIndex + mapLeftPos.x, Map::CHIP_SIZE * (-hIndex - 1) + mapLeftPos.y, 0), Map::CHIP_HALF_OFFSET);

            if (mapData[hIndex][wIndex] == Map::BLANK_CHIP_NUMBER)
            {
                isHit = false;
            }
            else
            {
                isHit = IsHitRectangles(checkPos, objectW, objectH, mapChipPos, Map::CHIP_SIZE, Map::CHIP_SIZE);
            }

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
        isTopHit = true;
        // fallSpeedをゼロにし、急激な落下を防ぐ
        fallSpeed = 0.0f;
    }
    else
    {
        isTopHit = false;
    }
    return isTopHit;
}

/// <summary>
/// 二点間の距離を出す
/// </summary>
/// <param name="x1">点１のx</param>
/// <param name="y1">点１のｙ</param>
/// <param name="x2">点２のｘ</param>
/// <param name="y2">点２のｙ</param>
/// <returns>二点間の距離</returns>
float Colision::DistanceSquare(const float x1, const float y1, const float x2, const float y2)
{
    //x,yそれぞれの長さを出す
    float distanceX = x2 - x1;
    float distanceY = y2 - y1;

    //２乗して足した値を出す
    return (distanceX * distanceX) + (distanceY * distanceY);
}

/// <summary>
/// 弾とオブジェクトとの接触判定(オブジェクトはプレイヤーやエネミー)
/// </summary>
/// <param name="shot">弾のベクター配列</param>
/// <param name="objectPos">オブジェクトの座標</param>
/// <param name="objectW">オブジェクトの幅</param>
/// <param name="objectH">オブジェクトの高さ</param>
/// <param name="objectLife">オブジェクトの体力</param>
/// <param name="objectKind">オブジェクトの種類(誰が発射した弾か)</param>
void Colision::ColisionShot(vector<Shot*> shot, const VECTOR& objectPos, const float objectW, const float objectH,int& objectLife,const int objectKind)
{
    for (int i = 0; i < shot.size(); i++)
    {
        bool isHit = false;
        if (shot[i]->GetSurvivalFlag())
        {
            //自分の弾じゃないかを確認する
            if (shot[i]->Getkinds() !=objectKind)
            {
                //ショットとオブジェクトが当たったかを判定する
                isHit=IsHitCircleWithRectangles(objectPos, objectW, objectH, shot[i]->GetPos(), shot[i]->GetRadius());
            }
        }
        //弾に当たっていたら弾の生存フラグをfalseにするのと体力を減らす
        if (isHit)
        {
            shot[i]->SetSurvivalFlag(false);
            objectLife -= shot[i]->GetDamage();
        }

    }
}














