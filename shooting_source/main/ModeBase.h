#pragma once
#include "ModeChanger.h"
#include "Parameter.h"

class ModeChanger;

class ModeBase{
protected:
	ModeChanger* modechanger; //モード切替を伝えるポインタ
	bool return_flag; //画面に戻ってきたフラグ
public:
	ModeBase(ModeChanger* changer, Parameter &param);
	virtual ~ModeBase(){}
	virtual void Update() = 0; //更新
	virtual void Draw() = 0; //描画
};