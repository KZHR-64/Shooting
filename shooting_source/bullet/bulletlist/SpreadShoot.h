#pragma once
#include "../AbstractBullet.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//拡散弾

class SpreadShoot : public AbstractBullet {
protected:
	float speed; //基となる速度
public:
	SpreadShoot(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle); //コンストラクタ(画像の番号、座標、速度、角度)
	~SpreadShoot(); //デストラクタ
	void Update(std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //更新
	void Draw() override; //描画
};

