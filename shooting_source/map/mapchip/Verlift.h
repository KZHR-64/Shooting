#pragma once
#include "../AbstractMapChip.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//�󂹂鑫��

class Verlift : public AbstractMapChip{
protected:
public:
	Verlift(MapChipManager* man, int num); //�R���X�g���N�^(�ԍ�)
	~Verlift(); //�f�X�g���N�^
	void Update(); //�X�V
	void Draw() override; //�`��
};
