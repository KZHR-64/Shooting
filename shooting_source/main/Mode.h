#pragma once
#include "ModeBase.h"
#include "ModeChanger.h"
#include "..\single\Key.h"
#include "..\single\Image.h"
#include <memory>
#include <stack>

class Mode : public  ModeChanger {
private:
	Parameter param;
	NextMode next; //���̉��
	bool blackout_flag; //�Ó]����
	int blackout_time; //�Ó]����
	bool erase; //���̃��[�h���I�����邩

	bool change; //�E�B���h�E��ς��邩
	bool full_screen; //�t���X�N���[���ɂ��邩(false�Ȃ炷��)

	std::stack<std::shared_ptr<ModeBase>> scene_stack; //�V�[���̃X�^�b�N

	void Blackout(); //�Ó]
	
public:
	Mode(); //�R���X�g���N�^
	~Mode(); //�f�X�g���N�^
	void ChangeMode(NextMode nmode, bool erase_now = false, bool change_window = false, bool full = true); //���̃��[�h�ɂ���(���݃��[�h���������邩�A�E�B���h�E��ς��邩�A�t���X�N���[���ɂ��邩)
	void ChangeMode(NextMode nmode, Parameter &parameter, bool erase_now = false); //���̃��[�h�ɂ���(���݃��[�h���������邩)
	void BackMode(); //�O�̃��[�h�ɖ߂�
	void Update(); //�X�V
	void Draw(); //�`��
};