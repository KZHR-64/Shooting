#pragma once
#include "DxLib.h"
#include "MapChipManager.h"
#include "./mapchip/NormalBlock.h"
#include <math.h>

using namespace std;

MapChipManager::MapChipManager(Parameter &param){
	stage_num = param.GetStageNum();
	next_map = 0;
	scroll_base_x = 1;
	scroll_base_y = 0;
	scroll_speed_x = scroll_base_x;
	scroll_speed_y = scroll_base_y;
	scroll_save_x = 0;
	scroll_save_y = 0;

	SetStageData();
	SetData();
}

MapChipManager::~MapChipManager(){
	stage_data.clear();
	mapchip.clear();
	mapchip_data.clear();
	standby_event.clear();
	back_data.clear();
}

//マップチップ情報の設定
void MapChipManager::SetData() {
	FILE *fp;
	char buf[256];
	char *p;
	char *tp;
	char *ctx;
	int num;

	fopen_s(&fp, "data/map/mapchip_data.csv", "rb");
	if (fp == NULL) DebugBreak(); //なければ終了

	memset(buf, 0, sizeof(buf)); //bufを初期化

	//ファイルから一行読み
	while (fgets(buf, 256, fp) != NULL)
	{
		p = strchr(buf, (int)'\n'); //改行を検索
		//改行がある場合
		if (p != NULL) {
			*p = '\0'; //改行を削除
		}
		tp = strtok_s(buf, ",", &ctx);
		num = atoi(tp); //番号を取得
		tp = strtok_s(NULL, ",", &ctx);
		mapchip_data[num].type = atoi(tp); //種類を取得
		tp = strtok_s(NULL, ",", &ctx);
		mapchip_data[num].image = atoi(tp); //画像の番号を取得
		tp = strtok_s(NULL, ",", &ctx);
		mapchip_data[num].size_x = atoi(tp); //横の大きさを取得
		tp = strtok_s(NULL, ",", &ctx);
		mapchip_data[num].size_y = atoi(tp); //縦の大きさを取得
		tp = strtok_s(NULL, ",", &ctx);
		mapchip_data[num].inhale = (1 == atoi(tp)); //吸い込めるかを取得
		tp = strtok_s(NULL, ",", &ctx);
		mapchip_data[num].breakable = (1 == atoi(tp)); //壊せるかを取得

	}

	fclose(fp);
}

//ステージ情報の設定
void MapChipManager::SetStageData() {
	FILE *fp;
	char buf[256];
	char *p;

	fopen_s(&fp, "data/map/stage_data.csv", "r");
	if (fp == NULL) DebugBreak(); //なければ終了

	memset(buf, 0, sizeof(buf)); //bufを初期化

	//ファイルから一行読み
	while (fgets(buf, 256, fp) != NULL)
	{
		p = strchr(buf, (int)'\n'); //改行を検索
		//改行がある場合
		if (p != NULL) {
			*p = '\0'; //改行を削除
		}
		stage_data.emplace_back(buf); //マップ情報ファイル名を取得
	}

	fclose(fp);

	SetMapData(stage_data[stage_num]);
}

//マップ情報の設定
void MapChipManager::SetMapData(char* file_name) {
	FILE *fp;
	char buf[512];
	char *p;
	char *tp;
	char *ctx;

	MapDataStruct new_map;

	fopen_s(&fp, file_name, "r");
	if (fp == NULL) DebugBreak(); //なければ終了

	memset(buf, 0, sizeof(buf)); //bufを初期化

	//ファイルから一行読み
	while (fgets(buf, 512, fp) != NULL)
	{
		p = strchr(buf, (int)'\n'); //改行を検索
		//改行がある場合
		if (p != NULL) {
			*p = '\0'; //改行を削除
		}
		tp = strtok_s(buf, ",", &ctx);
		strcpy_s(new_map.mapfile_name, tp); //マップ情報ファイル名を取得
		tp = strtok_s(NULL, ",", &ctx);
		strcpy_s(new_map.scroll_name, tp); //スクロール範囲ファイル名を取得
		tp = strtok_s(NULL, ",", &ctx);
		strcpy_s(new_map.back_name, tp); //BGM&背景ファイル名を取得
		tp = strtok_s(NULL, ",", &ctx);
		strcpy_s(new_map.enemy_name, tp); //敵配置ファイル名を取得
		tp = strtok_s(NULL, ",", &ctx);
		strcpy_s(new_map.event_name, tp); //イベント配置ファイル名を取得
		tp = strtok_s(NULL, ",", &ctx);
		strcpy_s(new_map.event_data_name, tp); //イベント情報ファイル名を取得
		map_data.emplace_back(new_map);

		memset(buf, 0, sizeof(buf)); //bufを初期化
	}

	fclose(fp);
}

