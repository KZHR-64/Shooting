#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
//#include "Game.h"
#include "../main/Parameter.h"
#include "AbstractMapChip.h"
#include "../player/Player.h"
#include "../enemy/EnemyManager.h"
#include "../event/EventManager.h"
//#include "Effect.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include "../single/Sound.h"
#include <map>
#include <list>
#include <vector>
#include <memory>

class AbstractMapChip;
class WarpDoor;
class Player;
class EnemyManager;
class EventManager;

struct MapChipDataStruct
{
	//�}�b�v�`�b�v���̍\����
	int type; //���
	int image; //�\������摜
	int size_x; //���̑傫��
	int size_y; //�c�̑傫��
	bool inhale; //�z�����߂邩
	bool breakable; //�󂹂邩
};

struct EventDataStruct
{
	//�C�x���g�z�u���̍\����
	bool flag; //�������邩
	int num; //�ԍ�
	float x; //x���W
	float y; //y���W
};

struct MapDataStruct
{
	//�}�b�v���̍\����
	char mapfile_name[256]; //�}�b�v�`�b�v�z�u�̃t�@�C����
	char scroll_name[256]; //�X�N���[�����̃t�@�C����
	char back_name[256]; //BGM�Ɣw�i�ݒ�̃t�@�C����
	char enemy_name[256]; //�G�z�u�̃t�@�C����
	char event_name[256]; //�C�x���g�z�u�̃t�@�C����
	char event_data_name[256]; //�C�x���g���̃t�@�C����
};

struct BackStruct
{
	//�w�i�̍\����
	int image; //�摜
	float x; //���W(��������Ƃ���)
	float y;
	float sx; //�X�N���[�����鑬�x(�{��)
	float sy;
	bool loop; //���[�v���邩
};

class MapChipManager{
private:
	std::list<std::shared_ptr<AbstractMapChip>> mapchip; //�}�b�v�`�b�v
	std::vector<EventDataStruct> standby_event; //�C�x���g
	std::vector<char*> stage_data; //�X�e�[�W���
	std::vector<MapDataStruct> map_data; //�}�b�v���
	std::map<int, MapChipDataStruct> mapchip_data; //�}�b�v�`�b�v���
	std::vector<BackStruct> back_data; //�w�i

	void SetData(); //�}�b�v�`�b�v���̐ݒ�
	void SetStageData(); //�X�e�[�W���̐ݒ�
	void SetMapData(char* file_name); //�}�b�v���̐ݒ�
	void SetBackData(); //BGM�Ɣw�i���̐ݒ�
	void MakeMapScroll(); //�X�N���[���͈͂̐ݒ�
	void MakeMapEvent(); //�C�x���g�J�n�ʒu�̐ݒ�
	void WindowCheck(std::shared_ptr<AbstractMapChip>); //��ʓ��Ɏ��܂��Ă��邩�m�F
	void MapScroll(std::shared_ptr<EnemyManager> enemy); //�}�b�v�̃X�N���[��
	void BackUpdate(); //�w�i�̍X�V
	void BackDraw(); //�w�i�̕`��

	int stage_num; //�X�e�[�W�ԍ�
	int next_map; //���̃}�b�v
	int bgm; //�Đ�����BGM
	int scroll_base_x; //��ƂȂ�X�N���[�����x
	int scroll_base_y;
	int scroll_speed_x; //�X�N���[�����x
	int scroll_speed_y;
	int scroll_save_x; //�ۑ������X�N���[�����x
	int scroll_save_y;

public:
	MapChipManager(Parameter &param); //�R���X�g���N�^
	~MapChipManager(); //�f�X�g���N�^
	void Reset(); //������
	void MakeMap(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EventManager> event); //�}�b�v�̐���(���@�A�G�A�C�x���g�̃N���X)
	std::shared_ptr<AbstractMapChip> SetMapChip(int num, float ini_x, float ini_y); //�}�b�v�`�b�v�̔z�u(�f�[�^�̔ԍ��A���W)
	std::shared_ptr<AbstractMapChip> HitCheck(float cx, float cy, int size_x, int size_y, bool check_inhale, bool check_break, bool abs_check = false); //�L�������}�b�v�`�b�v�ɓ������Ă��邩(�L������x,y���W�Ax,y�����̑傫���A�z�����߂邩�A�󂹂邩�A�����蔻��ɂ�����炸�m�F���邩)
	std::shared_ptr<AbstractMapChip> HitCheckLeft(float cx, float cy, float hit_size); //�L�������}�b�v�`�b�v�ɓ������Ă��邩(���̔���)(�L������x,y���W�A�����蔻��̑傫��)
	std::shared_ptr<AbstractMapChip> HitCheckRight(float cx, float cy, float hit_size); //�L�������}�b�v�`�b�v�ɓ������Ă��邩(�E�̔���)(�L������x,y���W�A�����蔻��̑傫��)
	std::shared_ptr<AbstractMapChip> HitCheckTop(float cx, float cy, float hit_size); //�L�������}�b�v�`�b�v�ɓ������Ă��邩(��̔���)(�L������x,y���W�A�����蔻��̑傫��)
	std::shared_ptr<AbstractMapChip> HitCheckBottom(float cx, float cy, float hit_size); //�L�������}�b�v�`�b�v�ɓ������Ă��邩(���̔���)(�L������x,y���W�A�����蔻��̑傫��)
	void CheckStep(float cx, float cy, int size_x, int size_y); //�L�������}�b�v�`�b�v�ɏ���Ă��邩(�L������x,y���W�Ax,y�����̑傫��)
	void EventHitCheck(std::shared_ptr<EventManager> event, float cx, float cy); //�L�������C�x���g�����ʒu�ɓ������Ă��邩(�L������x,y���W)
	
	int GetScrollSpeedX(); //���̃X�N���[�����x���擾
	int GetScrollSpeedY(); //�c�̃X�N���[�����x���擾
	void StopScroll(); //�X�N���[���̒�~
	void StartScroll(); //�X�N���[���̊J�n

	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy); //�X�V
	void Draw(); //�`��
};