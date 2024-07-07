#pragma once
#include "Sound.h"
#include "DxLib.h"
#include <iostream>

//�R���X�g���N�^
Sound::Sound() {
	FILE *fp;
	char buf[256];
	char *p;
	char *tp;
	char *ctx;
	int num;

	playing_bgm = -1;

	fopen_s(&fp, "data/bgm/bgm_data.csv", "r"); //BGM�̏���ǂݍ���
	if (fp == NULL) DebugBreak(); //�Ȃ���ΏI��
	memset(buf, 0, sizeof(buf)); //���������Z�b�g

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
		sprintf_s(bgm_data[num].name, "%s%s", "data/bgm/", tp); //�t�@�C�������i�[
		tp = strtok_s(NULL, ",", &ctx);
		bgm_data[num].loop_time = atoi(tp); //���[�v���Ԃ��i�[
	}
	fclose(fp);

	LoadSoundEffect();
}

//�f�X�g���N�^
Sound::~Sound() {
	DeleteBgm();
	DeleteSoundEffect();
	bgm_data.clear();
}

//���ʉ������[�h
void Sound::LoadSoundEffect() {
	FILE *fp;
	char buf[256];
	char file_name[256];
	char *p;
	char *tp;
	char *ctx;
	int num;

	fopen_s(&fp, "data/sound/sound_data.csv", "r"); //���ʉ��̏���ǂݍ���
	if (fp == NULL) DebugBreak(); //�Ȃ���ΏI��
	memset(buf, 0, sizeof(buf)); //���������Z�b�g

	//�t�@�C�������s�ǂ�
	while (fgets(buf, 256, fp) != NULL)
	{
		p = strchr(buf, '\n'); //���s������
		//���s������ꍇ
		if (p != NULL) {
			*p = '\0'; //���s���폜
		}
		tp = strtok_s(buf, ",", &ctx);
		num = atoi(tp); //�ԍ����擾
		tp = strtok_s(NULL, ",", &ctx);
		sprintf_s(file_name, "%s%s", "data/sound/", tp); //�t�@�C�������i�[
		sound_effect[num] = LoadSoundMem(file_name); //���ʉ���ǂݍ���
	}
	fclose(fp);
}

//BGM�����[�h
void Sound::LoadBgm(int num) {
	// �ԍ���BGM�������̏ꍇ
	if ((unsigned)num < bgm_data.size() && 0 <= num) {
		//BGM��Ԃ�
		auto bgm_num = loaded_bgm.find(num); //BGM������
		//�Ȃ������ꍇ
		if (bgm_num == loaded_bgm.end()) {
			loaded_bgm[num] = LoadSoundMem(bgm_data[num].name); //BGM�����[�h
		}

		// �w�肵��BGM���Đ����̏ꍇ
		if (CheckSoundMem(loaded_bgm[num]) == 1) {
			return; //�������Ȃ�
		}
		StopBgm();
		
		//�Ƃ肠���������ōĐ�(��ŕʏ����Ɉڂ�)
		SetLoopSamplePosSoundMem(bgm_data[num].loop_time, loaded_bgm[num]);
		ChangeVolumeSoundMem(volume_bgm, loaded_bgm[num]);
		PlaySoundMem(loaded_bgm[num], DX_PLAYTYPE_LOOP);
		playing_bgm = num; //�Đ����̋Ȃ��擾
	}
	else {
		StopBgm();
	}
}

//���ʉ������
void Sound::DeleteSoundEffect() {
	for each (auto var in sound_effect)
	{
		DeleteSoundMem(var.second);
	}
	sound_effect.clear(); //�����������
}

//BGM�̃����������
void Sound::DeleteBgm() {
	StopBgm();
	for each (auto var in loaded_bgm)
	{
		DeleteSoundMem(var.second);
	}
	loaded_bgm.clear(); //�����������
}

//bgm�̉��ʂ�ݒ�
void Sound::SetBgmVolume(int volume) {
	volume_bgm = VOLUME_SECTION * volume; //���ʂ�ݒ�
	if (playing_bgm < 0) return;
	//�Ȃ��Đ����Ȃ�
	if (CheckSoundMem(loaded_bgm[playing_bgm]) == 1) {
		ChangeVolumeSoundMem(volume_bgm, loaded_bgm[playing_bgm]); //���ʂ𒲐�
	}
}

//���ʉ��̉��ʂ�ݒ�
void Sound::SetSoundVolume(int volume) {
	volume_effect = VOLUME_SECTION * volume; //���ʂ�ݒ�
}

//bgm�̉��ʂ��擾
int Sound::GetBgmVolume() {
	return (volume_bgm / 25);
}

//���ʉ��̉��ʂ��擾
int Sound::GetSoundVolume() {
	return (volume_effect / 25);
}

//���ʉ����Đ�
void Sound::PlaySoundEffect(int num) {
	//���ʉ���T��
	auto bgm_num = sound_effect.find(num); //BGM������
	//�������ꍇ
	if (bgm_num != sound_effect.end()) {
		ChangeVolumeSoundMem(volume_effect, sound_effect[num]); //���ʂ𒲐�
		PlaySoundMem(sound_effect[num], DX_PLAYTYPE_BACK); //���ʉ����Đ�
	}
}

//���y���Đ�
void Sound::PlayBgm(int num) {
	StopBgm();
	//BGM��T��
	auto bgm_num = loaded_bgm.find(num); //BGM������
	//�������ꍇ
	if (bgm_num != loaded_bgm.end()) {
		ChangeVolumeSoundMem(volume_bgm, loaded_bgm[num]); //���ʂ𒲐�
		PlaySoundMem(loaded_bgm[num], DX_PLAYTYPE_LOOP); //BGM���Đ�
		playing_bgm = num; //�Đ����̋Ȃ��擾
	}
}

//���y���~
void Sound::StopBgm() {
	// ���[�h����BGM���m�F
	for each (auto var in loaded_bgm)
	{
		// �Đ�����BGM������Β�~����
		if (CheckSoundMem(var.second) == 1) {
			StopSoundMem(var.second);
		}
	}
}

//���y���~
void Sound::StopBgm(int num) {
	StopSoundMem(loaded_bgm[num]);
}