//BGMと背景情報の設定
void MapChipManager::SetBackData() {
	FILE *fp;
	char buf[256];
	char *p;
	char *tp;
	char *ctx;
	BackStruct back;

	//背景情報があれば初期化
	if (!back_data.empty()) back_data.clear();

	fopen_s(&fp, map_data[next_map].back_name, "rb");
	if (fp == NULL) DebugBreak(); //なければ終了

	memset(buf, 0, sizeof(buf)); //bufを初期化

	//BGM設定を読み込む
	fgets(buf, 256, fp);
	p = strchr(buf, (int)'\n'); //改行を検索
	//改行がある場合
	if (p != NULL) {
		*p = '\0'; //改行を削除
	}
	tp = strtok_s(buf, ",", &ctx);
	bgm = atoi(tp);

	//背景の設定
	//ファイルから一行読み
	while (fgets(buf, 256, fp) != NULL)
	{
		tp = strtok_s(buf, ",", &ctx);
		back.image = atoi(tp); //番号を取得
		tp = strtok_s(NULL, ",", &ctx);
		back.sx = (float)atof(tp); //スクロール速度を取得
		tp = strtok_s(NULL, ",", &ctx);
		back.sy = (float)atof(tp); //スクロール速度を取得
		tp = strtok_s(NULL, ",", &ctx);
		back.loop = (atoi(tp) == 1); //スクロールするか取得
		back.x = 0.f;
		back.y = 0.f;

		Image::Get_Instance()->LoadBackImage(back.image);

		back_data.emplace_back(back);
	}

	fclose(fp);
}

//マップの生成
void MapChipManager::MakeMap(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EventManager> event) {
	FILE *fp;
	char buf[64];
	int c;
	int i = 0;
	int row = 0; //行
	int col = 0; //列

	//自機の位置を設定
	player->SetX(0.f);
	player->SetY(240.f);

	Display::Get_Instance()->SetScrollX(0.f); //横方向のスクロールを初期化
	Display::Get_Instance()->SetScrollY(360.f); //縦方向のスクロールを初期化

	//マップチップがあれば初期化
	if (!mapchip.empty()) {
		
		mapchip.clear();
	}
	
	memset(buf, 0, sizeof(buf)); //bufを初期化

	fopen_s(&fp, map_data[next_map].mapfile_name, "rb");
	if (fp == NULL) DebugBreak(); //なければ終了

	while (1)
	{
		while (1)
		{
			c = fgetc(fp);
			//読み取った文字が「,」か改行、末端なら
			if (c == ',' || c == '\n' || c == EOF) {
				break; //ループから抜ける

			}
			//それ以外なら
			else {
				strcat_s(buf, (const char*)&c); //文字をつなげる
			}

		}

		//末端だったらループから抜ける
		if (c == EOF) {
			break;
		}

		//読み込んだ数値が-1でなければ
		int num = atoi(buf);
		if (num != -1) {
			//マップチップを配置
			SetMapChip(num, 32.f * col + (4.f * mapchip_data[0].size_x), 32.f * row);
			i++;
		}

		memset(buf, 0, sizeof(buf)); //bufを初期化

		col++; //列数を増やす

		//改行だったら列数をリセットして行数を増やす
		if (c == '\n') {
			col = 0;
			row++;
		}
	}
	fclose(fp);

	MakeMapScroll(); //スクロール範囲を設定
	MakeMapEvent(); //イベントを配置
	SetBackData(); //背景情報を設定
	enemy->SetStandby(map_data[next_map].enemy_name); //敵を配置
	event->SetStandby(map_data[next_map].event_data_name); //イベント情報を設定

	Sound::Get_Instance()->LoadBgm(bgm); //曲を再生
}

