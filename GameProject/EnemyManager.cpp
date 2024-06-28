#include"OneWayShotEnemy.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include"EnemyInformation.h"
#include"EasyEnemy.h"
#include"FallingAttackEnemy.h"
#include"BossEnemy.h"
#include"EnemyManager.h"
#include"ShotManager.h"
#include"Map.h"
#include"Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
EnemyManager::EnemyManager()
    :isBossActive(false)
{
    vector<EnemyInformation*> enemyInformation;
    //エネミーの初期化情報の入ったcsvファイルを読み込む
    enemyInformation = LoadEnemyInformation("Information/InitializeEnemy.csv");

    //読み込んだエネミーの数だけまわす
    for (const auto& information : enemyInformation)
    {
        //csvから読み込んだタイプと同じもののインスタンスを生成する
        if (information->type == EASY)
        {
            enemy.emplace_back(new EasyEnemy(information));
        }
        else if (information->type == ONE_WAY_SHOT)
        {
            enemy.emplace_back(new OneWayShotEnemy(information));
        }
        else if (information->type == FALLING_ATTACK)
        {
            enemy.emplace_back(new FallingAttackEnemy(information));
        }
        else if (information->type == BOSS)
        {
            enemy.emplace_back(new BossEnemy(information));
        }
    }
    //確保した初期化情報の入った中身を解放
    for (auto it : enemyInformation)
    {
        delete it;
    }
    enemyInformation.clear();
    
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyManager::~EnemyManager()
{
    //エネミーの要素を削除
    for (auto it : enemy)
    {
        delete it;
    }

    //それぞれのポインタが持ってる情報も削除
    enemy.clear();

    
}
/// <summary>
/// エネミー全体の更新処理
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="cameraPosition">カメラの座標</param>
/// <param name="shotManager">ショットを管理するクラス</param>
void EnemyManager::Update(const Map& map, const VECTOR& cameraPosition, ShotManager& shotManager,const VECTOR& playerPosition)
{
    //エネミー全てのアップデートをまわす
    for (int i = 0; i < enemy.size(); i++)
    {
        enemy[i]->Update(map, cameraPosition, shotManager,playerPosition);
        //ボスが動き出したかをチェックする
        if (enemy[i]->GetType() == BOSS)
        {
            isBossActive = enemy[i]->GetIsMoveStart();
        }
    }

    //体力が0になったら削除する
    for (auto it = enemy.begin(); it != enemy.end();)
    {
        if ((*it)->GetLife() <= 0)
        {
            it = enemy.erase(it);
        }
        else
        {
            ++it;
        }
    }

}
/// <summary>
/// 描画
/// </summary>
void EnemyManager::Draw()
{
    for (int i = 0; i < enemy.size(); i++)
    {
        enemy[i]->Draw();
    }

}


/// <summary>
/// CSVファイルからエネミーのデータを読み込む
/// </summary>
/// <param name="fileName">ファイル名</param>
vector<EnemyInformation*> EnemyManager::LoadEnemyInformation(const string& fileName)
{
    //ファイルを入れる変数を作成
    ifstream file(fileName);
    //引数として渡す用のベクター
    vector<EnemyInformation*> enemyInformation;

    //ファイルが開けない場合の処理
    if (!file.is_open())
    {
        cerr << "Failed to open file: " << fileName << endl;
    }

    string line;
    while (getline(file, line))
    {
        stringstream inputString(line);
        //読み込み用の文字列を用意
        string enemyType;
        string initializeX;
        string initializeY;
        string shotDirctionX;
        string shotDirctionY;
        string rotationRate;

        //代入用のクラスを作成
        EnemyInformation information;

        //inputStringで読み込んだ値を入れていく
        if (getline(inputString, enemyType,     ',') &&
            getline(inputString, initializeX,   ',') &&
            getline(inputString, initializeY,   ',') &&
            getline(inputString, shotDirctionX, ',') &&
            getline(inputString, shotDirctionY, ',') &&
            getline(inputString, rotationRate,  ',') )
        {
            //文字列をそれぞれの型に変更して代入
            information.type              = stoi(enemyType);
            information.initializeX       = stof(initializeX);
            information.initializeY       = stof(initializeY);
            information.shotDirectionX    = stoi(shotDirctionX);
            information.shotDirectionY    = stoi(shotDirctionY);
            information.imageRotationRate = stof(rotationRate);
        }
        //ベクターに追加
        enemyInformation.emplace_back(new EnemyInformation(information));
    }

    //終わったのでファイルを閉じる
    file.close();
    return enemyInformation;

}



