#pragma once
#include "DxLib.h"
#include "ScrollResetEvent.h"

using namespace std;

//�R���X�g���N�^
ScrollResetEvent::ScrollResetEvent(EventManager* man, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {
	
}

//�f�X�g���N�^
ScrollResetEvent::~ScrollResetEvent() {

}

//�X�V
void ScrollResetEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {

	Display::Get_Instance()->ReSetScrollXMax();
	Display::Get_Instance()->ReSetScrollYMax();
	end_flag = true;
}

//�`��
void ScrollResetEvent::Draw() {

}