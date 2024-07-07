#pragma once
#include "../character/CharacterBase.h"
#include "EnemyManager.h"
#include "../Define.h"
//#include "Game.h"
#include "../map/MapChipManager.h"
#include "../map/AbstractMapChip.h"
#include "../bullet/BulletManager.h"
#include "../effect/EffectManager.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <memory>

class EnemyManager;
class BulletManager;
class MapChipManager;
class EffectManager;
class AbstractMapChip;

class AbstractEnemy : public CharacterBase {
protected:
	EnemyManager* manager;

	std::vector<std::shared_ptr<AbstractEnemy>> parts; //�p�[�c�Ƃ��Ĉ����G
	AbstractEnemy* base_enemy; //�{��
	std::vector<HitStruct> hit; //�����蔻��

	bool live_flag; //�\�����邩
	bool end_flag; //�������邩
	bool boss_flag; //�{�X�L������
	bool hit_flag; //�����蔻��
	int image; //�\������摜
	int trance; //�����x
	int time; //�^�C�}�[
	int hp; //HP
	float x; //x���W
	float y; //y���W
	float base_x; //���X��x���W
	float base_y; //���X��y���W
	float sx; //x�����̑��x
	float sy; //y�����̑��x
	float angle; //�p�x
	float spin_speed; //��]���x
	bool lr; //����(0=���A1=�E)
	int jump_time; //�W�����v���Ă��鎞��
	bool jump_flag; //�W�����v���Ă��邩
	bool flying_flag; //���ł��邩
	bool damaged; //�_���[�W���󂯂Ă��邩
	int damage_time; //�_���[�W����̎���
	bool inhale; //�z�����߂邩
	bool hit_map; //�}�b�v�`�b�v�ɓ����邩
	bool inhaled_flag; //�z�����܂�Ă��邩

	void SetHit(float cx, float cy, float hit_size); //�����蔻��̔z�u(x,y���W�A�����蔻��̑傫��)

public:
	AbstractEnemy(EnemyManager* man, int num, float ini_x, float ini_y); //�R���X�g���N�^(�摜�̔ԍ��A���W)
	~AbstractEnemy(); //�f�X�g���N�^

	AbstractEnemy* GetBase(); //�{�̂��擾
	void SetBase(AbstractEnemy* base); //�{�̂�ݒ�
	bool GetEndFlag(); //�������邩���擾
	void SetEndFlag(bool flag); //�������邩��ݒ�
	bool GetBossFlag(); //�{�X�����擾
	void SetBossFlag(int rank); //�{�X����ݒ�(�i)
	bool GetHitFlag(); //�����蔻����擾
	void SetHitFlag(bool flag); //�����蔻���ݒ�
	void SetTrance(int set_trance); //�����x��ݒ�
	int GetTime(); //�G�̎��Ԃ�Ԃ�
	void SetTime(int set_time); //���Ԃ�ݒ�(����)
	int GetHp(); //HP��Ԃ�
	void SetHp(int set_hp); //HP��ݒ�(HP)
	float GetX(); //�G��x���W��Ԃ�
	void SetX(float set_x); //�G��x���W��ݒ�
	float GetY(); //�G��y���W��Ԃ�
	void SetY(float set_y); //�G��y���W��ݒ�
	float GetBaseX(); //�G�̌���x���W��Ԃ�
	void SetBaseX(float set_x); //�G�̌���x���W��ݒ�
	float GetBaseY(); //�G�̌���y���W��Ԃ�
	void SetBaseY(float set_y); //�G�̌���y���W��ݒ�
	void SetSpeed(float speed); //�p�x����ɑ��x��ݒ�
	float GetXSpeed(); //�G��x�����̑��x��Ԃ�
	void SetXSpeed(float set_x); //�G��x�����̑��x��ݒ�
	float GetYSpeed(); //�G��y�����̑��x��Ԃ�
	void SetYSpeed(float set_y); //�G��y�����̑��x��ݒ�
	float GetAngle(); //�p�x���擾
	void SetAngle(float set_angle); //�p�x��ݒ�(�p�x)
	float GetSpinSpeed(); //��]���x���擾
	void SetSpinSpeed(float set_angle); //��]���x��ݒ�(�p�x)
	bool GetLr(); //�������擾
	void SetLr(bool set_lr); //������ݒ�(����)
	bool GetFlying(); //���ł��邩���擾
	void SetFlying(bool flag); //���ł��邩��ݒ�
	bool GetDamaged(); //�_���[�W���󂯂Ă��邩���擾
	bool GetInhale(); //�z�����߂邩���擾
	void SetInhale(bool flag); //�z�����߂邩��ݒ�
	bool GetHitMap(); //�}�b�v�`�b�v�ɓ����邩���擾
	void SetHitMap(bool flag); //�}�b�v�`�b�v�ɓ����邩��ݒ�
	bool GetInhaledFlag(); //�z�����܂�Ă��邩���擾
	void SetInhaledFlag(bool flag); //�z�����܂�Ă��邩��ݒ�
	void Homing(float set_spin_speed, float speed, float set_x, float set_y); //�ڕW�Ɍ����Ă̑��x�𒲐�(��]���x�A���x�A�ڕW�̍��W)
	void HomingSpin(float set_spin_speed, float set_x, float set_y, bool use_base = false); //�ڕW�Ɍ����ĉ�](��]���x�A�ڕW�̍��W�A��̍��W���g����)
	void Spin(float set_spin_speed, float spin_max, float spin_min); //��]������(��]���x�A����A����)

	bool HitDamage(int damage_num); //�_���[�W����(�_���[�W�l)
	void HitUpdate(); //�����蔻��̍X�V
	void DrawHit(); //�����蔻��̕`��

	void AdjustPosition(std::shared_ptr<MapChipManager> map); //�ʒu�̒���
	void HitCheckBullet(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //�e�ɓ������Ă��邩
	void HitCheckEnemy(float cx, float cy, float hit_size, std::shared_ptr<EffectManager> effect); //�G�ɓ������Ă��邩
	bool HitCheckChara(float cx, float cy, float hit_size, bool check_hit = true); //�L�����N�^�[�Ƃ̓����蔻��(�L������x,y���W�A�����蔻��̑傫���A�����蔻��̗L�����m�F���邩)
	void Timer(); //�^�C�}�[�֘A�̍X�V

	virtual void AbsUpdate() = 0; //�K���s���X�V
	virtual void Update(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect) = 0; //�X�V
};