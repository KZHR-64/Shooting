#pragma once
#include "DxLib.h"
#include "Raidrone3.h"

using namespace std;

//コンストラクタ
Raidrone3::Raidrone3(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	hundle_num = 0;

	SetHit(0.f, 0.f, 16.f);

	float center = (float)Display::Get_Instance()->GetScrollY() + (WINDOW_Y / 2); //上下移動の基準
	//基準に合わせて始めの速度を設定
	sy = (ini_y < center) ? 2.f : -2.f;
}

//デストラクタ
Raidrone3::~Raidrone3() {
}

//必ず行う更新
void Raidrone3::AbsUpdate() {
	hundle_num = time % 6 / 3;
}

//更新
void Raidrone3::Update(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {
	
}

//描画
void Raidrone3::Draw() {
	int hundle = Image::Get_Instance()->GetCharaImage(image, hundle_num);
	Display::Get_Instance()->Draw(x, y, lr, angle, hundle, DX_BLENDMODE_NOBLEND);
}