#pragma once
#include "Singleton.h"
#include <list>

class Fps : public Singleton<Fps>{
private:
	std::list<int> _list;
	float _fps;
	unsigned _counter;

	void UpdateAverage();
	void Regist();
	unsigned getWaitTime();

	bool draw_flag; //fps�\�����s����
	int message_font; //�t�H���g���

public:
	Fps();
	~Fps();
	void Wait();
	void Draw();

	bool GetDrawFlag(); //FPS�\�����擾
	void SetDrawFlag(bool flag); //FPS�\����ݒ�(�t���O)
};