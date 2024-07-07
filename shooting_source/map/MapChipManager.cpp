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

//�}�b�v�`�b�v���̐ݒ�
void MapChipManager::SetData() {
	FILE *fp;
	char buf[256];
	char *p;
	char *tp;
	char *ctx;
	int num;

	fopen_s(&fp, "data/map/mapchip_data.csv", "rb");
	if (fp == NULL) DebugBreak(); //�Ȃ���ΏI��

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
		mapchip_data[num].type = atoi(tp); //��ނ��擾
		tp = strtok_s(NULL, ",", &ctx);
		mapchip_data[num].image = atoi(tp); //�摜�̔ԍ����擾
		tp = strtok_s(NULL, ",", &ctx);
		mapchip_data[num].size_x = atoi(tp); //���̑傫�����擾
		tp = strtok_s(NULL, ",", &ctx);
		mapchip_data[num].size_y = atoi(tp); //�c�̑傫�����擾
		tp = strtok_s(NULL, ",", &ctx);
		mapchip_data[num].inhale = (1 == atoi(tp)); //�z�����߂邩���擾
		tp = strtok_s(NULL, ",", &ctx);
		mapchip_data[num].breakable = (1 == atoi(tp)); //�󂹂邩���擾

	}

	fclose(fp);
}

//�X�e�[�W���̐ݒ�
void MapChipManager::SetStageData() {
	FILE *fp;
	char buf[256];
	char *p;

	fopen_s(&fp, "data/map/stage_data.csv", "r");
	if (fp == NULL) DebugBreak(); //�Ȃ���ΏI��

	memset(buf, 0, sizeof(buf)); //buf��������

	//�t�@�C�������s�ǂ�
	while (fgets(buf, 256, fp) != NULL)
	{
		p = strchr(buf, (int)'\n'); //���s������
		//���s������ꍇ
		if (p != NULL) {
			*p = '\0'; //���s���폜
		}
		stage_data.emplace_back(buf); //�}�b�v���t�@�C�������擾
	}

	fclose(fp);

	SetMapData(stage_data[stage_num]);
}

//�}�b�v���̐ݒ�
void MapChipManager::SetMapData(char* file_name) {
	FILE *fp;
	char buf[512];
	char *p;
	char *tp;
	char *ctx;

	MapDataStruct new_map;

	fopen_s(&fp, file_name, "r");
	if (fp == NULL) DebugBreak(); //�Ȃ���ΏI��

	memset(buf, 0, sizeof(buf)); //buf��������

	//�t�@�C�������s�ǂ�
	while (fgets(buf, 512, fp) != NULL)
	{
		p = strchr(buf, (int)'\n'); //���s������
		//���s������ꍇ
		if (p != NULL) {
			*p = '\0'; //���s���폜
		}
		tp = strtok_s(buf, ",", &ctx);
		strcpy_s(new_map.mapfile_name, tp); //�}�b�v���t�@�C�������擾
		tp = strtok_s(NULL, ",", &ctx);
		strcpy_s(new_map.scroll_name, tp); //�X�N���[���͈̓t�@�C�������擾
		tp = strtok_s(NULL, ",", &ctx);
		strcpy_s(new_map.back_name, tp); //BGM&�w�i�t�@�C�������擾
		tp = strtok_s(NULL, ",", &ctx);
		strcpy_s(new_map.enemy_name, tp); //�G�z�u�t�@�C�������擾
		tp = strtok_s(NULL, ",", &ctx);
		strcpy_s(new_map.event_name, tp); //�C�x���g�z�u�t�@�C�������擾
		tp = strtok_s(NULL, ",", &ctx);
		strcpy_s(new_map.event_data_name, tp); //�C�x���g���t�@�C�������擾
		map_data.emplace_back(new_map);

		memset(buf, 0, sizeof(buf)); //buf��������
	}

	fclose(fp);
}

