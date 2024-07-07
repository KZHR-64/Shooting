#pragma once
#include "DxLib.h"
#include "Option.h"

Option::Option(ModeChanger* changer, Parameter& param) : ModeBase(changer, param) {
	Reset();

	cursor_pos = 0; //cursor�̈ʒu��������

	LoadSetting();
}

Option::~Option() {
	
}

//������
void Option::Reset() {
	Sound::Get_Instance()->LoadBgm(1); //�Ȃ��Đ�
	Image::Get_Instance()->LoadBackImage(1);
	
	//�摜��ݒ�
	on_hundle = Image::Get_Instance()->GetEffectImage(3, 1);
	off_hundle = Image::Get_Instance()->GetEffectImage(3, 0);
	volume_hundle = Image::Get_Instance()->GetEffectImage(4, 0);
	graduation_hundle = Image::Get_Instance()->GetEffectImage(5, 0);
	
	return_flag = false; //�A�҃t���O��false
}

//�ݒ�̓ǂݍ���
void Option::LoadSetting() {
	FILE *fp;
	char buf[256];

	fopen_s(&fp, "config.dat", "rb"); //�ݒ��ǂݍ���

	//�Ȃ���΃f�t�H���g
	if (fp == NULL) {
		setting.fps_flag = Fps::Get_Instance()->GetDrawFlag();
		setting.full_screen = true;
		setting.volume_bgm = Sound::Get_Instance()->GetBgmVolume();
		setting.volume_effect = Sound::Get_Instance()->GetSoundVolume();
	}
	else {
		memset(buf, 0, sizeof(buf)); //���������Z�b�g

		fread(&setting, sizeof(setting), 1, fp);
		fclose(fp);
	}

	initial_fullscreen = setting.full_screen; //��ʊJ��������̐ݒ�
}

//�ݒ�̕ۑ�
void Option::SaveSetting() {
	FILE *fp;

	fopen_s(&fp, "config.dat", "wb"); //�ݒ�̓������t�@�C�����J��

	fwrite(&setting, sizeof(setting), 1, fp); //�t�@�C���ɐݒ����������

	fclose(fp);
}

//�X�V
void Option::Update(){
	//�A�҃t���O�������Ă���ꍇ
	if (return_flag) {
		Reset();
	}

	//��L�[��������Ă�����
	if (Key::Get_Instance()->KeyCheckOnce(Up)){
		Sound::Get_Instance()->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos = (cursor_pos - 1); //�J�[�\������Ɉړ�
	}

	//���L�[��������Ă�����
	if (Key::Get_Instance()->KeyCheckOnce(Down)){
		Sound::Get_Instance()->PlaySoundEffect(0); //���ʉ���炷
		cursor_pos = (cursor_pos + 1); //�J�[�\�������Ɉړ�
	}

	if (cursor_pos < 0) cursor_pos = 0;
	if (3 < cursor_pos) cursor_pos = 3;

	//���E�̓��͏����擾
	bool left = Key::Get_Instance()->KeyCheckOnce(Left);
	bool right = Key::Get_Instance()->KeyCheckOnce(Right);

	if (left || right){
		//�J�[�\���ʒu�ŏ���������
		switch (cursor_pos)
		{
		case 0:
			//fps�\��
			setting.fps_flag = !setting.fps_flag;
			Fps::Get_Instance()->SetDrawFlag(setting.fps_flag);
			break;
		case 1:
			//�t���X�N���[���\��
			setting.full_screen = !setting.full_screen;
			break;
		case 2:
			//BGM����
			if (left) {
				setting.volume_bgm--;
			}
			else if (right) {
				setting.volume_bgm++;
			}
			//���ʂ𒲐�
			if (setting.volume_bgm < 0) {
				setting.volume_bgm = 0;
			}
			if (VOLUME_MAX < setting.volume_bgm) {
				setting.volume_bgm = VOLUME_MAX;
			}
			Sound::Get_Instance()->SetBgmVolume(setting.volume_bgm); //���ʂ�ݒ�
			break;
		case 3:
			//���ʉ�����
			if (left) {
				setting.volume_effect--;
			}
			else if (right) {
				setting.volume_effect++;
			}
			//���ʂ𒲐�
			if (setting.volume_effect < 0) {
				setting.volume_effect = 0;
			}
			if (VOLUME_MAX < setting.volume_effect) {
				setting.volume_effect = VOLUME_MAX;
			}
			Sound::Get_Instance()->SetSoundVolume(setting.volume_effect); //���ʂ�ݒ�
			break;
		default:
			break;
		}
		Sound::Get_Instance()->PlaySoundEffect(0); //���ʉ���炷
	}

	//����L�[��������Ă�����
	if (Key::Get_Instance()->KeyCheckOnce(Jump)){
		Sound::Get_Instance()->PlaySoundEffect(1); //���ʉ���炷

		SaveSetting(); //�ݒ��ۑ�����
		return_flag = true; //�A�҃t���O�𗧂Ă�

		bool change = (initial_fullscreen != setting.full_screen); //�E�B���h�E�T�C�Y��ς��邩

		modechanger->ChangeMode(Next_Back, false, change, setting.full_screen); //���j���[�ɖ߂�
	}
}

