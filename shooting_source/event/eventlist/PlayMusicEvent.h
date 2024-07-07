#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <iostream>
#include <string>
#include <sstream>

//BGM�Đ��C�x���g

class PlayMusicEvent : public AbstractEvent {
protected:
	int bgm_num; //BGM�ԍ�
public:
	PlayMusicEvent(EventManager* man, int num, bool stop_player, bool stop_enemy); //�R���X�g���N�^(BGM�ԍ��A���@���~�߂邩�A�G���~�߂邩)
	~PlayMusicEvent(); //�f�X�g���N�^
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw(); //�`��
};
