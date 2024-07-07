#pragma once
#include "DxLib.h"
#include "EventManager.h"
#include "eventlist\WaitEvent.h"
#include "eventlist\ClearEvent.h"
#include "eventlist\MissEvent.h"
#include "eventlist\TalkEvent.h"
#include "eventlist\ScrollSettingEvent.h"
#include "eventlist\PlayerMoveEvent.h"
#include "eventlist\EnemySettingEvent.h"
#include "eventlist\EffectSettingEvent.h"
#include "eventlist\PlayMusicEvent.h"
#include "eventlist\WaitBattleEvent.h"
#include "eventlist\ScrollResetEvent.h"
#include <math.h>

using namespace std;

EventManager::EventManager(Parameter &param){
	message_font = CreateFontToHandle("Meiryo UI", 20, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1); //�t�H���g���
	
	x = 0.f;
	y = 0.f;

	enemy_stop = false;
	player_stop = false;
	clear_flag = false;
	restart_flag = false;
}

EventManager::~EventManager(){
	//�X�^�b�N��S�J��
	while (!event_queue.empty())
	{
		event_queue.pop();
	}
	event_data.clear();
	DeleteFontToHandle(message_font);
}

//�C�x���g��p��
void EventManager::SetStandby(char* file_name) {
	FILE* fp;
	char buf[256];
	char* p;
	char* tp;
	char* ctx;
	int num;

	fopen_s(&fp, file_name, "r");
	if (fp == NULL) return; //�Ȃ���ΏI��

	memset(buf, 0, sizeof(buf)); //buf��������

	//�t�@�C�������s�ǂ�
	while (fgets(buf, 256, fp) != NULL)
	{
		p = strchr(buf, (int)'\n'); //���s������
		//���s������ꍇ
		if (p != NULL) {
			*p = '\0'; //���s���폜
		}
		tp = strtok_s(buf, ",", &ctx);
		num = atoi(tp); //�ԍ����擾
		tp = strtok_s(NULL, ",", &ctx);
		event_data[num].position = (atoi(tp) == 1); //�ԍ����擾
		tp = strtok_s(NULL, ",", &ctx);
		strcpy_s(event_data[num].file_name, tp);
	}
	fclose(fp);
}

//�C�x���g��\��
void EventManager::SetEvent(int num) {
	shared_ptr<AbstractEvent> new_event;
	switch (num)
	{
	case 0:
		new_event = make_shared<WaitEvent>(this, 30, true, true);
		break;
	case 1:
		new_event = make_shared<ClearEvent>(this, 180, true, false);
		break;
	case 2:
		new_event = make_shared<MissEvent>(this, 180, true, false);
		break;
	default:
		new_event = make_shared<WaitEvent>(this, 30, true, true);
		break;
	}
	event_queue.push(new_event);

	//�����ꂽ�̂��ŏ��Ȃ�J�n
	if (1 == event_queue.size()) {
		EventStart();
	}
}

//�C�x���g�𕡐��\��(�t�@�C���ԍ�)
void EventManager::SetEventList(int num, float ini_x, float ini_y) {
	FILE* fp;
	char buf[512];
	char* p;
	char* tp[4];
	char* ctx;

	int event_size = (int)event_queue.size(); //���݂̃C�x���g��

	//���W��ݒ�
	x = ini_x;
	y = ini_y;

	fopen_s(&fp, event_data[num].file_name, "r");
	if (fp == NULL) return; //�Ȃ���ΏI��

	memset(buf, 0, sizeof(buf)); //buf��������

	//�t�@�C�������s�ǂ�
	while (fgets(buf, 512, fp) != NULL)
	{
		shared_ptr<AbstractEvent> new_event;
		p = strchr(buf, (int)'\n'); //���s������
		//���s������ꍇ
		if (p != NULL) {
			*p = '\0'; //���s���폜
		}
		tp[0] = strtok_s(buf, ",", &ctx);
		tp[1] = strtok_s(NULL, ",", &ctx);
		tp[2] = strtok_s(NULL, ",", &ctx);
		tp[3] = strtok_s(NULL, ",", &ctx);

		switch (atoi(tp[0]))
		{
		case 0:
			new_event = make_shared<WaitEvent>(this, atoi(tp[1]), atoi(tp[2]) == 1, atoi(tp[3]) == 1);
			break;
		case 1:
			new_event = make_shared<ClearEvent>(this, 180, true, false);
			break;
		case 2:
			new_event = make_shared<MissEvent>(this, 180, true, false);
			break;
		case 3:
			new_event = make_shared<TalkEvent>(this, tp[1], tp[2], true, true);
			break;
		case 4:
			new_event = make_shared<PlayerMoveEvent>(this, (float)atof(tp[1]), (float)atof(tp[2]), (float)atof(tp[3]), true, true);
			break;
		case 5:
			new_event = make_shared<EnemySettingEvent>(this, atoi(tp[1]), (float)atof(tp[2]), (float)atof(tp[3]), true, true);
			break;
		case 6:
			new_event = make_shared<EffectSettingEvent>(this, atoi(tp[1]), (float)atof(tp[2]), (float)atof(tp[3]), true, true);
			break;
		case 7:
			new_event = make_shared<PlayMusicEvent>(this, atoi(tp[1]), true, true);
			break;
		case 8:
			new_event = make_shared<WaitBattleEvent>(this, false, false);
			break;
		case 9:
			new_event = make_shared<ScrollSettingEvent>(this, atoi(tp[1]), atoi(tp[2]), true, true);
			break;
		case 10:
			new_event = make_shared<ScrollResetEvent>(this, true, true);
			break;
		default:
			new_event = make_shared<WaitEvent>(this, 30, true, true);
			break;
		}
		event_queue.push(new_event);
	}
	fclose(fp);

	enemy_stop = true;
	player_stop = true;

	//�O�ɃC�x���g���Ȃ���ΊJ�n
	if (event_size == 0) {
		EventStart();
	}
}

