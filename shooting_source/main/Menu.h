#pragma once
#include "ModeBase.h"
#include "..\single\Key.h"
#include "..\single\Sound.h"
#include "..\single\Image.h"
#include "..\single\Display.h"

struct ChoiceStruct
{
	//�I�����̍\����
	int image; //�g�p����摜
	float ex_rate; //�\���{��
};

class Menu : public ModeBase {
private:
	int count; //�J�E���^�[
	int cursor_pos; //�J�[�\���̈ʒu
	int logo; //�^�C�g�����S

	ChoiceStruct choice[4]; //�I����

	void Reset(); //������
public:
	Menu(ModeChanger* changer, Parameter& param); //�R���X�g���N�^
	~Menu(); //�f�X�g���N�^
	void Update(); //�X�V
	void Draw(); //�`��
};