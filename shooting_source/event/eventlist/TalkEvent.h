#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <iostream>
#include <string>
#include <sstream>
#include <memory>

//��b�C�x���g

class TalkEvent : public AbstractEvent {
protected:
	std::string chara_name; //�L�����N�^�[��
	std::string message; //����
public:
	TalkEvent(EventManager* man, char* name, char *str, bool stop_player, bool stop_enemy); //�R���X�g���N�^(�L�������A���́A���@���~�߂邩�A�G���~�߂邩)
	~TalkEvent(); //�f�X�g���N�^
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw(); //�`��
};
