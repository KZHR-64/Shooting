#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
//#include "Game.h"
#include "AbstractBullet.h"
#include "../main/Parameter.h"
#include "../player/Player.h"
#include "../effect/EffectManager.h"
#include "../enemy/EnemyManager.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include "../single/Sound.h"
#include <map>
#include <list>
#include <vector>
#include <memory>

class AbstractBullet;
class Player;
class EnemyManager;
class MapChipManager;
class EffectManager;

struct BulletDataStruct
{
	//�e���̍\����
	int type; //���
	int image; //�\������摜
	bool breakable; //�󂹂邩
	bool hit_player; //���@�ɓ����邩
	bool hit_enemy; //�G�ɓ����邩
	bool hit_map; //�}�b�v�`�b�v�ɓ����邩
	int damage; //�_���[�W�l
};

class BulletManager : public CharacterBase{
private:
	std::map<int, BulletDataStruct> bullet_data; //�e���
	std::list<std::shared_ptr<AbstractBullet>> bullet; //�e

	void SetData(); //�e���̐ݒ�

	float px; //���@�̍��W
	float py;

public:
	BulletManager(); //�R���X�g���N�^
	~BulletManager(); //�f�X�g���N�^
	void Reset(); //������
	void EraseCheck(); //�����邩�m�F
	std::shared_ptr<AbstractBullet> SetBullet(int num, float ini_x, float ini_y, float speed, float angle); //�e�̔z�u(�f�[�^�̔ԍ��A���W�A���x�A�p�x)
	void HitCheckMap(std::shared_ptr<MapChipManager> map); //�}�b�v�`�b�v�Ƃ̓����蔻��
	int HitCheckChara(float cx, float cy, float hit_size, bool check_player, bool check_enemy); //�L�����N�^�[�Ƃ̓����蔻��(�L������x,y���W�A�����蔻��̑傫���A���@�ɓ����邩�G�ɓ����邩)
	float GetPlayerX(); //���@��x���W���擾
	float GetPlayerY(); //���@��y���W���擾

	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw(); //�`��
};