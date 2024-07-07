#pragma once
#include "DxLib.h"
#include "Peckiller.h"

using namespace std;

//�R���X�g���N�^
Peckiller::Peckiller(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {

	SetHit(0.f, 0.f, 16.f);

	lr = RIGHT;
}

//�f�X�g���N�^
Peckiller::~Peckiller() {
}

//�K���s���X�V
void Peckiller::AbsUpdate() {

}

//�X�V
void Peckiller::Update(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {
	//��莞�Ԃ��������
	if (time == 120) {
		Sound::Get_Instance()->PlaySoundEffect(5); //���ʉ���炷
		sx = -0.1f;
	}
	else if (120 < time) {
		sx *= 1.1f;
		if (sx < -6.f) {
			sx = -6.f;
		}
	}

	if (time % 6 == 0 && 120 < time) {
		//���̈ʒu���v�Z
		float smoke_x = x + (40.f * cosf(angle));
		float smoke_y = y + (40.f * sinf(angle));
		effect->SetEffect(3, smoke_x, smoke_y); //���𔭐�
	}
}

//�`��
void Peckiller::Draw() {
	int hundle = Image::Get_Instance()->GetCharaImage(image, 0);
	Display::Get_Instance()->Draw(x, y, lr, angle, hundle, DX_BLENDMODE_NOBLEND);
}