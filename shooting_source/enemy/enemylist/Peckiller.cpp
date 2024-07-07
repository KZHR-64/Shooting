#pragma once
#include "DxLib.h"
#include "Peckiller.h"

using namespace std;

//コンストラクタ
Peckiller::Peckiller(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {

	SetHit(0.f, 0.f, 16.f);

	lr = RIGHT;
}

//デストラクタ
Peckiller::~Peckiller() {
}

//必ず行う更新
void Peckiller::AbsUpdate() {

}

//更新
void Peckiller::Update(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {
	//一定時間したら加速
	if (time == 120) {
		Sound::Get_Instance()->PlaySoundEffect(5); //効果音を鳴らす
		sx = -0.1f;
	}
	else if (120 < time) {
		sx *= 1.1f;
		if (sx < -6.f) {
			sx = -6.f;
		}
	}

	if (time % 6 == 0 && 120 < time) {
		//煙の位置を計算
		float smoke_x = x + (40.f * cosf(angle));
		float smoke_y = y + (40.f * sinf(angle));
		effect->SetEffect(3, smoke_x, smoke_y); //煙を発生
	}
}

//描画
void Peckiller::Draw() {
	int hundle = Image::Get_Instance()->GetCharaImage(image, 0);
	Display::Get_Instance()->Draw(x, y, lr, angle, hundle, DX_BLENDMODE_NOBLEND);
}