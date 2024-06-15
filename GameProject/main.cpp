#include"DxLib.h"
#include"SceneManager.h"
#include"Utility.h"
#include"Camera.h"
#include"Effect.h"
#include"Game.h"
#include"EffekseerForDXLib.h"

//----------------------------//
// WinMain関数.
//----------------------------//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// 画面モードの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16);		// 解像度をSCREEN_W*SCREEN_H、colorを16bitに設定.




	/////////////////////////////////
	// ウインドウモードに(コメントアウトしたらフルスクリーン).
	ChangeWindowMode(TRUE);
	////////////////////////////



		// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);
	//エフェクトの初期設定
	if (Effect::Setting() == -1)
	{
		DxLib_End();
		return -1;
	}

    SceneManager* sceneManager = new SceneManager();

	// 画面を初期化(真っ黒にする)
	SetCameraNearFar(10.0f, 500.0f);	//nearとfarの設定

    //ゲームループ
    sceneManager->GameLoop();		


	// Effekseerを終了する。
	Effkseer_End();
    //シーンマネージャーの解放
    delete sceneManager;

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}
