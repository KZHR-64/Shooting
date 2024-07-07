#pragma once
#include "DxLib.h"
#include "AbstractBullet.h"
#include <math.h>

using namespace std;

AbstractBullet::AbstractBullet(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle){
	manager = man;

	time = 0;
	live_flag = true;
	end_time = -1;
	end_flag = false;
	image = num;
	x = ini_x;
	y = ini_y;
	base_x = x;
	base_y = y;
	size_x = 1;
	size_y = 1;
	angle = ini_angle;
	SetSpeed(ini_speed);
	damage = 0;
	hit_player = false;
	hit_enemy = false;
	hit_map = false;
	breakable = false;
}

AbstractBullet::~AbstractBullet(){
	hit.clear(); //当たり判定のメモリを解放
}

//当たり判定の配置
void AbstractBullet::SetHit(float cx, float cy, float hit_size) {
	HitStruct new_hit;

	new_hit.angle = atan2f(cy, cx); //初期角度を設定
	new_hit.distance = sqrtf((cx * cx) + (cy * cy)); //本体との距離を設定
	new_hit.size = hit_size; //判定の大きさを設定
	new_hit.x = x;
	new_hit.y = y;

	hit.emplace_back(new_hit);
}

//消去するかを取得
bool AbstractBullet::GetEndFlag() {
	return end_flag;
}

//消去するかを設定
void AbstractBullet::SetEndFlag(bool flag) {
	end_flag = flag;
}

//弾の時間を返す
int AbstractBullet::GetTime() {
	return time;
}

//時間を設定(時間)
void AbstractBullet::SetTime(int set_time) {
	time = set_time;
}

//消滅までの時間を返す
int AbstractBullet::GetEndTime() {
	return end_time;
}

//消滅までの時間を設定
void AbstractBullet::SetEndTime(int set_time) {
	end_time = set_time;
}

//ダメージ値を返す
int AbstractBullet::GetDamage() {
	return damage;
}

//ダメージ値を設定
void AbstractBullet::SetDamage(int set_damage) {
	damage = set_damage;
}

//弾のx座標を返す
float AbstractBullet::GetX() {
	return x;
}

//弾のx座標を設定
void AbstractBullet::SetX(float set_x) {
	x = set_x;
}

//弾のy座標を返す
float AbstractBullet::GetY() {
	return y;
}

//弾のy座標を設定
void AbstractBullet::SetY(float set_y) {
	y = set_y;
}

//弾の元のx座標を返す
float AbstractBullet::GetBaseX() {
	return x;
}

//弾の元のx座標を設定
void AbstractBullet::SetBaseX(float set_x) {
	x = set_x;
}

//弾の元のy座標を返す
float AbstractBullet::GetBaseY() {
	return y;
}

//弾の元のy座標を設定
void AbstractBullet::SetBaseY(float set_y) {
	y = set_y;
}

//弾の横の大きさを返す
int AbstractBullet::GetSizeX() {
	return size_x;
}

//弾の横の大きさを設定
void AbstractBullet::SetSizeX(int set_size) {
	size_x = set_size;
}

//弾の縦の大きさを返す
int AbstractBullet::GetSizeY() {
	return size_y;
}

//弾の縦の大きさを設定
void AbstractBullet::SetSizeY(int set_size) {
	size_y = set_size;
}

//角度を基に速度を設定
void AbstractBullet::SetSpeed(float speed) {
	sx = speed * cosf(angle);
	sy = speed * sinf(angle);
}

//弾のx方向の速度を返す
float AbstractBullet::GetXSpeed() {
	return sx;
}

//弾のx方向の速度を設定
void AbstractBullet::SetXSpeed(float set_x) {
	sx = set_x;
}

//弾のy方向の速度を返す
float AbstractBullet::GetYSpeed() {
	return sy;
}

//弾のy方向の速度を設定
void AbstractBullet::SetYSpeed(float set_y) {
	sy = set_y;
}

//角度を取得
float AbstractBullet::GetAngle() {
	return angle;
}

//角度を設定(角度)
void AbstractBullet::SetAngle(float set_angle) {
	angle = set_angle;
}

//回転速度を取得
float AbstractBullet::GetSpinSpeed() {
	return 0.f;
}

//回転速度を設定(角度)
void AbstractBullet::SetSpinSpeed(float set_angle) {

}

//壊せるかを取得
bool AbstractBullet::GetBreakable() {
	return breakable;
}

//壊せるかを設定
void AbstractBullet::SetBreakable(bool flag) {
	breakable = flag;
}

//自機に当たるかを取得
bool AbstractBullet::GetHitPlayer() {
	return hit_player;
}

//自機に当たるかを設定
void AbstractBullet::SetHitPlayer(bool flag) {
	hit_player = flag;
}

//敵に当たるかを取得
bool AbstractBullet::GetHitEnemy() {
	return hit_enemy;
}

//敵に当たるかを設定
void AbstractBullet::SetHitEnemy(bool flag) {
	hit_enemy = flag;
}

//マップチップに当たるかを取得
bool AbstractBullet::GetHitMap() {
	return hit_map;
}

//マップチップに当たるかを設定
void AbstractBullet::SetHitMap(bool flag) {
	hit_map = flag;
}

//当たり判定の更新
void AbstractBullet::HitUpdate() {
	if (hit.size() <= 0) return;
	for (unsigned int i = 0; i < hit.size(); i++) {
		hit[i].x = x + (hit[i].distance * cosf(hit[i].angle + angle));
		hit[i].y = y + (hit[i].distance * sinf(hit[i].angle + angle));
	}
}

//当たり判定の描画
void AbstractBullet::DrawHit() {
	if (hit.size() <= 0) return;
	for (auto h : hit) {
		Display::Get_Instance()->HitDraw(h.x, h.y, h.size);
	}
}

//キャラクターとの当たり判定
int AbstractBullet::HitCheckChara(float cx, float cy, float hit_size, bool check_inhale) {
	if (hit.size() <= 0) return -1;

	for (auto h : hit) {
		float dif_x = cx - h.x;
		float dif_y = cy - h.y;
		float distance = sqrtf((dif_x * dif_x) + (dif_y * dif_y));

		if (distance <= hit_size + h.size) {
			//壊せる弾なら消す
			if (breakable) {
				end_flag = true;
			}
			return damage;
		}
	}

	return -1;
}

//マップチップとの当たり判定
void AbstractBullet::HitCheckMap(shared_ptr<MapChipManager> map) {
	
}