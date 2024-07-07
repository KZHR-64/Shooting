#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//弾を撃つ雑魚敵

class Raidrone : public AbstractEnemy {
protected:
	int hundle_num; //表示する画像
public:
	Raidrone(EnemyManager* ene, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~Raidrone(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Update(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //更新
	void Draw() override; //描画
};