//スクロール範囲の設定
void MapChipManager::MakeMapScroll() {
	FILE *fp;
	char buf[64];
	int c;
	int row = 0; //行
	int col = 0; //列

	memset(buf, 0, sizeof(buf)); //bufを初期化

	fopen_s(&fp, map_data[next_map].scroll_name, "rb");
	if (fp == NULL) DebugBreak(); //なければ終了

	while (1)
	{
		while (1)
		{
			c = fgetc(fp);
			//読み取った文字が「,」か改行、末端なら
			if (c == ',' || c == '\n' || c == EOF) {
				break; //ループから抜ける

			}
			//それ以外なら
			else {
				strcat_s(buf, (const char*)&c); //文字をつなげる
			}
		}

		//末端だったらループから抜ける
		if (c == EOF) {
			break;
		}

		//読み込んだ数値によってスクロール範囲を決定
		switch (atoi(buf))
		{
		case 0:
			Display::Get_Instance()->SetScrollXMin(col * 32);
			Display::Get_Instance()->SetScrollYMin(row * 32);
			break;
		case 1:
			Display::Get_Instance()->SetScrollXMax((col + 1) * 32);
			Display::Get_Instance()->SetScrollYMax((row + 1) * 32);
			break;
		default:
			break;
		}

		memset(buf, 0, sizeof(buf)); //bufを初期化

		col++; //列数を増やす

		//改行だったら列数をリセットして行数を増やす
		if (c == '\n') {
			col = 0;
			row++;
		}
		
	}
	fclose(fp);
}

//イベント開始位置の設定
void MapChipManager::MakeMapEvent() {
	FILE* fp;
	char buf[64];
	int c;
	int row = 0; //行
	int col = 0; //列
	EventDataStruct new_event;

	//配置したイベントがあれば初期化
	if (!standby_event.empty()) standby_event.clear();

	memset(buf, 0, sizeof(buf)); //bufを初期化

	fopen_s(&fp, map_data[next_map].event_name, "rb");
	if (fp == NULL) DebugBreak(); //なければ終了

	while (1)
	{
		while (1)
		{
			c = fgetc(fp);
			//読み取った文字が「,」か改行、末端なら
			if (c == ',' || c == '\n' || c == EOF) {
				break; //ループから抜ける

			}
			//それ以外なら
			else {
				strcat_s(buf, (const char*)&c); //文字をつなげる
			}
		}

		//末端だったらループから抜ける
		if (c == EOF) {
			break;
		}

		//読み込んだ数値が-1でなければ
		if (atoi(buf) != -1) {
			//イベントを配置
			new_event.flag = true;
			new_event.num = atoi(buf);
			new_event.x = 32.f * col;
			new_event.y = 32.f * row + 16.f;
			standby_event.emplace_back(new_event);
		}

		memset(buf, 0, sizeof(buf)); //bufを初期化

		col++; //列数を増やす

		//改行だったら列数をリセットして行数を増やす
		if (c == '\n') {
			col = 0;
			row++;
		}
	}
	fclose(fp);
}

//初期化
void MapChipManager::Reset(){
	
}

//マップチップの配置
shared_ptr<AbstractMapChip> MapChipManager::SetMapChip(int num, float ini_x, float ini_y) {
	shared_ptr<AbstractMapChip> new_mapchip;

	switch (mapchip_data[num].type)
	{
	case 0:
		new_mapchip = make_shared<NormalBlock>(this, mapchip_data[num].image);
		break;
	default:
		new_mapchip = make_shared<NormalBlock>(this, mapchip_data[num].image);
		break;
	}

	new_mapchip->SetX(ini_x); //座標を設定
	new_mapchip->SetY(ini_y);
	new_mapchip->SetBaseX(ini_x); //基の座標を設定
	new_mapchip->SetBaseY(ini_y);
	new_mapchip->SetSizeX(mapchip_data[num].size_x); //大きさを設定
	new_mapchip->SetSizeY(mapchip_data[num].size_y);
	new_mapchip->SetInhale(mapchip_data[num].inhale); //吸い込めるか設定
	new_mapchip->SetBreakable(mapchip_data[num].breakable); //壊せるか設定

	mapchip.emplace_back(new_mapchip);

	return new_mapchip;
}

