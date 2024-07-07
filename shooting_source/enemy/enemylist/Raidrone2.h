#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//�㉺����G���G

class Raidrone2 : public AbstractEnemy {
protected:
	int hundle_num; //�\������摜
	float speed_angle; //���x�p�̊p�x
public:
	Raidrone2(EnemyManager* ene, int num, float ini_x, float ini_y); //�R���X�g���N�^(�ԍ��A���W)
	~Raidrone2(); //�f�X�g���N�^
	void AbsUpdate() override; //�K���s���X�V
	void Update(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw() override; //�`��
};
