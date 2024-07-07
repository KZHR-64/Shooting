#pragma once
#include "DxLib.h"
#include "Gameover.h"

Gameover::Gameover(ModeChanger* changer, Parameter& param) : ModeBase(changer, param) {

	Sound::Get_Instance()->LoadBgm(3); //�Ȃ��Đ�
	Image::Get_Instance()->LoadBackImage(4);

	//�摜��ݒ�
	for (int i = 0; i < 2; i++)
	{
		select_hundle[i] = Image::Get_Instance()->GetEffectImage(11, i);
	}

	cursor_pos = 0; //cursor�̈ʒu��������
}

//�f�X�g���N�^
Gameover::~Gameover() {
	
}

//������
void Gameover::Reset() {

}

//�X�V
void Gameover::Update(){

	if (Key::Get_Instance()->KeyCheckOnce(Down) || Key::Get_Instance()->KeyCheckOnce(Up)){ //���L�[����L�[��������Ă�����
		Sound::Get_Instance()->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos = (cursor_pos + 1) % 2; //�J�[�\�������Ɉړ�
	}
	if (Key::Get_Instance()->KeyCheckOnce(Jump)){ //����L�[��������Ă�����
		Sound::Get_Instance()->PlaySoundEffect(1); //���ʉ���炷
		//�J�[�\���̈ʒu�ɂ���đJ�ڐ��ύX
		switch (cursor_pos)
		{
		case 0:
			modechanger->ChangeMode(Next_Game, true); //���[�h���Q�[����ʂɕύX
			break;
		case 1:
			modechanger->ChangeMode(Next_Back); //���[�h���X�e�[�W�Z���N�g�ɕύX
			break;
		default:
			break;
		}
	}
}

//�`��
void Gameover::Draw(){
	int back = Image::Get_Instance()->GetBackImage(4); //�w�i���擾
	Display::Get_Instance()->FixedDraw(320.f, 240.f, LEFT, 0.f, back); //�w�i��`��

	int blend_mode; //�\�����@
	int blend; //�����̖��邳

	//�I���ɂ���ĕ����̖��邳��ύX
	for (int i = 0; i < 2; i++)
	{
		blend_mode = ((cursor_pos == i) ? DX_BLENDMODE_NOBLEND : DX_BLENDMODE_SUB);
		blend = ((cursor_pos == i) ? 1 : 64);
		Display::Get_Instance()->FixedDraw(480.f, 244.f + (96.f * i), LEFT, 0.f, select_hundle[i], 1.f, blend_mode, blend); //�I������`��
	}
}