#pragma once
#include "DxLib.h"
#include "CatchBeam.h"

using namespace std;

//�R���X�g���N�^
CatchBeam::CatchBeam(EffectManager* eff, int num, float ini_x, float ini_y) : AbstractEffect(eff, num, ini_x, ini_y) {
	beam_num = 0;
}

//�f�X�g���N�^
CatchBeam::~CatchBeam() {

}

//�X�V
void CatchBeam::Update() {
	//�\������ׂ��r�[���̐���ݒ�
	beam_num = (int)(x - base_x) / 64;
	if (beam_num == 0) beam_num = 1;
}

//�`��
void CatchBeam::Draw() {
	int hundle = Image::Get_Instance()->GetEffectImage(13, 0);
	int hundle2 = Image::Get_Instance()->GetEffectImage(14, 0);

	for (int i = 0; i < beam_num; i++) {
		Display::Get_Instance()->Draw(base_x + (i * 64.f), y, LEFT, 0.f, hundle2, DX_BLENDMODE_ALPHA, 192);
	}
	Display::Get_Instance()->Draw(x, y, LEFT, angle, hundle, DX_BLENDMODE_ALPHA, 192);
}