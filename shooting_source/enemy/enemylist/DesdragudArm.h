#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//1ボスの腕

class DesdragudArm : public AbstractEnemy {
protected:

public:
	DesdragudArm(EnemyManager* ene, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~DesdragudArm(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Update(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //更新
	void Draw() override; //描画
};
