#pragma once
#include "DxLib.h"
#include "Explode.h"

using namespace std;

//�R���X�g���N�^
Explode::Explode(EffectManager* eff, int num, float ini_x, float ini_y) : AbstractEffect(eff, num, ini_x, ini_y) {
	hundle_num = 0;
}

//�f�X�g���N�^
Explode::~Explode() {

}

//�X�V
void Explode::Update() {
	if (time == 0) {
		Sound::Get_Instance()->PlaySoundEffect(10); //���ʉ���炷
	}

	//��莞�Ԃ��߂��������
	if (48 <= time) {
		end_flag = true;
	}
	else {
		//�\������摜������
		hundle_num = time / 6;
	}

}

//�`��
void Explode::Draw() {
	int hundle = Image::Get_Instance()->GetEffectImage(15, hundle_num);

	Display::Get_Instance()->Draw(x, y, LEFT, angle, hundle, DX_BLENDMODE_NOBLEND);
}