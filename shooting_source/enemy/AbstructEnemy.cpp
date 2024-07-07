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
	base_enemy = NULL; //�{�̂͊�{�I��NULL
}

AbstractEnemy::~AbstractEnemy(){

	for (auto ene : parts) {
		ene->SetEndFlag(true); //�p�[�c������
		ene.reset();
	}
	parts.clear();
	hit.clear(); //�����蔻��̃����������
}

//�����蔻��̔z�u
void AbstractEnemy::SetHit(float cx, float cy, float hit_size) {
	HitStruct new_hit;

	new_hit.angle = atan2f(cy, cx); //�����p�x��ݒ�
	new_hit.distance = sqrtf((cx * cx) + (cy * cy)); //�{�̂Ƃ̋�����ݒ�
	new_hit.size = hit_size; //����̑傫����ݒ�
	new_hit.x = x;
	new_hit.y = y;

	hit.emplace_back(new_hit);
}

//�{�̂��擾
AbstractEnemy* AbstractEnemy::GetBase() {
	return base_enemy;
}

//�{�̂�ݒ�
void AbstractEnemy::SetBase(AbstractEnemy* base) {
	base_enemy = base;
}

//�������邩���擾
bool AbstractEnemy::GetEndFlag() {
	return end_flag;
}

//�������邩��ݒ�
void AbstractEnemy::SetEndFlag(bool flag) {
	end_flag = flag;
}

//�{�X�����擾
bool AbstractEnemy::GetBossFlag() {
	return boss_flag;
}

//�{�X����ݒ�
void AbstractEnemy::SetBossFlag(int rank) {
	boss_flag = (0 < rank); //�i��0�ȏ�Ȃ�{�X
}

//�����蔻����擾
bool AbstractEnemy::GetHitFlag() {
	return hit_flag;
}

//�����蔻���ݒ�
void AbstractEnemy::SetHitFlag(bool flag) {
	hit_flag = flag;
}

//�����x��ݒ�
void AbstractEnemy::SetTrance(int set_trance) {
	trance = set_trance;
}

//�G�̎��Ԃ�Ԃ�
int AbstractEnemy::GetTime() {
	return time;
}

//���Ԃ�ݒ�
void AbstractEnemy::SetTime(int set_time) {
	time = set_time;
}

//HP��Ԃ�
int AbstractEnemy::GetHp() {
	return hp;
}

//HP��ݒ�
void AbstractEnemy::SetHp(int set_hp) {
	hp = set_hp;
}

//�G��x���W��Ԃ�
float AbstractEnemy::GetX() {
	return x;
}

//�G��x���W��ݒ�
void AbstractEnemy::SetX(float set_x) {
	x = set_x;
}

//�G��y���W��Ԃ�
float AbstractEnemy::GetY() {
	return y;
}

//�G��y���W��ݒ�
void AbstractEnemy::SetY(float set_y) {
	y = set_y;
}

//�G�̌���x���W��Ԃ�
float AbstractEnemy::GetBaseX() {
	return x;
}

//�G�̌���x���W��ݒ�
void AbstractEnemy::SetBaseX(float set_x) {
	x = set_x;
}

//�G�̌���y���W��Ԃ�
float AbstractEnemy::GetBaseY() {
	return y;
}

//�G�̌���y���W��ݒ�
void AbstractEnemy::SetBaseY(float set_y) {
	y = set_y;
}

//�p�x����ɑ��x��ݒ�
void AbstractEnemy::SetSpeed(float speed) {
	sx = speed * cosf(angle);
	sy = speed * sinf(angle);
}

//�G��x�����̑��x��Ԃ�
float AbstractEnemy::GetXSpeed() {
	return sx;
}

//�G��x�����̑��x��ݒ�
void AbstractEnemy::SetXSpeed(float set_x) {
	sx = set_x;
}