//BGM�Ɣw�i���̐ݒ�
void MapChipManager::SetBackData() {
	FILE *fp;
	char buf[256];
	char *p;
	char *tp;
	char *ctx;
	BackStruct back;

	//�w�i��񂪂���Ώ�����
	if (!back_data.empty()) back_data.clear();

	fopen_s(&fp, map_data[next_map].back_name, "rb");
	if (fp == NULL) DebugBreak(); //�Ȃ���ΏI��

	memset(buf, 0, sizeof(buf)); //buf��������

	//BGM�ݒ��ǂݍ���
	fgets(buf, 256, fp);
	p = strchr(buf, (int)'\n'); //���s������
	//���s������ꍇ
	if (p != NULL) {
		*p = '\0'; //���s���폜
	}
	tp = strtok_s(buf, ",", &ctx);
	bgm = atoi(tp);

	//�w�i�̐ݒ�
	//�t�@�C�������s�ǂ�
	while (fgets(buf, 256, fp) != NULL)
	{
		tp = strtok_s(buf, ",", &ctx);
		back.image = atoi(tp); //�ԍ����擾
		tp = strtok_s(NULL, ",", &ctx);
		back.sx = (float)atof(tp); //�X�N���[�����x���擾
		tp = strtok_s(NULL, ",", &ctx);
		back.sy = (float)atof(tp); //�X�N���[�����x���擾
		tp = strtok_s(NULL, ",", &ctx);
		back.loop = (atoi(tp) == 1); //�X�N���[�����邩�擾
		back.x = 0.f;
		back.y = 0.f;

		Image::Get_Instance()->LoadBackImage(back.image);

		back_data.emplace_back(back);
	}

	fclose(fp);
}

//�}�b�v�̐���
void MapChipManager::MakeMap(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EventManager> event) {
	FILE *fp;
	char buf[64];
	int c;
	int i = 0;
	int row = 0; //�s
	int col = 0; //��

	//���@�̈ʒu��ݒ�
	player->SetX(0.f);
	player->SetY(240.f);

	Display::Get_Instance()->SetScrollX(0.f); //�������̃X�N���[����������
	Display::Get_Instance()->SetScrollY(360.f); //�c�����̃X�N���[����������

	//�}�b�v�`�b�v������Ώ�����
	if (!mapchip.empty()) {
		
		mapchip.clear();
	}
	
	memset(buf, 0, sizeof(buf)); //buf��������

	fopen_s(&fp, map_data[next_map].mapfile_name, "rb");
	if (fp == NULL) DebugBreak(); //�Ȃ���ΏI��

	while (1)
	{
		while (1)
		{
			c = fgetc(fp);
			//�ǂݎ�����������u,�v�����s�A���[�Ȃ�
			if (c == ',' || c == '\n' || c == EOF) {
				break; //���[�v���甲����

			}
			//����ȊO�Ȃ�
			else {
				strcat_s(buf, (const char*)&c); //�������Ȃ���
			}

		}

		//���[�������烋�[�v���甲����
		if (c == EOF) {
			break;
		}

		//�ǂݍ��񂾐��l��-1�łȂ����
		int num = atoi(buf);
		if (num != -1) {
			//�}�b�v�`�b�v��z�u
			SetMapChip(num, 32.f * col + (4.f * mapchip_data[0].size_x), 32.f * row);
			i++;
		}

		memset(buf, 0, sizeof(buf)); //buf��������

		col++; //�񐔂𑝂₷

		//���s��������񐔂����Z�b�g���čs���𑝂₷
		if (c == '\n') {
			col = 0;
			row++;
		}
	}
	fclose(fp);

	MakeMapScroll(); //�X�N���[���͈͂�ݒ�
	MakeMapEvent(); //�C�x���g��z�u
	SetBackData(); //�w�i����ݒ�
	enemy->SetStandby(map_data[next_map].enemy_name); //�G��z�u
	event->SetStandby(map_data[next_map].event_data_name); //�C�x���g����ݒ�

	Sound::Get_Instance()->LoadBgm(bgm); //�Ȃ��Đ�
}

//�X�N���[���͈͂̐ݒ�
void MapChipManager::MakeMapScroll() {
	FILE *fp;
	char buf[64];
	int c;
	int row = 0; //�s
	int col = 0; //��

	memset(buf, 0, sizeof(buf)); //buf��������

	fopen_s(&fp, map_data[next_map].scroll_name, "rb");
	if (fp == NULL) DebugBreak(); //�Ȃ���ΏI��

	while (1)
	{
		while (1)
		{
			c = fgetc(fp);
			//�ǂݎ�����������u,�v�����s�A���[�Ȃ�
			if (c == ',' || c == '\n' || c == EOF) {
				break; //���[�v���甲����

			}
			//����ȊO�Ȃ�
			else {
				strcat_s(buf, (const char*)&c); //�������Ȃ���
			}
		}

		//���[�������烋�[�v���甲����
		if (c == EOF) {
			break;
		}

		//�ǂݍ��񂾐��l�ɂ���ăX�N���[���͈͂�����
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

		memset(buf, 0, sizeof(buf)); //buf��������

		col++; //�񐔂𑝂₷

		//���s��������񐔂����Z�b�g���čs���𑝂₷
		if (c == '\n') {
			col = 0;
			row++;
		}
		
	}
	fclose(fp);
}

