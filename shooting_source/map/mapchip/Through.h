#pragma once
#include "../AbstractMapChip.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//���蔲���鑫��

class Through : public AbstractMapChip{
protected:
public:
	Through(MapChipManager *man, float ini_x, float ini_y); //�R���X�g���N�^(���W)
	~Through(); //�f�X�g���N�^
	void Draw() override; //�`��
};
