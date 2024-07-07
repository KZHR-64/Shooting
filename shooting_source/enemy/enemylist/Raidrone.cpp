#pragma once
#include "DxLib.h"
#include "Raidrone.h"

using namespace std;

//コンストラクタ
Raidrone::Raidrone(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	hundle_num = 0;

	SetHit(0.f, 0.f, 16.f);
}

//デストラクタ
Raidrone::~Raidrone() {
}

//必ず行う更新
void Raidrone::AbsUpdate() {
	hundle_num = time % 6 / 3;
}

//更新
void Raidrone::Update(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {
	
}

//描画
void Raidrone::Draw() {
	int hundle = Image::Get_Instance()->GetCharaImage(image, hundle_num);
	Display::Get_Instance()->Draw(x, y, lr, angle, hundle, DX_BLENDMODE_NOBLEND);
}