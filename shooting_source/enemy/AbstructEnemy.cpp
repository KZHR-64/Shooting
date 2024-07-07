#pragma once
#include "DxLib.h"
#include "AbstractEnemy.h"
#include <math.h>

using namespace std;

AbstractEnemy::AbstractEnemy(EnemyManager* man, int num, float ini_x, float ini_y){
	manager = man;

	time = 0;
	live_flag = true;
	end_flag = false;
	boss_flag = false;
	image = num;
	trance = 255;
	hp = 1;
	x = ini_x;
	y = ini_y;
	base_x = x;
	base_y = y;
	sx = 0.f;
	sy = 0.f;
	lr = LEFT;
	angle = 0.f;
	spin_speed = 0.00f;
	jump_time = 0;
	jump_flag = false;
	hit_flag = true;
	flying_flag = false;
	damaged = false;
	damage_time = false;
	inhale = false;
	hit_map = true;
	inhaled_flag = false;
	base_enemy = NULL; //本体は基本的にNULL
}

AbstractEnemy::~AbstractEnemy(){

	for (auto ene : parts) {
		ene->SetEndFlag(true); //パーツを消去
		ene.reset();
	}
	parts.clear();
	hit.clear(); //当たり判定のメモリを解放
}

//当たり判定の配置
void AbstractEnemy::SetHit(float cx, float cy, float hit_size) {
	HitStruct new_hit;

	new_hit.angle = atan2f(cy, cx); //初期角度を設定
	new_hit.distance = sqrtf((cx * cx) + (cy * cy)); //本体との距離を設定
	new_hit.size = hit_size; //判定の大きさを設定
	new_hit.x = x;
	new_hit.y = y;

	hit.emplace_back(new_hit);
}

//本体を取得
AbstractEnemy* AbstractEnemy::GetBase() {
	return base_enemy;
}

//本体を設定
void AbstractEnemy::SetBase(AbstractEnemy* base) {
	base_enemy = base;
}

//消去するかを取得
bool AbstractEnemy::GetEndFlag() {
	return end_flag;
}

//消去するかを設定
void AbstractEnemy::SetEndFlag(bool flag) {
	end_flag = flag;
}

//ボスかを取得
bool AbstractEnemy::GetBossFlag() {
	return boss_flag;
}

//ボスかを設定
void AbstractEnemy::SetBossFlag(int rank) {
	boss_flag = (0 < rank); //格が0以上ならボス
}

//当たり判定を取得
bool AbstractEnemy::GetHitFlag() {
	return hit_flag;
}

//当たり判定を設定
void AbstractEnemy::SetHitFlag(bool flag) {
	hit_flag = flag;
}

//透明度を設定
void AbstractEnemy::SetTrance(int set_trance) {
	trance = set_trance;
}

//敵の時間を返す
int AbstractEnemy::GetTime() {
	return time;
}

//時間を設定
void AbstractEnemy::SetTime(int set_time) {
	time = set_time;
}

//HPを返す
int AbstractEnemy::GetHp() {
	return hp;
}

//HPを設定
void AbstractEnemy::SetHp(int set_hp) {
	hp = set_hp;
}

//敵のx座標を返す
float AbstractEnemy::GetX() {
	return x;
}

//敵のx座標を設定
void AbstractEnemy::SetX(float set_x) {
	x = set_x;
}

//敵のy座標を返す
float AbstractEnemy::GetY() {
	return y;
}

//敵のy座標を設定
void AbstractEnemy::SetY(float set_y) {
	y = set_y;
}

//敵の元のx座標を返す
float AbstractEnemy::GetBaseX() {
	return x;
}

//敵の元のx座標を設定
void AbstractEnemy::SetBaseX(float set_x) {
	x = set_x;
}

//敵の元のy座標を返す
float AbstractEnemy::GetBaseY() {
	return y;
}

//敵の元のy座標を設定
void AbstractEnemy::SetBaseY(float set_y) {
	y = set_y;
}

