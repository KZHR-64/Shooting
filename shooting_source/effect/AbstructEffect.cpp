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

//�������邩���擾
bool AbstractEffect::GetEndFlag() {
	return end_flag;
}

//�������邩��ݒ�
void AbstractEffect::SetEndFlag(bool set_flag) {
	end_flag = set_flag;
}

//�G�t�F�N�g�̎��Ԃ�Ԃ�
int AbstractEffect::GetTime() {
	return time;
}

//���Ԃ�ݒ�(����)
void AbstractEffect::SetTime(int set_time) {
	time = set_time;
}

//�G�t�F�N�g��x���W��Ԃ�
float AbstractEffect::GetX() {
	return x;
}

//�G�t�F�N�g��x���W��ݒ�
void AbstractEffect::SetX(float set_x) {
	x = set_x;
}

//�G�t�F�N�g��y���W��Ԃ�
float AbstractEffect::GetY() {
	return y;
}

//�G�t�F�N�g��y���W��ݒ�
void AbstractEffect::SetY(float set_y) {
	y = set_y;
}

//�G�t�F�N�g�̌���x���W��Ԃ�
float AbstractEffect::GetBaseX() {
	return base_x;
}

//�G�t�F�N�g�̌���x���W��ݒ�
void AbstractEffect::SetBaseX(float set_x) {
	base_x = set_x;
}

//�G�t�F�N�g�̌���y���W��Ԃ�
float AbstractEffect::GetBaseY() {
	return base_y;
}

//�G�t�F�N�g�̌���y���W��ݒ�
void AbstractEffect::SetBaseY(float set_y) {
	base_y = set_y;
}

//�G�t�F�N�g��x�����̑��x��Ԃ�
float AbstractEffect::GetXSpeed() {
	return sx;
}

//�G�t�F�N�g��x�����̑��x��ݒ�
void AbstractEffect::SetXSpeed(float set_x) {
	sx = set_x;
}

//�G�t�F�N�g��y�����̑��x��Ԃ�
float AbstractEffect::GetYSpeed() {
	return sy;
}

//�G�t�F�N�g��y�����̑��x��ݒ�
void AbstractEffect::SetYSpeed(float set_y) {
	sy = set_y;
}

//�p�x���擾
float AbstractEffect::GetAngle() {
	return 0.f;
}

//�p�x��ݒ�(�p�x)
void AbstractEffect::SetAngle(float set_angle) {

}

//��]���x���擾
float AbstractEffect::GetSpinSpeed() {
	return 0.f;
}

//��]���x��ݒ�(�p�x)
void AbstractEffect::SetSpinSpeed(float set_angle) {

}