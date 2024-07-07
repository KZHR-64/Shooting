#pragma once
#include "DxLib.h"
#include "Player.h"
#include <math.h>

using namespace std;

Player::Player(){
	//Image::Get_Instance()->LoadPlayerImage(); //�摜�����[�h

	body.def_angle = atan2f(-8.f, -4.f);
	body.def_distance = sqrtf((4.f * 4.f) + (8.f * 8.f));
	body.spin_angle = 0.f;
	body.spin_distance = 0.f;

	right_thigh.def_angle = atan2f(13.f, 6.f);
	right_thigh.def_distance = sqrtf((6.f * 6.f) + (13.f * 13.f));
	right_thigh.spin_angle = atan2f(8.f, 0.f);
	right_thigh.spin_distance = sqrtf(8.f * 8.f);

	right_leg.def_angle = atan2f(7.f, 0.f);
	right_leg.def_distance = sqrtf(7.f * 7.f);
	right_leg.spin_angle = atan2f(12.f, 0.f);
	right_leg.spin_distance = sqrtf(12.f * 12.f);

	left_thigh.def_angle = atan2f(13.f, -6.f);
	left_thigh.def_distance = sqrtf((6.f * 6.f) + (13.f * 13.f));
	left_thigh.spin_angle = atan2f(8.f, 0.f);
	left_thigh.spin_distance = sqrtf(8.f * 8.f);

	left_leg.def_angle = atan2f(7.f, 0.f);
	left_leg.def_distance = sqrtf(7.f * 7.f);
	left_leg.spin_angle = atan2f(12.f, 0.f);
	left_leg.spin_distance = sqrtf(12.f * 12.f);

	right_shoulder.def_angle = atan2f(-4.f, 12.f);
	right_shoulder.def_distance = sqrtf((12.f * 12.f) + (4.f * 4.f));
	right_shoulder.spin_angle = atan2f(0.f, 0.f);
	right_shoulder.spin_distance = sqrtf(0.f * 0.f);

	right_arm.def_angle = atan2f(11.f, 0.f);
	right_arm.def_distance = sqrtf((11.f * 11.f) + (0.f * 0.f));
	right_arm.spin_angle = atan2f(6.f, 14.f);
	right_arm.spin_distance = sqrtf((6.f * 6.f) + (14.f * 14.f));

	left_shoulder.def_angle = atan2f(-4.f, -12.f);
	left_shoulder.def_distance = sqrtf((12.f * 12.f) + (4.f * 4.f));
	left_shoulder.spin_angle = atan2f(0.f, 0.f);
	left_shoulder.spin_distance = sqrtf(0.f * 0.f);

	left_arm.def_angle = atan2f(11.f, 0.f);
	left_arm.def_distance = sqrtf(11.f * 11.f);
	left_arm.spin_angle = atan2f(12.f, 0.f);
	left_arm.spin_distance = sqrtf(12.f * 12.f);

	Reset(); //������
	hp = 6;
}

Player::~Player(){
	//Image::Get_Instance()->DeletePlayerImage();
}

//������
void Player::Reset(){
	if(hp <= 0) hp = 6; //HP��������
	sx = 0.f; //���x��������
	sy = 0.f; //���x��������
	angle = 0.f; //�p�x��������
	sangle = 0.f; //��]���x��������
	move_time = 0;
	move_type = Move_Stand; //�Î~��Ԃɐݒ�
	lr = RIGHT; //�ŏ��͉E����
	damaged = false; //�_���[�W���󂯂��t���O��������
	damage_time = false; //�_���[�W����̎��Ԃ�������
	handle = 0; //�\������摜�̔ԍ���������
	inv_time = 0; //���G���Ԃ�������
	draw_flag = true; //�`��t���O��������

	body.angle = angle;
	right_thigh.angle = angle;
	right_leg.angle = angle;
	left_thigh.angle = angle;
	left_leg.angle = angle;
	right_shoulder.angle = angle;
	left_shoulder.angle = angle;
	right_arm.angle = 0.f;
	left_arm.angle = angle;

	SetParts();

	//catch_enemy = NULL;
	catch_effect = NULL;

	attack.flag = false; //�U���t���O��������
	attack.push_time = 0; //���������Ԃ�������

	catch_arm.flag = false; //���݃r�[�������t���O��������
	catch_arm.catch_flag = false; //����ł���t���O��������
	catch_arm.x = x; //���W��������
	catch_arm.y = false;
	
}

