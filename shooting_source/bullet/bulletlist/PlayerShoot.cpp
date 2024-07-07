#pragma once
#include "DxLib.h"
#include "PlayerShoot.h"

using namespace std;

//コンストラクタ
PlayerShoot::PlayerShoot(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	SetHit(0.f, 0.f, 32.f);
	bx = x;
	by = y;
	bx2 = x;
	by2 = y;
}

//デストラクタ
PlayerShoot::~PlayerShoot() {

}

//更新
void PlayerShoot::Update(shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {
	bx2 = bx;
	by2 = by;
	bx = x;
	by = y;
}

//描画
void PlayerShoot::Draw() {
	int hundle = Image::Get_Instance()->GetEffectImage(13, 0);
	Display::Get_Instance()->Draw(bx2, by2, RIGHT, angle, hundle, DX_BLENDMODE_ALPHA, 128);
	Display::Get_Instance()->Draw(bx, by, RIGHT, angle, hundle, DX_BLENDMODE_ALPHA, 192);
	Display::Get_Instance()->Draw(x, y, RIGHT, angle, hundle, DX_BLENDMODE_NOBLEND);
}