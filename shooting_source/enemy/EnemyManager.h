#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
//#include "Game.h"
#include "AbstractEnemy.h"
#include "../main/Parameter.h"
#include "../player/Player.h"
#include "../map/MapChipManager.h"
#include "../effect/EffectManager.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include "../single/Sound.h"
#include <map>
#include <list>
#include <vector>
#include <memory>

class Player;
class AbstractEnemy;
class MapChipManager;
class EffectManager;

struct EnemyDataStruct
{
	//�G���̍\����
	int type; //���
	int image; //�\������摜
	int hp; //HP
	int size_x; //���̑傫��
	int size_y; //�c�̑傫��
	bool inhale; //�z�����߂邩
	int rank; //�i(0=�G���A1=���{�X�A2�ȏ�=�{�X)
};

struct StandbyEnemyDataStruct
{
	//�}�b�v�ɔz�u����G�̍\����
	bool flag; //�o��������
	int num; //���
	float x; //���W
	float y;
};

class EnemyManager : public CharacterBase{
private:
	std::map<int, EnemyDataStruct> enemy_data; //�e���
	std::list<std::shared_ptr<AbstractEnemy>> enemy; //�G
	std::vector<StandbyEnemyDataStruct> standby_enemy; //�}�b�v�ɔz�u����G

	bool boss_battle; //�{�X����s���Ă��邩
	bool boss_flag; //�{�X���o�Ă��邩
	bool midboss_flag; //���{�X���o�Ă��邩
	float px; //���@�̍��W
	float py;

	void SetData(); //�G���̐ݒ�

public:
	EnemyManager(); //�R���X�g���N�^
	~EnemyManager(); //�f�X�g���N�^
	void Reset(); //������
	void EraseCheck(); //�����邩�m�F
	void SetStandby(char* file_name); //�G���}�b�v�ɔz�u
	std::shared_ptr<AbstractEnemy> SetEnemy(int num, float ini_x, float ini_y, AbstractEnemy* base = NULL); //�G�̔z�u(�f�[�^�̔ԍ��A���W�A�{��)
	void SpawnCheck(); //�G���o���ł��邩�m�F
	bool HitCheckChara(float cx, float cy, float hit_size); //�L�����N�^�[�Ƃ̓����蔻��(�L������x,y���W�Ax,y�����̑傫��)
	std::shared_ptr<AbstractEnemy> InhaleCheck(float cx, float cy, float hit_size, bool check_inhaled); //�z�����ݔ���(�L������x,y���W�A�����蔻��̑傫���A���łɋz�����܂�Ă�����̂��擾����)
	void HitCheckBullet(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //�e�ɓ������Ă��邩
	void HitCheckEnemy(std::shared_ptr<EffectManager> effect); //�G�ɓ������Ă��邩
	bool GetBossFlag(); //�{�X�풆���擾
	bool GetBeatBoss(); //�{�X��|�������擾
	float GetPlayerX(); //���@��x���W���擾
	float GetPlayerY(); //���@��y���W���擾

	void Update(std::shared_ptr<MapChipManager> map, std::shared_ptr<BulletManager> bullet, std::shared_ptr<Player> player, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw(); //�`��
};