//角度を基に速度を設定
void AbstractEnemy::SetSpeed(float speed) {
	sx = speed * cosf(angle);
	sy = speed * sinf(angle);
}

//敵のx方向の速度を返す
float AbstractEnemy::GetXSpeed() {
	return sx;
}

//敵のx方向の速度を設定
void AbstractEnemy::SetXSpeed(float set_x) {
	sx = set_x;
}

//敵のy方向の速度を返す
float AbstractEnemy::GetYSpeed() {
	return sy;
}

//敵のy方向の速度を設定
void AbstractEnemy::SetYSpeed(float set_y) {
	sy = set_y;
}

//角度を取得
float AbstractEnemy::GetAngle() {
	return angle;
}

//角度を設定(角度)
void AbstractEnemy::SetAngle(float set_angle) {
	angle = set_angle;
}

//回転速度を取得
float AbstractEnemy::GetSpinSpeed() {
	return spin_speed;
}

//回転速度を設定(角度)
void AbstractEnemy::SetSpinSpeed(float set_angle) {
	spin_speed = set_angle;
}

//向きを取得
bool AbstractEnemy::GetLr() {
	return lr;
}

//向きを設定
void AbstractEnemy::SetLr(bool set_lr) {
	lr = set_lr;
}

//飛んでいるかを取得
bool AbstractEnemy::GetFlying() {
	return flying_flag;
}

//飛んでいるかを設定
void AbstractEnemy::SetFlying(bool flag) {
	flying_flag = flag;
}

//ダメージを受けているかを取得
bool AbstractEnemy::GetDamaged() {
	return damaged;
}

//吸い込めるかを取得
bool AbstractEnemy::GetInhale() {
	return inhale;
}

//吸い込めるかを設定
void AbstractEnemy::SetInhale(bool flag) {
	inhale = flag;
}

//マップチップに当たるかを取得
bool AbstractEnemy::GetHitMap() {
	return hit_map;
}

//マップチップに当たるかを設定
void AbstractEnemy::SetHitMap(bool flag) {
	hit_map = flag;
}

//吸い込まれているかを取得
bool AbstractEnemy::GetInhaledFlag() {
	return inhaled_flag;
}

//吸い込まれているかを設定
void AbstractEnemy::SetInhaledFlag(bool flag) {
	inhaled_flag = flag;
}

//目標に向けての速度を調整
void AbstractEnemy::Homing(float set_spin_speed, float speed, float set_x, float set_y) {
	float vx = sx;
	float vy = sy;
	float vx1, vx2, vx3;
	float vy1, vy2, vy3;

	//相対位置ベクトルを計算
	float svx = set_x - x;
	float svy = set_y - y;

	//自機へのベクトルを計算
	float v = sqrtf(svx * svx + svy * svy);
	if (v) {
		vx1 = svx / v * speed;
		vy1 = svy / v * speed;
	}
	else {
		vx1 = 0.f;
		vy1 = 1.f;
	}

	//右回りの場合のベクトルを計算
	vx2 = cosf(set_spin_speed) * vx - sinf(set_spin_speed) * vy;
	vy2 = sinf(set_spin_speed) * vx + cosf(set_spin_speed) * vy;

	//自機方向のベクトルが回転速度以内の場合
	if (vx * vx2 + vy * vy2 <= vx * vx1 + vy * vy1) {
		vx = vx1;
		vy = vy1;
	}
	//速度以上の場合
	else
	{
		//左回りの場合のベクトルを計算
		vx3 = cosf(set_spin_speed) * vx + sinf(set_spin_speed) * vy;
		vy3 = -sinf(set_spin_speed) * vx + cosf(set_spin_speed) * vy;

		//右回りの場合
		if (svx * vx3 + svy * vx3 <= svx * vx2 + svy * vx2) {
			vx = vx2;
			vy = vy2;
		}
		//左回りの場合
		else {
			vx = vx3;
			vy = vy3;
		}
	}

	//x,y方向から角度を計算
	angle = atan2f(vy, vx);
	sx = vx;
	sy = vy;
}