//���͗����̊m�F(�n����A�T���n�߂�_)
bool Player::RecordCheck(bool record[], int point){
	int i;
	for (i = point; i < RECORD; i++){
		//�O�ɉ�����Ă��邩
		if (record[i]) return true; //������Ă�����true
	}
	return false; //�Ȃ�������false
}

//���@�̑���
void Player::Control() {
	float ini_sx = 0.f; //�v�Z�p�̑��x
	float ini_sy = 0.f;

	//����������Ă�����
	if (Key::Get_Instance()->KeyCheck(Left)){
		//�U����ԂłȂ��ꍇ
		if (!attack.flag) {
			//lr = LEFT; //����������
			move_type = Move_Walk; //�������s��Ԃ�
		}
		// ���O�ɍ���������Ă��Ȃ�������
		if (!commando[Left][0]){
			//���̑O�ɉ�����Ă����ꍇ
			if (RecordCheck(commando[Left], 1)){
			}
		}
		ini_sx -= move_speed;
	}
	//�E��������Ă�����
	if (Key::Get_Instance()->KeyCheck(Right)){
		//�U����ԂłȂ��ꍇ
		if (!attack.flag) {
			//lr = RIGHT; //�������E��
			move_type = Move_Walk; //�������s��Ԃ�
		}
		// ���O�ɉE��������Ă��Ȃ�������
		if (!commando[Right][0]){
			//���̑O�ɉ�����Ă����ꍇ
			if (RecordCheck(commando[Right], 1)){
			}
		}
		ini_sx += move_speed;
	}
	//�オ������Ă�����
	if (Key::Get_Instance()->KeyCheck(Up)) {
		// ���O�ɏオ������Ă��Ȃ�������
		if (!commando[Up][0]) {
			//���̑O�ɉ�����Ă����ꍇ
			if (RecordCheck(commando[Up], 1)) {
			}
		}
		ini_sy -= move_speed;
	}
	//����������Ă�����
	if (Key::Get_Instance()->KeyCheck(Down)) {
		// ���O�ɏオ������Ă��Ȃ�������
		if (!commando[Down][0]) {
			//���̑O�ɉ�����Ă����ꍇ
			if (RecordCheck(commando[Down], 1)) {
			}
		}
		ini_sy += move_speed;
	}

	if (ini_sx && ini_sy) {
		ini_sx /= sqrtf(2.f);
		ini_sy /= sqrtf(2.f);
	}

	sx = ini_sx;
	sy = ini_sy;

}

//�_���[�W����
void Player::DamageAction() {
	//�_���[�W���󂯂��΂���Ȃ�
	if (damage_time == DAMAGE_TIME_MAX) {
		sx = 0.0; //x���x��������
		sy = 0.0; //y���x��������
		move_type = Move_Stand; //�����Î~��Ԃ�
	}
	damage_time--; //���쎞�Ԃ�����
	//���쎞�Ԃ�����������
	if (damage_time == 0) {
		damaged = false; //�t���O��false��
	}
}

//�ړ�
void Player::Move() {
	//�_���[�W���󂯂Ă�����
	if (damaged) {
		DamageAction(); //�_���[�W����
	}
	//�󂯂Ă��Ȃ�������
	else {
		Control(); //�ʏ�̑���
	}
}

