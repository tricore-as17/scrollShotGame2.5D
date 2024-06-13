#include"DxLib.h"
#include"WorldSprite.h"

/// <summary>
/// 初期化
/// </summary>
/// <param name="textureGraph">テクスチャの画像ハンドル</param>
/// <param name="chipPixelSize">スプライトの１チップのピクセルサイズ</param>
/// <param name="spriteNo">スプライト番号</param>
void WorldSprite::Initialize(int textureGraph, int chipPixelSize, int spriteNo)
{
    //マップのチップグラフをワールドスプライトのテクスチャグラフに代入
    this->textureGraph = textureGraph;

    // NOTE:初期化時に固定しているが、変更したければ自分で関数を追加する必要がある
    // ４頂点分のuvデータを設定
    int texW, texH;
    //チップグラフの縦方向と横方向のサイズをゲット
    GetGraphTextureSize(textureGraph, &texW, &texH);
    //幅から一つのサイズを割って数を出す
    //幅と高さは同じなので一つに
    int chipXNum = texW / chipPixelSize;
    int chipYNum = texH / chipPixelSize;
    //ここでdivgraphを手動で行っているみたいな感じ
    int chipNoX = spriteNo % chipXNum;       //列の指定
    int chipNoY = spriteNo / chipXNum;       //行の指定
    float oneChipUVXRate = 1.0f / (float)chipXNum;   // テクスチャ全部を1.0とした時のcihp一個に対するuvのサイズ
    float oneChipUVYRate = 1.0f / (float)chipYNum;
    //テクスチャの座標の設定
    // 0.0ならx1もしくはy1　//1.0ならx2もしくはy2
    //テクスチャを張る4つの座標＝この座標の列or行数+
    Vertex[0].u = (chipNoX + 0.0f) * oneChipUVXRate;     //チップの左上のx座標
    Vertex[0].v = (chipNoY + 0.0f) * oneChipUVYRate;     //チップの左上のY座標
    Vertex[1].u = (chipNoX + 1.0f) * oneChipUVXRate;     //チップの右上のx座標
    Vertex[1].v = (chipNoY + 0.0f) * oneChipUVYRate;     //チップの右上のy座標
    Vertex[2].u = (chipNoX + 0.0f) * oneChipUVXRate;     //チップの左下のx座標
    Vertex[2].v = (chipNoY + 1.0f) * oneChipUVYRate;     //チップの右上のy座標
    Vertex[3].u = (chipNoX + 1.0f) * oneChipUVXRate;     //チップの右下のx座標
    Vertex[3].v = (chipNoY + 1.0f) * oneChipUVYRate;     //チップの右下のy座標

    // ディフューズ、スペキュラは初期化時に固定(ここは気にしない)
    for (int i = 0; i < 4; i++)
    {
        Vertex[i].dif = GetColorU8(255, 255, 255, 255);
        Vertex[i].spc = GetColorU8(0, 0, 0, 0);
        Vertex[i].norm = VGet(0.0f, 0.0f, -1.0f);   // 回転をサポートしないのでノーマルも固定

        // 補助テクスチャをサポートしないのでuv固定
        Vertex[i].su = 0.0f;
        Vertex[i].sv = 0.0f;
    }

    // ２ポリゴン分のインデックスデータをセット
    Index[0] = 0;
    Index[1] = 1;
    Index[2] = 2;
    Index[3] = 3;
    Index[4] = 2;
    Index[5] = 1;
}

/// <summary>
/// サイズとポジションに応じて４頂点分の頂点位置を調整
/// </summary>
/// <param name="position">ポジション</param>
/// <param name="chipSize">配置するワールドスプライトのサイズ</param>
void WorldSprite::SetTransform(const VECTOR& position, float spriteSize)
{
    this->position = position;
    // ピボット中心で設定
    //spriteSizeは0.725
    //左上、右上、左下、右下に座標を設定
    Vertex[0].pos = VScale(VGet(-1.0f, 1.0f, 0.0f), spriteSize * 0.5f);
    Vertex[1].pos = VScale(VGet(1.0f, 1.0f, 0.0f), spriteSize * 0.5f);
    Vertex[2].pos = VScale(VGet(-1.0, -1.0f, 0.0f), spriteSize * 0.5f);
    Vertex[3].pos = VScale(VGet(1.0f, -1.0f, 0.0f), spriteSize * 0.5f);
    for (int i = 0; i < 4; i++)
    {
        Vertex[i].pos = VAdd(Vertex[i].pos, position);
    }
}

/// <summary>
/// 描画
/// </summary>
void WorldSprite::Draw()
{
    // ２ポリゴンの描画
    //4は頂点の数2がポリゴンの数
    DrawPolygonIndexed3D(Vertex, 4, Index, 2, textureGraph, TRUE);
}
