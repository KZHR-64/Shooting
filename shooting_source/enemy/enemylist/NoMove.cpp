#pragma once
#include "DxLib.h"
#include "NoMove.h"

using namespace std;

//コンストラクタ
NoMove::NoMove(EnemyManager* ene, int num, float ini_x, float ini_y) : AbstractEnemy(ene, num, ini_x, ini_y) {

}

//デストラクタ
NoMove::~NoMove() {

}

//必ず行う更新
void NoMove::AbsUpdate() {
	
}

//更新
void NoMove::Update(shared_ptr<BulletManager> bullet, shared_ptr<EffectManager> effect) {
	
}

//描画
void NoMove::Draw() {
	int hundle = Image::Get_Instance()->GetCharaImage(image, 0);
	Display::Get_Instance()->Draw(x, y, lr, angle, hundle, DX_BLENDMODE_NOBLEND);
}