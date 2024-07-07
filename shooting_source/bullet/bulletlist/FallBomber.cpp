#pragma once
#include "DxLib.h"
#include "FallBomber.h"

using namespace std;

//�R���X�g���N�^
FallBomber::FallBomber(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	angle = 1.5f * PI;
	SetSpeed(4.f);
}

//�f�X�g���N�^
FallBomber::~FallBomber() {

}

//�X�V
void FallBomber::Update(shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {
	float px = manager->GetPlayerX(); //���@��x���W
	float top = (float)Display::Get_Instance()->GetScrollY(); //��ʏ�
	
	//��ʊO�ɏo����
	if (y < top - (8.f * size_y) && sy < -1.f) {
		time = 0;
		SetSpeed(0.f);
	}

	//��ʊO�ɏo�Ă��炵�΂炭�o������
	if (time == 12 && -0.1f < sy) {
		x = px - 128.f + (float)GetRand(256);
		angle = 0.5f * PI; //�p�x��ݒ�
		SetSpeed(4.f);
	}
}

//�`��
void FallBomber::Draw() {
	int hundle = Image::Get_Instance()->GetBulletImage(image, 0);
	Display::Get_Instance()->Draw(x, y, LEFT, angle, hundle, DX_BLENDMODE_NOBLEND);
}