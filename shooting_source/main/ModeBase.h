#pragma once
#include "ModeChanger.h"
#include "Parameter.h"

class ModeChanger;

class ModeBase{
protected:
	ModeChanger* modechanger; //���[�h�ؑւ�`����|�C���^
	bool return_flag; //��ʂɖ߂��Ă����t���O
public:
	ModeBase(ModeChanger* changer, Parameter &param);
	virtual ~ModeBase(){}
	virtual void Update() = 0; //�X�V
	virtual void Draw() = 0; //�`��
};