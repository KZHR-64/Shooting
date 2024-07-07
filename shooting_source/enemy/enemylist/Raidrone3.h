#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//��܂��͉��Ɉړ�����G���G

class Raidrone3 : public AbstractEnemy {
protected:
	int hundle_num; //�\������摜
public:
	Raidrone3(EnemyManager* ene, int num, float ini_x, float ini_y); //�R���X�g���N�^(�ԍ��A���W)
	~Raidrone3(); //�f�X�g���N�^
	void AbsUpdate() override; //�K���s���X�V
	void Update(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw() override; //�`��
};
