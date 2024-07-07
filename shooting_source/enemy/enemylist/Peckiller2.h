#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//なぜか飛んできたキツツキ(自機狙い)

class Peckiller2 : public AbstractEnemy {
protected:
	float speed;
public:
	Peckiller2(EnemyManager* ene, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~Peckiller2(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Update(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //更新
	void Draw() override; //描画
};
