#pragma once
#include "DxLib.h"
#include "PlayMusicEvent.h"

using namespace std;

//�R���X�g���N�^
PlayMusicEvent::PlayMusicEvent(EventManager* man, int num, bool stop_player, bool stop_enemy) : AbstractEvent(man, stop_player, stop_enemy) {

	bgm_num = num;
}

//�f�X�g���N�^
PlayMusicEvent::~PlayMusicEvent() {

}

//�X�V
void PlayMusicEvent::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect) {

	Sound::Get_Instance()->LoadBgm(bgm_num);
	end_flag = true;
}

//�`��
void PlayMusicEvent::Draw() {

}