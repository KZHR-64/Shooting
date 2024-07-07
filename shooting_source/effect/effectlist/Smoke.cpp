#pragma once
#include "DxLib.h"
#include "Smoke.h"

using namespace std;

//コンストラクタ
Smoke::Smoke(EffectManager* eff, int num, float ini_x, float ini_y) : AbstractEffect(eff, num, ini_x, ini_y) {
	hundle_num = 0;
}

//デストラクタ
Smoke::~Smoke() {

}

//更新
void Smoke::Update() {

	//一定時間を過ぎたら消す
	if (24 <= time) {
		end_flag = true;
	}
	else {
		//表示する画像を決定
		hundle_num = time / 4;
	}

}

//描画
void Smoke::Draw() {
	int hundle = Image::Get_Instance()->GetEffectImage(17, hundle_num);

	Display::Get_Instance()->Draw(x, y, LEFT, angle, hundle, DX_BLENDMODE_NOBLEND);
}