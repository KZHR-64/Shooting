#pragma once
#include "DxLib.h"
#include "NoMove.h"

//コンストラクタ
Nomove::Nomove(float initial_x, float initial_y) : AbstractMapChip(initial_x, initial_y) {

}

//デストラクタ
Nomove::~Nomove() {

}

//描画
void Nomove::Draw() {
	DrawBox((int)x - 16, (int)y - 16, (int)x + 16, (int)y + 16, GetColor(128, 128, 128), true);
}