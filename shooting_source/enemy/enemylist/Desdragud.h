#pragma once
#include "../AbstractEnemy.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//1ボス(デスドラグド)

class Desdragud : public AbstractEnemy {
protected:
	float left_arm_distance, left_arm_angle, right_arm_distance, right_arm_angle;
	float left_shoulder_distance, left_shoulder_angle, right_shoulder_distance, right_shoulder_angle;
	float left_arm_spin_distance, left_arm_spin_angle, right_arm_spin_distance, right_arm_spin_angle;
	float left_arm_x, left_arm_y, right_arm_x, right_arm_y;
	float left_shoulder_x, left_shoulder_y, right_shoulder_x, right_shoulder_y;

	int attack_num; //攻撃パターン

	void Attack1(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //自機狙い弾
	void Attack2(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //ミサイル
	void Attack3(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //チャージショット

public:
	Desdragud(EnemyManager* ene, int num, float ini_x, float ini_y); //コンストラクタ(番号、座標)
	~Desdragud(); //デストラクタ
	void AbsUpdate() override; //必ず行う更新
	void Update(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //更新
	void Draw() override; //描画
};
