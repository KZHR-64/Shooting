#pragma once
#include "Parameter.h"

Parameter::Parameter() {
	//stage_num[stage] = 1; //�X�e�[�W�ԍ���������
}

Parameter::~Parameter() {
	stage_num.clear();
}

//�l���R�s�[
void Parameter::CopyParam(Parameter &param) {
	for each (auto var in param.stage_num)
	{
		stage_num[var.first] = var.second;
	}
}

int Parameter::GetStageNum() {
	//�X�e�[�W�ԍ���Ԃ�
	auto num = stage_num.find(stage); //�X�e�[�W�ԍ�������
	if (num == stage_num.end()) {
		//�Ȃ������ꍇ
		return 0; //�Ƃ肠����0��Ԃ�
	}
	else {
		//�������ꍇ
		return num->second;
	}
	
}

void Parameter::SetStageNum(int num) {
	//�X�e�[�W�ԍ���ݒ�
	stage_num[stage] = num;
}