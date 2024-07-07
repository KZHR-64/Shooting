#pragma once
#include "../AbstractBullet.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//��U��ʊO�ɔ��ł���~��~�T�C��

class FallBomber : public AbstractBullet {
protected:

public:
	FallBomber(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle); //�R���X�g���N�^(�摜�̔ԍ��A���W�A���x�A�p�x)
	~FallBomber(); //�f�X�g���N�^
	void Update(std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw() override; //�`��
};

