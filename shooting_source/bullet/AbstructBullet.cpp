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
	hit.clear(); //�����蔻��̃����������
}

//�����蔻��̔z�u
void AbstractBullet::SetHit(float cx, float cy, float hit_size) {
	HitStruct new_hit;

	new_hit.angle = atan2f(cy, cx); //�����p�x��ݒ�
	new_hit.distance = sqrtf((cx * cx) + (cy * cy)); //�{�̂Ƃ̋�����ݒ�
	new_hit.size = hit_size; //����̑傫����ݒ�
	new_hit.x = x;
	new_hit.y = y;

	hit.emplace_back(new_hit);
}

//�������邩���擾
bool AbstractBullet::GetEndFlag() {
	return end_flag;
}

//�������邩��ݒ�
void AbstractBullet::SetEndFlag(bool flag) {
	end_flag = flag;
}

//�e�̎��Ԃ�Ԃ�
int AbstractBullet::GetTime() {
	return time;
}

//���Ԃ�ݒ�(����)
void AbstractBullet::SetTime(int set_time) {
	time = set_time;
}

//���ł܂ł̎��Ԃ�Ԃ�
int AbstractBullet::GetEndTime() {
	return end_time;
}

//���ł܂ł̎��Ԃ�ݒ�
void AbstractBullet::SetEndTime(int set_time) {
	end_time = set_time;
}

//�_���[�W�l��Ԃ�
int AbstractBullet::GetDamage() {
	return damage;
}

//�_���[�W�l��ݒ�
void AbstractBullet::SetDamage(int set_damage) {
	damage = set_damage;
}

//�e��x���W��Ԃ�
float AbstractBullet::GetX() {
	return x;
}

//�e��x���W��ݒ�
void AbstractBullet::SetX(float set_x) {
	x = set_x;
}

//�e��y���W��Ԃ�
float AbstractBullet::GetY() {
	return y;
}

//�e��y���W��ݒ�
void AbstractBullet::SetY(float set_y) {
	y = set_y;
}

//�e�̌���x���W��Ԃ�
float AbstractBullet::GetBaseX() {
	return x;
}

//�e�̌���x���W��ݒ�
void AbstractBullet::SetBaseX(float set_x) {
	x = set_x;
}

//�e�̌���y���W��Ԃ�
float AbstractBullet::GetBaseY() {
	return y;
}

//�e�̌���y���W��ݒ�
void AbstractBullet::SetBaseY(float set_y) {
	y = set_y;
}

//�e�̉��̑傫����Ԃ�
int AbstractBullet::GetSizeX() {
	return size_x;
}

//�e�̉��̑傫����ݒ�
void AbstractBullet::SetSizeX(int set_size) {
	size_x = set_size;
}

//�e�̏c�̑傫����Ԃ�
int AbstractBullet::GetSizeY() {
	return size_y;
}

//�e�̏c�̑傫����ݒ�
void AbstractBullet::SetSizeY(int set_size) {
	size_y = set_size;
}

//�p�x����ɑ��x��ݒ�
void AbstractBullet::SetSpeed(float speed) {
	sx = speed * cosf(angle);
	sy = speed * sinf(angle);
}

//�e��x�����̑��x��Ԃ�
float AbstractBullet::GetXSpeed() {
	return sx;
}

//�e��x�����̑��x��ݒ�
void AbstractBullet::SetXSpeed(float set_x) {
	sx = set_x;
}

//�e��y�����̑��x��Ԃ�
float AbstractBullet::GetYSpeed() {
	return sy;
}

//�e��y�����̑��x��ݒ�
void AbstractBullet::SetYSpeed(float set_y) {
	sy = set_y;
}

//�p�x���擾
float AbstractBullet::GetAngle() {
	return angle;
}

//�p�x��ݒ�(�p�x)
void AbstractBullet::SetAngle(float set_angle) {
	angle = set_angle;
}

//��]���x���擾
float AbstractBullet::GetSpinSpeed() {
	return 0.f;
}

//��]���x��ݒ�(�p�x)
void AbstractBullet::SetSpinSpeed(float set_angle) {

}

//�󂹂邩���擾
bool AbstractBullet::GetBreakable() {
	return breakable;
}

//�󂹂邩��ݒ�
void AbstractBullet::SetBreakable(bool flag) {
	breakable = flag;
}

//���@�ɓ����邩���擾
bool AbstractBullet::GetHitPlayer() {
	return hit_player;
}

//���@�ɓ����邩��ݒ�
void AbstractBullet::SetHitPlayer(bool flag) {
	hit_player = flag;
}

//�G�ɓ����邩���擾
bool AbstractBullet::GetHitEnemy() {
	return hit_enemy;
}

//�G�ɓ����邩��ݒ�
void AbstractBullet::SetHitEnemy(bool flag) {
	hit_enemy = flag;
}

//�}�b�v�`�b�v�ɓ����邩���擾
bool AbstractBullet::GetHitMap() {
	return hit_map;
}

//�}�b�v�`�b�v�ɓ����邩��ݒ�
void AbstractBullet::SetHitMap(bool flag) {
	hit_map = flag;
}

//�����蔻��̍X�V
void AbstractBullet::HitUpdate() {
	if (hit.size() <= 0) return;
	for (unsigned int i = 0; i < hit.size(); i++) {
		hit[i].x = x + (hit[i].distance * cosf(hit[i].angle + angle));
		hit[i].y = y + (hit[i].distance * sinf(hit[i].angle + angle));
	}
}

//�����蔻��̕`��
void AbstractBullet::DrawHit() {
	if (hit.size() <= 0) return;
	for (auto h : hit) {
		Display::Get_Instance()->HitDraw(h.x, h.y, h.size);
	}
}

//�L�����N�^�[�Ƃ̓����蔻��
int AbstractBullet::HitCheckChara(float cx, float cy, float hit_size, bool check_inhale) {
	if (hit.size() <= 0) return -1;

	for (auto h : hit) {
		float dif_x = cx - h.x;
		float dif_y = cy - h.y;
		float distance = sqrtf((dif_x * dif_x) + (dif_y * dif_y));

		if (distance <= hit_size + h.size) {
			//�󂹂�e�Ȃ����
			if (breakable) {
				end_flag = true;
			}
			return damage;
		}
	}

	return -1;
}

//�}�b�v�`�b�v�Ƃ̓����蔻��
void AbstractBullet::HitCheckMap(shared_ptr<MapChipManager> map) {
	
}