//目標に向けて回転
void AbstractEnemy::HomingSpin(float set_spin_speed, float set_x, float set_y, bool use_base) {
	//目標への角度を計算
	float target_angle = (use_base) ? atan2f(set_y - base_y, set_x - base_x) : atan2f(set_y - y, set_x - x);

	//キャラの角度を計算用に編集
	angle = atan2f(sinf(angle), cosf(angle));

	//両方の角度の正負が同じ場合
	if (0.f <= target_angle * angle) {
		//角度の差が回転角度未満の場合
		if (fabsf(target_angle - angle) <= set_spin_speed) {
			angle = target_angle;
		}
		//角度以上の場合
		else {
			//目標角度が大きい場合は足す
			if (angle < target_angle) {
				angle += set_spin_speed;
			}
			//小さければ引く
			else {
				angle -= set_spin_speed;
			}
		}
	}
	//異なる場合
	else {
		//右側、左の角度の差を計算
		float sub_right = fabsf(target_angle) + fabsf(angle);
		float sub_left = fabsf(2.f * PI - sub_right);
		//回転方向を設定
		float spin = (0.f < angle) ? set_spin_speed : -set_spin_speed;
		//どちらかの角度の差が回転角度以下の場合
		if (sub_right <= set_spin_speed || sub_left <= set_spin_speed) {
			angle = target_angle;
		}
		//角度以上の場合
		else {
			//差が小さい方へ回転
			if (sub_right < sub_left) {
				angle -= spin;
			}
			else {
				angle += spin;
			}
		}
	}
}

//パーツを回転させる
void AbstractEnemy::Spin(float set_spin_speed, float spin_max, float spin_min) {
	angle += set_spin_speed; //パーツを回転させる

	//上限に達したら
	if (spin_max < angle) {
		angle = spin_max;
	}
	//下限に達したら
	if (angle < spin_min) {
		angle = spin_min;
	}
}

//当たり判定の更新
void AbstractEnemy::HitUpdate() {
	if (hit.size() <= 0) return;
	for (unsigned int i = 0; i < hit.size(); i++) {
		hit[i].x = x + (hit[i].distance * cosf(hit[i].angle + angle));
		hit[i].y = y + (hit[i].distance * sinf(hit[i].angle + angle));
	}
}

//ダメージ処理
bool AbstractEnemy::HitDamage(int damage_num) {
	damaged = true;
	damage_time = 6;

	//本体がいるならそっちにダメージ
	if (base_enemy != NULL) {
		bool flag = base_enemy->HitDamage(damage_num);
		return flag;
	}
	
	hp -= damage_num;

	//HPが0になったら
	if (hp <= 0) {
		end_flag = true; //敵を消す
		return true;
	}

	return false;
}

//当たり判定の描画
void AbstractEnemy::DrawHit() {
	if (hit.size() <= 0) return;
	for (auto h : hit) {
		Display::Get_Instance()->HitDraw(h.x, h.y, h.size);
	}
}

