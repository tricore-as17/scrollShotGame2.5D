#pragma once
#include"DxLib.h"

/// <summary>
/// 背景クラス
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

    int domeModelHandle;        //描画する背景用のスカイドームのハンドル

};

