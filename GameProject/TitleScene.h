#pragma once

class SceneBase;

/// <summary>
/// タイトのシーン
/// </summary>
class TitleScene:public SceneBase
{
public:
    //コンストラクタ
    TitleScene();
    //デストラクタ
    ~TitleScene();
    /// <summary>
    /// 更新処理
    /// </summary>
    void Update() override;
    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;
private:

    InputManager* inputManager;         //入力に関する処理をまとめたもの


};

