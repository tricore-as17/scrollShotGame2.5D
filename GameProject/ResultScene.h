#pragma once

class InputManager;

/// <summary>
/// ゲーム終了後の画面
/// </summary>
class ResultScene:public SceneBase
{
public:
    //コンストラクタ
    ResultScene();
    //デストラクタ
    ~ResultScene();
    /// <summary>
    /// 更新処理
    /// </summary>
    void Update() override;
    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;
private:
    InputManager* inputManager;
};

