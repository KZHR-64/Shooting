#pragma once
#include "DxLib.h"
#include "PlayerMoveEvent.h"

using namespace std;

//�R���X�g���N�^
PlayerMoveEvent::PlayerMoveEvent(EventManager* man, float speed, float x, float y, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {
	move_speed = speed;
	px = x;
	py = y;
}

//�f�X�g���N�^
PlayerMoveEvent::~PlayerMoveEvent() {

}

//�X�V
void PlayerMoveEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {
	float x = player->GetX();
	float y = player->GetY();
	float angle = atan2f(stop_y - y, stop_x - x);

	//�n�߂̏���
	if (time == 0) {
		//�ڕW�̍��W��ݒ�
		stop_x = x + px;
		stop_y = y + py;
	}

	player->SetXSpeed(move_speed * cosf(angle));
	player->SetYSpeed(move_speed * sinf(angle));

	//�ړI�n�ɋ߂Â�����I��
	if (fabsf(stop_x - x) < move_speed && fabsf(stop_y - y) < move_speed) {
		player->SetX(stop_x);
		player->SetY(stop_y);
		player->SetXSpeed(0.f);
		player->SetYSpeed(0.f);
		end_flag = true;
	}

}

//�`��
void PlayerMoveEvent::Draw() {

}