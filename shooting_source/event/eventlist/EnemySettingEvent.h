#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <iostream>
#include <string>
#include <sstream>

//敵出現イベント

class EnemySettingEvent : public AbstractEvent {
protected:
	int enemy_num; //敵番号
	float ex; //x座標
	float ey; //y座標
public:
	EnemySettingEvent(EventManager* man, int num, float x, float y, bool stop_player, bool stop_enemy); //コンストラクタ(敵番号、座標、自機を止めるか、敵を止めるか)
	~EnemySettingEvent(); //デストラクタ
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //更新
	void Draw(); //描画
};
