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

//���삷�邩���擾
bool AbstractMapChip::GetLiveFlag() {
	return live_flag;
}

//���삷�邩��ݒ�
void AbstractMapChip::SetLiveFlag(bool flag) {
	live_flag = flag;
}

//�`�悷�邩���擾
bool AbstractMapChip::GetDrawFlag() {
	return draw_flag;
}

//�`�悷�邩��ݒ�
void AbstractMapChip::SetDrawFlag(bool flag) {
	draw_flag = flag;
}

//�}�b�v�`�b�v�̎��Ԃ�Ԃ�
int AbstractMapChip::GetTime() {
	return time;
}

//���Ԃ�ݒ�(����)
void AbstractMapChip::SetTime(int set_time) {
	time = set_time;
}

//�}�b�v�`�b�v��x���W��Ԃ�
float AbstractMapChip::GetX() {
	return x;
}

//�}�b�v�`�b�v��x���W��ݒ�
void AbstractMapChip::SetX(float set_x) {
	x = set_x;
}

//�}�b�v�`�b�v��y���W��Ԃ�
float AbstractMapChip::GetY() {
	return y;
}

//�}�b�v�`�b�v��y���W��ݒ�
void AbstractMapChip::SetY(float set_y) {
	y = set_y;
}

//�}�b�v�`�b�v�̌���x���W��Ԃ�
float AbstractMapChip::GetBaseX() {
	return x;
}

//�}�b�v�`�b�v�̌���x���W��ݒ�
void AbstractMapChip::SetBaseX(float set_x) {
	x = set_x;
}

//�}�b�v�`�b�v�̌���y���W��Ԃ�
float AbstractMapChip::GetBaseY() {
	return y;
}

//�}�b�v�`�b�v�̌���y���W��ݒ�
void AbstractMapChip::SetBaseY(float set_y) {
	y = set_y;
}

//�}�b�v�`�b�v�̉��̑傫����Ԃ�
int AbstractMapChip::GetSizeX() {
	return size_x;
}

//�}�b�v�`�b�v�̉��̑傫����ݒ�
void AbstractMapChip::SetSizeX(int set_size) {
	size_x = set_size;
}

//�}�b�v�`�b�v�̏c�̑傫����Ԃ�
int AbstractMapChip::GetSizeY() {
	return size_y;
}

//�}�b�v�`�b�v�̏c�̑傫����ݒ�
void AbstractMapChip::SetSizeY(int set_size) {
	size_y = set_size;
}

//�}�b�v�`�b�v��x�����̑��x��Ԃ�
float AbstractMapChip::GetXSpeed() {
	return sx;
}

//�}�b�v�`�b�v��x�����̑��x��ݒ�
void AbstractMapChip::SetXSpeed(float set_x) {
	sx = set_x;
}

//�}�b�v�`�b�v��y�����̑��x��Ԃ�
float AbstractMapChip::GetYSpeed() {
	return sy;
}

//�}�b�v�`�b�v��y�����̑��x��ݒ�
void AbstractMapChip::SetYSpeed(float set_y) {
	sy = set_y;
}

//�p�x���擾
float AbstractMapChip::GetAngle() {
	return 0.f;
}

//�p�x��ݒ�(�p�x)
void AbstractMapChip::SetAngle(float set_angle) {

}

//��]���x���擾
float AbstractMapChip::GetSpinSpeed() {
	return 0.f;
}

//��]���x��ݒ�(�p�x)
void AbstractMapChip::SetSpinSpeed(float set_angle) {

}

//�����蔻����擾
bool AbstractMapChip::GetHitFlag() {
	return hit_flag;
}

//�����蔻���ݒ�
void AbstractMapChip::SetHitFlag(bool flag) {
	hit_flag = flag;
}

//�z�����߂邩���擾
bool AbstractMapChip::GetInhale() {
	return inhale;
}

//�z�����߂邩��ݒ�
void AbstractMapChip::SetInhale(bool flag) {
	inhale = flag;
}

//�󂹂邩���擾
bool AbstractMapChip::GetBreakable() {
	return breakable;
}

//�󂹂邩��ݒ�
void AbstractMapChip::SetBreakable(bool flag) {
	breakable = flag;
}

//�z�����܂�Ă��邩���擾
bool AbstractMapChip::GetInhaledFlag() {
	return inhaled_flag;
}

//�z�����܂�Ă��邩��ݒ�
void AbstractMapChip::SetInhaledFlag(bool flag) {
	inhaled_flag = flag;
}