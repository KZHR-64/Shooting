#pragma once
#include "DxLib.h"
#include "Desdragud.h"

using namespace std;

//コンストラクタ
Desdragud::Desdragud(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {
	shared_ptr<AbstractEnemy> arm;
	left_shoulder_angle = atan2f(-20.f, -24.f);
	left_shoulder_distance = sqrtf((24.f * 24.f) + (20.f * 20.f));
	right_shoulder_angle = atan2f(-20.f, 24.f);
	right_shoulder_distance = sqrtf((24.f * 24.f) + (20.f * 20.f));

	left_arm_angle = atan2f(-18.f, -24.f);
	left_arm_distance = sqrtf((24.f * 24.f) + (18.f * 18.f));
	right_arm_angle = atan2f(-18.f, 24.f);
	right_arm_distance = sqrtf((24.f * 24.f) + (18.f * 18.f));

	left_arm_spin_angle = atan2f(0.f, 34.f);
	left_arm_spin_distance = sqrtf((34.f * 34.f));
	right_arm_spin_angle = atan2f(0.f, 34.f);
	right_arm_spin_distance = sqrtf((34.f * 34.f));

	left_arm_x = x + left_arm_angle * cosf(left_arm_angle + angle);
	left_arm_y = y + left_arm_angle * sinf(left_arm_angle + angle);
	right_arm_x = x + right_arm_distance * cosf(right_arm_distance + angle);
	right_arm_y = y + right_arm_distance * sinf(right_arm_distance + angle);

	SetHit(0.f, 0.f, 16.f);
	SetHit(0.f, -48.f, 16.f);
	SetHit(0.f, 32.f, 16.f);

	//腕
	arm = ene->SetEnemy(34, x, y, this);
	parts.emplace_back(arm);
	arm = ene->SetEnemy(34, x, y, this);
	parts.emplace_back(arm);
	//肩
	arm = ene->SetEnemy(35, x, y, this);
	arm->SetAngle(0.5f * PI);
	parts.emplace_back(arm);
	arm = ene->SetEnemy(35, x, y, this);
	arm->SetAngle(0.5f * PI);
	parts.emplace_back(arm);

	AbsUpdate();

	attack_num = 0;
}

//自機狙い弾とばらまき
void Desdragud::Attack1(shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect) {
	float px = manager->GetPlayerX();
	float py = manager->GetPlayerY();
	float top = (float)Display::Get_Instance()->GetScrollY() + 64.f; //判定上
	float bottom = (float)(Display::Get_Instance()->GetScrollY() + WINDOW_Y) - 64.f; //判定底

	if (time == 1) {
		sy = -2.f;
	}

	//上下の限界に達したら方向転換
	if (y <= top) {
		y = top;
		sy = 2.f;
	}

	if (bottom <= y) {
		y = bottom;
		sy = -2.f;
	}

	parts[2]->HomingSpin((3.f / 180.f) * PI, px, py);
	parts[3]->HomingSpin((3.f / 180.f) * PI, parts[3]->GetX() - 16.f, parts[3]->GetY());

	parts[0]->SetAngle(parts[2]->GetAngle());
	parts[1]->SetAngle(parts[3]->GetAngle());

	//一定時間ごとに弾を発射
	if (time % 45 == 0 && time < 450 && 0 < time) {
		//弾の位置を計算
		float shoot_x = parts[0]->GetX() + (24.f * cosf(parts[2]->GetAngle()));
		float shoot_y = parts[0]->GetY() + (24.f * sinf(parts[2]->GetAngle()));
		float shoot_x2 = parts[1]->GetX() + (24.f * cosf(parts[3]->GetAngle()));
		float shoot_y2 = parts[1]->GetY() + (24.f * sinf(parts[3]->GetAngle()));
		bullet->SetBullet(2, shoot_x + sx, shoot_y + sy, 6.f, parts[2]->GetAngle()); //弾を発射
		bullet->SetBullet(2, shoot_x2 + sx, shoot_y2 + sy, 4.f, parts[3]->GetAngle()); //弾を発射
		bullet->SetBullet(2, shoot_x2 + sx, shoot_y2 + sy, 4.f, parts[3]->GetAngle() + (60.f / 180.f) * PI); //弾を発射
		bullet->SetBullet(2, shoot_x2 + sx, shoot_y2 + sy, 4.f, parts[3]->GetAngle() - (60.f / 180.f) * PI); //弾を発射
		Sound::Get_Instance()->PlaySoundEffect(7); //効果音を鳴らす
	}

	//元の位置に戻る
	if (420 < time) {
		float center = (float)Display::Get_Instance()->GetScrollY() + (WINDOW_Y / 2); //上下移動の基準
		//基準に合わせて始めの速度を設定
		sy = (y < center) ? 2.f : -2.f;
		if (fabsf(center - y) < 3.f) {
			y = center;
			sy = 0.f;
			time = 0;
		}
	}
}

//ミサイル
void Desdragud::Attack2(shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect) {
	//一定時間ごとに弾を発射
	if (time % 60 == 0 && 0 < time) {
		shared_ptr<AbstractEnemy> new_enemy;
		new_enemy = manager->SetEnemy(6, x + 24.f , y - 16.f);
		new_enemy->SetAngle(-0.5f * PI);
	}

	if (time == 330) {
		time = 0;
	}
}

//チャージショット
void Desdragud::Attack3(shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect) {
	float px = manager->GetPlayerX();
	float py = manager->GetPlayerY();

	if (time % 90 < 60) {
		parts[2]->HomingSpin((3.f / 180.f) * PI, px, py);
		parts[3]->HomingSpin((3.f / 180.f) * PI, px, py);
	}

	parts[0]->SetAngle(parts[2]->GetAngle());
	parts[1]->SetAngle(parts[3]->GetAngle());

	//一定時間ごとに弾を発射
	if (time % 90 == 72) {
		//弾の位置を計算
		float shoot_x = parts[0]->GetX() + (24.f * cosf(parts[2]->GetAngle()));
		float shoot_y = parts[0]->GetY() + (24.f * sinf(parts[2]->GetAngle()));
		float shoot_x2 = parts[1]->GetX() + (24.f * cosf(parts[3]->GetAngle()));
		float shoot_y2 = parts[1]->GetY() + (24.f * sinf(parts[3]->GetAngle()));
		bullet->SetBullet(4, shoot_x + sx, shoot_y + sy, 12.f, parts[2]->GetAngle()); //弾を発射
		bullet->SetBullet(4, shoot_x2 + sx, shoot_y2 + sy, 12.f, parts[3]->GetAngle()); //弾を発射
		Sound::Get_Instance()->PlaySoundEffect(12); //効果音を鳴らす
	}

	if (time == 360) {
		time = 0;
	}
}

//デストラクタ
Desdragud::~Desdragud() {

}

//必ず行う更新
void Desdragud::AbsUpdate() {

	parts[0]->SetAngle(parts[2]->GetAngle());
	parts[1]->SetAngle(parts[3]->GetAngle());

	left_shoulder_x = x + (left_shoulder_distance * cosf(left_shoulder_angle + angle));
	left_shoulder_y = y + (left_shoulder_distance * sinf(left_shoulder_angle + angle));
	right_shoulder_x = x + (right_shoulder_distance * cosf(right_shoulder_angle + angle));
	right_shoulder_y = y + (right_shoulder_distance * sinf(right_shoulder_angle + angle));

	left_arm_x = x + (left_arm_distance * cosf(left_arm_angle + angle)) + (left_arm_spin_distance * cosf(left_arm_spin_angle + parts[0]->GetAngle()));
	left_arm_y = y + (left_arm_distance * sinf(left_arm_angle + angle)) + (left_arm_spin_distance * sinf(left_arm_spin_angle + parts[0]->GetAngle()));
	right_arm_x = x + (right_arm_distance * cosf(right_arm_angle + angle)) + (right_arm_spin_distance * cosf(right_arm_spin_angle + parts[1]->GetAngle()));
	right_arm_y = y + (right_arm_distance * sinf(right_arm_angle + angle)) + (right_arm_spin_distance * sinf(right_arm_spin_angle + parts[1]->GetAngle()));

	parts[2]->SetX(left_shoulder_x);
	parts[2]->SetY(left_shoulder_y);
	parts[3]->SetX(right_shoulder_x);
	parts[3]->SetY(right_shoulder_y);

	parts[0]->SetX(left_arm_x);
	parts[0]->SetY(left_arm_y);
	parts[1]->SetX(right_arm_x);
	parts[1]->SetY(right_arm_y);
}

//更新
void Desdragud::Update(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {
	//ボスでないなら逃亡
	if (!boss_flag) {
		if (time == 0) {
			sy = -1.f;
		}
		sy *= 1.1f;
		if (sy < -16.f) sy = -16.f;
		return;
	}

	switch (attack_num)
	{
	case 0:
		Attack1(bullet, effect);
		break;
	case 1:
		Attack2(bullet, effect);
		break;
	case 2:
		Attack3(bullet, effect);
		break;
	default:
		break;
	}

	//時間が0なら攻撃パターンを変更
	if (time == 0) {
		attack_num = (attack_num + 1) % 3;
	}
}

//描画
void Desdragud::Draw() {
	int hundle = Image::Get_Instance()->GetCharaImage(33, 0);
	parts[2]->Draw();
	parts[0]->Draw();
	Display::Get_Instance()->Draw(x, y, lr, angle, hundle, DX_BLENDMODE_NOBLEND);
	parts[3]->Draw();
	parts[1]->Draw();

}