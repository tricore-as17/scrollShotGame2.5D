﻿#pragma once
#include"DxLib.h"
#include<list>


//クラスのプロトタイプ宣言
class SceneBase;

class SceneManager
{
public:
    //コンストラクト
    SceneManager();
    //デストラクタ
    ~SceneManager();

    /// <summary>
    /// ゲームループをまわす処理
    /// </summary>
    void GameLoop();

    /// <summary>
    /// ゲームを継続するかの判断
    /// </summary>
    /// <returns>継続するかのフラグ</returns>
    bool IsContinueGame();


private:

    /// <summary>
    /// 現在のシーンを削除して次のシーンのポインタを入れる
    /// </summary>
    void SceneChange();

    SceneBase* nowScene;        //現在のループでのシーンを保存するポインタ
    SceneBase* nextScene;       //次のループでのシーンを保存するポインタ
    


  
};

