#pragma once
#include "DxLib.h"
#include "EffectManager.h"
#include "effectlist/CatchBeam.h"
#include "effectlist/Explode.h"
#include "effectlist/CallSign.h"
#include "effectlist/Smoke.h"
#include <math.h>

using namespace std;

EffectManager::EffectManager(){

}

EffectManager::~EffectManager(){
	effect.clear();
}

//初期化
void EffectManager::Reset(){

}

//エフェクトの配置
std::shared_ptr<AbstractEffect> EffectManager::SetEffect(int num, float ini_x, float ini_y) {
	std::shared_ptr<AbstractEffect> new_effect;

	switch (num)
	{
	case 0:
		new_effect = make_shared<CatchBeam>(this, num, ini_x, ini_y);
		break;
	case 1:
		new_effect = make_shared<Explode>(this, num, ini_x, ini_y);
		break;
	case 2:
		new_effect = make_shared<CallSign>(this, num, ini_x, ini_y);
		break;
	case 3:
		new_effect = make_shared<Smoke>(this, num, ini_x, ini_y);
		break;
	default:
		new_effect = make_shared<CatchBeam>(this, num, ini_x, ini_y);
		break;
	}

	effect.emplace_back(new_effect);

	return new_effect;
}

//更新
void EffectManager::Update(){
	if (effect.size() == 0) return;
	for (auto eff : effect) {
		eff->Update();
		eff->SetX(eff->GetX() + eff->GetXSpeed());
		eff->SetY(eff->GetY() + eff->GetYSpeed());
		int time = eff->GetTime();
		time++;
		eff->SetTime(time);
	}

	for (auto eff = effect.begin(); eff != effect.end();) {
		//消去フラグがtrueなら消去
		if ((*eff)->GetEndFlag()) {
			eff = effect.erase(eff);
		}
		else {
			eff++;
		}
	}
}

//描画
void EffectManager::Draw(){
	if (effect.size() == 0) return;
	for (auto eff : effect) {
		eff->Draw();
	}
}