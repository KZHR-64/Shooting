#pragma once
#include "DxLib.h"
#include "StraightShoot.h"

using namespace std;

//�R���X�g���N�^
StraightShoot::StraightShoot(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	SetHit(0.f, 0.f, 8.f);
}

//�f�X�g���N�^
StraightShoot::~StraightShoot() {

}

//�X�V
void StraightShoot::Update(shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect){

}

//�`��
void StraightShoot::Draw() {
	int hundle = Image::Get_Instance()->GetBulletImage(image, 0);
	Display::Get_Instance()->Draw(x, y, RIGHT, angle, hundle, DX_BLENDMODE_NOBLEND);
}