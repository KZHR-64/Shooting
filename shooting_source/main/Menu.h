#pragma once
#include "ModeBase.h"
#include "..\single\Key.h"
#include "..\single\Sound.h"
#include "..\single\Image.h"
#include "..\single\Display.h"

struct ChoiceStruct
{
	//選択肢の構造体
	int image; //使用する画像
	float ex_rate; //表示倍率
};

class Menu : public ModeBase {
private:
	int count; //カウンター
	int cursor_pos; //カーソルの位置
	int logo; //タイトルロゴ

	ChoiceStruct choice[4]; //選択肢

	void Reset(); //初期化
public:
	Menu(ModeChanger* changer, Parameter& param); //コンストラクタ
	~Menu(); //デストラクタ
	void Update(); //更新
	void Draw(); //描画
};