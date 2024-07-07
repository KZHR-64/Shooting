#pragma once
#include "Key.h"
#include "DxLib.h"

Key::Key() {
	button[Jump].key = KEY_INPUT_Z; //�W�����v��z�L�[
	button[Jump].pad = PAD_INPUT_1; //�W�����v��1�{�^��
	button[Attack].key = KEY_INPUT_X; //�U����x�L�[
	button[Attack].pad = PAD_INPUT_2; //�U����2�{�^��
	button[Up].key = KEY_INPUT_UP; //��ړ��͏�L�[
	button[Up].pad = PAD_INPUT_UP; //��ړ��͏�{�^��
	button[Down].key = KEY_INPUT_DOWN; //���ړ��͉��L�[
	button[Down].pad = PAD_INPUT_DOWN; //���ړ��͉��{�^��
	button[Left].key = KEY_INPUT_LEFT; //���ړ��͍��L�[
	button[Left].pad = PAD_INPUT_LEFT; //���ړ��͍��{�^��
	button[Right].key = KEY_INPUT_RIGHT; //�E�ړ��͉E�L�[
	button[Right].pad = PAD_INPUT_RIGHT; //�E�ړ��͉E�{�^��
	button[Plus].key = KEY_INPUT_A; //L�{�^����a�L�[
	button[Plus].pad = PAD_INPUT_5; //L�{�^����3�{�^��
	//button[Minus].key = KEY_INPUT_S; //R�{�^����s�L�[
	//button[Minus].pad = 7; //R�{�^����4�{�^��

	pad = 0;
}

//�X�V
void Key::Update() {
	int i;
	for (i = 0; i < 256; i++) old_key_list[i] = key_list[i]; //��O�̓��͏�Ԃ𓾂�
	old_pad = pad; //��O�̓��͏�Ԃ𓾂�
	GetHitKeyStateAll(key_list); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	pad = GetJoypadInputState(DX_INPUT_PAD1); // �S�Ẵ{�^���̓��͏�Ԃ𓾂�
}

//����ɑΉ�����L�[���擾
void Key::GetKey(Key_Func* set_key) {
	for (int i = 0; i < BUTTON; i++)
	{
		set_key[i].key = button[i].key; //�L�[�̐ݒ�
		set_key[i].pad = button[i].pad; //�p�b�h�̐ݒ�
	}
}

//����ɑΉ�����L�[��ύX
void Key::SetKey(Key_Func* set_key) {
	for (int i = 0; i < BUTTON; i++)
	{
		button[i].key = set_key[i].key; //�L�[�̐ݒ�
		button[i].pad = set_key[i].pad; //�p�b�h�̐ݒ�
	}
}

//�L�[��������Ă��邩
bool Key::KeyCheck(int check) {
	if (key_list[button[check].key] != 0 || (pad & button[check].pad)) return true; //�Ή�����L�[���p�b�h�̃{�^����������Ă�����true��
	else return false; //�����łȂ����false��Ԃ�
}

//�L�[����x�����ꂽ��
bool Key::KeyCheckOnce(int check) {
	//�Ή�����L�[���p�b�h�̃{�^����������Ă�����
	if (key_list[button[check].key] != 0 || (pad & button[check].pad)) {
		if (old_key_list[button[check].key] == 0 && !(old_pad & button[check].pad)) return true; //��O�ɉ�����Ă��Ȃ����true��
		else return false; //�����łȂ����false��Ԃ�
	}
	else return false; //�����łȂ����false��Ԃ�
}

//�L�[����x�����ꂽ��
bool Key::KeyCheckLetGo(int check) {
	//�Ή�����L�[���p�b�h�̃{�^����������Ă�����
	if (key_list[button[check].key] == 0 && !(pad & button[check].pad)) {
		if (old_key_list[button[check].key] != 0 || (old_pad & button[check].pad)) return true; //��O�ɉ�����Ă����true��
		else return false; //�����łȂ����false��Ԃ�
	}
	else return false; //�����łȂ����false��Ԃ�
}

//�����ꂽ�L�[����Ԃ�
int Key::GetKeyOnce() {
	for (int i = 0; i < 256; i++)
	{
		// ������Ă���L�[���������ꍇ
		if (key_list[i] != 0) {
			if (old_key_list[i] == 0) return i; //��O�ɉ�����Ă��Ȃ����i��Ԃ�
		}
	}
	return -1; //�Ȃ����-1��Ԃ�
}

//�����ꂽ�{�^������Ԃ�
int Key::GetPadOnce() {
	for (int i = 0; i < 28; i++) {
		// ������Ă���{�^�����������ꍇ
		if (pad & (1 << i)) {
			if (!(old_pad & (1 << i))) return (int)pow(2, i); //��O�ɉ�����Ă��Ȃ����i��Ԃ�
		}
	}
	return -1; //�Ȃ����-1��Ԃ�
}