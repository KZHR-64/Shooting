#pragma once
#include "../AbstractMapChip.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//すり抜ける足場

class Through : public AbstractMapChip{
protected:
public:
	Through(MapChipManager *man, float ini_x, float ini_y); //コンストラクタ(座標)
	~Through(); //デストラクタ
	void Draw() override; //描画
};
