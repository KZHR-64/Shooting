#pragma once
#include "DxLib.h"
#include "ScrollSettingEvent.h"

using namespace std;

//�R���X�g���N�^
ScrollSettingEvent::ScrollSettingEvent(EventManager* man, int x, int y, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {
	px = x;
	py = y;

	if (px < 0) {
		px = Display::Get_Instance()->GetScrollXMax();
	}
	else {
		px += (int)(man->GetX());
	}
	if (py < 0) {
		py = Display::Get_Instance()->GetScrollYMax();
	}
	else {
		py += (int)(man->GetY());
	}
}

//�f�X�g���N�^
ScrollSettingEvent::~ScrollSettingEvent() {

}

//�X�V
void ScrollSettingEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {

	Display::Get_Instance()->SetScrollXMax(px);
	Display::Get_Instance()->SetScrollYMax(py);
	end_flag = true;
}

//�`��
void ScrollSettingEvent::Draw() {

}