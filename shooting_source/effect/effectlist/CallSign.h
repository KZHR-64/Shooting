#pragma once
#include "../AbstractEffect.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//�����M��

class CallSign : public AbstractEffect {
private:
	int hundle_num; //�\������摜
public:
	CallSign(EffectManager* eff, int num, float ini_x, float ini_y); //�R���X�g���N�^(�ԍ��A���W)
	~CallSign(); //�f�X�g���N�^
	void Update(); //�X�V
	void Draw() override; //�`��
};
