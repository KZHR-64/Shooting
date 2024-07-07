#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//中ボス1

class JumboRaidrone : public AbstractEnemy {
protected:
	int hundle_num; //表示する画像
	float bsy; //攻撃前の速度
	int attack_num; //攻撃パターン

	void Attack1(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //ミサイル
	void Attack2(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //雑魚召喚

public:
	JumboRaidrone(EnemyManager* ene, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~JumboRaidrone(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Update(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //更新
	void Draw() override; //描画
};
