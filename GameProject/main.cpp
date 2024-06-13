#include"DxLib.h"
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
	SetGraphMode(SCREEN_W, SCREEN_H, 16);		// 解像度をSCREEN_W*SCREEN_H、colorを16bitに設定.




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

	

	// 背景のスクロールをするためにテクスチャモードをラッピングに修正.
	//SetTextureAddressMode(DX_TEXADDRESS_WRAP);

	// グラフィックの描画先を裏画面にセット


	Utility::FpsInitialize();
	Game* game = new Game;

	game->Initialize();

	



	// ゲームループ.
	while (1)
	{
		Utility::FpsUpdate();
		// 画面を初期化(真っ黒にする)
		SetCameraNearFar(10.0f, 500.0f);	//nearとfarの設定
		ClearDrawScreen();
		game->Update();
		game->Draw();

		SetUseZBuffer3D(TRUE);
		SetWriteZBuffer3D(TRUE);


		/*int nowTime = GetNowCount();
		DrawFormatString(600, 400, GetColor(255, 255, 255), "%d", nowTime);*/

		// 裏画面の内容を表画面にコピーする（描画の確定）.
		ScreenFlip();

		// Windows 特有の面倒な処理をＤＸライブラリにやらせる
		// マイナスの値（エラー値）が返ってきたらループを抜ける
		if (ProcessMessage() < 0)
		{
			break;
		}
		// もしＥＳＣキーが押されていたらループから抜ける
		else if ( CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
		//ここでFPSの調整
		Utility::FpsControll();
		
	};
	//gameFinalize(game);
	// Effekseerを終了する。
	Effkseer_End();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;					// ソフトの終了
}
