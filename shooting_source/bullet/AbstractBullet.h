#pragma once
#include "../character/CharacterBase.h"
#include "BulletManager.h"
#include "../Define.h"
//#include "Game.h"
#include "../map/MapChipManager.h"
#include "../map/AbstractMapChip.h"
#include "../effect/EffectManager.h"
#include "../enemy/EnemyManager.h"
//#include "Bullet.h"
//#include "Enemy.h"
//#include "Bullet.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <vector>
#include <memory>

class BulletManager;
class EnemyManager;
class MapChipManager;
class EffectManager;
class AbstractMapChip;

class AbstractBullet : public CharacterBase{
protected:
	BulletManager* manager;
	std::vector<HitStruct> hit; //�����蔻��

	bool live_flag; //���삷�邩
	bool end_flag; //�������邩
	int image; //�\������摜
	int time; //�^�C�}�[
	int end_time; //���ł܂ł̎���
	int damage; //�_���[�W�l
	float x; //x���W
	float y; //y���W
	float base_x; //���X��x���W
	float base_y; //���X��y���W
	int size_x; //���̑傫��
	int size_y; //�c�̑傫��
	float sx; //x�����̑��x
	float sy; //y�����̑��x
	float angle; //�p�x
	bool breakable; //�󂹂邩
	bool hit_player; //���@�ɓ����邩
	bool hit_enemy; //�G�ɓ����邩
	bool hit_map; //�}�b�v�`�b�v�ɓ����邩

	void SetHit(float cx, float cy, float hit_size); //�����蔻��̔z�u(x,y���W�A�����蔻��̑傫��)

public:
	AbstractBullet(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle); //�R���X�g���N�^(�摜�̔ԍ��A���W�A���x�A�p�x)
	~AbstractBullet(); //�f�X�g���N�^

	bool GetEndFlag(); //�������邩���擾
	void SetEndFlag(bool flag); //�������邩��ݒ�
	int GetTime(); //�e�̎��Ԃ�Ԃ�
	void SetTime(int set_time); //���Ԃ�ݒ�(����)
	int GetEndTime(); //���ł܂ł̎��Ԃ�Ԃ�
	void SetEndTime(int set_time); //���ł܂ł̎��Ԃ�ݒ�(����)
	int GetDamage(); //�_���[�W�l��Ԃ�
	void SetDamage(int set_damage); //�_���[�W�l��ݒ�(�_���[�W�l)
	float GetX(); //�e��x���W��Ԃ�
	void SetX(float set_x); //�e��x���W��ݒ�
	float GetY(); //�e��y���W��Ԃ�
	void SetY(float set_y); //�e��y���W��ݒ�
	float GetBaseX(); //�e�̌���x���W��Ԃ�
	void SetBaseX(float set_x); //�e�̌���x���W��ݒ�
	float GetBaseY(); //�e�̌���y���W��Ԃ�
	void SetBaseY(float set_y); //�e�̌���y���W��ݒ�
	int GetSizeX(); //�e�̉��̑傫����Ԃ�
	void SetSizeX(int set_size); //�e�̉��̑傫����ݒ�
	int GetSizeY(); //�e�̏c�̑傫����Ԃ�
	void SetSizeY(int set_size); //�e�̏c�̑傫����ݒ�
	void SetSpeed(float speed); //�p�x����ɑ��x��ݒ�
	float GetXSpeed(); //�e��x�����̑��x��Ԃ�
	void SetXSpeed(float set_x); //�e��x�����̑��x��ݒ�
	float GetYSpeed(); //�e��y�����̑��x��Ԃ�
	void SetYSpeed(float set_y); //�e��y�����̑��x��ݒ�
	float GetAngle(); //�p�x���擾
	void SetAngle(float set_angle); //�p�x��ݒ�(�p�x)
	float GetSpinSpeed(); //��]���x���擾
	void SetSpinSpeed(float set_angle); //��]���x��ݒ�(�p�x)
	bool GetBreakable(); //�󂹂邩���擾
	void SetBreakable(bool flag); //�󂹂邩��ݒ�
	bool GetHitPlayer(); //���@�ɓ����邩���擾
	void SetHitPlayer(bool flag); //���@�ɓ����邩��ݒ�
	bool GetHitEnemy(); //�G�ɓ����邩���擾
	void SetHitEnemy(bool flag); //�G�ɓ����邩��ݒ�
	bool GetHitMap(); //�}�b�v�`�b�v�ɓ����邩���擾
	void SetHitMap(bool flag); //�}�b�v�`�b�v�ɓ����邩��ݒ�

	void HitUpdate(); //�����蔻��̍X�V
	void DrawHit(); //�����蔻��̕`��

	int HitCheckChara(float cx, float cy, float hit_size, bool check_inhale = false); //�L�����N�^�[�Ƃ̓����蔻��(�L������x,y���W�A�����蔻��̑傫���A�z�����ݔ��肩)
	void HitCheckMap(std::shared_ptr<MapChipManager> map); //�}�b�v�`�b�v�Ƃ̓����蔻��

	virtual void Update(std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect) = 0;
};