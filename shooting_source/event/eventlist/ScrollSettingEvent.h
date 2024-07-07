#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <iostream>
#include <string>
#include <sstream>

//�X�N���[���ʒu�����C�x���g

class ScrollSettingEvent : public AbstractEvent {
protected:
	int px; //x���W
	int py; //y���W
public:
	ScrollSettingEvent(EventManager* man, int x, int y, bool stop_player, bool stop_enemy); //�R���X�g���N�^(���W�A���@���~�߂邩�A�G���~�߂邩)
	~ScrollSettingEvent(); //�f�X�g���N�^
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw(); //�`��
};
