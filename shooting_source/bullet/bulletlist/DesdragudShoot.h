#pragma once
#include "../AbstractBullet.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//�f�X�h���O�h�̃`���[�W�V���b�g

class DesdragudShoot : public AbstractBullet {
protected:
	float bx, by, bx2, by2; //1,2�t���[���O�̍��W
	float base_speed; //��ƂȂ鑬�x
	float speed; //���x
public:
	DesdragudShoot(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle); //�R���X�g���N�^(�摜�̔ԍ��A���W�A���x�A�p�x)
	~DesdragudShoot(); //�f�X�g���N�^
	void Update(std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //�X�V
	void Draw() override; //�`��
};

