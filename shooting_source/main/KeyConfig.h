#pragma once
#include "ModeBase.h"
#include "..\single\Key.h"
#include "..\single\Sound.h"
#include "..\single\Image.h"
#include "..\single\Display.h"

struct KeySettingStruct{
	//�ݒ�̍\����
	int key_up;			//��̃L�[
	int key_down;		//���̃L�[
	int key_left;		//���̃L�[
	int key_right;		//�E�̃L�[
	int key_jump;		//�W�����v�̃L�[
	int key_attack;		//�U���̃L�[
	int key_plus;			//+�{�^���̃L�[
	//int key_minus;			//-�{�^���̃L�[
	int pad_up;			//��̃{�^��
	int pad_down;		//���̃{�^��
	int pad_left;		//���̃{�^��
	int pad_right;		//�E�̃{�^��
	int pad_jump;		//�W�����v�̃{�^��
	int pad_attack;		//�U���̃{�^��
	int pad_plus;			//+�{�^��
	//int pad_minus;			//-�{�^��
};

class KeyConfig : public ModeBase {
private:

	int message_font; //�t�H���g���

	std::map<int, char*> key_map; //�L�[�̔ԍ��ɑΉ����镶��

	int key_cursor; //�J�[�\���̈ʒu(�L�[�R���t�B�O)
	int pad_cursor; //�J�[�\���̈ʒu(�p�b�h�R���t�B�O)

	Key_Func button[BUTTON]; //�Ή�����{�^��
	char key_input[BUTTON]; //���͂����L�[�̕���

	KeySettingStruct setting;

	void Reset(); //������
	void LoadSetting(); //�ݒ�̓ǂݍ���
	void SaveSetting(); //�ݒ�̕ۑ�

public:
	KeyConfig(ModeChanger* changer, Parameter& param); //�R���X�g���N�^
	~KeyConfig(); //�f�X�g���N�^
	void Update(); //�X�V
	void Draw(); //�`��
};