//�`��
void Option::Draw(){
	int back = Image::Get_Instance()->GetBackImage(1); //�w�i���擾
	Display::Get_Instance()->FixedDraw(320.f, 240.f, LEFT, 0.f, back); //�w�i��`��

	int blend_mode; //�\�����@
	int blend; //�����̖��邳

	//FPS
	//�I���ɂ���ĕ����̖��邳��ύX
	blend_mode = (setting.fps_flag ? DX_BLENDMODE_SUB : DX_BLENDMODE_NOBLEND);
	blend = (setting.fps_flag ? 96 : 1);
	Display::Get_Instance()->FixedDraw(344.f, 144.f, LEFT, 0.f, off_hundle, 1.f, blend_mode, blend); //�I������`��
	blend_mode = (setting.fps_flag ? DX_BLENDMODE_NOBLEND : DX_BLENDMODE_SUB);
	blend = (setting.fps_flag ? 1 : 96);
	Display::Get_Instance()->FixedDraw(504.f, 144.f, LEFT, 0.f, on_hundle, 1.f, blend_mode, blend);

	//�t���X�N���[��
	//�I���ɂ���ĕ����̖��邳��ύX
	blend_mode = (setting.full_screen ? DX_BLENDMODE_SUB : DX_BLENDMODE_NOBLEND);
	blend = (setting.full_screen ? 96 : 1);
	Display::Get_Instance()->FixedDraw(344.f, 208.f, LEFT, 0.f, off_hundle, 1.f, blend_mode, blend);
	blend_mode = (setting.full_screen ? DX_BLENDMODE_NOBLEND : DX_BLENDMODE_SUB);
	blend = (setting.full_screen ? 1 : 96);
	Display::Get_Instance()->FixedDraw(504.f, 208.f, LEFT, 0.f, on_hundle, 1.f, blend_mode, blend);

	//����
	Display::Get_Instance()->FixedDraw(424.f, 272.f, LEFT, 0.f, volume_hundle);
	for (int i = 0; i < setting.volume_bgm; i++)
	{
		Display::Get_Instance()->FixedDraw(278.f + (12.f * i), 272.f, LEFT, 0.f, graduation_hundle);
	}

	Display::Get_Instance()->FixedDraw(424.f, 336.f, LEFT, 0.f, volume_hundle);
	for (int i = 0; i < setting.volume_effect; i++)
	{
		Display::Get_Instance()->FixedDraw(278.f + (12.f * i), 336.f, LEFT, 0.f, graduation_hundle);
	}

	//�I�������ʒu�ȊO�͏����Â�����
	for (int i = 0; i < 4; i++)
	{
		if (i == cursor_pos) continue;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 112 + (64 * i), 640, 176 + (64 * i), GetColor(128, 128, 128), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}