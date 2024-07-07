#pragma once
#include "DxLib.h"
#include "Missile.h"

using namespace std;

//コンストラクタ
Missile::Missile(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {

	SetHit(0.f, 0.f, 16.f);
	speed = 4.f;
	angle = PI;
}

//デストラクタ
Missile::~Missile() {
}

//必ず行う更新
void Missile::AbsUpdate() {

}

//更新
void Missile::Update(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {
	float px = manager->GetPlayerX();
	float py = manager->GetPlayerY();
	
	if (time == 0) {
		Sound::Get_Instance()->PlaySoundEffect(11); //効果音を鳴らす
	}

	//一定時間したら追尾開始
	if (30 < time && time < 120) {
		//Homing((3.f / 180.f) * PI, 4.f, px, py);
		HomingSpin((3.f / 180.f) * PI, px, py);
	}

	if (time % 6 == 0) {
		//煙の位置を計算
		float smoke_x = x + (-16.f * cosf(angle));
		float smoke_y = y + (-16.f * sinf(angle));
		effect->SetEffect(3, smoke_x, smoke_y); //煙を発生
	}

	SetSpeed(speed);
}

//描画
void Missile::Draw() {
	int hundle = Image::Get_Instance()->GetCharaImage(image, 0);
	Display::Get_Instance()->Draw(x, y, lr, angle, hundle, DX_BLENDMODE_NOBLEND);
}