#pragma once
#include "../AbstractMapChip.h"
#include "../Define.h"
//#include "Game.h"
//#include "Map.h"
//#include "Bullet.h"
//#include "Enemy.h"
//#include "Effect.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//����

class NormalBlock : public AbstractMapChip{
protected:

public:
	NormalBlock(MapChipManager* man, int num); //�R���X�g���N�^(�ԍ�)
	~NormalBlock(); //�f�X�g���N�^
	void Update(); //�X�V
	void Draw() override; //�`��
};
