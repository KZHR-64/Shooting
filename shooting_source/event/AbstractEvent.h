#pragma once
#include "../character/CharacterBase.h"
#include "EventManager.h"
#include "../Define.h"
//#include "Map.h"
#include "../player/Player.h"
#include "../enemy/EnemyManager.h"
#include "../effect/EffectManager.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <memory>

class EventManager;
class Player;
class EnemyManager;
class EffectManager;

class AbstractEvent : public CharacterBase{
protected:
	EventManager* manager;
	int time; //�^�C�}�[
	bool end_flag; //�I��������
	bool player_stop; //���@�̓������~�߂邩
	bool enemy_stop; //�G�̓������~�߂邩

public:
	AbstractEvent(EventManager* man, bool stop_player, bool stop_enemy); //�R���X�g���N�^(���@���~�߂邩�A�G���~�߂邩)
	~AbstractEvent(); //�f�X�g���N�^

	int GetTime(); //���Ԃ�Ԃ�
	void SetTime(int set_time); //���Ԃ�ݒ�(����)
	bool GetEndFlag(); //�I���������擾
	bool GetPlayerStop(); //���@���~�߂邩�擾
	bool GetEnemyStop(); //�G���~�߂邩�擾

	virtual void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect) = 0;
};