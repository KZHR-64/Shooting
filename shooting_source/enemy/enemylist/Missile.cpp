#pragma once
#include "DxLib.h"
#include "Missile.h"

using namespace std;

//�R���X�g���N�^
Missile::Missile(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {

	SetHit(0.f, 0.f, 16.f);
	speed = 4.f;
	angle = PI;
}

//�f�X�g���N�^
Missile::~Missile() {
}

//�K���s���X�V
void Missile::AbsUpdate() {

}

//�X�V
void Missile::Update(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {
	float px = manager->GetPlayerX();
	float py = manager->GetPlayerY();
	
	if (time == 0) {
		Sound::Get_Instance()->PlaySoundEffect(11); //���ʉ���炷
	}

	//��莞�Ԃ�����ǔ��J�n
	if (30 < time && time < 120) {
		//Homing((3.f / 180.f) * PI, 4.f, px, py);
		HomingSpin((3.f / 180.f) * PI, px, py);
	}

	if (time % 6 == 0) {
		//���̈ʒu���v�Z
		float smoke_x = x + (-16.f * cosf(angle));
		float smoke_y = y + (-16.f * sinf(angle));
		effect->SetEffect(3, smoke_x, smoke_y); //���𔭐�
	}

	SetSpeed(speed);
}

//�`��
void Missile::Draw() {
	int hundle = Image::Get_Instance()->GetCharaImage(image, 0);
	Display::Get_Instance()->Draw(x, y, lr, angle, hundle, DX_BLENDMODE_NOBLEND);
}