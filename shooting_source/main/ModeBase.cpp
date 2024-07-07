#pragma once
#include "ModeBase.h"

ModeBase::ModeBase(ModeChanger* changer, Parameter& param) : modechanger(changer) {
	return_flag = false;
}