#pragma once
#include "Sound.h"
#include "DxLib.h"
#include <iostream>

//コンストラクタ
Sound::Sound() {
	FILE *fp;
	char buf[256];
	char *p;
	char *tp;
	char *ctx;
	int num;

	playing_bgm = -1;

	fopen_s(&fp, "data/bgm/bgm_data.csv", "r"); //BGMの情報を読み込む
	if (fp == NULL) DebugBreak(); //なければ終了
	memset(buf, 0, sizeof(buf)); //メモリをセット

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
		sprintf_s(bgm_data[num].name, "%s%s", "data/bgm/", tp); //ファイル名を格納
		tp = strtok_s(NULL, ",", &ctx);
		bgm_data[num].loop_time = atoi(tp); //ループ時間を格納
	}
	fclose(fp);

	LoadSoundEffect();
}

//デストラクタ
Sound::~Sound() {
	DeleteBgm();
	DeleteSoundEffect();
	bgm_data.clear();
}

//効果音をロード
void Sound::LoadSoundEffect() {
	FILE *fp;
	char buf[256];
	char file_name[256];
	char *p;
	char *tp;
	char *ctx;
	int num;

	fopen_s(&fp, "data/sound/sound_data.csv", "r"); //効果音の情報を読み込む
	if (fp == NULL) DebugBreak(); //なければ終了
	memset(buf, 0, sizeof(buf)); //メモリをセット

	//ファイルから一行読み
	while (fgets(buf, 256, fp) != NULL)
	{
		p = strchr(buf, '\n'); //改行を検索
		//改行がある場合
		if (p != NULL) {
			*p = '\0'; //改行を削除
		}
		tp = strtok_s(buf, ",", &ctx);
		num = atoi(tp); //番号を取得
		tp = strtok_s(NULL, ",", &ctx);
		sprintf_s(file_name, "%s%s", "data/sound/", tp); //ファイル名を格納
		sound_effect[num] = LoadSoundMem(file_name); //効果音を読み込み
	}
	fclose(fp);
}

//BGMをロード
void Sound::LoadBgm(int num) {
	// 番号がBGM数未満の場合
	if ((unsigned)num < bgm_data.size() && 0 <= num) {
		//BGMを返す
		auto bgm_num = loaded_bgm.find(num); //BGMを検索
		//なかった場合
		if (bgm_num == loaded_bgm.end()) {
			loaded_bgm[num] = LoadSoundMem(bgm_data[num].name); //BGMをロード
		}

		// 指定したBGMが再生中の場合
		if (CheckSoundMem(loaded_bgm[num]) == 1) {
			return; //何もしない
		}
		StopBgm();
		
		//とりあえずここで再生(後で別処理に移す)
		SetLoopSamplePosSoundMem(bgm_data[num].loop_time, loaded_bgm[num]);
		ChangeVolumeSoundMem(volume_bgm, loaded_bgm[num]);
		PlaySoundMem(loaded_bgm[num], DX_PLAYTYPE_LOOP);
		playing_bgm = num; //再生中の曲を取得
	}
	else {
		StopBgm();
	}
}

//効果音を解放
void Sound::DeleteSoundEffect() {
	for each (auto var in sound_effect)
	{
		DeleteSoundMem(var.second);
	}
	sound_effect.clear(); //メモリを解放
}

//BGMのメモリを解放
void Sound::DeleteBgm() {
	StopBgm();
	for each (auto var in loaded_bgm)
	{
		DeleteSoundMem(var.second);
	}
	loaded_bgm.clear(); //メモリを解放
}

//bgmの音量を設定
void Sound::SetBgmVolume(int volume) {
	volume_bgm = VOLUME_SECTION * volume; //音量を設定
	if (playing_bgm < 0) return;
	//曲が再生中なら
	if (CheckSoundMem(loaded_bgm[playing_bgm]) == 1) {
		ChangeVolumeSoundMem(volume_bgm, loaded_bgm[playing_bgm]); //音量を調整
	}
}

//効果音の音量を設定
void Sound::SetSoundVolume(int volume) {
	volume_effect = VOLUME_SECTION * volume; //音量を設定
}

//bgmの音量を取得
int Sound::GetBgmVolume() {
	return (volume_bgm / 25);
}

//効果音の音量を取得
int Sound::GetSoundVolume() {
	return (volume_effect / 25);
}

//効果音を再生
void Sound::PlaySoundEffect(int num) {
	//効果音を探す
	auto bgm_num = sound_effect.find(num); //BGMを検索
	//あった場合
	if (bgm_num != sound_effect.end()) {
		ChangeVolumeSoundMem(volume_effect, sound_effect[num]); //音量を調整
		PlaySoundMem(sound_effect[num], DX_PLAYTYPE_BACK); //効果音を再生
	}
}

//音楽を再生
void Sound::PlayBgm(int num) {
	StopBgm();
	//BGMを探す
	auto bgm_num = loaded_bgm.find(num); //BGMを検索
	//あった場合
	if (bgm_num != loaded_bgm.end()) {
		ChangeVolumeSoundMem(volume_bgm, loaded_bgm[num]); //音量を調整
		PlaySoundMem(loaded_bgm[num], DX_PLAYTYPE_LOOP); //BGMを再生
		playing_bgm = num; //再生中の曲を取得
	}
}

//音楽を停止
void Sound::StopBgm() {
	// ロードしたBGMを確認
	for each (auto var in loaded_bgm)
	{
		// 再生中のBGMがあれば停止する
		if (CheckSoundMem(var.second) == 1) {
			StopSoundMem(var.second);
		}
	}
}

//音楽を停止
void Sound::StopBgm(int num) {
	StopSoundMem(loaded_bgm[num]);
}