//������
void EventManager::Reset(){
	enemy_stop = false;
	player_stop = false;
	clear_flag = false;
	restart_flag = false;
	//�X�^�b�N��S�J��
	while (!event_queue.empty())
	{
		event_queue.pop();
	}
	event_data.clear();
}

//�C�x���g���J�n
void EventManager::EventStart() {
	//��~�t���O��ݒ�
	player_stop = event_queue.front()->GetPlayerStop();
	enemy_stop = event_queue.front()->GetEnemyStop();
}

//�I�������C�x���g������
void EventManager::EventEnd() {
	//��~�t���O������
	player_stop = false;
	enemy_stop = false;

	event_queue.pop();

	//��������ΊJ�n
	if (1 <= event_queue.size()) {
		EventStart();
	}
}

//�C�x���g��S�ď���
void EventManager::AllEventEnd() {
	//��~�t���O������
	enemy_stop = false;
	player_stop = false;
	//�X�^�b�N��S�J��
	while (!event_queue.empty())
	{
		event_queue.pop();
	}
}

//���@���~�߂邩�擾
bool EventManager::GetPlayerStop() {
	return player_stop;
}

//���@���~�߂邩�ݒ�
void EventManager::SetPlayerStop(bool flag) {
	player_stop = flag;
}

//�G���~�߂邩�擾
bool EventManager::GetEnemyStop() {
	return enemy_stop;
}

//�G���~�߂邩�ݒ�
void EventManager::SetEnemyStop(bool flag) {
	enemy_stop = flag;
}

//�N���A���������擾
bool EventManager::GetClearFlag() {
	return clear_flag;
}

//�N���A��������ݒ�
void EventManager::SetClearFlag(bool flag) {
	clear_flag = flag;
}

//���Ȃ��������擾
bool EventManager::GetRestartFlag() {
	return restart_flag;
}

//���Ȃ�������ݒ�
void EventManager::SetRestartFlag(bool flag) {
	restart_flag = flag;
}

//�t�H���g�����擾
int EventManager::GetFont() {
	return message_font;
}

//�Q�Ƃ�����W���擾
bool EventManager::GetPosition(int num) {
	if (event_data.size() < (unsigned)num) return false;
	return event_data[num].position;
}


//x���W��Ԃ�
float EventManager::GetX() {
	return x;
}

//y���W��Ԃ�
float EventManager::GetY() {
	return y;
}

//�X�V
void EventManager::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect, std::shared_ptr<MapChipManager> map){
	if (event_queue.size() == 0) return;
	
	int time = event_queue.front()->GetTime();
	if (time == 0 && player_stop) {
		player->SetXSpeed(0.f);
		player->SetYSpeed(0.f);
	}
	event_queue.front()->Update(player, enemy, effect);
	time++;
	event_queue.front()->SetTime(time);
	//�C�x���g���I�����Ă��������
	if (event_queue.front()->GetEndFlag()) {
		EventEnd();
	}

	if (player_stop || enemy_stop) {
		map->StopScroll();
	}
	if(event_queue.size() == 0) {
		map->StartScroll();
	}
}

//�`��
void EventManager::Draw(){
	/*for (unsigned int i = 0; i < event_data.size(); i++) {
		DrawFormatString(128, 64 + (24 * i), GetColor(255, 0, 0), "%s", event_data[i].file_name);
	}*/

	if (event_queue.size() == 0) return;
	event_queue.front()->Draw();

}