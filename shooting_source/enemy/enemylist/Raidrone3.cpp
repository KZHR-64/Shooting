#pragma once
#include "DxLib.h"
#include "Raidrone3.h"

using namespace std;

//�R���X�g���N�^
Raidrone3::Raidrone3(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	hundle_num = 0;

	SetHit(0.f, 0.f, 16.f);

	float center = (float)Display::Get_Instance()->GetScrollY() + (WINDOW_Y / 2); //�㉺�ړ��̊
	//��ɍ��킹�Ďn�߂̑��x��ݒ�
	sy = (ini_y < center) ? 2.f : -2.f;
}

//�f�X�g���N�^
Raidrone3::~Raidrone3() {
}

//�K���s���X�V
void Raidrone3::AbsUpdate() {
	hundle_num = time % 6 / 3;
}

//�X�V
void Raidrone3::Update(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {
	
}

//�`��
void Raidrone3::Draw() {
	int hundle = Image::Get_Instance()->GetCharaImage(image, hundle_num);
	Display::Get_Instance()->Draw(x, y, lr, angle, hundle, DX_BLENDMODE_NOBLEND);
}