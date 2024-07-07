#pragma once
#include "Parameter.h"
#include "../Define.h"

class ModeChanger {
public:
	ModeChanger() = default;
	virtual ~ModeChanger() = default;
	virtual void ChangeMode(NextMode nmode, bool erase_now = false, bool change_window = false, bool full = true) = 0; //���̃��[�h�ɂ���
	virtual void ChangeMode(NextMode nmode, Parameter &parameter, bool erase_now = false) = 0; //���̃��[�h�ɂ���
	virtual void BackMode() = 0; //�O�̃��[�h�ɖ߂�
};