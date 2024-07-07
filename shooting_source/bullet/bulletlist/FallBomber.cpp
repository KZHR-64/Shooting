#pragma once
#include "DxLib.h"
#include "FallBomber.h"

using namespace std;

//コンストラクタ
FallBomber::FallBomber(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle) : AbstractBullet(man, num, ini_x, ini_y, ini_speed, ini_angle) {
	angle = 1.5f * PI;
	SetSpeed(4.f);
}

//デストラクタ
FallBomber::~FallBomber() {

}

//更新
void FallBomber::Update(shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {
	float px = manager->GetPlayerX(); //自機のx座標
	float top = (float)Display::Get_Instance()->GetScrollY(); //画面上
	
	//画面外に出たら
	if (y < top - (8.f * size_y) && sy < -1.f) {
		time = 0;
		SetSpeed(0.f);
	}

	//画面外に出てからしばらく経ったら
	if (time == 12 && -0.1f < sy) {
		x = px - 128.f + (float)GetRand(256);
		angle = 0.5f * PI; //角度を設定
		SetSpeed(4.f);
	}
}

//描画
void FallBomber::Draw() {
	int hundle = Image::Get_Instance()->GetBulletImage(image, 0);
	Display::Get_Instance()->Draw(x, y, LEFT, angle, hundle, DX_BLENDMODE_NOBLEND);
}