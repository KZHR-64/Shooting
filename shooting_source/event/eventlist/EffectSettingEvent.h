#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <iostream>
#include <string>
#include <sstream>

//エフェクト発生イベント

class EffectSettingEvent : public AbstractEvent {
protected:
	int effect_num; //エフェクト番号
	float ex; //x座標
	float ey; //y座標
public:
	EffectSettingEvent(EventManager* man, int num, float x, float y, bool stop_player, bool stop_enemy); //コンストラクタ(エフェクト番号、座標、自機を止めるか、敵を止めるか)
	~EffectSettingEvent(); //デストラクタ
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //更新
	void Draw(); //描画
};
