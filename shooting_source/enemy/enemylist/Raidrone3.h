#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//上または下に移動する雑魚敵

class Raidrone3 : public AbstractEnemy {
protected:
	int hundle_num; //表示する画像
public:
	Raidrone3(EnemyManager* ene, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~Raidrone3(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Update(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //更新
	void Draw() override; //描画
};
