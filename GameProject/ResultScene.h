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
    /// <param name="inputManager">入力管理クラス</param>
    void Update(InputManager* inputManager) override;
    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;
private:
};

