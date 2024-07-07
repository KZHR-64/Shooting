#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <iostream>
#include <string>
#include <sstream>

//�o�g���ҋ@�C�x���g

class WaitBattleEvent : public AbstractEvent {
protected:

public:
	WaitBattleEvent(EventManager* man, bool stop_player, bool stop_enemy); //�R���X�g���N�^(���@���~�߂邩�A�G���~�߂邩)
	~WaitBattleEvent(); //�f�X�g���N�^
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw(); //�`��
};