//�C�x���g�J�n�ʒu�̐ݒ�
void MapChipManager::MakeMapEvent() {
	FILE* fp;
	char buf[64];
	int c;
	int row = 0; //�s
	int col = 0; //��
	EventDataStruct new_event;

	//�z�u�����C�x���g������Ώ�����
	if (!standby_event.empty()) standby_event.clear();

	memset(buf, 0, sizeof(buf)); //buf��������

	fopen_s(&fp, map_data[next_map].event_name, "rb");
	if (fp == NULL) DebugBreak(); //�Ȃ���ΏI��

	while (1)
	{
		while (1)
		{
			c = fgetc(fp);
			//�ǂݎ�����������u,�v�����s�A���[�Ȃ�
			if (c == ',' || c == '\n' || c == EOF) {
				break; //���[�v���甲����

			}
			//����ȊO�Ȃ�
			else {
				strcat_s(buf, (const char*)&c); //�������Ȃ���
			}
		}

		//���[�������烋�[�v���甲����
		if (c == EOF) {
			break;
		}

		//�ǂݍ��񂾐��l��-1�łȂ����
		if (atoi(buf) != -1) {
			//�C�x���g��z�u
			new_event.flag = true;
			new_event.num = atoi(buf);
			new_event.x = 32.f * col;
			new_event.y = 32.f * row + 16.f;
			standby_event.emplace_back(new_event);
		}

		memset(buf, 0, sizeof(buf)); //buf��������

		col++; //�񐔂𑝂₷

		//���s��������񐔂����Z�b�g���čs���𑝂₷
		if (c == '\n') {
			col = 0;
			row++;
		}
	}
	fclose(fp);
}

//������
void MapChipManager::Reset(){
	
}

//�}�b�v�`�b�v�̔z�u
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

	new_mapchip->SetX(ini_x); //���W��ݒ�
	new_mapchip->SetY(ini_y);
	new_mapchip->SetBaseX(ini_x); //��̍��W��ݒ�
	new_mapchip->SetBaseY(ini_y);
	new_mapchip->SetSizeX(mapchip_data[num].size_x); //�傫����ݒ�
	new_mapchip->SetSizeY(mapchip_data[num].size_y);
	new_mapchip->SetInhale(mapchip_data[num].inhale); //�z�����߂邩�ݒ�
	new_mapchip->SetBreakable(mapchip_data[num].breakable); //�󂹂邩�ݒ�

	mapchip.emplace_back(new_mapchip);

	return new_mapchip;
}

//�L�������}�b�v�`�b�v�ɓ������Ă��邩
shared_ptr<AbstractMapChip> MapChipManager::HitCheck(float cx, float cy, int size_x, int size_y, bool check_inhale, bool check_break, bool abs_check) {
	for (auto map : mapchip) {
		if ((!map->GetHitFlag() && !abs_check) || !map->GetLiveFlag()) continue; //�����蔻�肪�Ȃ���Δ�΂�
		float x = 4.f * map->GetSizeX() + 4.f * size_x; //����p
		float y = 4.f * map->GetSizeY() + 4.f * size_y; //����p
		float center_y = map->GetY() + 4.f * map->GetSizeY(); //�}�b�v�`�b�v�̒��S
		bool inhale_flag = (map->GetInhale() && check_inhale && !map->GetInhaledFlag()) || !check_inhale; //�z�����߂邩
		bool break_flag = (map->GetBreakable() && check_break) || !check_break; //�󂹂邩
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf(cx - map->GetX()) < x && fabsf(cy - center_y) < y && inhale_flag && break_flag) {
			
			//�󂷂��m�F���Ă�����
			if (map->GetBreakable() && check_break) {
				map->SetLiveFlag(false); //����t���O��false��
			}
			return map; //map��Ԃ�
		}
	}
	return NULL;
}

//�L�������}�b�v�`�b�v�ɓ������Ă��邩(���̔���)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckLeft(float cx, float cy, float hit_size) {
	for (auto map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //�����蔻�肪�Ȃ���Δ�΂�
		float x = 4.f * map->GetSizeX(); //����p
		float y = 4.f * map->GetSizeY() + hit_size; //����p
		float center_y = map->GetY() + 4.f * map->GetSizeY(); //�}�b�v�`�b�v�̒��S
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf((cx - hit_size) - map->GetX()) < x && fabsf(cy - center_y) < y) {
			return map; //map��Ԃ�
		}
	}
	return NULL;
}

