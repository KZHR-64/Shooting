#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//1�{�X(�f�X�h���O�h)

class Desdragud : public AbstractEnemy {
protected:
	float left_arm_distance, left_arm_angle, right_arm_distance, right_arm_angle;
	float left_shoulder_distance, left_shoulder_angle, right_shoulder_distance, right_shoulder_angle;
	float left_arm_spin_distance, left_arm_spin_angle, right_arm_spin_distance, right_arm_spin_angle;
	float left_arm_x, left_arm_y, right_arm_x, right_arm_y;
	float left_shoulder_x, left_shoulder_y, right_shoulder_x, right_shoulder_y;

	int attack_num; //�U���p�^�[��

	void Attack1(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //���@�_���e
	void Attack2(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //�~�T�C��
	void Attack3(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //�`���[�W�V���b�g

public:
	Desdragud(EnemyManager* ene, int num, float ini_x, float ini_y); //�R���X�g���N�^(�ԍ��A���W)
	~Desdragud(); //�f�X�g���N�^
	void AbsUpdate() override; //�K���s���X�V
	void Update(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw() override; //�`��
};
