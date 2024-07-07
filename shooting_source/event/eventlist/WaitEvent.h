#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//��莞�Ԓ�~����C�x���g

class WaitEvent : public AbstractEvent{
protected:
	int wait_time; //�҂�����
public:
	WaitEvent(EventManager* man, int waiting, bool stop_player, bool stop_enemy); //�R���X�g���N�^(�҂����ԁA���@���~�߂邩�A�G���~�߂邩)
	~WaitEvent(); //�f�X�g���N�^
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw(); //�`��
};
