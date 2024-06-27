#pragma once


/// <summary>
/// 背景用のクラス
/// </summary>
class BackGround
{
public:
    //コンストラクタ
    BackGround();
    //デストラクタ
    virtual ~BackGround();
    /// <summary>
    /// 描画
    /// </summary>
    void Draw();
private:
    //定数
    static constexpr int SKY_IMAGE_SIZE   = 500;   //空画像の大きさ
    static constexpr int ANDER_CLOUD_SIZE = 300;   //下にある雲の大きさ
    static constexpr int CLOUD_SIZE       = 550;   //上に描画される雲の画像
    static constexpr int FOREST_SIZE      = 340;   //奥の森の画像のサイズ
    static constexpr int WOOD_SIZE        = 300;   //手前の木のサイズ

    //メンバ変数
    //画像ハンドル
    int cloudImage;             //雲の画像
    int anderCloudImage;        //下の方にある雲の画像
    int woodImage;              //木の画像
    int forestImage;            //森の画像
    int skyImage;               //青い空の画像
    //座標
    VECTOR skyPosition;         //空画像の座標
    VECTOR anderCloudPosition;  //下の方に置く空の画像
    VECTOR cloudPoaition;       //雲の画像の座標
    VECTOR forestPosition;      //奥の森の座標
    VECTOR woodPosition;        //手前の木の座標
};
