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

//������
void EffectManager::Reset(){

}

//�G�t�F�N�g�̔z�u
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

//�X�V
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
		//�����t���O��true�Ȃ����
		if ((*eff)->GetEndFlag()) {
			eff = effect.erase(eff);
		}
		else {
			eff++;
		}
	}
}

//�`��
void EffectManager::Draw(){
	if (effect.size() == 0) return;
	for (auto eff : effect) {
		eff->Draw();
	}
}