//�G��y�����̑��x��Ԃ�
float AbstractEnemy::GetYSpeed() {
	return sy;
}

//�G��y�����̑��x��ݒ�
void AbstractEnemy::SetYSpeed(float set_y) {
	sy = set_y;
}

//�p�x���擾
float AbstractEnemy::GetAngle() {
	return angle;
}

//�p�x��ݒ�(�p�x)
void AbstractEnemy::SetAngle(float set_angle) {
	angle = set_angle;
}

//��]���x���擾
float AbstractEnemy::GetSpinSpeed() {
	return spin_speed;
}

//��]���x��ݒ�(�p�x)
void AbstractEnemy::SetSpinSpeed(float set_angle) {
	spin_speed = set_angle;
}

//�������擾
bool AbstractEnemy::GetLr() {
	return lr;
}

//������ݒ�
void AbstractEnemy::SetLr(bool set_lr) {
	lr = set_lr;
}

//���ł��邩���擾
bool AbstractEnemy::GetFlying() {
	return flying_flag;
}

//���ł��邩��ݒ�
void AbstractEnemy::SetFlying(bool flag) {
	flying_flag = flag;
}

//�_���[�W���󂯂Ă��邩���擾
bool AbstractEnemy::GetDamaged() {
	return damaged;
}

//�z�����߂邩���擾
bool AbstractEnemy::GetInhale() {
	return inhale;
}

//�z�����߂邩��ݒ�
void AbstractEnemy::SetInhale(bool flag) {
	inhale = flag;
}

//�}�b�v�`�b�v�ɓ����邩���擾
bool AbstractEnemy::GetHitMap() {
	return hit_map;
}

//�}�b�v�`�b�v�ɓ����邩��ݒ�
void AbstractEnemy::SetHitMap(bool flag) {
	hit_map = flag;
}

//�z�����܂�Ă��邩���擾
bool AbstractEnemy::GetInhaledFlag() {
	return inhaled_flag;
}

//�z�����܂�Ă��邩��ݒ�
void AbstractEnemy::SetInhaledFlag(bool flag) {
	inhaled_flag = flag;
}

//�ڕW�Ɍ����Ă̑��x�𒲐�
void AbstractEnemy::Homing(float set_spin_speed, float speed, float set_x, float set_y) {
	float vx = sx;
	float vy = sy;
	float vx1, vx2, vx3;
	float vy1, vy2, vy3;

	//���Έʒu�x�N�g�����v�Z
	float svx = set_x - x;
	float svy = set_y - y;

	//���@�ւ̃x�N�g�����v�Z
	float v = sqrtf(svx * svx + svy * svy);
	if (v) {
		vx1 = svx / v * speed;
		vy1 = svy / v * speed;
	}
	else {
		vx1 = 0.f;
		vy1 = 1.f;
	}

	//�E���̏ꍇ�̃x�N�g�����v�Z
	vx2 = cosf(set_spin_speed) * vx - sinf(set_spin_speed) * vy;
	vy2 = sinf(set_spin_speed) * vx + cosf(set_spin_speed) * vy;

	//���@�����̃x�N�g������]���x�ȓ��̏ꍇ
	if (vx * vx2 + vy * vy2 <= vx * vx1 + vy * vy1) {
		vx = vx1;
		vy = vy1;
	}
	//���x�ȏ�̏ꍇ
	else
	{
		//�����̏ꍇ�̃x�N�g�����v�Z
		vx3 = cosf(set_spin_speed) * vx + sinf(set_spin_speed) * vy;
		vy3 = -sinf(set_spin_speed) * vx + cosf(set_spin_speed) * vy;

		//�E���̏ꍇ
		if (svx * vx3 + svy * vx3 <= svx * vx2 + svy * vx2) {
			vx = vx2;
			vy = vy2;
		}
		//�����̏ꍇ
		else {
			vx = vx3;
			vy = vy3;
		}
	}

	//x,y��������p�x���v�Z
	angle = atan2f(vy, vx);
	sx = vx;
	sy = vy;
}

