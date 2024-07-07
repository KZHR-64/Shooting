#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <iostream>
#include <string>
#include <sstream>

//スクロール位置調整イベント

class ScrollResetEvent : public AbstractEvent {
protected:
public:
	ScrollResetEvent(EventManager* man, bool stop_player, bool stop_enemy); //コンストラクタ(座標、自機を止めるか、敵を止めるか)
	~ScrollResetEvent(); //デストラクタ
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //更新
	void Draw(); //描画
};
