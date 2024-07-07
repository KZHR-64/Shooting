#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <iostream>
#include <string>
#include <sstream>

//�G�t�F�N�g�����C�x���g

class EffectSettingEvent : public AbstractEvent {
protected:
	int effect_num; //�G�t�F�N�g�ԍ�
	float ex; //x���W
	float ey; //y���W
public:
	EffectSettingEvent(EventManager* man, int num, float x, float y, bool stop_player, bool stop_enemy); //�R���X�g���N�^(�G�t�F�N�g�ԍ��A���W�A���@���~�߂邩�A�G���~�߂邩)
	~EffectSettingEvent(); //�f�X�g���N�^
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw(); //�`��
};
