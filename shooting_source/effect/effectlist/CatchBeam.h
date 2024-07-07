#pragma once
#include "../AbstractEffect.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//���݃r�[��

class CatchBeam : public AbstractEffect {
private:
	int beam_num; //�\������r�[���̐�
public:
	CatchBeam(EffectManager* eff, int num, float ini_x, float ini_y); //�R���X�g���N�^(�ԍ��A���W)
	~CatchBeam(); //�f�X�g���N�^
	void Update(); //�X�V
	void Draw() override; //�`��
};
