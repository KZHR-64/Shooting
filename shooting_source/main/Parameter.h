#pragma once
#include <map>
#include <string>

typedef enum {
	//�V�ԃX�e�[�W
	
} StageNum;

class Parameter {
private:
	std::map<std::string, int> stage_num; //�X�e�[�W�֘A�̐��l
	const std::string stage = "stage"; //�X�e�[�W�ԍ���\���^�O

public:
	Parameter(); //�R���X�g���N�^
	~Parameter(); //�f�X�g���N�^
	void CopyParam(Parameter &param); //�l���R�s�[
	int GetStageNum(); //�X�e�[�W�ԍ���Ԃ�
	void SetStageNum(int num); //�X�e�[�W�ԍ���ݒ�
};