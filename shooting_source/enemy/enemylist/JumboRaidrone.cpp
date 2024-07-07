#pragma once
#include "DxLib.h"
#include "JumboRaidrone.h"

using namespace std;

//�R���X�g���N�^
JumboRaidrone::JumboRaidrone(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	hundle_num = 0;
	sy = -2.f;
	bsy = 0.f;
	attack_num = 0;

	SetHit(0.f, 0.f, 48.f);
}

//�f�X�g���N�^
JumboRaidrone::~JumboRaidrone() {
}

//�y���e
void JumboRaidrone::Attack1(shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect) {
	//�ꎞ��~
	if (time == 0) {
		bsy = sy;
		sy = 0.f;
	}
	if (time == 60) {
		bullet->SetBullet(3, x - 24.f, y + 48.f, 8.f, PI); //�e�𔭎�
		Sound::Get_Instance()->PlaySoundEffect(12); //���ʉ���炷
	}

	//��莞�Ԃ�����ړ��ĊJ
	if (time == 120) {
		time = 0;
		attack_num = 0;
		sy = bsy;
	}
}

//�G������
void JumboRaidrone::Attack2(shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect) {
	float right = (float)(Display::Get_Instance()->GetScrollX() + WINDOW_X); //����E
	float py = manager->GetPlayerY();

	//�ꎞ��~
	if (time == 0) {
		bsy = sy;
		sy = 0.f;
	}
	if (time == 30) {
		effect->SetEffect(2, x, y - 64.f);
	}

	if (time == 60) {
		shared_ptr<AbstractEnemy> new_enemy;
		new_enemy = manager->SetEnemy(1, right + 48.f, py);
		new_enemy->SetXSpeed(-4.f);
	}

	//��莞�Ԃ�����ړ��ĊJ
	if (time == 90) {
		time = 0;
		attack_num = 0;
		sy = bsy;
	}
}

//�K���s���X�V
void JumboRaidrone::AbsUpdate() {
	hundle_num = time % 6 / 3;
}

//�X�V
void JumboRaidrone::Update(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {
	float top = (float)Display::Get_Instance()->GetScrollY() + 64.f; //�����
	float bottom = (float)(Display::Get_Instance()->GetScrollY() + WINDOW_Y) - 64.f; //�����

	//�㉺�̌��E�ɒB����������]��
	if (y <= top) {
		y = top;
		sy = 2.f;
	}

	if (bottom <= y) {
		y = bottom;
		sy = -2.f;
	}

	//��莞�Ԃ��ƂɍU���p�^�[����ύX
	if (time % 210 == 0 && attack_num == 0) {
		attack_num = GetRand(1) + 1;
		
		time = 0;
	}

	switch (attack_num)
	{
	case 1:
		Attack1(bullet, effect);
		break;
	case 2:
		Attack2(bullet, effect);
		break;
	default:
		//�U���p�^�[����0�Ȃ��莞�Ԃ��Ƃɒe������
		if (time % 60 == 0) {
			bullet->SetBullet(2, x - 4.f, y + 20.f + sy, 6.f, PI); //�e�𔭎�
			Sound::Get_Instance()->PlaySoundEffect(7); //���ʉ���炷
		}
		break;
	}
}

//�`��
void JumboRaidrone::Draw() {
	int hundle = Image::Get_Instance()->GetCharaImage(32, hundle_num);
	Display::Get_Instance()->Draw(x, y, lr, angle, hundle, DX_BLENDMODE_ALPHA, trance);
}