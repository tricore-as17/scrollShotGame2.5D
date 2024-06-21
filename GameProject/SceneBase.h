#pragma once
#include"InputManager.h"
#include"Font.h"

/// <summary>
/// それぞれのシーンで継承する基底クラス
/// </summary>
class SceneBase abstract
{
public:

    /// <summary>
    /// 次のシーンベースを返す
    /// </summary>
    /// <returns></returns>
    SceneBase* GetNextScene(){ return inputScene; }
    /// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="inputManager">入力管理クラス</param>
    virtual void Update(InputManager* inputManager)abstract;

    virtual void Draw() abstract;

    SceneBase* inputScene;      //次のループでのシーンを入れる変数


};

