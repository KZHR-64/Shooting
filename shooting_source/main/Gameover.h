#pragma once
#include "ModeBase.h"
#include "Parameter.h"
#include "..\single\Key.h"
#include "..\single\Sound.h"
#include "..\single\Image.h"
#include "..\single\Display.h"

class GameBase;

class Gameover : public ModeBase {
private:
	void Reset(); //初期化
	Parameter parameter;
	
	int cursor_pos; //カーソルの位置
	int select_hundle[2]; //選択肢の画像

public:
	Gameover(ModeChanger* changer, Parameter& param); //コンストラクタ
	~Gameover(); //デストラクタ
	void Update(); //更新
	void Draw(); //描画
};