//�L�������}�b�v�`�b�v�ɓ������Ă��邩(�E�̔���)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckRight(float cx, float cy, float hit_size) {
	for (auto map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //�����蔻�肪�Ȃ���Δ�΂�
		float x = 4.f * map->GetSizeX(); //����p
		float y = 4.f * map->GetSizeY() + hit_size; //����p
		float center_y = map->GetY() + 4.f * map->GetSizeY(); //�}�b�v�`�b�v�̒��S
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf((cx + hit_size) - map->GetX()) < x && fabsf(cy - center_y) < y) {
			return map; //map��Ԃ�
		}
	}
	return NULL;
}

//�L�������}�b�v�`�b�v�ɓ������Ă��邩(��̔���)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckTop(float cx, float cy, float hit_size) {
	for (auto map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //�����蔻�肪�Ȃ���Δ�΂�
		float x = 4.f * map->GetSizeX() + hit_size; //����p
		float y = 8.f * map->GetSizeY(); //����p
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf(cx - map->GetX()) < x && fabsf((cy - hit_size) - map->GetY()) < y && map->GetY() + y < cy) {
			return map; //map��Ԃ�
		}
	}
	return NULL;
}

//�L�������}�b�v�`�b�v�ɓ������Ă��邩(���̔���)
shared_ptr<AbstractMapChip> MapChipManager::HitCheckBottom(float cx, float cy, float hit_size) {
	for (auto map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //�����蔻�肪�Ȃ���Δ�΂�
		float x = 4.f * map->GetSizeX() + hit_size; //����p
		float y = hit_size; //����p
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf(cx - map->GetX()) < x && fabsf(cy - map->GetY()) < hit_size) {
			return map; //map��Ԃ�
		}
	}
	return NULL;
}

//�L�������}�b�v�`�b�v�ɏ���Ă��邩
void MapChipManager::CheckStep(float cx, float cy, int size_x, int size_y) {
	for (auto map : mapchip) {
		if (!map->GetHitFlag() || !map->GetLiveFlag()) continue; //�����蔻�肪�Ȃ���Δ�΂�
		float x = 4.f * map->GetSizeX() + 4.f * size_x; //����p
		float y = 8.f * map->GetSizeY(); //����p
		float sub_y = (cy + 4.f * size_y) - map->GetY();
		//���̃}�b�v�`�b�v�����݂��A�������Ă���Ȃ�
		if (fabsf(cx - map->GetX()) < x && sub_y < y && 0.f < sub_y) {
			
		}
		//�����łȂ����
		else {
			
		}
	}
}

//�L�������C�x���g�����ʒu�ɓ������Ă��邩
void MapChipManager::EventHitCheck(shared_ptr<EventManager> event, float cx, float cy) {
	/*for (unsigned int i = 0; i < standby_event.size(); i++) {
		bool hit_x = (fabsf(cx - standby_event[i].x) < 32.f) || event->GetPosition(i);
		bool hit_y = (fabsf(cy - standby_event[i].y) < 32.f) || !event->GetPosition(i);
		if (hit_x && hit_y && standby_event[i].flag) {
			Sound::Get_Instance()->PlaySoundEffect(7); //���ʉ���炷
			event->SetEventList(standby_event[i].num, standby_event[i].x, standby_event[i].y); //�C�x���g��\��
			standby_event[i].flag = false; //�t���O��false��
			break;
		}
	}*/

	//���ʂ̓X�N���[���ʒu�ōs��
	for (unsigned int i = 0; i < standby_event.size(); i++) {
		bool hit_x = (standby_event[i].x - (float)Display::Get_Instance()->GetScrollX() < 16.f) || event->GetPosition(i);
		bool hit_y = (fabsf((float)Display::Get_Instance()->GetScrollY() - standby_event[i].y) < 16.f) || !event->GetPosition(i);
		if (hit_x && hit_y && standby_event[i].flag) {
			Sound::Get_Instance()->PlaySoundEffect(7); //���ʉ���炷
			event->SetEventList(standby_event[i].num, standby_event[i].x, standby_event[i].y); //�C�x���g��\��
			standby_event[i].flag = false; //�t���O��false��
			break;
		}
	}
}

//��ʓ��Ɏ��܂��Ă��邩�m�F
void MapChipManager::WindowCheck(shared_ptr<AbstractMapChip> map) {
	float left = (float)Display::Get_Instance()->GetScrollX(); //��ʍ��[
	float right = (float)(Display::Get_Instance()->GetScrollX() + WINDOW_X); //��ʉE�[
	float top = (float)Display::Get_Instance()->GetScrollY(); //��ʏ�
	float bottom = (float)(Display::Get_Instance()->GetScrollY() + +WINDOW_Y); //��ʒ�

	bool draw_flag; //�`�悷��t���O
	float x = map->GetX();
	float y = map->GetY();
	int size_x = map->GetSizeX();
	int size_y = map->GetSizeY();

	//��ʓ��Ȃ�`�悷��
	draw_flag = (left - 32.f - (4.f * size_x) < x && x < right + 32.f +(4.f * size_x) && top - 32.f - (8.f * size_y) < y && y < bottom + 32.f);
	map->SetDrawFlag(draw_flag);
	
}

