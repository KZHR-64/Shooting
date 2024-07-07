#pragma once
#include "../AbstractMapChip.h"
#include "../Define.h"
//#include "Game.h"
//#include "Map.h"
//#include "Bullet.h"
//#include "Enemy.h"
//#include "Effect.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//足場

class NormalBlock : public AbstractMapChip{
protected:

public:
	NormalBlock(MapChipManager* man, int num); //コンストラクタ(番号)
	~NormalBlock(); //デストラクタ
	void Update(); //更新
	void Draw() override; //描画
};
