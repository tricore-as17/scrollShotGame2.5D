#pragma once


class Font
{
public:
	//定数
	static constexpr int TITLE_GAMELOGO_SIZE = 150;		//タイトルロゴのサイズ
	static constexpr int TITLE_EXPLANETION_SIZE = 50;	//タイトル画面でのボタン説明サイズ
	static constexpr int GAME_DISTANCE_SIZE = 70;		//ゲーム中の経過距離のサイズ
	static constexpr int GAME_ANNOUNCE_SIZE = 50;		//ゲームアナウンスのサイズ
	static constexpr int COMPLIMENT_SIZE = 30;			//障害物を飛び越えた時の誉め言葉
	static constexpr int CLEAREND_TITLE_SIZE = 150;		//ゲームクリアとゲームオーバー画面のタイトルサイズ
	static constexpr int END_TIME_SIZE = 100;			//ゲームオーバー時に表示する経過時間のサイズ
	//コンストラクタ・デストラクタ
	Font();
	virtual ~Font();
	//描画
	//それぞれのハンドルをゲッター
	int GetTitleLogoHandle()const { return titleLogoHandle; }
	int GetTitleExplanetionHandle()const { return titleExplanetionHandle; }
	int GetgameDistanceHandle()const { return gameDistanceHandle; }
	int GetGameAnnouceHandle() const { return gameAnnounceHandle; }
	int GetComplimentHandle()const { return complimentHandle; }
	int GetClearEndTitleHandle() const{ return clearEndTitleHandle; }
	int GetEndTimeHandle() const { return endTimeHandle; }

private:
	//ハンドルデータ
	int titleLogoHandle;
	int titleExplanetionHandle;
	int gameDistanceHandle;
	int gameAnnounceHandle;
	int complimentHandle;
	int clearEndTitleHandle;
	int endTimeHandle;

};
