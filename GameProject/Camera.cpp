#include"Camera.h"
#include"Map.h"
#include"Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
    :isMoveStop(false)
{
    //奥行0.1～1000までをカメラの描画範囲とする
    SetCameraNearFar(0.1f, 1000.0f);
    //座標の初期化
    position = VGet(0, 0, 0);
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
    //処理なし
}

/// <summary>
/// ゲーム開始ごとの初期化
/// </summary>
void Camera::Initialize()
{
    //座標の初期化
    position = VGet(0, 0, 0);

}

/// <summary>
/// カメラをプレイヤーの位置やマップの位置に合わせて更新する
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="player">プレイヤのインスタンス</param>
void Camera::Update(const Map& map, const Player& player)
{
    if (isMoveStop)
    {
        return;
    }
    //プレイヤーとマップの座標を持ってくる
    VECTOR playerPosition = player.GetPosition();
    int mapYNum = map.getMapYNum();

    // 大きさ0.5のマップチップを、マップYの数だけ配置する
    // プレイヤーの地面のY位置を0としたいので、地上部のマップチップの数は二つ減らした位置で調整
    // その真ん中に表示するので半分を計算で出す
    // プレイヤーのX座標には追従したいのでplayerのXを使う
    VECTOR cameraPosition = VGet(playerPosition.x, Map::CHIP_SIZE * (mapYNum - 2) * 0.5f, playerPosition.z - 15.0f);


    // 注視する視点は、カメラと平行にまっすぐz=0地点
    VECTOR lookPosition = VGet(cameraPosition.x, cameraPosition.y, 0.0f);

    position = cameraPosition;

    // カメラに位置を反映.
    SetCameraPositionAndTarget_UpVecY(position, lookPosition);
    
}

/// <summary>
/// カメラの移動を止める
/// </summary>
void Camera::StopCameraMove()
{
    //止めるフラグを立てる
    isMoveStop = true;
}
