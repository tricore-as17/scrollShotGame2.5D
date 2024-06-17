#include"LeftShotEnemy.h"
#include<fstream>
#include<sstream>
#include<iostream>
#include"EnemyInformation.h"
#include"EasyEnemy.h"
#include"EnemyManager.h"
#include"ShotManager.h"
#include"Map.h"
#include"Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
EnemyManager::EnemyManager()
{
    //エネミーの初期化情報の入ったcsvファイルを読み込む
    LoadEnemyInformation("Information/InitializeEnemy.csv");

    //読み込んだエネミーの数だけまわす
    for (const auto& information : enemyInformation)
    {
        //csvから読み込んだタイプと同じもののインスタンスを生成する
        if (information->type == EASY)
        {
            enemy.emplace_back(new EasyEnemy(information));
        }
        if (information->type == LEFT_SHOT)
        {
            enemy.emplace_back(new LeftShotEnemy(information));
        }
    }
    
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
    //初期化情報の要素を削除
    for (auto it : enemyInformation)
    {
        delete it;
    }
    //それぞれのポインタが持ってる情報も削除
    enemyInformation.clear();
    enemy.clear();

    
}
/// <summary>
/// エネミー全体の更新処理
/// </summary>
/// <param name="map">マップのインスタンス</param>
/// <param name="cameraPosition">カメラの座標</param>
/// <param name="shotManager">ショットを管理するクラス</param>
void EnemyManager::Update(const Map& map, const VECTOR& cameraPosition, ShotManager& shotManager)
{
    //エネミー全てのアップデートをまわす
    for (int i = 0; i < enemy.size(); i++)
    {
        enemy[i]->Update(map, cameraPosition, shotManager);
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
void EnemyManager::LoadEnemyInformation(const string& fileName)
{
    //ファイルを入れる変数を作成
    ifstream file(fileName);

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

        //代入用のクラスを作成
        EnemyInformation information;

        //inputStringで読み込んだ値を入れていく
        if (getline(inputString, enemyType, ',') &&
            getline(inputString, initializeX, ',') &&
            getline(inputString, initializeY, ','))
        {
            //文字列をそれぞれの型に変更して代入
            information.type = stoi(enemyType);
            information.initializeX = stof(initializeX);
            information.initializeY = stof(initializeY);
        }
        //ベクターに追加
        enemyInformation.emplace_back(new EnemyInformation(information));
    }

    //終わったのでファイルを閉じる
    file.close();

}



