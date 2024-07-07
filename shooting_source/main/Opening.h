#pragma once
#include "ModeBase.h"
#include "..\single\Key.h"
#include "..\single\Sound.h"
#include "..\single\Image.h"
#include "..\single\Display.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

class Opening : public ModeBase {
private:

	int logo; //ロゴのハンドル
	int pal; //ロゴの透明度
	int time; //タイマー

public:
	Opening(ModeChanger* changer, Parameter& param); //コンストラクタ
	~Opening(); //デストラクタ
	void Update(); //更新
	void Draw(); //描画
};