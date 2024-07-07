#pragma once
#include "DxLib.h"
#include "EffectSettingEvent.h"

using namespace std;

//�R���X�g���N�^
EffectSettingEvent::EffectSettingEvent(EventManager* man, int num, float x, float y, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {
	effect_num = num;
	ex = x + man->GetX();
	ey = y + man->GetX();

}

//�f�X�g���N�^
EffectSettingEvent::~EffectSettingEvent() {

}

//�X�V
void EffectSettingEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {
	effect->SetEffect(effect_num, ex, ey);

	end_flag = true;
}

//�`��
void EffectSettingEvent::Draw() {

}