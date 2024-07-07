#pragma once
#include "Mode.h"
#include "Option.h"
#include "KeyConfig.h"
#include "..\single\Key.h"
#include "..\single\Sound.h"
#include "..\single\Image.h"
#include "..\single\Display.h"
#include "..\single\Fps.h"

class System {
private:
	SettingStruct OptionSetting(); //�I�v�V�����̓ǂݍ���
	void KeySetting(); //�L�[�R���t�B�O�̓ǂݍ���

public:
	System(); //�R���X�g���N�^
	~System(); //�f�X�g���N�^
	void Setting(); //�����ݒ�̓ǂݍ���
	void Finalize(); //�I��
	void Update(); //�X�V
};