//キャラがマップチップに当たっているか
shared_ptr<AbstractMapChip> MapChipManager::HitCheck(float cx, float cy, int size_x, int size_y, bool check_inhale, bool check_break, bool abs_check) {
	for (auto map : mapchip) {
		if ((!map->GetHitFlag() && !abs_check) || !map->GetLiveFlag()) continue; //当たり判定がなければ飛ばす
		float x = 4.f * map->GetSizeX() + 4.f * size_x; //判定用
		float y = 4.f * map->GetSizeY() + 4.f * size_y; //判定用
		float center_y = map->GetY() + 4.f * map->GetSizeY(); //マップチップの中心
		bool inhale_flag = (map->GetInhale() && check_inhale && !map->GetInhaledFlag()) || !check_inhale; //吸い込めるか
		bool break_flag = (map->GetBreakable() && check_break) || !check_break; //壊せるか
		//そのマップチップが存在し、当たっているなら
		if (fabsf(cx - map->GetX()) < x && fabsf(cy - center_y) < y && inhale_flag && break_flag) {
			
			//壊すか確認していたら
			if (map->GetBreakable() && check_break) {
				map->SetLiveFlag(false); //動作フラグをfalseに
			}
			return map; //mapを返す
		}
	}
	return NULL;
}

//キャラがマップチップに当たっているか(左の判定)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckLeft(float cx, float cy, float hit_size) {
	for (auto map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //当たり判定がなければ飛ばす
		float x = 4.f * map->GetSizeX(); //判定用
		float y = 4.f * map->GetSizeY() + hit_size; //判定用
		float center_y = map->GetY() + 4.f * map->GetSizeY(); //マップチップの中心
		//そのマップチップが存在し、当たっているなら
		if (fabsf((cx - hit_size) - map->GetX()) < x && fabsf(cy - center_y) < y) {
			return map; //mapを返す
		}
	}
	return NULL;
}

//キャラがマップチップに当たっているか(右の判定)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckRight(float cx, float cy, float hit_size) {
	for (auto map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //当たり判定がなければ飛ばす
		float x = 4.f * map->GetSizeX(); //判定用
		float y = 4.f * map->GetSizeY() + hit_size; //判定用
		float center_y = map->GetY() + 4.f * map->GetSizeY(); //マップチップの中心
		//そのマップチップが存在し、当たっているなら
		if (fabsf((cx + hit_size) - map->GetX()) < x && fabsf(cy - center_y) < y) {
			return map; //mapを返す
		}
	}
	return NULL;
}

//キャラがマップチップに当たっているか(上の判定)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckTop(float cx, float cy, float hit_size) {
	for (auto map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //当たり判定がなければ飛ばす
		float x = 4.f * map->GetSizeX() + hit_size; //判定用
		float y = 8.f * map->GetSizeY(); //判定用
		//そのマップチップが存在し、当たっているなら
		if (fabsf(cx - map->GetX()) < x && fabsf((cy - hit_size) - map->GetY()) < y && map->GetY() + y < cy) {
			return map; //mapを返す
		}
	}
	return NULL;
}

//キャラがマップチップに当たっているか(下の判定)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckBottom(float cx, float cy, float hit_size) {
	for (auto map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //当たり判定がなければ飛ばす
		float x = 4.f * map->GetSizeX() + hit_size; //判定用
		float y = hit_size; //判定用
		//そのマップチップが存在し、当たっているなら
		if (fabsf(cx - map->GetX()) < x && fabsf(cy - map->GetY()) < hit_size) {
			return map; //mapを返す
		}
	}
	return NULL;
}

