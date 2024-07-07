#pragma once
#include "DxLib.h"
#include "StageSelect.h"
#include "Parameter.h"

StageSelect::StageSelect(ModeChanger* changer, Parameter& param) : ModeBase(changer, param) {
	stage_num = param.GetStageNum();
	cursor_pos_x = 0;
	cursor_pos_y = 0;

	message_font = CreateFontToHandle("Meiryo UI", 32, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2); //�t�H���g���

	Reset();
}

//�f�X�g���N�^
StageSelect::~StageSelect() {
	DeleteFontToHandle(message_font);
}

//������
void StageSelect::Reset() {
	FILE *fp;
	char buf[512];
	char *p;
	char *tp;
	char *ctx;

	Sound::Get_Instance()->LoadBgm(2); //�Ȃ��Đ�
	Image::Get_Instance()->LoadBackImage(3);

	fopen_s(&fp, "data/subtitle.csv", "r");
	if (fp == NULL) DebugBreak(); //�Ȃ���ΏI��

	//�ݒ�
	for (int i = 0; i < STAGE_MAX; i++) {
		subtitle[i].select_flag = true;
		subtitle[7].select_flag = false;
		subtitle[i].hundle = Image::Get_Instance()->GetEffectImage(10, 0); //�T���l�C�����擾

		//�T�u�^�C�g�����擾
		fgets(buf, 512, fp);
		//�I���\�Ȃ�
		if (subtitle[i].select_flag) {
			p = strchr(buf, (int)'\n'); //���s������
			//���s������ꍇ
			if (p != NULL) {
				*p = '\0'; //���s���폜
			}
			tp = strtok_s(buf, ",", &ctx);
			subtitle[i].str1 = (std::string)tp;
			tp = strtok_s(NULL, ",", &ctx);
			subtitle[i].str2 = (std::string)tp;
		}
		//�I��s�Ȃ�
		else {
			subtitle[i].hundle = Image::Get_Instance()->GetEffectImage(10, 0);
			subtitle[i].str1 = "�H"; 
			subtitle[i].str2 = "�H";
		}
	}

	fclose(fp);

	return_flag = false; //�A�҃t���O��false
}

//���̍X�V
void StageSelect::SetData() {

}

//�X�V
void StageSelect::Update() {
	Parameter param;
	//�A�҃t���O�������Ă���ꍇ
	if (return_flag) {
		Reset();
	}

	//�X�e�[�W�I��
	if (Key::Get_Instance()->KeyCheckOnce(Left)){ //���{�^����������Ă�����
		Sound::Get_Instance()->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos_x = (cursor_pos_x + 3) % 4; //�J�[�\���ԍ������炷
	}
	if (Key::Get_Instance()->KeyCheckOnce(Right)){ //�E�{�^����������Ă�����
		Sound::Get_Instance()->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos_x = (cursor_pos_x + 1) % 4; //�J�[�\���ԍ��𑝂₷
	}
	if (Key::Get_Instance()->KeyCheckOnce(Up)){ //���{�^����������Ă�����
		Sound::Get_Instance()->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos_y = (cursor_pos_y + 1) % 2; //�J�[�\���ԍ������炷
	}
	if (Key::Get_Instance()->KeyCheckOnce(Down)){ //���{�^����������Ă�����
		Sound::Get_Instance()->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos_y = (cursor_pos_y + 1) % 2; //�J�[�\���ԍ��𑝂₷
	}

	stage_num = (cursor_pos_y * 4) + cursor_pos_x; //�X�e�[�W�ԍ���ݒ�
	if (stage_num < 0) {
		stage_num = 0;//�X�e�[�W�ԍ���0�����ɂȂ����ꍇ��0��
	}
	if (STAGE_MAX <= stage_num) {
		stage_num = STAGE_MAX - 1;//�X�e�[�W�ԍ����ő�𒴂����ꍇ�͍ő�l��
		cursor_pos_x = (STAGE_MAX - 1) % 4;
		cursor_pos_y = STAGE_MAX / 4;
	}

	if (Key::Get_Instance()->KeyCheckOnce(Jump)){ //����{�^����������Ă�����
		//�X�e�[�W���I���\�Ȃ�
		if (subtitle[stage_num].select_flag) {
			Sound::Get_Instance()->PlaySoundEffect(1); //���ʉ���炷
			return_flag = true; //�A�҃t���O�𗧂Ă�
			param.SetStageNum(stage_num); //�X�e�[�W�ԍ���ݒ�
			modechanger->ChangeMode(Next_Game, param); //���[�h���Q�[���ɕύX
		}
		//�����łȂ����
		else {
			Sound::Get_Instance()->PlaySoundEffect(3); //���ʉ���炷
		}
	}
	if (Key::Get_Instance()->KeyCheckOnce(Attack)){ //�߂�{�^����������Ă�����
		Sound::Get_Instance()->PlaySoundEffect(2); //���ʉ���炷
		modechanger->ChangeMode(Next_Back, param); //���j���[�ɖ߂�
	}
}

//�`��
void StageSelect::Draw() {

	int back = Image::Get_Instance()->GetBackImage(3); //�w�i���擾
	Display::Get_Instance()->FixedDraw(320.f, 240.f, LEFT, 0.f, back); //�w�i��`��

	//�J�[�\����\��
	int cursor_x = 43 + (cursor_pos_x * 136);
	int cursor_y = 68 + (cursor_pos_y * 136);
	DrawBox(cursor_x, cursor_y, cursor_x + 144, cursor_y + 144, GetColor(238, 131, 111), true);

	//�T���l�C����\��
	for (int i = 0; i < STAGE_MAX; i++) {
		float x = 43.f + 72.f + ((i % 4) * 136.f);
		float y = 68.f + 72.f + ((i / 4) * 136.f);
		Display::Get_Instance()->FixedDraw(x, y, LEFT, 0.f, subtitle[i].hundle);
	}

	DrawFormatString(0, 30, GetColor(255, 255, 255), "%d", stage_num);
	
	DrawStringToHandle(60, 374, subtitle[stage_num].str1.c_str(), GetColor(236, 236, 236), message_font, GetColor(21, 169, 175));
	DrawStringToHandle(60, 416, subtitle[stage_num].str2.c_str(), GetColor(236, 236, 236), message_font, GetColor(21, 169, 175));
}