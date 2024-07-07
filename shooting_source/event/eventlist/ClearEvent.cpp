#pragma once
#include "DxLib.h"
#include "ClearEvent.h"

using namespace std;

//�R���X�g���N�^
ClearEvent::ClearEvent(EventManager* man, int waiting, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {
	wait_time = waiting;
}

//�f�X�g���N�^
ClearEvent::~ClearEvent() {

}

//�X�V
void ClearEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {
	//�҂����Ԃ��߂�����I��
	if (wait_time <= time) {
		manager->SetClearFlag(true);
		end_flag = true;
	}
}

//�`��
void ClearEvent::Draw() {

}