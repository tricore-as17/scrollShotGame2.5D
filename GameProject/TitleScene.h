#pragma once

class SceneBase;
class InputManager;

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
    /// <param name="inputManager">入力管理クラス</param>
    void Update(InputManager* inputManager) override;
    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw() override;
private:



};

