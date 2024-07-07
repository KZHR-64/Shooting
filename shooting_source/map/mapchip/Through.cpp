#pragma once
#include "DxLib.h"
#include "Through.h"

//�R���X�g���N�^
Through::Through(MapChipManager *man, float ini_x, float ini_y) : AbstractMapChip(man, 0, ini_x, ini_y) {
	size_x = 4;
	size_y = 2;
	through = true;
	inhale = false;
	breakable = false;

}

//�f�X�g���N�^
Through::~Through() {

}

//�`��
void Through::Draw() {
	DrawBox((int)x - 16, (int)y, (int)x + 16, (int)y + 8, GetColor(128, 128, 128), true);
}