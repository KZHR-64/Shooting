#pragma once
#include "DxLib.h"
#include "MissEvent.h"

using namespace std;

//コンストラクタ
MissEvent::MissEvent(EventManager* man, int waiting, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {
	wait_time = waiting;
}

//デストラクタ
MissEvent::~MissEvent() {

}

//更新
void MissEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {
	//待ち時間を過ぎたら終了
	if (wait_time <= time) {
		manager->SetRestartFlag(true);
		end_flag = true;
	}

	//イベント開始時
	if (time == 0) {
		Sound::Get_Instance()->StopBgm();
		player->SetXSpeed(0.f);
		player->SetYSpeed(0.f);
	}

	if (time == 30) {
		float px = player->GetX();
		float py = player->GetY();
		player->SetDrawFlag(false);
		effect->SetEffect(1, px, py); //爆発
	}
}

//描画
void MissEvent::Draw() {

}