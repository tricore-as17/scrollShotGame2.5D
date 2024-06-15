#pragma once
#include"SceneBase.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene:public SceneBase
{
public:
    GameScene();
    ~GameScene();


    void Update()override;

    void Draw() override;

};

