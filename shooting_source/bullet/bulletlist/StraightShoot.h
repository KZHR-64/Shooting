#pragma once
#include "../AbstractBullet.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//直進弾

class StraightShoot : public AbstractBullet{
protected:

public:
	StraightShoot(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle); //コンストラクタ(画像の番号、座標、速度、角度)
	~StraightShoot(); //デストラクタ
	void Update(std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //更新
	void Draw() override; //描画
};
