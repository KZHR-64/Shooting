#pragma once
#include "DxLib.h"
#include "WaitBattleEvent.h"

using namespace std;

//�R���X�g���N�^
WaitBattleEvent::WaitBattleEvent(EventManager* man, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {

	
}

//�f�X�g���N�^
WaitBattleEvent::~WaitBattleEvent() {

}

//�X�V
void WaitBattleEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {

	//�{�X�����Ȃ��Ȃ�I��
	if (!enemy->GetBossFlag()) {
		end_flag = true;
	}
}

//�`��
void WaitBattleEvent::Draw() {

}