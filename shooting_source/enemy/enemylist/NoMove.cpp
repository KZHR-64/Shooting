#pragma once
#include "DxLib.h"
#include "NoMove.h"

using namespace std;

//�R���X�g���N�^
NoMove::NoMove(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {

}

//�f�X�g���N�^
NoMove::~NoMove() {

}

//�K���s���X�V
void NoMove::AbsUpdate() {
	
}

//�X�V
void NoMove::Update(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {
	
}

//�`��
void NoMove::Draw() {
	int hundle = Image::Get_Instance()->GetCharaImage(image, 0);
	Display::Get_Instance()->Draw(x, y, lr, angle, hundle, DX_BLENDMODE_NOBLEND);
}