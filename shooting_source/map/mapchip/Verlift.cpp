#pragma once
#include "DxLib.h"
#include "Verlift.h"

using namespace std;

//�R���X�g���N�^
Verlift::Verlift(MapChipManager* man, int num) : AbstractMapChip(man, num) {
	
}

//�f�X�g���N�^
Verlift::~Verlift() {

}

//�X�V
void Verlift::Update(){

}

//�`��
void Verlift::Draw() {
	DrawBox((int)x - (4 * size_x), (int)y, (int)x + (4 * size_x), (int)y + (8 * size_y), GetColor(128, 128, 128), true);
}