//�ڕW�Ɍ����ĉ�]
void AbstractEnemy::HomingSpin(float set_spin_speed, float set_x, float set_y, bool use_base) {
	//�ڕW�ւ̊p�x���v�Z
	float target_angle = (use_base) ? atan2f(set_y - base_y, set_x - base_x) : atan2f(set_y - y, set_x - x);

	//�L�����̊p�x���v�Z�p�ɕҏW
	angle = atan2f(sinf(angle), cosf(angle));

	//�����̊p�x�̐����������ꍇ
	if (0.f <= target_angle * angle) {
		//�p�x�̍�����]�p�x�����̏ꍇ
		if (fabsf(target_angle - angle) <= set_spin_speed) {
			angle = target_angle;
		}
		//�p�x�ȏ�̏ꍇ
		else {
			//�ڕW�p�x���傫���ꍇ�͑���
			if (angle < target_angle) {
				angle += set_spin_speed;
			}
			//��������Έ���
			else {
				angle -= set_spin_speed;
			}
		}
	}
	//�قȂ�ꍇ
	else {
		//�E���A���̊p�x�̍����v�Z
		float sub_right = fabsf(target_angle) + fabsf(angle);
		float sub_left = fabsf(2.f * PI - sub_right);
		//��]������ݒ�
		float spin = (0.f < angle) ? set_spin_speed : -set_spin_speed;
		//�ǂ��炩�̊p�x�̍�����]�p�x�ȉ��̏ꍇ
		if (sub_right <= set_spin_speed || sub_left <= set_spin_speed) {
			angle = target_angle;
		}
		//�p�x�ȏ�̏ꍇ
		else {
			//�������������։�]
			if (sub_right < sub_left) {
				angle -= spin;
			}
			else {
				angle += spin;
			}
		}
	}
}

//�p�[�c����]������
void AbstractEnemy::Spin(float set_spin_speed, float spin_max, float spin_min) {
	angle += set_spin_speed; //�p�[�c����]������

	//����ɒB������
	if (spin_max < angle) {
		angle = spin_max;
	}
	//�����ɒB������
	if (angle < spin_min) {
		angle = spin_min;
	}
}

//�����蔻��̍X�V
void AbstractEnemy::HitUpdate() {
	if (hit.size() <= 0) return;
	for (unsigned int i = 0; i < hit.size(); i++) {
		hit[i].x = x + (hit[i].distance * cosf(hit[i].angle + angle));
		hit[i].y = y + (hit[i].distance * sinf(hit[i].angle + angle));
	}
}

//�_���[�W����
bool AbstractEnemy::HitDamage(int damage_num) {
	damaged = true;
	damage_time = 6;

	//�{�̂�����Ȃ炻�����Ƀ_���[�W
	if (base_enemy != NULL) {
		bool flag = base_enemy->HitDamage(damage_num);
		return flag;
	}
	
	hp -= damage_num;

	//HP��0�ɂȂ�����
	if (hp <= 0) {
		end_flag = true; //�G������
		return true;
	}

	return false;
}

//�����蔻��̕`��
void AbstractEnemy::DrawHit() {
	if (hit.size() <= 0) return;
	for (auto h : hit) {
		Display::Get_Instance()->HitDraw(h.x, h.y, h.size);
	}
}

