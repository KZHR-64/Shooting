#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//���{�X1

class JumboRaidrone : public AbstractEnemy {
protected:
	int hundle_num; //�\������摜
	float bsy; //�U���O�̑��x
	int attack_num; //�U���p�^�[��

	void Attack1(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //�~�T�C��
	void Attack2(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //�G������

public:
	JumboRaidrone(EnemyManager* ene, int num, float ini_x, float ini_y); //�R���X�g���N�^(�ԍ��A���W)
	~JumboRaidrone(); //�f�X�g���N�^
	void AbsUpdate() override; //�K���s���X�V
	void Update(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw() override; //�`��
};
