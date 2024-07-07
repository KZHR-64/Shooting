#pragma once
#include "../AbstractEffect.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//噴射による煙

class Smoke : public AbstractEffect {
private:
	int hundle_num; //表示する画像
public:
	Smoke(EffectManager* eff, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~Smoke(); //デストラクタ
	void Update(); //更新
	void Draw() override; //描画
};
