#pragma once
#include "../Define.h"
#include "Singleton.h"
#include <map>
#include <vector>

struct BgmDataStruct{
	//BGM情報の構造体
	int hundle; //種類
	int num; //種類
	char name[128]; //ファイル名
	int loop_time; //ループする時間
};

class Sound final : public Singleton<Sound> {
	friend Singleton<Sound>;
private:
	std::map<int, BgmDataStruct> bgm_data; //BGMの情報
	std::map<int, int> loaded_bgm; //BGM(番号、ハンドル)
	std::map<int, int> sound_effect; //効果音
	int volume_bgm; //BGMの音量
	int volume_effect; //効果音の音量
	int playing_bgm; //再生中のBGM

	void DeleteBgm(); //BGMのメモリを解放
	void DeleteSoundEffect(); //効果音を解放
public:
	Sound(); //コンストラクタ
	~Sound(); //デストラクタ
	void DeleteSound(); //曲を解放
	void LoadSoundEffect(); //効果音をロード
	void LoadBgm(int num); //BGMをロード
	void SetBgmVolume(int volume); //bgmの音量を設定(音量)
	void SetSoundVolume(int volume); //効果音の音量を設定(音量)
	int GetBgmVolume(); //bgmの音量を取得
	int GetSoundVolume(); //効果音の音量を取得
	void PlaySoundEffect(int num); //効果音を再生(効果音の番号)
	void PlayBgm(int num); //音楽を再生(曲の番号)
	void StopBgm(); //音楽を停止
	void StopBgm(int num); //音楽を停止(曲の番号)
};