//�ʒu�̒���
void AbstractEnemy::AdjustPosition(shared_ptr<MapChipManager> map) {
	shared_ptr<AbstractMapChip> mapchip;

	bool step_flag = false; //�}�b�v�`�b�v�ɏ���Ă��邩
	bool left_hit = false; //�������������Ă��邩
	bool right_hit = false; //�E�����������Ă��邩
	bool top_hit = false; //�㑤���������Ă��邩
	bool bottom_hit = false; //�������������Ă��邩

	float sub_x = 0.f; //����ɂǂꂾ���߂荞��ł��邩

	angle += spin_speed; //��]

	x += sx; //�s���\��̍��W������

	//���E�Ƃ̔���
	for (unsigned int i = 0; i < hit.size(); i++) {
		mapchip = map->HitCheckLeft(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL) {
			left_hit = true; //�����������������Ƃ�
			sub_x = (hit[i].x - hit[i].size) - (mapchip->GetX() + 4.f * mapchip->GetSizeX());
			x += fabsf(sub_x);
			sx = 0.f;
			HitUpdate();
			mapchip = map->HitCheckLeft(hit[i].x, hit[i].y, hit[i].size);
		}
		mapchip = map->HitCheckRight(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL) {
			right_hit = true; //�E���������������Ƃ�
			sub_x = (hit[i].x + hit[i].size) - (mapchip->GetX() - 4.f * mapchip->GetSizeX());
			x -= fabsf(sub_x);
			sx = 0.f;
			HitUpdate();
			mapchip = map->HitCheckRight(hit[i].x, hit[i].y, hit[i].size);
		}
	}

	//�������������Ă�����
	if (left_hit && right_hit) {
		hp = 0; //HP��0��
		damaged = true;
		//���x��������
		sx = 0.f;
		sy = 0.f;
		return;
	}

	//�W�����v��
	if (jump_flag && !flying_flag){
		//�㏸���Ԓ��Ȃ�
		if (0 < jump_time) {
			jump_time--; //���Ԃ�����
		}
		else
		{
			if (sy < 0.4f && sy > -0.4f) sy = 0.4f;
			sy += fabsf(sy * 1.3f); //���x��1.3(0.7)�{(��s����1.1�{)����
			if (sy > 10.f) sy = 10.f;
		}
	}
	
	y += sy; //�s���\��̍��W������
	HitUpdate(); //�����蔻����X�V
	
	//�㉺�Ƃ̔���
	for (unsigned int i = 0; i < hit.size(); i++) {
		mapchip = map->HitCheckTop(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL) {
			top_hit = true; //�㑤�������������Ƃ�
			sub_x = (hit[i].y - hit[i].size) - (mapchip->GetY() + 8.f * mapchip->GetSizeY());
			y += fabsf(sub_x);
			sy = 0.f;
			HitUpdate();
			mapchip = map->HitCheckTop(hit[i].x, hit[i].y, hit[i].size);
		}
		mapchip = map->HitCheckBottom(hit[i].x, hit[i].y, hit[i].size);
		while (mapchip != NULL) {
			bottom_hit = true; //�����������������Ƃ�
			sub_x = (hit[i].y + hit[i].size) - (mapchip->GetY());
			y -= fabsf(sub_x);
			sy = 0.f;
			HitUpdate();
			mapchip = map->HitCheckBottom(hit[i].x, hit[i].y, hit[i].size);
		}
	}

	//�������������Ă�����
	if (top_hit && bottom_hit) {
		hp = 0; //HP��0��
		damaged = true;
		//���x��������
		sx = 0.f;
		sy = 0.f;
		return;
	}
}

//�e�ɓ������Ă��邩
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

	//HP��0�ɂȂ�����
	if (flag) {
		//end_flag = true; //�G������
		effect->SetEffect(1, x, y); //����
	}
}

//�G�ɓ������Ă��邩
void AbstractEnemy::HitCheckEnemy(float cx, float cy, float hit_size, shared_ptr<EffectManager> effect) {
	if (hit.size() <= 0 || !hit_flag) return;

	for (auto h : hit) {

		
	}

}

//�L�����N�^�[�Ƃ̓����蔻��
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

//�^�C�}�[�֘A�̍X�V
void AbstractEnemy::Timer() {
	time++;
	if (0 < damage_time) {
		damage_time--;
		if (damage_time <= 0) {
			damaged = false;
		}
	}
}