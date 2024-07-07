#pragma once
#include "DxLib.h"
#include "Menu.h"
#include <math.h>

Menu::Menu(ModeChanger* changer, Parameter& param) : ModeBase(changer, param) {

	Reset(); //������
	
	cursor_pos = 0; //cursor�̈ʒu��������
}

//�f�X�g���N�^
Menu::~Menu() {
	
}

//������
void Menu::Reset() {
	Sound::Get_Instance()->LoadBgm(0); //�Ȃ��Đ�
	Image::Get_Instance()->LoadBackImage(4);
	for (int i = 0; i < 4; i++)
	{
		choice[i].image = Image::Get_Instance()->GetEffectImage(0, i); //�摜��ݒ�
		choice[i].ex_rate = 1.f; //�{����������
	}
	logo = Image::Get_Instance()->GetEffectImage(1, 0); //�摜��ݒ�

	count = 0;
	return_flag = false; //�A�҃t���O��false
}

//�X�V
void Menu::Update(){
	Parameter param;

	//�A�҃t���O�������Ă���ꍇ
	if (return_flag) {
		Reset(); //������
	}
	if (Key::Get_Instance()->KeyCheckOnce(Up)){ //��L�[��������Ă�����
		Sound::Get_Instance()->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos += 3; //�J�[�\������Ɉړ�
		count = 0; //�J�E���^�[��������
	}

	if (Key::Get_Instance()->KeyCheckOnce(Down)){ //���L�[��������Ă�����
		Sound::Get_Instance()->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos++; //�J�[�\�������Ɉړ�
		count = 0; //�J�E���^�[��������
	}

	cursor_pos %= 4; //�J�[�\�������킹��

	//�I�����̏�Ԃ��X�V
	for (int i = 0; i < 4; i++)
	{
		if (i == cursor_pos) {
			choice[i].ex_rate = 1.1f + (0.1f * sinf(PI * 2.f / 90.f * count)); //�I������Ă���ꍇ�͊g��A�k�����J��Ԃ�
		}
		else {
			choice[i].ex_rate = 1.f; //�I������Ă��Ȃ���Γ��{
		}
	}

	if (Key::Get_Instance()->KeyCheckOnce(Jump)){ //����L�[��������Ă�����
		Sound::Get_Instance()->PlaySoundEffect(1); //���ʉ���炷
		return_flag = true; //�A�҃t���O�𗧂Ă�
		//�J�[�\���̈ʒu�ɂ���đJ�ڐ��ύX
		switch (cursor_pos)
		{
		case 0:
			//modechanger->ChangeMode(Next_StageSelect); //���[�h���X�e�[�W�Z���N�g�ɕύX
			param.SetStageNum(0); //�X�e�[�W�ԍ���ݒ�
			modechanger->ChangeMode(Next_Game); //���[�h���Q�[���ɕύX
			break;
		case 1:
			modechanger->ChangeMode(Next_Option); //���[�h���I�v�V�����ɕύX
			break;
		case 2:
			modechanger->ChangeMode(Next_Config); //���[�h���L�[�R���t�B�O�ɕύX
			break;
		case 3:
			PostMessageA(GetMainWindowHandle(), WM_CLOSE, 0, 0);
			break;
		default:
			break;
		}
	}

	/*if (Key::Get_Instance()->KeyCheckOnce(Attack)){ //�߂�{�^����������Ă�����
		Sound::Get_Instance()->PlaySoundEffect(2); //���ʉ���炷
		modechanger->ChangeMode(Next_Back); //�I�[�v�j���O�ɖ߂�
	}*/

	count = (count + 1) % 90;//�J�E���^�[�𑝉�
}

//�`��
void Menu::Draw(){
	
	int image = Image::Get_Instance()->GetEffectImage(7, 0); //�摜���擾

	int back = Image::Get_Instance()->GetBackImage(4); //�w�i���擾
	Display::Get_Instance()->FixedDraw(320.f, 240.f, LEFT, 0.f, back); //�w�i��`��

	//Display::Get_Instance()->FixedDraw(320.f, 96.f, LEFT, 0.f, logo); //���S��`��

	for (int i = 0; i < 4; i++)
	{
		Display::Get_Instance()->FixedDraw(480.f, 212.f + (64.f * i), LEFT, 0.f, choice[i].image, choice[i].ex_rate); //�I������`��
	}

	//DrawFormatString(128, 0, GetColor(255, 255, 255), "%d", orb[0].trance);
}