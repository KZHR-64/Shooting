#pragma once
#include "ModeBase.h"
#include "..\single\Key.h"
#include "..\single\Sound.h"
#include "..\single\Image.h"
#include "..\single\Display.h"
#include "..\single\Fps.h"

struct SettingStruct{
	//�ݒ�̍\����
	bool fps_flag;		//FPS��\�����邩
	bool full_screen;	//�t���X�N���[���ŕ\�����邩
	int volume_bgm;		//BGM�̉���
	int volume_effect;	//���ʉ��̉���
};

class Option : public ModeBase {
private:

	int cursor_pos; //�J�[�\���̈ʒu
	bool initial_fullscreen; //��ʊJ��������̃E�B���h�E�T�C�Y
	int on_hundle; //ON�̃n���h��
	int off_hundle; //OFF�̃n���h��
	int volume_hundle; //���ʂ̃n���h��
	int graduation_hundle; //���ʖڐ��̃n���h��

	SettingStruct setting;
	
	void Reset(); //������
	void LoadSetting(); //�ݒ�̓ǂݍ���
	void SaveSetting(); //�ݒ�̕ۑ�

public:
	Option(ModeChanger* changer, Parameter& param); //�R���X�g���N�^
	~Option(); //�f�X�g���N�^
	void Update(); //�X�V
	void Draw(); //�`��
};