//キャラがマップチップに乗っているか
void MapChipManager::CheckStep(float cx, float cy, int size_x, int size_y) {
	for (auto map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //当たり判定がなければ飛ばす
		float x = 4.f * map->GetSizeX() + 4.f * size_x; //判定用
		float y = 8.f * map->GetSizeY(); //判定用
		float sub_y = (cy + 4.f * size_y) - map->GetY();
		//そのマップチップが存在し、当たっているなら
		if (fabsf(cx - map->GetX()) < x && sub_y < y && 0.f < sub_y) {
			
		}
		//そうでなければ
		else {
			
		}
	}
}

//キャラがイベント発生位置に当たっているか
void MapChipManager::EventHitCheck(shared_ptr<EventManager> event, float cx, float cy) {
	/*for (unsigned int i = 0; i < standby_event.size(); i++) {
		bool hit_x = (fabsf(cx - standby_event[i].x) < 32.f) || event->GetPosition(i);
		bool hit_y = (fabsf(cy - standby_event[i].y) < 32.f) || !event->GetPosition(i);
		if (hit_x && hit_y && standby_event[i].flag) {
			Sound::Get_Instance()->PlaySoundEffect(7); //効果音を鳴らす
			event->SetEventList(standby_event[i].num, standby_event[i].x, standby_event[i].y); //イベントを予約
			standby_event[i].flag = false; //フラグをfalseに
			break;
		}
	}*/

	//判別はスクロール位置で行う
	for (unsigned int i = 0; i < standby_event.size(); i++) {
		bool hit_x = (standby_event[i].x - (float)Display::Get_Instance()->GetScrollX() < 16.f) || event->GetPosition(i);
		bool hit_y = (fabsf((float)Display::Get_Instance()->GetScrollY() - standby_event[i].y) < 16.f) || !event->GetPosition(i);
		if (hit_x && hit_y && standby_event[i].flag) {
			Sound::Get_Instance()->PlaySoundEffect(7); //効果音を鳴らす
			event->SetEventList(standby_event[i].num, standby_event[i].x, standby_event[i].y); //イベントを予約
			standby_event[i].flag = false; //フラグをfalseに
			break;
		}
	}
}

//画面内に収まっているか確認
void MapChipManager::WindowCheck(shared_ptr<AbstractMapChip> map) {
	float left = (float)Display::Get_Instance()->GetScrollX(); //画面左端
	float right = (float)(Display::Get_Instance()->GetScrollX() + WINDOW_X); //画面右端
	float top = (float)Display::Get_Instance()->GetScrollY(); //画面上
	float bottom = (float)(Display::Get_Instance()->GetScrollY() + +WINDOW_Y); //画面底

	bool draw_flag; //描画するフラグ
	float x = map->GetX();
	float y = map->GetY();
	int size_x = map->GetSizeX();
	int size_y = map->GetSizeY();

	//画面内なら描画する
	draw_flag = (left - 32.f - (4.f * size_x) < x && x < right + 32.f +(4.f * size_x) && top - 32.f - (8.f * size_y) < y && y < bottom + 32.f);
	map->SetDrawFlag(draw_flag);
	
}

//横のスクロール速度を取得
int MapChipManager::GetScrollSpeedX() {
	return scroll_speed_x;
}

//縦のスクロール速度を取得
int MapChipManager::GetScrollSpeedY() {
	return scroll_speed_y;
}

//スクロールの停止
void MapChipManager::StopScroll() {
	if (scroll_speed_x == 0 && scroll_speed_y == 0) return;
	scroll_save_x = scroll_speed_x;
	scroll_save_y = scroll_speed_y;
	
	scroll_speed_x = 0;
	scroll_speed_y = 0;
}

//スクロールの開始
void MapChipManager::StartScroll() {
	scroll_speed_x = scroll_save_x;
	scroll_speed_y = scroll_save_y;
}

