#pragma once
#include "DxLib.h"
#include "NormalBlock.h"

using namespace std;

//コンストラクタ
NormalBlock::NormalBlock(MapChipManager* man, int num) : AbstractMapChip(man, num) {
	
}

//デストラクタ
NormalBlock::~NormalBlock() {
	
}

//更新
void NormalBlock::Update(){

}

//描画
void NormalBlock::Draw() {
	int hundle = Image::Get_Instance()->GetMapchipImage(image);
	//画像の大きさを取得
	int size_x;
	int size_y;
	GetGraphSize(hundle, &size_x, &size_y);

	Display::Get_Instance()->Draw(x, y + (float)(size_y / 2), LEFT, angle, hundle, DX_BLENDMODE_NOBLEND);
}