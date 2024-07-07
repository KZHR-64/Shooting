#pragma once
#include "DxLib.h"
#include "Peckiller2.h"

using namespace std;

//�R���X�g���N�^
Peckiller2::Peckiller2(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {

	SetHit(0.f, 0.f, 16.f);
	speed = 0.f;
}

//�f�X�g���N�^
Peckiller2::~Peckiller2() {
}

//�K���s���X�V
void Peckiller2::AbsUpdate() {

}

//�X�V
void Peckiller2::Update(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {
	float px = manager->GetPlayerX();
	float py = manager->GetPlayerY();

	if (time < 180) {
		Sound::Get_Instance()->PlaySoundEffect(5); //���ʉ���炷
		HomingSpin((3.f / 180.f) * PI, px, py);
	}
	//��莞�Ԃ��������
	else if (time == 180) {
		speed = 0.1f;
	}
	else if (180 < time) {
		speed *= 1.1f;
		if (6.f < speed) {
			speed = 6.f;
		}

		if (time % 6 == 0) {
			//���̈ʒu���v�Z
			float smoke_x = x + (-40.f * cosf(angle));
			float smoke_y = y + (-40.f * sinf(angle));
			effect->SetEffect(3, smoke_x, smoke_y); //���𔭐�
		}
	}

	SetSpeed(speed);
}

//�`��
void Peckiller2::Draw() {
	int hundle = Image::Get_Instance()->GetCharaImage(image, 0);
	float draw_angle = angle;
	if (0.5f * PI < angle || angle < -0.5f * PI) {
		lr = RIGHT;
		draw_angle += PI;
	}
	else {
		lr = LEFT;
	}

	Display::Get_Instance()->Draw(x, y, lr, draw_angle, hundle, DX_BLENDMODE_NOBLEND);
}