//マップのスクロール
void MapChipManager::MapScroll(std::shared_ptr<EnemyManager> enemy) {
	
	//スクロール量を取得
	int dif_x = Display::Get_Instance()->GetScrollX();
	int dif_y = Display::Get_Instance()->GetScrollY();
	int scroll_max_x = Display::Get_Instance()->GetScrollXMax();
	int scroll_max_y = Display::Get_Instance()->GetScrollYMax();

	dif_x += scroll_speed_x;
	dif_y += scroll_speed_y;

	Display::Get_Instance()->SetScrollX((float)dif_x);
	Display::Get_Instance()->SetScrollY((float)dif_y);

	if (scroll_max_x <= dif_x + WINDOW_X) {
		scroll_speed_x = 0;
	}
	else {
		scroll_speed_x = scroll_base_x;
	}

	if (scroll_max_y <= dif_y + WINDOW_Y) {
		scroll_speed_y = 0;
	}
	else {
		scroll_speed_y = scroll_base_y;
	}
}

//背景の更新
void MapChipManager::BackUpdate() {
	for (unsigned int i = 0; i < back_data.size(); i++) {
		//スクロール量を取得
		int dif_x = Display::Get_Instance()->GetScrollX();
		int dif_y = Display::Get_Instance()->GetScrollY();

		//背景画像の大きさを取得
		int size_x;
		int size_y;
		int image = Image::Get_Instance()->GetBackImage(back_data[i].image);
		GetGraphSize(image, &size_x, &size_y);

		//スクロール量の分だけ背景を移動
		back_data[i].x -= ((float)scroll_speed_x * back_data[i].sx);
		back_data[i].y -= ((float)scroll_speed_y * back_data[i].sy);
		
		//背景がループする場合
		if (back_data[i].loop) {
			//背景(の右端)が画面外(左)に出た場合
			if (back_data[i].x < -size_x) {
				back_data[i].x += size_x; //画像の大きさ分右へ移動
			}

			//背景(の右端)が画面外(右)に出た場合
			if (back_data[i].x > 0) {
				back_data[i].x -= size_x; //画像の大きさ分左へ移動
			}
		}
		//しない場合
		else {
			//背景(の左端)が画面端(左)より右に出た場合
			if (back_data[i].x > 0.f) {
				back_data[i].x = 0.f; //背景の左端を0に移動
			}
			//背景(の右端)が画面端(右)より左に出た場合
			if (back_data[i].x + (float)size_x < WINDOW_X) {
				back_data[i].x = (float)(WINDOW_X - size_x); //背景の左端をウィンドウ-画像に移動
			}
		}
	}
}

//背景の描画
void MapChipManager::BackDraw() {
	for (auto back : back_data) {
		//背景画像の大きさを取得
		int size_x;
		int size_y;
		int image = Image::Get_Instance()->GetBackImage(back.image); //背景を取得
		GetGraphSize(image, &size_x, &size_y);
		float x = back.x;// +(float)size_x;
		float y = back.y;// +(float)size_y;

		Display::Get_Instance()->BackDraw(x, y, image); //背景を描画
		//ループする場合もう1枚
		if (back.loop) {
			Display::Get_Instance()->BackDraw(x + size_x, y, image); //背景を描画
		}
	}
}

//更新
void MapChipManager::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy){
	MapScroll(enemy);
	
	BackUpdate();

	for (auto map : mapchip) {
		if (!map->GetLiveFlag()) continue;
		//吸い込み状態なら
		map->Update();
		map->SetX(map->GetX() + map->GetXSpeed());
		map->SetY(map->GetY() + map->GetYSpeed());
		int time = map->GetTime();
		time++;
		map->SetTime(time);

		WindowCheck(map); //描画するか確認
	}
}

//描画
void MapChipManager::Draw(){
	BackDraw(); //背景の描画

	for (auto map : mapchip) {
		if (map->GetLiveFlag() && map->GetDrawFlag()) {
			map->Draw();
		}
	}

	/*for (auto eve : standby_event) {
		int hundle = Image::Get_Instance()->GetMapchipImage(0);
		Display::Get_Instance()->Draw(eve.x, eve.y, LEFT, 0.f, hundle, DX_BLENDMODE_NOBLEND);
	}*/

	/*for (unsigned int i = 0; i < back_data.size(); i++) {
		DrawFormatString(64, 64 + (24 * i), GetColor(255, 0, 0), "%f %f % d", back_data[i].x, back_data[i].y, standby_event.size());
	}*/
}