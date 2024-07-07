#pragma once
#include "DxLib.h"
#include "WaitBattleEvent.h"

using namespace std;

//コンストラクタ
WaitBattleEvent::WaitBattleEvent(EventManager* man, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {

	
}

//デストラクタ
WaitBattleEvent::~WaitBattleEvent() {

}

//更新
void WaitBattleEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {

	//ボスがいないなら終了
	if (!enemy->GetBossFlag()) {
		end_flag = true;
	}
}

//描画
void WaitBattleEvent::Draw() {

}