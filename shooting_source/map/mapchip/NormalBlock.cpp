#pragma once
#include "DxLib.h"
#include "NormalBlock.h"

using namespace std;

//�R���X�g���N�^
NormalBlock::NormalBlock(MapChipManager* man, int num) : AbstractMapChip(man, num) {
	
}

//�f�X�g���N�^
NormalBlock::~NormalBlock() {
	
}

//�X�V
void NormalBlock::Update(){

}

//�`��
void NormalBlock::Draw() {
	int hundle = Image::Get_Instance()->GetMapchipImage(image);
	//�摜�̑傫�����擾
	int size_x;
	int size_y;
	GetGraphSize(hundle, &size_x, &size_y);

	Display::Get_Instance()->Draw(x, y + (float)(size_y / 2), LEFT, angle, hundle, DX_BLENDMODE_NOBLEND);
}