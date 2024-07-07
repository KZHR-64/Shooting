#pragma once
#include "ModeBase.h"
#include "Parameter.h"
#include "..\single\Key.h"
#include "..\single\Sound.h"
#include "..\single\Image.h"
#include "..\single\Display.h"

class GameBase;

class Gameover : public ModeBase {
private:
	void Reset(); //������
	Parameter parameter;
	
	int cursor_pos; //�J�[�\���̈ʒu
	int select_hundle[2]; //�I�����̉摜

public:
	Gameover(ModeChanger* changer, Parameter& param); //�R���X�g���N�^
	~Gameover(); //�f�X�g���N�^
	void Update(); //�X�V
	void Draw(); //�`��
};