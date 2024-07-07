#pragma once
#include "DxLib.h"
#include "System.h"
#include <time.h>

System::System(){
	SetDXArchiveKeyString("SUKIMA-KZHR");
}

System::~System() {

}
//�I�v�V�����̓ǂݍ���
SettingStruct System::OptionSetting() {
	FILE *fp;
	char buf[256];

	SettingStruct initial;

	fopen_s(&fp, "config.dat", "rb"); //�ݒ��ǂݍ���

	//�Ȃ���΃f�t�H���g
	if (fp == NULL) {
		initial.fps_flag = true;
		initial.full_screen = true;
		initial.volume_bgm = 12;
		initial.volume_effect = 12;
	}
	else {
		memset(buf, 0, sizeof(buf)); //���������Z�b�g

		fread(&initial, sizeof(initial), 1, fp);
		fclose(fp);
	}

	return initial;
}

//�L�[�R���t�B�O�̓ǂݍ���
void System::KeySetting() {
	FILE *fp;
	char buf[256];

	KeySettingStruct key_initiial;
	Key_Func button[BUTTON];

	fopen_s(&fp, "key_config.dat", "rb"); //�ݒ��ǂݍ���

	//�Ȃ���΃f�t�H���g
	if (fp == NULL) {
		key_initiial.key_up = KEY_INPUT_UP; //��ړ��͏�L�[
		key_initiial.key_down = KEY_INPUT_DOWN; //���ړ��͉��L�[
		key_initiial.key_left = KEY_INPUT_LEFT; //���ړ��͍��L�[
		key_initiial.key_right = KEY_INPUT_RIGHT; //�E�ړ��͉E�L�[
		key_initiial.key_jump = KEY_INPUT_Z; //�W�����v��z�L�[
		key_initiial.key_attack = KEY_INPUT_X; //�U����x�L�[
		key_initiial.key_plus = KEY_INPUT_A; //+�{�^����a�L�[
		key_initiial.pad_up = PAD_INPUT_UP; //��ړ��͏�{�^��
		key_initiial.pad_down = PAD_INPUT_DOWN; //���ړ��͉��{�^��
		key_initiial.pad_left = PAD_INPUT_LEFT; //���ړ��͍��{�^��
		key_initiial.pad_right = PAD_INPUT_RIGHT; //�E�ړ��͉E�{�^��
		key_initiial.pad_jump = PAD_INPUT_1; //�W�����v��1�{�^��
		key_initiial.pad_attack = PAD_INPUT_2; //�U����2�{�^��
		key_initiial.pad_plus = PAD_INPUT_3; //+�{�^����3�{�^��
	}
	else {
		memset(buf, 0, sizeof(buf)); //���������Z�b�g

		fread(&key_initiial, sizeof(key_initiial), 1, fp);
		fclose(fp);
	}

	button[Jump].key = key_initiial.key_jump;
	button[Attack].key = key_initiial.key_attack;
	button[Up].key = key_initiial.key_up;
	button[Down].key = key_initiial.key_down;
	button[Left].key = key_initiial.key_left;
	button[Right].key = key_initiial.key_right;
	button[Plus].key = key_initiial.key_plus;
	//button[Minus].key = setting.key_minus;
	button[Jump].pad = key_initiial.pad_jump;
	button[Attack].pad = key_initiial.pad_attack;
	button[Up].pad = key_initiial.pad_up;
	button[Down].pad = key_initiial.pad_down;
	button[Left].pad = key_initiial.pad_left;
	button[Right].pad = key_initiial.pad_right;
	button[Plus].pad = key_initiial.pad_plus;
	//button[Minus].pad = setting.pad_minus;

	Key::Get_Instance()->SetKey(button); //�ݒ���m�肷��
}

//�����ݒ�̓ǂݍ���
void System::Setting() {
	
	SettingStruct initial = OptionSetting(); //�ݒ��ǂݍ���

	//�L�[�̐ݒ��ǂݍ���
	SetOutApplicationLogValidFlag(false);
	SetAlwaysRunFlag(TRUE);
	SetWindowSizeChangeEnableFlag(initial.full_screen);
	ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_X, WINDOW_Y, 16);
	SetMainWindowText("�A�N�V��������");
	if (DxLib_Init() == -1) DebugBreak();
	SetDrawScreen(DX_SCREEN_BACK);

	time_t now = time(NULL);
	struct tm pnow;
	localtime_s(&pnow, &now);

	SRand(pnow.tm_hour + pnow.tm_min + pnow.tm_sec);

	KeySetting();

	Fps::Get_Instance()->SetDrawFlag(initial.fps_flag);
	Sound::Get_Instance()->SetBgmVolume(initial.volume_bgm);
	Sound::Get_Instance()->SetSoundVolume(initial.volume_effect);

	Image::Get_Instance()->LoadEffectImage();
}

//�I��
void System::Finalize() {
	DxLib_End();
}

//�X�V
void System::Update(){
	Mode mode;
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		mode.Draw();
		mode.Update();
		Fps::Get_Instance()->Draw();
		Fps::Get_Instance()->Wait();
	}
}