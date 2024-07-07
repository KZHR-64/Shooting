#pragma once
#include "DxLib.h"
#include "Raidrone2.h"

using namespace std;

//コンストラクタ
Raidrone2::Raidrone2(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	hundle_num = 0;

	SetHit(0.f, 0.f, 16.f);

	float center = (float)Display::Get_Instance()->GetScrollY() + (WINDOW_Y / 2); //上下移動の基準
	//基準に合わせて始めの速度を設定
	speed_angle = (ini_y < center) ? 0.f : PI;
}

//デストラクタ
Raidrone2::~Raidrone2() {
}

//必ず行う更新
void Raidrone2::AbsUpdate() {
	hundle_num = time % 6 / 3;
}

//更新
void Raidrone2::Update(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {
	sy = 4.f * sinf(speed_angle);

	speed_angle += (PI / 72.f);

	if (2.f * PI < speed_angle) {
		speed_angle -= 2.f * PI;
	}
}

//描画
void Raidrone2::Draw() {
	int hundle = Image::Get_Instance()->GetCharaImage(image, hundle_num);
	Display::Get_Instance()->Draw(x, y, lr, angle, hundle, DX_BLENDMODE_NOBLEND);
}