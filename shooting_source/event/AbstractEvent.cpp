#pragma once
#include "DxLib.h"
#include "AbstractEvent.h"
#include <math.h>

using namespace std;

AbstractEvent::AbstractEvent(EventManager* man, bool stop_player, bool stop_enemy){
	manager = man;
	time = 0;
	end_flag = false;
	player_stop = stop_player; //自機の動きを止めるか
	enemy_stop = stop_enemy; //敵の動きを止めるか
}

AbstractEvent::~AbstractEvent(){

}

//時間を返す
int AbstractEvent::GetTime() {
	return time;
}

//時間を設定
void AbstractEvent::SetTime(int set_time) {
	time = set_time;
}

//終了したか取得
bool AbstractEvent::GetEndFlag() {
	return end_flag;
}

//自機を止めるか取得
bool AbstractEvent::GetPlayerStop() {
	return player_stop;
}

//敵を止めるか取得
bool AbstractEvent::GetEnemyStop() {
	return enemy_stop;
}