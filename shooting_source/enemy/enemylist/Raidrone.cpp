#pragma once
#include "DxLib.h"
#include "Raidrone.h"

using namespace std;

//�R���X�g���N�^
Raidrone::Raidrone(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	hundle_num = 0;

	SetHit(0.f, 0.f, 16.f);
}

//�f�X�g���N�^
Raidrone::~Raidrone() {
}

//�K���s���X�V
void Raidrone::AbsUpdate() {
	hundle_num = time % 6 / 3;
}

//�X�V
void Raidrone::Update(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {
	
}

//�`��
void Raidrone::Draw() {
	int hundle = Image::Get_Instance()->GetCharaImage(image, hundle_num);
	Display::Get_Instance()->Draw(x, y, lr, angle, hundle, DX_BLENDMODE_NOBLEND);
}