//���̃X�N���[�����x���擾
int MapChipManager::GetScrollSpeedX() {
	return scroll_speed_x;
}

//�c�̃X�N���[�����x���擾
int MapChipManager::GetScrollSpeedY() {
	return scroll_speed_y;
}

//�X�N���[���̒�~
void MapChipManager::StopScroll() {
	if (scroll_speed_x == 0 && scroll_speed_y == 0) return;
	scroll_save_x = scroll_speed_x;
	scroll_save_y = scroll_speed_y;
	
	scroll_speed_x = 0;
	scroll_speed_y = 0;
}

//�X�N���[���̊J�n
void MapChipManager::StartScroll() {
	scroll_speed_x = scroll_save_x;
	scroll_speed_y = scroll_save_y;
}

//�}�b�v�̃X�N���[��
void MapChipManager::MapScroll(std::shared_ptr<EnemyManager> enemy) {
	
	//�X�N���[���ʂ��擾
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

//�w�i�̍X�V
void MapChipManager::BackUpdate() {
	for (unsigned int i = 0; i < back_data.size(); i++) {
		//�X�N���[���ʂ��擾
		int dif_x = Display::Get_Instance()->GetScrollX();
		int dif_y = Display::Get_Instance()->GetScrollY();

		//�w�i�摜�̑傫�����擾
		int size_x;
		int size_y;
		int image = Image::Get_Instance()->GetBackImage(back_data[i].image);
		GetGraphSize(image, &size_x, &size_y);

		//�X�N���[���ʂ̕������w�i���ړ�
		back_data[i].x -= ((float)scroll_speed_x * back_data[i].sx);
		back_data[i].y -= ((float)scroll_speed_y * back_data[i].sy);
		
		//�w�i�����[�v����ꍇ
		if (back_data[i].loop) {
			//�w�i(�̉E�[)����ʊO(��)�ɏo���ꍇ
			if (back_data[i].x < -size_x) {
				back_data[i].x += size_x; //�摜�̑傫�����E�ֈړ�
			}

			//�w�i(�̉E�[)����ʊO(�E)�ɏo���ꍇ
			if (back_data[i].x > 0) {
				back_data[i].x -= size_x; //�摜�̑傫�������ֈړ�
			}
		}
		//���Ȃ��ꍇ
		else {
			//�w�i(�̍��[)����ʒ[(��)���E�ɏo���ꍇ
			if (back_data[i].x > 0.f) {
				back_data[i].x = 0.f; //�w�i�̍��[��0�Ɉړ�
			}
			//�w�i(�̉E�[)����ʒ[(�E)��荶�ɏo���ꍇ
			if (back_data[i].x + (float)size_x < WINDOW_X) {
				back_data[i].x = (float)(WINDOW_X - size_x); //�w�i�̍��[���E�B���h�E-�摜�Ɉړ�
			}
		}
	}
}

//�w�i�̕`��
void MapChipManager::BackDraw() {
	for (auto back : back_data) {
		//�w�i�摜�̑傫�����擾
		int size_x;
		int size_y;
		int image = Image::Get_Instance()->GetBackImage(back.image); //�w�i���擾
		GetGraphSize(image, &size_x, &size_y);
		float x = back.x;// +(float)size_x;
		float y = back.y;// +(float)size_y;

		Display::Get_Instance()->BackDraw(x, y, image); //�w�i��`��
		//���[�v����ꍇ����1��
		if (back.loop) {
			Display::Get_Instance()->BackDraw(x + size_x, y, image); //�w�i��`��
		}
	}
}

//�X�V
void MapChipManager::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy){
	MapScroll(enemy);
	
	BackUpdate();

	for (auto map : mapchip) {
		if (!map->GetLiveFlag()) continue;
		//�z�����ݏ�ԂȂ�
		map->Update();
		map->SetX(map->GetX() + map->GetXSpeed());
		map->SetY(map->GetY() + map->GetYSpeed());
		int time = map->GetTime();
		time++;
		map->SetTime(time);

		WindowCheck(map); //�`�悷�邩�m�F
	}
}

//�`��
void MapChipManager::Draw(){
	BackDraw(); //�w�i�̕`��

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