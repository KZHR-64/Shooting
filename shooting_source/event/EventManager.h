#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
//#include "Game.h"
#include "AbstractEvent.h"
#include "../main/Parameter.h"
#include "../player/Player.h"
#include "../enemy/EnemyManager.h"
#include "../effect/EffectManager.h"
#include "../map/MapChipManager.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include "../single/Sound.h"
#include <map>
#include <vector>
#include <queue>
#include <memory>

class AbstractEvent;
class Player;
class EnemyManager;
class EffectManager;
class MapChipManager;

struct EventListStruct
{
	//�C�x���g���̍\����
	int type; //���
	bool position; //�Q�Ƃ�����W(0=x,1=y)
	char file_name[256]; //�t�@�C����
};

class EventManager : public CharacterBase{
private:
	std::map<int, EventListStruct> event_data; //�C�x���g���
	std::queue<std::shared_ptr<AbstractEvent>> event_queue; //�C�x���g�̃R���e�i

	int message_font; //�t�H���g���
	
	float x, y; //���W

	bool player_stop; //���@�̓������~�߂邩
	bool enemy_stop; //�G�̓������~�߂邩
	bool clear_flag; //�X�e�[�W���N���A������
	bool restart_flag; //���Ȃ�����

public:
	EventManager(Parameter &param); //�R���X�g���N�^
	~EventManager(); //�f�X�g���N�^
	void Reset(); //������
	void SetStandby(char* file_name); //�C�x���g��p��
	void SetEvent(int num); //�C�x���g��\��(���)
	void SetEventList(int num, float ini_x, float ini_y); //�C�x���g�𕡐��\��(�t�@�C���ԍ�)

	void EventStart(); //�C�x���g���J�n
	void EventEnd(); //�I�������C�x���g������
	void AllEventEnd(); //�C�x���g��S�ď���
	bool GetPlayerStop(); //���@���~�߂邩�擾
	void SetPlayerStop(bool flag); //���@���~�߂邩�ݒ�
	bool GetEnemyStop(); //�G���~�߂邩�擾
	void SetEnemyStop(bool flag); //�G���~�߂邩�ݒ�
	bool GetClearFlag(); //�N���A���������擾
	void SetClearFlag(bool flag); //�N���A��������ݒ�
	bool GetRestartFlag(); //���Ȃ��������擾
	void SetRestartFlag(bool flag); //���Ȃ�������ݒ�
	int GetFont(); //�t�H���g�����擾
	bool GetPosition(int num); //�Q�Ƃ�����W���擾(�t�@�C���ԍ��A���W)
	float GetX(); //x���W��Ԃ�
	float GetY(); //y���W��Ԃ�

	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect, std::shared_ptr<MapChipManager> map); //�X�V
	void Draw(); //�`��
};