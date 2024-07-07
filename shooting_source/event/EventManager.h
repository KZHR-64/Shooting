#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
//#include "Game.h"
#include "AbstractEvent.h"
#include "../main/Parameter.h"
#include "../player/Player.h"
#include "../enemy/EnemyManager.h"
#include "../effect/EffectManager.h"
#include "../map/MapChipManager.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include "../single/Sound.h"
#include <map>
#include <vector>
#include <queue>
#include <memory>

class AbstractEvent;
class Player;
class EnemyManager;
class EffectManager;
class MapChipManager;

struct EventListStruct
{
	//イベント情報の構造体
	int type; //種類
	bool position; //参照する座標(0=x,1=y)
	char file_name[256]; //ファイル名
};

class EventManager : public CharacterBase{
private:
	std::map<int, EventListStruct> event_data; //イベント情報
	std::queue<std::shared_ptr<AbstractEvent>> event_queue; //イベントのコンテナ

	int message_font; //フォント情報
	
	float x, y; //座標

	bool player_stop; //自機の動きを止めるか
	bool enemy_stop; //敵の動きを止めるか
	bool clear_flag; //ステージをクリアしたか
	bool restart_flag; //やりなおすか

public:
	EventManager(Parameter &param); //コンストラクタ
	~EventManager(); //デストラクタ
	void Reset(); //初期化
	void SetStandby(char* file_name); //イベントを用意
	void SetEvent(int num); //イベントを予約(種類)
	void SetEventList(int num, float ini_x, float ini_y); //イベントを複数予約(ファイル番号)

	void EventStart(); //イベントを開始
	void EventEnd(); //終了したイベントを消去
	void AllEventEnd(); //イベントを全て消去
	bool GetPlayerStop(); //自機を止めるか取得
	void SetPlayerStop(bool flag); //自機を止めるか設定
	bool GetEnemyStop(); //敵を止めるか取得
	void SetEnemyStop(bool flag); //敵を止めるか設定
	bool GetClearFlag(); //クリアしたかを取得
	void SetClearFlag(bool flag); //クリアしたかを設定
	bool GetRestartFlag(); //やりなおすかを取得
	void SetRestartFlag(bool flag); //やりなおすかを設定
	int GetFont(); //フォント情報を取得
	bool GetPosition(int num); //参照する座標を取得(ファイル番号、座標)
	float GetX(); //x座標を返す
	float GetY(); //y座標を返す

	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<MapChipManager> map); //更新
	void Draw(); //描画
};