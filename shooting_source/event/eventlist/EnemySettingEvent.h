#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <iostream>
#include <string>
#include <sstream>

//�G�o���C�x���g

class EnemySettingEvent : public AbstractEvent {
protected:
	int enemy_num; //�G�ԍ�
	float ex; //x���W
	float ey; //y���W
public:
	EnemySettingEvent(EventManager* man, int num, float x, float y, bool stop_player, bool stop_enemy); //�R���X�g���N�^(�G�ԍ��A���W�A���@���~�߂邩�A�G���~�߂邩)
	~EnemySettingEvent(); //�f�X�g���N�^
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw(); //�`��
};
