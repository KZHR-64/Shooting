#pragma once
#include "DxLib.h"
#include "DesdragudShoot.h"

using namespace std;

//コンストラクタ
DesdragudShoot::DesdragudShoot(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	SetHit(0.f, 0.f, 24.f);
	base_speed = ini_speed;
	speed = 1.f;
	bx = x;
	by = y;
	bx2 = x;
	by2 = y;
}

//デストラクタ
DesdragudShoot::~DesdragudShoot() {

}

//更新
void DesdragudShoot::Update(shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {
	if (time == 0) {
		SetSpeed(speed); //始めは遅い
	}

	speed *= 1.05f; //徐々に加速

	//加速しきったなら
	if (base_speed <= speed) {
		speed = base_speed; //速度を調整
	}

	SetSpeed(speed);
	bx2 = bx;
	by2 = by;
	bx = x;
	by = y;
}

//描画
void DesdragudShoot::Draw() {
	int hundle = Image::Get_Instance()->GetBulletImage(image, 0);
	Display::Get_Instance()->Draw(bx2, by2, LEFT, angle, hundle, DX_BLENDMODE_ALPHA, 128);
	Display::Get_Instance()->Draw(bx, by, LEFT, angle, hundle, DX_BLENDMODE_ALPHA, 192);
	Display::Get_Instance()->Draw(x, y, LEFT, angle, hundle, DX_BLENDMODE_NOBLEND);
}