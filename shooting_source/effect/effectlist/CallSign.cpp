#pragma once
#include "DxLib.h"
#include "CallSign.h"

using namespace std;

//�R���X�g���N�^
CallSign::CallSign(EffectManager* eff, int num, float ini_x, float ini_y) : AbstractEffect(eff, num, ini_x, ini_y) {
	hundle_num = 0;
}

//�f�X�g���N�^
CallSign::~CallSign() {

}

//�X�V
void CallSign::Update() {
	if (time == 0) {
		Sound::Get_Instance()->PlaySoundEffect(10); //���ʉ���炷
	}

	y -= 2.0f;

	//��莞�Ԃ��߂��������
	if (66 <= time) {
		end_flag = true;
	}
	else {
		//�\������摜������
		hundle_num = time / 6;
	}

}

//�`��
void CallSign::Draw() {
	int hundle = Image::Get_Instance()->GetEffectImage(16, hundle_num);

	Display::Get_Instance()->Draw(x, y, LEFT, angle, hundle, DX_BLENDMODE_NOBLEND);
}