//位置の調節
void AbstractEnemy::AdjustPosition(shared_ptr<MapChipManager> map) {
	shared_ptr<AbstractMapChip> mapchip;

	bool step_flag = false; //マップチップに乗っているか
	bool left_hit = false; //左側が当たっているか
	bool right_hit = false; //右側が当たっているか
	bool top_hit = false; //上側が当たっているか
	bool bottom_hit = false; //下側が当たっているか

	float sub_x = 0.f; //足場にどれだけめり込んでいるか

	angle += spin_speed; //回転

	x += sx; //行く予定の座標を決定

	//左右との判定
	for (unsigned int i = 0; i < hit.size(); i++) {
		mapchip = map->HitCheckLeft(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL) {
			left_hit = true; //左側が当たったことに
			sub_x = (hit[i].x - hit[i].size) - (mapchip->GetX() + 4.f * mapchip->GetSizeX());
			x += fabsf(sub_x);
			sx = 0.f;
			HitUpdate();
			mapchip = map->HitCheckLeft(hit[i].x, hit[i].y, hit[i].size);
		}
		mapchip = map->HitCheckRight(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL) {
			right_hit = true; //右側が当たったことに
			sub_x = (hit[i].x + hit[i].size) - (mapchip->GetX() - 4.f * mapchip->GetSizeX());
			x -= fabsf(sub_x);
			sx = 0.f;
			HitUpdate();
			mapchip = map->HitCheckRight(hit[i].x, hit[i].y, hit[i].size);
		}
	}

	//両側が当たっていたら
	if (left_hit && right_hit) {
		hp = 0; //HPを0に
		damaged = true;
		//速度を初期化
		sx = 0.f;
		sy = 0.f;
		return;
	}

	//ジャンプ中
	if (jump_flag && !flying_flag){
		//上昇時間中なら
		if (0 < jump_time) {
			jump_time--; //時間を減少
		}
		else
		{
			if (sy < 0.4f && sy > -0.4f) sy = 0.4f;
			sy += fabsf(sy * 1.3f); //速度を1.3(0.7)倍(飛行中は1.1倍)する
			if (sy > 10.f) sy = 10.f;
		}
	}
	
	y += sy; //行く予定の座標を決定
	HitUpdate(); //当たり判定を更新
	
	//上下との判定
	for (unsigned int i = 0; i < hit.size(); i++) {
		mapchip = map->HitCheckTop(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL) {
			top_hit = true; //上側が当たったことに
			sub_x = (hit[i].y - hit[i].size) - (mapchip->GetY() + 8.f * mapchip->GetSizeY());
			y += fabsf(sub_x);
			sy = 0.f;
			HitUpdate();
			mapchip = map->HitCheckTop(hit[i].x, hit[i].y, hit[i].size);
		}
		mapchip = map->HitCheckBottom(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL) {
			bottom_hit = true; //下側が当たったことに
			sub_x = (hit[i].y + hit[i].size) - (mapchip->GetY());
			y -= fabsf(sub_x);
			sy = 0.f;
			HitUpdate();
			mapchip = map->HitCheckBottom(hit[i].x, hit[i].y, hit[i].size);
		}
	}

	//両側が当たっていたら
	if (top_hit && bottom_hit) {
		hp = 0; //HPを0に
		damaged = true;
		//速度を初期化
		sx = 0.f;
		sy = 0.f;
		return;
	}
}

//弾に当たっているか
void AbstractEnemy::HitCheckBullet(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {
	if (hit.size() <= 0) return;

	bool flag = false;

	for (auto h : hit) {
		int damage = bullet->HitCheckChara(h.x, h.y, h.size, false, true);

		if (0 < damage && !damaged) {
			//hp -= damage;
			//damaged = true;
			//damage_time = 6;
			flag = HitDamage(damage);
		}
	}

	//HPが0になったら
	if (flag) {
		//end_flag = true; //敵を消す
		effect->SetEffect(1, x, y); //爆発
	}
}

//敵に当たっているか
void AbstractEnemy::HitCheckEnemy(float cx, float cy, float hit_size, shared_ptr<EffectManager> effect) {
	if (hit.size() <= 0 || !hit_flag) return;

	for (auto h : hit) {

		
	}

}

//キャラクターとの当たり判定
bool AbstractEnemy::HitCheckChara(float cx, float cy, float hit_size, bool check_hit) {
	if (hit.size() <= 0) return false;

	for (auto h : hit) {

		float dif_x = cx - h.x;
		float dif_y = cy - h.y;
		float distance = sqrtf((dif_x * dif_x) + (dif_y * dif_y));

		if (distance <= hit_size + h.size) {
			return true;
		}
	}

	return false;
}

//タイマー関連の更新
void AbstractEnemy::Timer() {
	time++;
	if (0 < damage_time) {
		damage_time--;
		if (damage_time <= 0) {
			damaged = false;
		}
	}
}