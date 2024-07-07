#pragma once
#include "../AbstractEffect.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//爆発

class Explode : public AbstractEffect {
private:
	int hundle_num; //表示する画像
public:
	Explode(EffectManager* eff, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~Explode(); //デストラクタ
	void Update(); //更新
	void Draw() override; //描画
};
