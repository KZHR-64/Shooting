#pragma once
#include "../AbstractBullet.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//デスドラグドのチャージショット

class DesdragudShoot : public AbstractBullet {
protected:
	float bx, by, bx2, by2; //1,2フレーム前の座標
	float base_speed; //基となる速度
	float speed; //速度
public:
	DesdragudShoot(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle); //コンストラクタ(画像の番号、座標、速度、角度)
	~DesdragudShoot(); //デストラクタ
	void Update(std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //更新
	void Draw() override; //描画
};

