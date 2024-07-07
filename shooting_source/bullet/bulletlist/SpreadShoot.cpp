#pragma once
#include "DxLib.h"
#include "SpreadShoot.h"

using namespace std;

//コンストラクタ
SpreadShoot::SpreadShoot(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	speed = ini_speed;
}

//デストラクタ
SpreadShoot::~SpreadShoot() {

}

//更新
void SpreadShoot::Update(shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {

	//かなり減速したなら
	if (speed <= 0.1f) {
		Sound::Get_Instance()->PlaySoundEffect(10); //効果音を鳴らす
		end_flag = true;
		//炸裂
		for (int i = 0; i < 8; i++)
		{
			float shot_angle = (2.f * PI) * ((float)(i) / 8);
			manager->SetBullet(2, x, y, 6.f, shot_angle);
		}
	}
	//速度があるなら
	else {
		speed *= 0.95f; //徐々に減速
	}

	SetSpeed(speed);
}

//描画
void SpreadShoot::Draw() {
	int hundle = Image::Get_Instance()->GetBulletImage(image, 0);
	Display::Get_Instance()->Draw(x, y, LEFT, angle, hundle, DX_BLENDMODE_NOBLEND);
}