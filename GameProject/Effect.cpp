#include"EffekseerForDXLib.h"
#include"Effect.h"

//コンストラクタ
Effect::Effect(const char* fileName) :playTime(0), pos(VGet(0.0f, 0.0f, 0.0f)), playFlag(false), playHandle(-1)
{
	//ハンドルの読み込み
	handle = LoadEffekseerEffect(fileName, 1.5f);
}
//デストラクタ
Effect::~Effect()
{
	//エフェクトリソースの削除
	DeleteEffekseerEffect(handle);
}

/// <summary>
/// エフェクトを表示する時の初期設定
/// </summary>
/// <returns>初期化が成功したかの判定</returns>
int Effect::Setting()
{
	//Effekseerをしようする際にDirectX11を使えるようにする必要がある
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	//Effekseerの初期化
	if (Effekseer_Init(8000) == -1)
	{
		return -1;
	}

	// フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
	// Effekseerを使用する場合は必ず設定する。
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DXライブラリのデバイスロストした時のコールバックを設定する。
	// ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
	// 切り替えは行わないが一応セッティング
	// ただし、DirectX11を使用する場合は実行する必要はない。
	//Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);
	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);
	return 0;
}
