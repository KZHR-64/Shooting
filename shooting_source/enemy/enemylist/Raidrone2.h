#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//上下する雑魚敵

class Raidrone2 : public AbstractEnemy {
protected:
	int hundle_num; //表示する画像
	float speed_angle; //速度用の角度
public:
	Raidrone2(EnemyManager* ene, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~Raidrone2(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Update(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //更新
	void Draw() override; //描画
};
