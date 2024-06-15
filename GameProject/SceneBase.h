#pragma once

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
    /// Updateの純粋仮想関数
    /// </summary>
    virtual void Update()abstract;

    virtual void Draw() = 0;

    SceneBase* inputScene;      //次のループでのシーンを入れる変数


};

