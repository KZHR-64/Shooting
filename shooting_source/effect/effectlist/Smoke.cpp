#pragma once
#include "DxLib.h"
#include "Smoke.h"

using namespace std;

//�R���X�g���N�^
Smoke::Smoke(EffectManager* eff, int num, float ini_x, float ini_y) : AbstractEffect(eff, num, ini_x, ini_y) {
	hundle_num = 0;
}

//�f�X�g���N�^
Smoke::~Smoke() {

}

//�X�V
void Smoke::Update() {

	//��莞�Ԃ��߂��������
	if (24 <= time) {
		end_flag = true;
	}
	else {
		//�\������摜������
		hundle_num = time / 4;
	}

}

//�`��
void Smoke::Draw() {
	int hundle = Image::Get_Instance()->GetEffectImage(17, hundle_num);

	Display::Get_Instance()->Draw(x, y, LEFT, angle, hundle, DX_BLENDMODE_NOBLEND);
}