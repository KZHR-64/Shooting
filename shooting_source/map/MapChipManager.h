#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
//#include "Game.h"
#include "../main/Parameter.h"
#include "AbstractMapChip.h"
#include "../player/Player.h"
#include "../enemy/EnemyManager.h"
#include "../event/EventManager.h"
//#include "Effect.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include "../single/Sound.h"
#include <map>
#include <list>
#include <vector>
#include <memory>

class AbstractMapChip;
class WarpDoor;
class Player;
class EnemyManager;
class EventManager;

struct MapChipDataStruct
{
	//マップチップ情報の構造体
	int type; //種類
	int image; //表示する画像
	int size_x; //横の大きさ
	int size_y; //縦の大きさ
	bool inhale; //吸い込めるか
	bool breakable; //壊せるか
};

struct EventDataStruct
{
	//イベント配置情報の構造体
	bool flag; //発生するか
	int num; //番号
	float x; //x座標
	float y; //y座標
};

struct MapDataStruct
{
	//マップ情報の構造体
	char mapfile_name[256]; //マップチップ配置のファイル名
	char scroll_name[256]; //スクロール情報のファイル名
	char back_name[256]; //BGMと背景設定のファイル名
	char enemy_name[256]; //敵配置のファイル名
	char event_name[256]; //イベント配置のファイル名
	char event_data_name[256]; //イベント情報のファイル名
};

struct BackStruct
{
	//背景の構造体
	int image; //画像
	float x; //座標(左下を基準とする)
	float y;
	float sx; //スクロールする速度(倍率)
	float sy;
	bool loop; //ループするか
};

class MapChipManager{
private:
	std::list<std::shared_ptr<AbstractMapChip>> mapchip; //マップチップ
	std::vector<EventDataStruct> standby_event; //イベント
	std::vector<char*> stage_data; //ステージ情報
	std::vector<MapDataStruct> map_data; //マップ情報
	std::map<int, MapChipDataStruct> mapchip_data; //マップチップ情報
	std::vector<BackStruct> back_data; //背景

	void SetData(); //マップチップ情報の設定
	void SetStageData(); //ステージ情報の設定
	void SetMapData(char* file_name); //マップ情報の設定
	void SetBackData(); //BGMと背景情報の設定
	void MakeMapScroll(); //スクロール範囲の設定
	void MakeMapEvent(); //イベント開始位置の設定
	void WindowCheck(std::shared_ptr<AbstractMapChip>); //画面内に収まっているか確認
	void MapScroll(std::shared_ptr<EnemyManager> enemy); //マップのスクロール
	void BackUpdate(); //背景の更新
	void BackDraw(); //背景の描画

	int stage_num; //ステージ番号
	int next_map; //次のマップ
	int bgm; //再生するBGM
	int scroll_base_x; //基となるスクロール速度
	int scroll_base_y;
	int scroll_speed_x; //スクロール速度
	int scroll_speed_y;
	int scroll_save_x; //保存したスクロール速度
	int scroll_save_y;

public:
	MapChipManager(Parameter &param); //コンストラクタ
	~MapChipManager(); //デストラクタ
	void Reset(); //初期化
	void MakeMap(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EventManager> event); //マップの生成(自機、敵、イベントのクラス)
	std::shared_ptr<AbstractMapChip> SetMapChip(int num, float ini_x, float ini_y); //マップチップの配置(データの番号、座標)
	std::shared_ptr<AbstractMapChip> HitCheck(float cx, float cy, int size_x, int size_y, bool check_inhale, bool check_break, bool abs_check = false); //キャラがマップチップに当たっているか(キャラのx,y座標、x,y方向の大きさ、吸い込めるか、壊せるか、当たり判定にかかわらず確認するか)
	std::shared_ptr<AbstractMapChip> HitCheckLeft(float cx, float cy, float hit_size); //キャラがマップチップに当たっているか(左の判定)(キャラのx,y座標、当たり判定の大きさ)
	std::shared_ptr<AbstractMapChip> HitCheckRight(float cx, float cy, float hit_size); //キャラがマップチップに当たっているか(右の判定)(キャラのx,y座標、当たり判定の大きさ)
	std::shared_ptr<AbstractMapChip> HitCheckTop(float cx, float cy, float hit_size); //キャラがマップチップに当たっているか(上の判定)(キャラのx,y座標、当たり判定の大きさ)
	std::shared_ptr<AbstractMapChip> HitCheckBottom(float cx, float cy, float hit_size); //キャラがマップチップに当たっているか(下の判定)(キャラのx,y座標、当たり判定の大きさ)
	void CheckStep(float cx, float cy, int size_x, int size_y); //キャラがマップチップに乗っているか(キャラのx,y座標、x,y方向の大きさ)
	void EventHitCheck(std::shared_ptr<EventManager> event, float cx, float cy); //キャラがイベント発生位置に当たっているか(キャラのx,y座標)
	
	int GetScrollSpeedX(); //横のスクロール速度を取得
	int GetScrollSpeedY(); //縦のスクロール速度を取得
	void StopScroll(); //スクロールの停止
	void StartScroll(); //スクロールの開始

	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy); //更新
	void Draw(); //描画
};