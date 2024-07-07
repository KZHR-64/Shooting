#pragma once
#include "ModeBase.h"
#include "..\single\Key.h"
#include "..\single\Sound.h"
#include "..\single\Image.h"
#include "..\single\Display.h"
#include <vector>
#include <iostream>
#include <string>
#include <sstream>

class Opening : public ModeBase {
private:

	int logo; //���S�̃n���h��
	int pal; //���S�̓����x
	int time; //�^�C�}�[

public:
	Opening(ModeChanger* changer, Parameter& param); //�R���X�g���N�^
	~Opening(); //�f�X�g���N�^
	void Update(); //�X�V
	void Draw(); //�`��
};