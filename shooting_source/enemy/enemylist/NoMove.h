#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//�����Ȃ��G

class NoMove : public AbstractEnemy {
protected:

public:
	NoMove(EnemyManager* ene, int num, float ini_x, float ini_y); //�R���X�g���N�^(�ԍ��A���W)
	~NoMove(); //�f�X�g���N�^
	void AbsUpdate() override; //�K���s���X�V
	void Update(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw() override; //�`��
};
