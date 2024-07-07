#pragma once
#include "DxLib.h"
#include "AbstractEvent.h"
#include <math.h>

using namespace std;

AbstractEvent::AbstractEvent(EventManager* man, bool stop_player, bool stop_enemy){
	manager = man;
	time = 0;
	end_flag = false;
	player_stop = stop_player; //���@�̓������~�߂邩
	enemy_stop = stop_enemy; //�G�̓������~�߂邩
}

AbstractEvent::~AbstractEvent(){

}

//���Ԃ�Ԃ�
int AbstractEvent::GetTime() {
	return time;
}

//���Ԃ�ݒ�
void AbstractEvent::SetTime(int set_time) {
	time = set_time;
}

//�I���������擾
bool AbstractEvent::GetEndFlag() {
	return end_flag;
}

//���@���~�߂邩�擾
bool AbstractEvent::GetPlayerStop() {
	return player_stop;
}

//�G���~�߂邩�擾
bool AbstractEvent::GetEnemyStop() {
	return enemy_stop;
}