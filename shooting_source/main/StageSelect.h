#pragma once
#include "ModeBase.h"
#include "..\single\Key.h"
#include "..\single\Sound.h"
#include "..\single\Image.h"
#include "..\single\Display.h"
#include <iostream>
#include <string>
#include <sstream>

struct SubTitleStruct
{
	//�T�u�^�C�g���̍\����
	int hundle; //�T���l�C���̃n���h��
	bool select_flag; //�I�ׂ邩
	std::string str1; //�T�u�^�C�g��1�s��
	std::string str2; //�T�u�^�C�g��2�s��
};

class StageSelect : public ModeBase {
private:
	void Reset(); //������
	void SetData(); //���̍X�V
	int stage_num; //�I���X�e�[�W
	int cursor_pos_x; //�J�[�\���̈ʒu
	int cursor_pos_y; //�J�[�\���̈ʒu

	int message_font; //�t�H���g���

	SubTitleStruct subtitle[STAGE_MAX];
public:
	StageSelect(ModeChanger* changer, Parameter& param); //�R���X�g���N�^
	~StageSelect(); //�f�X�g���N�^
	void Update(); //�X�V
	void Draw(); //�`��
};