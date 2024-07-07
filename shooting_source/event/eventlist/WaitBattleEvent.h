#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <iostream>
#include <string>
#include <sstream>

//バトル待機イベント

class WaitBattleEvent : public AbstractEvent {
protected:

public:
	WaitBattleEvent(EventManager* man, bool stop_player, bool stop_enemy); //コンストラクタ(自機を止めるか、敵を止めるか)
	~WaitBattleEvent(); //デストラクタ
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //更新
	void Draw(); //描画
};
