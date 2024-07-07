#include <DxLib.h>
#include "Fps.h"

const static int LIST_LEN_MAX = 120;	//�ő�120�t���[���őҋ@�������v�Z����(2�ȏ�ɂ���)
const static int FPS = 60;		//FPS
const static int UPINTVL = 60;		//60�t���[���Ɉ�x�X�V����

Fps::Fps() :_counter(0), _fps(0){
	message_font = CreateFontToHandle("���C���I", 18, 2, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1); //�t�H���g�̐ݒ�
}


Fps::~Fps() {
	DeleteFontToHandle(message_font);
}

void Fps::Wait()
{
	_counter++;
	Sleep(getWaitTime());   //�҂ׂ����Ԃ��擾���đ҂�
	Regist();
	if (_counter == UPINTVL) {  //�X�V�^�C�~���O��1�񕽋ϒl���X�V����
		UpdateAverage();
		_counter = 0;
	}
}

void Fps::Draw()
{
	if (_fps == 0 || !draw_flag) {
		return;
	}
	DrawFormatStringToHandle(556, 2, GetColor(255, 255, 255), message_font, "%04.1ffps", _fps);
}

void Fps::Regist()
{
	_list.push_back(GetNowCount());   //���݂̎������L��
	if (_list.size() > LIST_LEN_MAX){  //�킩��R�ꂽ��|�b�v
		_list.pop_front();
	}
}

unsigned Fps::getWaitTime()
{
	int len = (int)_list.size();
	if (len == 0){
		return 0;
	}
	int shouldTookTime = (int)(1000 / 60.f*(len));            //�v�Z�ォ����ׂ�����
	int actuallyTookTime = GetNowCount() - _list.front();   //���ۂɂ�����������
	int waitTime = shouldTookTime - actuallyTookTime;       //�v�Z�ォ����ׂ����� - ���ۂɂ����������ԁ@�͂��Ȃ킿�҂ׂ�����
	waitTime = waitTime > 0 ? waitTime : 0;
	return (unsigned)(waitTime);
}

void Fps::UpdateAverage() {
	int len = (int)_list.size();
	if (len < LIST_LEN_MAX) {   //�܂����ς��v�Z���郌�x���ɂ܂ł��܂��Ă��Ȃ���Όv�Z���Ȃ�
		return;
	}
	int tookTime = _list.back() - _list.front();//LIST_LEN_MAX�t���[���ɂ�����������
	float average = (float)tookTime / (len - 1);//���ς����
	if (average == 0) {//0����h�~
		return;
	}
	_fps = (1000 / average);
}

//FPS�\����ݒ�
void Fps::SetDrawFlag(bool flag) {
	draw_flag = flag;
}

//FPS�\�����擾
bool Fps::GetDrawFlag() {
	return draw_flag;
}