#pragma once
#include "Mode.h"
#include "Option.h"
#include "KeyConfig.h"
#include "..\single\Key.h"
#include "..\single\Sound.h"
#include "..\single\Image.h"
#include "..\single\Display.h"
#include "..\single\Fps.h"

class System {
private:
	SettingStruct OptionSetting(); //オプションの読み込み
	void KeySetting(); //キーコンフィグの読み込み

public:
	System(); //コンストラクタ
	~System(); //デストラクタ
	void Setting(); //初期設定の読み込み
	void Finalize(); //終了
	void Update(); //更新
};