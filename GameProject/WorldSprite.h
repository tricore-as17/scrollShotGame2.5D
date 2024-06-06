#pragma once

/// <summary>
/// 3D座標空間にスプライトを表示する仕組み（ピボットは中心固定、画像のgraphは外で管理）
/// </summary>
class WorldSprite
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="textureGraph">テクスチャの画像ハンドル</param>
	/// <param name="chipPixelSize">スプライトの１チップのピクセルサイズ</param>
	/// <param name="spriteNo">スプライト番号</param>
	void Initialize(int textureGraph, int chipPixelSize, int spriteNo);
	/// <summary>
	/// サイズとポジションに応じて４頂点分の頂点位置を調整
	/// </summary>
	/// <param name="pos">ポジション</param>
	/// <param name="chipSize">配置するワールドスプライトのサイズ</param>
	void SetTransform(const VECTOR& pos, float spriteSize);
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//ゲッター
	const VECTOR& GetPos()const { return pos; }

private:
	int			textureGraph;	// スプライトを作成する元テクスチャのグラフィックハンドル
	VECTOR		pos;			// 描画ポジション
	VERTEX3D	Vertex[4];		// 頂点バッファ
	WORD		Index[6];		// インデックスバッファ
};
