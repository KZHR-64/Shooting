#pragma once
#include "DxLib.h"
#include "DesdragudArm.h"

using namespace std;

//コンストラクタ
DesdragudArm::DesdragudArm(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {

	SetHit(0.f, 0.f, 16.f);
}

//デストラクタ
DesdragudArm::~DesdragudArm() {

}

//必ず行う更新
void DesdragudArm::AbsUpdate() {
	
}

//更新
void DesdragudArm::Update(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {

}

//描画
void DesdragudArm::Draw() {
	int hundle = Image::Get_Instance()->GetCharaImage(34, 0);
	Display::Get_Instance()->Draw(x, y, lr, angle, hundle, DX_BLENDMODE_NOBLEND);
}