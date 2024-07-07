#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//なぜか飛んできたキツツキ

class Peckiller : public AbstractEnemy {
protected:

public:
	Peckiller(EnemyManager* ene, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~Peckiller(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Update(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //更新
	void Draw() override; //描画
};
