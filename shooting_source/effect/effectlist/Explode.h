#pragma once
#include "../AbstractEffect.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//����

class Explode : public AbstractEffect {
private:
	int hundle_num; //�\������摜
public:
	Explode(EffectManager* eff, int num, float ini_x, float ini_y); //�R���X�g���N�^(�ԍ��A���W)
	~Explode(); //�f�X�g���N�^
	void Update(); //�X�V
	void Draw() override; //�`��
};
