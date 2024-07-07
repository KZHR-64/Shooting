#pragma once
#include "DxLib.h"
#include "EnemySettingEvent.h"

using namespace std;

//コンストラクタ
EnemySettingEvent::EnemySettingEvent(EventManager* man, int num, float x, float y, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {
	enemy_num = num;
	ex = x + man->GetX();
	ey = y + man->GetY();
}

//デストラクタ
EnemySettingEvent::~EnemySettingEvent() {

}

//更新
void EnemySettingEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {
	enemy->SetEnemy(enemy_num, ex, ey);
	
	end_flag = true;
}

//描画
void EnemySettingEvent::Draw() {

}