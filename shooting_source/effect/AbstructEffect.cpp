#pragma once
#include "DxLib.h"
#include "AbstractEffect.h"
#include <math.h>

using namespace std;

AbstractEffect::AbstractEffect(EffectManager* man, int num, float ini_x, float ini_y){
	manager = man;

	flag = true;
	time = 0;
	end_flag = false;
	image = num;
	x = ini_x;
	y = ini_y;
	base_x = x;
	base_y = y;
	sx = 0.f;
	sy = 0.f;
	angle = 0.f;
}

AbstractEffect::~AbstractEffect(){

}

//消去するかを取得
bool AbstractEffect::GetEndFlag() {
	return end_flag;
}

//消去するかを設定
void AbstractEffect::SetEndFlag(bool set_flag) {
	end_flag = set_flag;
}

//エフェクトの時間を返す
int AbstractEffect::GetTime() {
	return time;
}

//時間を設定(時間)
void AbstractEffect::SetTime(int set_time) {
	time = set_time;
}

//エフェクトのx座標を返す
float AbstractEffect::GetX() {
	return x;
}

//エフェクトのx座標を設定
void AbstractEffect::SetX(float set_x) {
	x = set_x;
}

//エフェクトのy座標を返す
float AbstractEffect::GetY() {
	return y;
}

//エフェクトのy座標を設定
void AbstractEffect::SetY(float set_y) {
	y = set_y;
}

//エフェクトの元のx座標を返す
float AbstractEffect::GetBaseX() {
	return base_x;
}

//エフェクトの元のx座標を設定
void AbstractEffect::SetBaseX(float set_x) {
	base_x = set_x;
}

//エフェクトの元のy座標を返す
float AbstractEffect::GetBaseY() {
	return base_y;
}

//エフェクトの元のy座標を設定
void AbstractEffect::SetBaseY(float set_y) {
	base_y = set_y;
}

//エフェクトのx方向の速度を返す
float AbstractEffect::GetXSpeed() {
	return sx;
}

//エフェクトのx方向の速度を設定
void AbstractEffect::SetXSpeed(float set_x) {
	sx = set_x;
}

//エフェクトのy方向の速度を返す
float AbstractEffect::GetYSpeed() {
	return sy;
}

//エフェクトのy方向の速度を設定
void AbstractEffect::SetYSpeed(float set_y) {
	sy = set_y;
}

//角度を取得
float AbstractEffect::GetAngle() {
	return 0.f;
}

//角度を設定(角度)
void AbstractEffect::SetAngle(float set_angle) {

}

//回転速度を取得
float AbstractEffect::GetSpinSpeed() {
	return 0.f;
}

//回転速度を設定(角度)
void AbstractEffect::SetSpinSpeed(float set_angle) {

}