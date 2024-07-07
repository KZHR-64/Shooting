#pragma once
#include "DxLib.h"
#include "Opening.h"

Opening::Opening(ModeChanger* changer, Parameter& param) : ModeBase(changer, param){
	logo = Image::Get_Instance()->GetEffectImage(6, 0);

	time = 0;
	pal = 0;
}

Opening::~Opening() {
}

//更新
void Opening::Update(){
	//帰還フラグが立っている場合
	if (return_flag) {
		time = 0;
		return_flag = false; //帰還フラグをfalseに
	}
	
	if (time == 18) {
		Sound::Get_Instance()->PlaySoundEffect(4); //効果音を鳴らす
	}

	if (pal < 255) {
		pal += 5;
	}

	if (180 <= time) {
		return_flag = true; //帰還フラグを立て
		modechanger->ChangeMode(Next_Menu, true); //モードをメニューに変更
	}
	
	time++;
}

//描画
void Opening::Draw(){
	DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(255, 255, 255), true);

	//Display::Get_Instance()->FixedDraw(520.f, 260.f, LEFT, 0.f, logo, 1.0, DX_BLENDMODE_ALPHA, pal);
}