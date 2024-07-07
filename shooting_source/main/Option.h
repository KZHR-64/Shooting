#pragma once
#include "ModeBase.h"
#include "..\single\Key.h"
#include "..\single\Sound.h"
#include "..\single\Image.h"
#include "..\single\Display.h"
#include "..\single\Fps.h"

struct SettingStruct{
	//設定の構造体
	bool fps_flag;		//FPSを表示するか
	bool full_screen;	//フルスクリーンで表示するか
	int volume_bgm;		//BGMの音量
	int volume_effect;	//効果音の音量
};

class Option : public ModeBase {
private:

	int cursor_pos; //カーソルの位置
	bool initial_fullscreen; //画面開いた直後のウィンドウサイズ
	int on_hundle; //ONのハンドル
	int off_hundle; //OFFのハンドル
	int volume_hundle; //音量のハンドル
	int graduation_hundle; //音量目盛のハンドル

	SettingStruct setting;
	
	void Reset(); //初期化
	void LoadSetting(); //設定の読み込み
	void SaveSetting(); //設定の保存

public:
	Option(ModeChanger* changer, Parameter& param); //コンストラクタ
	~Option(); //デストラクタ
	void Update(); //更新
	void Draw(); //描画
};