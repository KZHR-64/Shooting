#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
//#include "Game.h"
#include "../map/MapChipManager.h"
#include "../map/AbstractMapChip.h"
#include "../bullet/BulletManager.h"
#include "../enemy/EnemyManager.h"
#include "../effect/EffectManager.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <memory>

class MapChipManager;
class BulletManager;
class EnemyManager;
class EffectManager;
class AbstractMapChip;
class AbstractBullet;
class AbstractEnemy;
class AbstractEffect;

struct AttackStruct
{
	//�U���̍\����
	bool flag; //�U�����Ă��邩
	int push_time; //�{�^���������Ă��鎞��
};

struct CatcherStruct
{
	//���݃r�[���̍\����
	bool flag; //�o���Ă��邩
	bool catch_flag; //����ł��邩
	float x; //���W
	float y;
};

struct PlayerPartsStruct
{
	//�p�[�c�̍\����
	float x; //���W
	float y;
	float angle; //�p�x
	float total_angle; //�p�x�̍��v
	float def_angle; //�v�Z�p�̊p�x
	float def_distance; //�v�Z�p�̋���
	float spin_angle; //��]�̊�ƂȂ�p�x
	float spin_distance; //��]�̊�ƂȂ鋗��
};

class Player : public CharacterBase{
private:
	void Control(); //���@�̑���
	void DamageAction(); //�_���[�W����
	void Move(); //�ړ�
	void SetGraphic(); //�\������摜������
	void SetKeyRecord(); //�L�[�̗������X�V
	bool RecordCheck(bool record[], int point = 0); //���͗����̊m�F(�n����A�T���n�߂�_)
	void SetParts(); //�p�[�c�����낦��
	float PartsSpin(float parts_angle, float spin_speed, float spin_max, float spin_min); //�p�[�c����]������(��̊p�x�A��]���x�A����A����)

	int hp; //HP
	float x, y; //���W
	float fx, fy; //���ɍs���\��̍��W
	float sx, sy; //���x
	float angle; //�p�x
	float sangle; //��]���x
	bool lr; //����(0=���A1=�E)
	bool damaged; //�_���[�W���󂯂Ă��邩
	int damage_time; //�_���[�W����̎���
	int move_type; //�s���Ă��铮��
	int move_time; //����̎���
	int handle; //�\������摜�̔ԍ�
	int inv_time; //���G����
	bool draw_flag; //�`�悷�邩
	const float move_speed = 6.f; //��ƂȂ�ړ����x
	const float hit_size = 16.f; //�����蔻��̑傫��

	AttackStruct attack;
	CatcherStruct catch_arm;
	//std::shared_ptr<AbstractEnemy> catch_enemy; //���񂾓G
	std::shared_ptr<AbstractEffect> catch_effect; //�r�[���p�̃G�t�F�N�g

	PlayerPartsStruct body, left_thigh, left_leg, right_thigh, right_leg, left_shoulder, right_shoulder, left_arm, right_arm; //�e�p�[�c
	
	bool commando[BUTTON][RECORD]; //���͂����L�[�̗���

public:
	Player(); //�R���X�g���N�^
	~Player(); //�f�X�g���N�^
	void Reset(); //������
	void AdjustPosition(std::shared_ptr<MapChipManager> map, bool event_flag); //�ʒu�̒���
	void AttackCheck(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //�U��
	void InhaleCheck(std::shared_ptr<MapChipManager> map, std::shared_ptr<EnemyManager> enemy); //�z�����߂邩�m�F
	void HitCheckEnemy(std::shared_ptr<EnemyManager> enemy); //�G�ɓ������Ă��邩
	void HitCheckBullet(std::shared_ptr<BulletManager> bullet); //�e�ɓ������Ă��邩
	int GetHp(); //HP��Ԃ�
	float GetX(); //x���W��Ԃ�
	float GetY(); //y���W��Ԃ�
	void SetX(float px); //x���W��ݒ�
	void SetY(float py); //y���W��ݒ�
	float GetXSpeed(); //���̑��x��Ԃ�
	float GetYSpeed(); //�c�̑��x��Ԃ�
	void SetXSpeed(float speed_x); //���̑��x��ݒ�(����)
	void SetYSpeed(float speed_y); //�c�̑��x��ݒ�(����)
	void SetDrawFlag(bool flag); //�`�悷�邩�ݒ�
	void Update(); //�X�V
	void Draw() override; //�`��
};