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

//�X�V
void Opening::Update(){
	//�A�҃t���O�������Ă���ꍇ
	if (return_flag) {
		time = 0;
		return_flag = false; //�A�҃t���O��false��
	}
	
	if (time == 18) {
		Sound::Get_Instance()->PlaySoundEffect(4); //���ʉ���炷
	}

	if (pal < 255) {
		pal += 5;
	}

	if (180 <= time) {
		return_flag = true; //�A�҃t���O�𗧂�
		modechanger->ChangeMode(Next_Menu, true); //���[�h�����j���[�ɕύX
	}
	
	time++;
}

//�`��
void Opening::Draw(){
	DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(255, 255, 255), true);

	//Display::Get_Instance()->FixedDraw(520.f, 260.f, LEFT, 0.f, logo, 1.0, DX_BLENDMODE_ALPHA, pal);
}