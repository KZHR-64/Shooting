#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
//#include "Game.h"
#include "AbstractEffect.h"
#include "../main/Parameter.h"
#include "../player/Player.h"
//#include "Effect.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include "../single/Sound.h"
#include <map>
#include <list>
#include <queue>
#include <memory>

class AbstractEffect;

class EffectManager : public CharacterBase{
private:
	std::list<std::shared_ptr<AbstractEffect>> effect; //�G�t�F�N�g

public:
	EffectManager(); //�R���X�g���N�^
	~EffectManager(); //�f�X�g���N�^
	void Reset(); //������
	std::shared_ptr<AbstractEffect> SetEffect(int num, float ini_x, float ini_y); //�G�t�F�N�g�̔z�u(�f�[�^�̔ԍ��A���W)

	void Update(); //�X�V
	void Draw(); //�`��
};