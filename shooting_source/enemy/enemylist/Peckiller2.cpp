#pragma once
#include "DxLib.h"
#include "Peckiller2.h"

using namespace std;

//コンストラクタ
Peckiller2::Peckiller2(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {

	SetHit(0.f, 0.f, 16.f);
	speed = 0.f;
}

//デストラクタ
Peckiller2::~Peckiller2() {
}

//必ず行う更新
void Peckiller2::AbsUpdate() {

}

//更新
void Peckiller2::Update(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {
	float px = manager->GetPlayerX();
	float py = manager->GetPlayerY();

	if (time < 180) {
		Sound::Get_Instance()->PlaySoundEffect(5); //効果音を鳴らす
		HomingSpin((3.f / 180.f) * PI, px, py);
	}
	//一定時間したら加速
	else if (time == 180) {
		speed = 0.1f;
	}
	else if (180 < time) {
		speed *= 1.1f;
		if (6.f < speed) {
			speed = 6.f;
		}

		if (time % 6 == 0) {
			//煙の位置を計算
			float smoke_x = x + (-40.f * cosf(angle));
			float smoke_y = y + (-40.f * sinf(angle));
			effect->SetEffect(3, smoke_x, smoke_y); //煙を発生
		}
	}

	SetSpeed(speed);
}

//描画
void Peckiller2::Draw() {
	int hundle = Image::Get_Instance()->GetCharaImage(image, 0);
	float draw_angle = angle;
	if (0.5f * PI < angle || angle < -0.5f * PI) {
		lr = RIGHT;
		draw_angle += PI;
	}
	else {
		lr = LEFT;
	}

	Display::Get_Instance()->Draw(x, y, lr, draw_angle, hundle, DX_BLENDMODE_NOBLEND);
}