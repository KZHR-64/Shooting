#pragma once
#include "DxLib.h"
#include "SpreadShoot.h"

using namespace std;

//�R���X�g���N�^
SpreadShoot::SpreadShoot(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	speed = ini_speed;
}

//�f�X�g���N�^
SpreadShoot::~SpreadShoot() {

}

//�X�V
void SpreadShoot::Update(shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {

	//���Ȃ茸�������Ȃ�
	if (speed <= 0.1f) {
		Sound::Get_Instance()->PlaySoundEffect(10); //���ʉ���炷
		end_flag = true;
		//�y��
		for (int i = 0; i < 8; i++)
		{
			float shot_angle = (2.f * PI) * ((float)(i) / 8);
			manager->SetBullet(2, x, y, 6.f, shot_angle);
		}
	}
	//���x������Ȃ�
	else {
		speed *= 0.95f; //���X�Ɍ���
	}

	SetSpeed(speed);
}

//�`��
void SpreadShoot::Draw() {
	int hundle = Image::Get_Instance()->GetBulletImage(image, 0);
	Display::Get_Instance()->Draw(x, y, LEFT, angle, hundle, DX_BLENDMODE_NOBLEND);
}