#pragma once
#include "DxLib.h"
#include "Mode.h"
#include "Game.h"
#include "StageSelect.h"
#include "Option.h"
#include "KeyConfig.h"
#include "Opening.h"
#include "Menu.h"
#include "Gameover.h"

using namespace std;

Mode::Mode(){
	//Image::Get_Instance()->LoadEffectImage();
	next = Next_None;
	change = false;
	erase = false;
	full_screen = false;
	blackout_time = 0;
	blackout_flag = false; //�Ó]��Ԃ�������
	scene_stack.push(make_shared<Opening>(this, param));//(ModeBase*) new Opening(this)); //�n�߂̓I�[�v�j���O���
}

Mode::~Mode()
{
	//�X�^�b�N��S�J��
	while (!scene_stack.empty())
	{
		scene_stack.pop();
	}
}

//�Ó]
void Mode::Blackout() {
	//�Ó]����̏ꍇ
	if (blackout_time == 0) {
		//Sound::Get_Instance()->StopBgm();
	}

	blackout_time++; //�Ó]���Ԃ𑝉�

	//�Ó]���Ԃ����ɒB�����ꍇ
	if (42 < blackout_time) {
		//�E�B���h�E�T�C�Y��ύX����ꍇ
		if (change) {
			SetWindowSizeExtendRate(1.0);
			SetWindowSizeChangeEnableFlag(full_screen); //�ݒ��ύX
			SetMainWindowText("�e�X�g");
			SetDrawScreen(DX_SCREEN_BACK);
		}
		//���݂̃��[�h�������ꍇ
		if (erase) {
			scene_stack.pop();
		}
		//���Ɉڂ�
		switch (next){
		case Next_Opening: //�I�[�v�j���O�̏ꍇ
			scene_stack.push(make_shared<Opening>(this, param));
			break;
		case Next_Menu: //���j���[��ʂ̏ꍇ
			scene_stack.push(make_shared<Menu>(this, param));
			break;
		case Next_StageSelect: //�X�e�[�W�Z���N�g��ʂ̏ꍇ
			param.SetStageNum(0);
			scene_stack.push(make_shared<StageSelect>(this, param));
			break;
		case Next_Game: //�Q�[����ʂ̏ꍇ
			scene_stack.push(make_shared<Game>(this, param));
			break;
		case Next_Gameover: //�Q�[���I�[�o�[��ʂ̏ꍇ
			scene_stack.push(make_shared<Gameover>(this, param));
			break;
		case Next_Option: //�I�v�V������ʂ̏ꍇ
			scene_stack.push(make_shared<Option>(this, param));
			break;
		case Next_Config: //�L�[�R���t�B�O��ʂ̏ꍇ
			scene_stack.push(make_shared<KeyConfig>(this, param));
			break;
		case Next_Back: //�߂�ꍇ
			scene_stack.pop();
			break;
		default:
			break;
		}
		blackout_flag = false; //�Ó]�t���O��false��
	}
}

//���̃��[�h�ɂ���
void Mode::ChangeMode(NextMode nmode, bool erase_now, bool change_window, bool full){
	next = nmode; //���̏�ʂ�ݒ�
	blackout_flag = true; //�Ó]
	blackout_time = 0; //�Ó]���Ԃ�������
	erase = erase_now; //���̃��[�h��������
	change = change_window; //�E�B���h�E��ς��邩
	full_screen = full; //�t���X�N���[���ɂ��邩
}

//���̃��[�h�ɂ���
void Mode::ChangeMode(NextMode nmode, Parameter &parameter, bool erase_now){
	param.CopyParam(parameter);
	next = nmode; //���̏�ʂ�ݒ�
	blackout_flag = true; //�Ó]
	blackout_time = 0; //�Ó]���Ԃ�������
	erase = erase_now; //���̃��[�h��������
	change = false; //�E�B���h�E��ς��邩
}

// �O�̃��[�h�ɖ߂�
void Mode::BackMode() {
	scene_stack.pop();
}

//�X�V
void Mode::Update(){
	Key::Get_Instance()->Update(); //�L�[���X�V
	
	//�Ó]���̏ꍇ
	if (blackout_flag) {
		Blackout(); //�Ó]����
	}
	else {
		scene_stack.top()->Update();
	}
}

//�`��
void Mode::Draw(){
	scene_stack.top()->Draw();

	//�Ó]���̏ꍇ
	if (blackout_flag) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (256 / 42) * blackout_time); //�`�惂�[�h�𔽉f

		DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(0, 0, 0), true); //��ʂ��Â�����

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //�`�惂�[�h��߂�
	}
}