//�ʒu�̒���
void Player::AdjustPosition(std::shared_ptr<MapChipManager> map, bool event_flag) {
	//�擾�p�N���X
	shared_ptr<AbstractMapChip> mapchip;

	bool left_hit = false; //�������������Ă��邩
	bool right_hit = false; //�E�����������Ă��邩
	bool top_hit = false; //�㑤���������Ă��邩
	bool bottom_hit = false; //�������������Ă��邩

	//�����x
	float accel = 0.3f;

	float left = (float)Display::Get_Instance()->GetScrollX(); //��ʍ��[
	float right = (float)(Display::Get_Instance()->GetScrollX() + WINDOW_X); //��ʉE�[
	float top = (float)Display::Get_Instance()->GetScrollY(); //��ʏ�
	float bottom = (float)(Display::Get_Instance()->GetScrollY() + WINDOW_Y); //��ʒ�

	//���E�̔��肩��s��
	//���݂̍��W��ݒ�
	fx = x;
	fy = y;

	//�s���\��̍��W������
	fx += sx + (float)map->GetScrollSpeedX();

	//�C�x���g���łȂ���Ή�ʓ��Ɏ��߂�
	if (!event_flag) {
		if (fx < left + hit_size) {
			fx = left + hit_size;
			left_hit = true; //�����������������Ƃ�
		}
		if (right - hit_size < fx) {
			fx = right - hit_size;
			right_hit = true; //�E���������������Ƃ�
		}
	}

	//�}�b�v�`�b�v�Ƃ̐ڐG����
	mapchip = map->HitCheckLeft(fx, fy, hit_size);
	while (mapchip != NULL) {
		left_hit = true; //�����������������Ƃ�
		fx = mapchip->GetX() + 4.f * mapchip->GetSizeX() + hit_size;
		sx = 0.f;
		mapchip = map->HitCheckLeft(fx, fy, hit_size);
	}
	mapchip = map->HitCheckRight(fx, fy, hit_size);
	while (mapchip != NULL) {
		right_hit = true; //�E���������������Ƃ�
		fx = mapchip->GetX() - 4.f * mapchip->GetSizeX() - hit_size;
		sx = 0.f;
		mapchip = map->HitCheckRight(fx, fy, hit_size);
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

	//���ɏ㉺�̔���
	//�p�x��ݒ�
	angle += sangle;

	//�s���\��̍��W������
	fy += sy + (float)map->GetScrollSpeedY();

	//�C�x���g���łȂ���Ή�ʓ��Ɏ��߂�
	if (!event_flag) {
		if (fy < top + hit_size) {
			fy = top + hit_size;
			top_hit = true; //�㑤�������������Ƃ�
		}
		if (bottom - hit_size < fy) {
			fy = bottom - hit_size;
			bottom_hit = true; //�����������������Ƃ�
		}
	}

	//�}�b�v�`�b�v�Ƃ̐ڐG����
	//����
	mapchip = map->HitCheckTop(fx, fy, hit_size);
	while (mapchip != NULL) {
		top_hit = true; //�㑤�������������Ƃ�
		fy = mapchip->GetY() + 8.f * mapchip->GetSizeY() + hit_size;
		sy = 0.f;
		mapchip = map->HitCheckTop(fx, fy, hit_size);
	}
	//����
	mapchip = map->HitCheckBottom(fx, fy, hit_size);
	if (mapchip != NULL) bottom_hit = true; //�����������������Ƃ�
	while (mapchip != NULL) {
		fy = mapchip->GetY() - hit_size;
		sy = 0.f;
		mapchip = map->HitCheckBottom(fx, fy, hit_size);
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

	

	//���̍��W������
	x = fx;
	y = fy;

	SetParts(); //�p�[�c�̔z�u
}

//�U��
void Player::AttackCheck(shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect) {
	shared_ptr<AbstractBullet> bul;
	float shoot_angle = (lr ? 0.f : PI); //�����ɂ���Č��p�x������
	//�U��(����)�̃{�^����������Ă�����
	if (Key::Get_Instance()->KeyCheck(Jump) && !catch_arm.flag && !catch_arm.catch_flag) {
		attack.push_time++; //�����Ă��鎞�Ԃ𑝉�
		//���߂čU���{�^�����������������Ă��΂炭������
		if (attack.push_time == 1 || attack.push_time % 6 == 1) {
			bul = bullet->SetBullet(0, x, y, 16.f, shoot_angle); //�e�𔭎�
			//bul = bullet->SetBullet(1, x, y, 16.f, shoot_angle + (PI / 6.66f)); //�e�𔭎�
			//bul = bullet->SetBullet(1, x, y, 16.f, shoot_angle - (PI / 6.66f)); //�e�𔭎�
			Sound::Get_Instance()->PlaySoundEffect(7); //���ʉ���炷
		}
	}
	else {
		attack.push_time = 0; //�����Ă��鎞�Ԃ�������
	}

	//����(�߂�)�̃{�^���������ꂽ��
	if (Key::Get_Instance()->KeyCheckOnce(Attack)) {
		//���݃r�[�����o�Ă��Ȃ��Ȃ�
		if (!catch_arm.flag && !catch_arm.catch_flag) {
			catch_arm.flag = true; //�r�[���𔭐�
			catch_arm.x = right_arm.x + 32.f; //���W��ݒ�
			catch_arm.y = right_arm.y;
			catch_effect = effect->SetEffect(0, catch_arm.x, catch_arm.y); //�G�t�F�N�g�𔭐�
			Sound::Get_Instance()->PlaySoundEffect(8); //���ʉ���炷
		}
		//�G������ł�����
		if (catch_arm.catch_flag) {
			catch_arm.catch_flag = false; //���݂�����
			//catch_enemy->SetSpinSpeed(PI / 30.f);
			//catch_enemy->SetXSpeed(16.f); //�G�𓊂���
			//catch_enemy.reset(); //������j��
			bullet->SetBullet(1, catch_arm.x, catch_arm.y, 16.f, shoot_angle); //�e�𔭎�
			Sound::Get_Instance()->PlaySoundEffect(5); //���ʉ���炷
		}
	}

	//����(�߂�)�̃{�^����������Ă�����
	if (Key::Get_Instance()->KeyCheck(Attack) && catch_arm.flag) {
		//�G������ł��Ȃ�������
		if (!catch_arm.catch_flag) {
			catch_arm.x += 32.f; //�r�[���͒��i
			catch_arm.y = right_arm.y;
		}
	}
	//�����ꂽ��
	else {
		catch_arm.flag = false; //�r�[��������
	}

	//�G������ł�����
	if (catch_arm.catch_flag) {
		//���@���r�[��������Ă�����
		if (64.f < fabsf(right_arm.x - catch_arm.x)) {
			catch_arm.x -= 32.f; //���@�̕��ֈ�������
		}
		//�߂��Ȃ�
		if (fabsf(right_arm.x - catch_arm.x) < 64.f) {
			catch_arm.x = right_arm.x + 64.f; //���W�����킹��
		}
		catch_arm.y = right_arm.y;
		//���񂾓G�������Ă���Ȃ�
		/*if (2 <= catch_enemy.use_count()) {
			catch_enemy->SetX(catch_arm.x); //���W�����݃r�[���ɍ��킹��
			catch_enemy->SetY(catch_arm.y);
		}*/
	}

	//�G�t�F�N�g�������
	if (2 <= catch_effect.use_count()) {
		catch_effect->SetX(catch_arm.x);
		catch_effect->SetY(catch_arm.y);
		catch_effect->SetBaseX(right_arm.x + 32.f);
	}

	//�r�[������ʊO�ɏo����
	if (Display::Get_Instance()->GetScrollX() + WINDOW_X + 64 < (int)catch_arm.x && !catch_arm.catch_flag) {
		catch_arm.flag = false; //�r�[��������
	}

	//�r�[�����Ȃ����
	if (!catch_arm.flag && 1 <= catch_effect.use_count() && !catch_arm.catch_flag) {
		catch_effect->SetEndFlag(true); //�G�t�F�N�g������
		catch_effect.reset(); //�G�t�F�N�g�̌�����j��
	}

}

//�\������摜������
void Player::SetGraphic() {
	//�_���[�W���󂯂Ă���ꍇ
	if (0 < damage_time || hp <= 0) {
		handle = 21;
		return;
	}

	//������Ԃ̏ꍇ
	
}

//�L�[�̗������X�V
void Player::SetKeyRecord() {
	//���͗����̍X�V
	for (int i = 0; i < BUTTON; i++){
		for (int j = RECORD - 1; j > 0; j--){
			commando[i][j] = commando[i][j - 1]; //�O�̃L�[���擾
		}
	}
	for (int i = 0; i < BUTTON; i++) commando[i][0] = Key::Get_Instance()->KeyCheck(i); //��������Ă���̂�}��

}

//�p�[�c�����낦��
void Player::SetParts() {
	//�i�ތ����ɂ���đ̂��X����
	if (sx < 0.f) {
		body.angle = PartsSpin(body.angle, -PI * 0.025f, 0.125f * PI, -0.125f * PI);
		right_thigh.angle = PartsSpin(right_thigh.angle, -PI * 0.025f, 0.5f * PI, -0.175f * PI);
		right_leg.angle = PartsSpin(right_leg.angle, -PI * 0.025f, 0.5f * PI, 0.f);
		left_thigh.angle = PartsSpin(left_thigh.angle, -PI * 0.025f, 0.5f * PI, -0.125f * PI);
		left_leg.angle = PartsSpin(left_leg.angle, -PI * 0.025f, 0.5f * PI, 0.f);
		right_shoulder.angle = PartsSpin(right_shoulder.angle, -PI * 0.025f, 0.5f * PI, 0.f);
		left_shoulder.angle = PartsSpin(left_shoulder.angle, -PI * 0.025f, 0.5f * PI, 0.f);
		left_arm.angle = PartsSpin(left_arm.angle, -PI * 0.025f, 0.f, -0.25f * PI);
	}
	else if (0.f < sx) {
		body.angle = PartsSpin(body.angle, PI * 0.025f, 0.125f * PI, -0.125f * PI);
		right_thigh.angle = PartsSpin(right_thigh.angle, -PI * 0.025f, 0.5f * PI, -0.25f * PI);
		right_leg.angle = PartsSpin(right_leg.angle, PI * 0.025f, 0.25f * PI, 0.f);
		left_thigh.angle = PartsSpin(left_thigh.angle, PI * 0.025f, 0.125f * PI, 0.f);
		left_leg.angle = PartsSpin(left_leg.angle, PI * 0.025f, 0.f, 0.f);
		right_shoulder.angle = PartsSpin(right_shoulder.angle, PI * 0.025f, 0.f, 0.f);
		left_shoulder.angle = PartsSpin(left_shoulder.angle, PI * 0.025f, 0.f, 0.f);
		left_arm.angle = PartsSpin(left_arm.angle, -PI * 0.025f, 0.f, -0.125f * PI);
	}
	else {
		body.angle *= 0.9f;
		right_thigh.angle *= 0.9f;
		right_leg.angle *= 0.9f;
		left_thigh.angle *= 0.9f;
		left_leg.angle *= 0.9f;
		right_shoulder.angle *= 0.9f;
		left_shoulder.angle *= 0.9f;
		left_arm.angle *= 0.9f;
	}

	float sum_angle = 0.f;

	//����
	body.total_angle = body.angle;
	sum_angle = body.def_angle + body.total_angle;
	body.x = x + (body.def_distance * cosf(sum_angle));
	body.y = y + (body.def_distance * sinf(sum_angle));

	//�E��
	right_thigh.total_angle = body.total_angle + right_thigh.angle;
	sum_angle = right_thigh.def_angle + body.total_angle;
	right_thigh.x = body.x + (right_thigh.def_distance * cosf(sum_angle)) + (right_thigh.spin_distance * cosf(right_thigh.spin_angle + right_thigh.total_angle));
	right_thigh.y = body.y + (right_thigh.def_distance * sinf(sum_angle)) + (right_thigh.spin_distance * sinf(right_thigh.spin_angle + right_thigh.total_angle));
	right_leg.total_angle = right_thigh.total_angle + right_leg.angle;
	sum_angle = right_leg.def_angle + right_thigh.total_angle;
	right_leg.x = right_thigh.x + (right_leg.def_distance * cosf(sum_angle)) + (right_leg.spin_distance * cosf(right_leg.spin_angle + right_leg.total_angle));
	right_leg.y = right_thigh.y + (right_leg.def_distance * sinf(sum_angle)) + (right_leg.spin_distance * sinf(right_leg.spin_angle + right_leg.total_angle));

	//����
	left_thigh.total_angle = body.total_angle + left_thigh.angle;
	sum_angle = left_thigh.def_angle + body.angle;
	left_thigh.x = body.x + (left_thigh.def_distance * cosf(sum_angle)) + (left_thigh.spin_distance * cosf(left_thigh.spin_angle + left_thigh.total_angle));
	left_thigh.y = body.y + (left_thigh.def_distance * sinf(sum_angle)) + (left_thigh.spin_distance * sinf(left_thigh.spin_angle + left_thigh.total_angle));
	left_leg.total_angle = left_thigh.total_angle + left_leg.angle;
	sum_angle = left_leg.def_angle + left_thigh.total_angle;
	left_leg.x = left_thigh.x + (left_leg.def_distance * cosf(sum_angle)) + (left_leg.spin_distance * cosf(left_leg.spin_angle + left_leg.total_angle));
	left_leg.y = left_thigh.y + (left_leg.def_distance * sinf(sum_angle)) + (left_leg.spin_distance * sinf(left_leg.spin_angle + left_leg.total_angle));

	//�E�r
	right_shoulder.total_angle = body.total_angle + right_shoulder.angle;
	sum_angle = right_shoulder.def_angle + body.total_angle;
	right_shoulder.x = body.x + (right_shoulder.def_distance * cosf(sum_angle)) + (right_shoulder.spin_distance * cosf(right_shoulder.spin_angle + right_shoulder.total_angle));
	right_shoulder.y = body.y + (right_shoulder.def_distance * sinf(sum_angle)) + (right_shoulder.spin_distance * sinf(right_shoulder.spin_angle + right_shoulder.total_angle));
	right_arm.total_angle = right_arm.angle;
	sum_angle = right_arm.def_angle + right_shoulder.total_angle;
	right_arm.x = right_shoulder.x + (right_arm.def_distance * cosf(sum_angle)) + (right_arm.spin_distance * cosf(right_arm.spin_angle + right_arm.total_angle));
	right_arm.y = right_shoulder.y + (right_arm.def_distance * sinf(sum_angle)) + (right_arm.spin_distance * sinf(right_arm.spin_angle + right_arm.total_angle));

	//���r
	left_shoulder.total_angle = body.total_angle + left_shoulder.angle;
	sum_angle = left_shoulder.def_angle + body.total_angle;
	left_shoulder.x = body.x + (left_shoulder.def_distance * cosf(sum_angle)) + (left_shoulder.spin_distance * cosf(left_shoulder.spin_angle + left_shoulder.total_angle));
	left_shoulder.y = body.y + (left_shoulder.def_distance * sinf(sum_angle)) + (left_shoulder.spin_distance * sinf(left_shoulder.spin_angle + left_shoulder.total_angle));
	left_arm.total_angle = left_shoulder.total_angle + left_arm.angle;
	sum_angle = left_arm.def_angle + left_shoulder.total_angle;
	left_arm.x = left_shoulder.x + (left_arm.def_distance * cosf(sum_angle)) + (left_arm.spin_distance * cosf(left_arm.spin_angle + left_arm.total_angle));
	left_arm.y = left_shoulder.y + (left_arm.def_distance * sinf(sum_angle)) + (left_arm.spin_distance * sinf(left_arm.spin_angle + left_arm.total_angle));
}

//�p�[�c����]������
float Player::PartsSpin(float parts_angle, float spin_speed, float spin_max, float spin_min) {
	float set_angle = parts_angle;

	set_angle += spin_speed; //�p�[�c����]������

	//����ɒB������
	if (spin_max < set_angle) {
		set_angle = spin_max;
	}
	//�����ɒB������
	if (set_angle < spin_min) {
		set_angle = spin_min;
	}

	return set_angle;
}

//�z�����߂邩�m�F
void Player::InhaleCheck(shared_ptr<MapChipManager> map, shared_ptr<EnemyManager> enemy) {
	if (!catch_arm.flag || catch_arm.catch_flag) return; //���ݏ�ԂłȂ������łɂ���ł���Ȃ�߂�

	std::shared_ptr<AbstractEnemy> catch_enemy = enemy->InhaleCheck(catch_arm.x, catch_arm.y, 32.f, false); //���񂾓G

	//�G�����񂾂�
	if (catch_enemy != NULL) {
		catch_arm.catch_flag = true; //���݃t���O��true��
		//catch_enemy->SetInhaledFlag(true); //�G�����ݏ�Ԃ�
		//catch_enemy->SetHitFlag(false); //�G�̓����蔻�������
		catch_enemy->SetEndFlag(true); //�G������
		Sound::Get_Instance()->PlaySoundEffect(6); //���ʉ���炷
	}
}

//�G�ɓ������Ă��邩
void Player::HitCheckEnemy(shared_ptr<EnemyManager> enemy) {
	if (0 < inv_time) return; //���G���Ԓ��Ȃ�I��

	//�G�ɓ������Ă�����
	if (enemy->HitCheckChara(x, y, hit_size)) {
		hp--; //HP������
		damaged = true; //�_���[�W���
		damage_time = DAMAGE_TIME_MAX; //�_���[�W���Ԃ�ݒ�
		inv_time = DAMAGE_INV_TIME; //���G���Ԃ�ݒ�
		Sound::Get_Instance()->PlaySoundEffect(9); //���ʉ���炷
	}
}

//�e�ɓ������Ă��邩
void Player::HitCheckBullet(shared_ptr<BulletManager> bullet) {
	if (0 < inv_time) return; //���G���Ԓ��Ȃ�I��
	
	//�e�ɓ������Ă�����
	if (0 < bullet->HitCheckChara(x, y, hit_size, true, false)) {
		hp--; //HP������
		damaged = true; //�_���[�W���
		damage_time = DAMAGE_TIME_MAX; //�_���[�W���Ԃ�ݒ�
		inv_time = DAMAGE_INV_TIME; //���G���Ԃ�ݒ�
		Sound::Get_Instance()->PlaySoundEffect(9); //���ʉ���炷
	}
}

//HP��Ԃ�
int Player::GetHp() {
	return hp;
}

//x���W��Ԃ�
float Player::GetX() {
	return x;
}

//x���W��ݒ�
void Player::SetX(float px) {
	x = px;
}

//y���W��Ԃ�
float Player::GetY() {
	return y;
}

//y���W��ݒ�
void Player::SetY(float py) {
	y = py;
}

//���̑��x��Ԃ�
float Player::GetXSpeed() {
	return sx;
}

//���̑��x��ݒ�
void Player::SetXSpeed(float px) {
	sx = px;
}

//�c�̑��x��Ԃ�
float Player::GetYSpeed() {
	return sy;
}

//�c�̑��x��ݒ�
void Player::SetYSpeed(float py) {
	sy = py;
}

//�`�悷�邩�ݒ�
void Player::SetDrawFlag(bool flag) {
	draw_flag = flag;
}

//�X�V
void Player::Update(){
	Move();
	SetKeyRecord(); //�L�[�̗������X�V
	
	//���G���Ԓ��Ȃ�
	if (0 < inv_time) {
		inv_time--; //���G���Ԃ�����
	}
}

//�`��
void Player::Draw(){
	int image = Image::Get_Instance()->GetCharaImage(0, 0); //���@�̉摜���擾
	int image2 = Image::Get_Instance()->GetCharaImage(1, 0); //���@�̉摜���擾
	int image3 = Image::Get_Instance()->GetCharaImage(2, 0); //���@�̉摜���擾
	int image4 = Image::Get_Instance()->GetCharaImage(3, 0); //���@�̉摜���擾
	int image5 = Image::Get_Instance()->GetCharaImage(4, 0); //���@�̉摜���擾
	int image6 = Image::Get_Instance()->GetCharaImage(5, 0); //���@�̉摜���擾
	int image7 = Image::Get_Instance()->GetCharaImage(6, 0); //���@�̉摜���擾

	//HP����̉摜���擾
	int life = Image::Get_Instance()->GetEffectImage(9, 0);
	int life_bar = Image::Get_Instance()->GetEffectImage(8, 0);

	int trance = 255; //�����x

	//HP����̕`��
	Display::Get_Instance()->FixedDraw(64.f, 448.f, LEFT, 0.f, life_bar);
	for (int i = 0; i < hp; i++) {
		Display::Get_Instance()->FixedDraw(34.f + (12.f * i), 448.f, LEFT, 0.f, life);
	}

	//���G���Ԓ��͓_�ł���
	if (0 < inv_time) {
		if (inv_time % 10 < 5) {
			trance = 96;
		}
		else {
			trance = 192;
		}
	}

	//���@�̕`��
	if (draw_flag) {

		Display::Get_Instance()->Draw(right_arm.x, right_arm.y, lr, right_arm.total_angle, image7, DX_BLENDMODE_ALPHA, trance); //�E�r��`��
		Display::Get_Instance()->Draw(right_shoulder.x, right_shoulder.y, lr, right_shoulder.total_angle, image5, DX_BLENDMODE_ALPHA, trance);
		Display::Get_Instance()->Draw(right_thigh.x, right_thigh.y, lr, right_thigh.total_angle, image2, DX_BLENDMODE_ALPHA, trance); //�E����`��
		Display::Get_Instance()->Draw(right_leg.x, right_leg.y, lr, right_leg.total_angle, image3, DX_BLENDMODE_ALPHA, trance);
		Display::Get_Instance()->Draw(body.x, body.y, lr, body.total_angle, image, DX_BLENDMODE_ALPHA, trance); //���@��`��
		Display::Get_Instance()->Draw(left_thigh.x, left_thigh.y, lr, left_thigh.total_angle, image2, DX_BLENDMODE_ALPHA, trance); //������`��
		Display::Get_Instance()->Draw(left_leg.x, left_leg.y, lr, left_leg.total_angle, image3, DX_BLENDMODE_ALPHA, trance);
		Display::Get_Instance()->Draw(left_shoulder.x, left_shoulder.y, lr, left_shoulder.total_angle, image4, DX_BLENDMODE_ALPHA, trance); //���r��`��
		Display::Get_Instance()->Draw(left_arm.x, left_arm.y, lr, left_arm.total_angle, image6, DX_BLENDMODE_ALPHA, trance);

		Display::Get_Instance()->HitDraw(x, y, hit_size);
	}

	//DrawString(0, 40, "�v���C���[", GetColor(255, 255, 255));
	//DrawFormatString(0, 100, GetColor(0, 0, 255), "%d", Display::Get_Instance()->GetScrollXMin());
	//DrawFormatString(0, 128, GetColor(0, 0, 255), "%d %d", catch_effect.use_count(), catch_arm.flag);
	
}
