#pragma once
#include "AbstractMapChip.h"
#include "../Define.h"
//#include "Game.h"
//#include "Map.h"
//#include "Bullet.h"
//#include "Enemy.h"
//#include "Effect.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

class Nomove : public AbstractMapChip{
protected:

public:
	Nomove(float initial_x, float initial_y); //コンストラクタ(座標)
	~Nomove(); //デストラクタ
	void Draw() override; //描画
};
