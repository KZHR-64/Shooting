#pragma once
#include "ModeBase.h"
#include "Parameter.h"
#include "..\player\Player.h"
#include "..\map\MapChipManager.h"
#include "..\enemy\EnemyManager.h"
#include "..\bullet\BulletManager.h"
#include "..\effect\EffectManager.h"
#include "..\event\EventManager.h"
#include "..\single\Key.h"
#include "..\single\Display.h"
#include "..\single\Sound.h"
#include "..\single\Image.h"
#include <memory>

class GameBase;
class Player;
class MapChipManager;
class EnemyManager;
class BulletManager;
class EffectManager;
class EventManager;
//class Parameter;

class Game : public ModeBase {
private:
	std::shared_ptr<Player> player;
	std::shared_ptr<MapChipManager> map;
	std::shared_ptr<EnemyManager> enemy;
	std::shared_ptr<BulletManager> bullet;
	std::shared_ptr<EffectManager> effect;
	std::shared_ptr<EventManager> event;
	Parameter parameter;
	int stage_num; //�X�e�[�W�ԍ�
	int live; //�c�@
	bool pause_flag; //�|�[�Y��ʂ��J���Ă��邩
	int cursor; //�|�[�Y��ʂ̃J�[�\��
	
	void GameUpdate(); //�Q�[���̍X�V
	void PauseUpdate(); //�|�[�Y��ʂ̍X�V

public:
	Game(ModeChanger *changer, Parameter &param); //�R���X�g���N�^
	~Game(); //�f�X�g���N�^
	void Restart(); //�ĊJ
	void Update(); //�X�V
	void Draw(); //�`��
};