#pragma once
#include "../AbstractEffect.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//���˂ɂ�鉌

class Smoke : public AbstractEffect {
private:
	int hundle_num; //�\������摜
public:
	Smoke(EffectManager* eff, int num, float ini_x, float ini_y); //�R���X�g���N�^(�ԍ��A���W)
	~Smoke(); //�f�X�g���N�^
	void Update(); //�X�V
	void Draw() override; //�`��
};
