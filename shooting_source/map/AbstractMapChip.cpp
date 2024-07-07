#pragma once
#include "DxLib.h"
#include "AbstractMapChip.h"
#include <math.h>

using namespace std;

AbstractMapChip::AbstractMapChip(MapChipManager* man, int num){
	manager = man;

	live_flag = true;
	draw_flag = true;
	time = 0;
	image = num;
	x = 0.f;
	y = 0.f;
	base_x = x;
	base_y = y;
	size_x = 1;
	size_y = 1;
	sx = 0.f;
	sy = 0.f;
	angle = 0.f;
	breakable = false;
	inhale = false;
	inhaled_flag = false;
	hit_flag = true;
}

AbstractMapChip::~AbstractMapChip(){

}

//動作するかを取得
bool AbstractMapChip::GetLiveFlag() {
	return live_flag;
}

//動作するかを設定
void AbstractMapChip::SetLiveFlag(bool flag) {
	live_flag = flag;
}

//描画するかを取得
bool AbstractMapChip::GetDrawFlag() {
	return draw_flag;
}

//描画するかを設定
void AbstractMapChip::SetDrawFlag(bool flag) {
	draw_flag = flag;
}

//マップチップの時間を返す
int AbstractMapChip::GetTime() {
	return time;
}

//時間を設定(時間)
void AbstractMapChip::SetTime(int set_time) {
	time = set_time;
}

//マップチップのx座標を返す
float AbstractMapChip::GetX() {
	return x;
}

//マップチップのx座標を設定
void AbstractMapChip::SetX(float set_x) {
	x = set_x;
}

//マップチップのy座標を返す
float AbstractMapChip::GetY() {
	return y;
}

//マップチップのy座標を設定
void AbstractMapChip::SetY(float set_y) {
	y = set_y;
}

//マップチップの元のx座標を返す
float AbstractMapChip::GetBaseX() {
	return x;
}

//マップチップの元のx座標を設定
void AbstractMapChip::SetBaseX(float set_x) {
	x = set_x;
}

//マップチップの元のy座標を返す
float AbstractMapChip::GetBaseY() {
	return y;
}

//マップチップの元のy座標を設定
void AbstractMapChip::SetBaseY(float set_y) {
	y = set_y;
}

//マップチップの横の大きさを返す
int AbstractMapChip::GetSizeX() {
	return size_x;
}

//マップチップの横の大きさを設定
void AbstractMapChip::SetSizeX(int set_size) {
	size_x = set_size;
}

//マップチップの縦の大きさを返す
int AbstractMapChip::GetSizeY() {
	return size_y;
}

//マップチップの縦の大きさを設定
void AbstractMapChip::SetSizeY(int set_size) {
	size_y = set_size;
}

//マップチップのx方向の速度を返す
float AbstractMapChip::GetXSpeed() {
	return sx;
}

//マップチップのx方向の速度を設定
void AbstractMapChip::SetXSpeed(float set_x) {
	sx = set_x;
}

//マップチップのy方向の速度を返す
float AbstractMapChip::GetYSpeed() {
	return sy;
}

//マップチップのy方向の速度を設定
void AbstractMapChip::SetYSpeed(float set_y) {
	sy = set_y;
}

//角度を取得
float AbstractMapChip::GetAngle() {
	return 0.f;
}

//角度を設定(角度)
void AbstractMapChip::SetAngle(float set_angle) {

}

//回転速度を取得
float AbstractMapChip::GetSpinSpeed() {
	return 0.f;
}

//回転速度を設定(角度)
void AbstractMapChip::SetSpinSpeed(float set_angle) {

}

//当たり判定を取得
bool AbstractMapChip::GetHitFlag() {
	return hit_flag;
}

//当たり判定を設定
void AbstractMapChip::SetHitFlag(bool flag) {
	hit_flag = flag;
}

//吸い込めるかを取得
bool AbstractMapChip::GetInhale() {
	return inhale;
}

//吸い込めるかを設定
void AbstractMapChip::SetInhale(bool flag) {
	inhale = flag;
}

//壊せるかを取得
bool AbstractMapChip::GetBreakable() {
	return breakable;
}

//壊せるかを設定
void AbstractMapChip::SetBreakable(bool flag) {
	breakable = flag;
}

//吸い込まれているかを取得
bool AbstractMapChip::GetInhaledFlag() {
	return inhaled_flag;
}

//吸い込まれているかを設定
void AbstractMapChip::SetInhaledFlag(bool flag) {
	inhaled_flag = flag;
}