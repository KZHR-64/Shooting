#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <iostream>
#include <string>
#include <sstream>

//自機移動イベント

class PlayerMoveEvent : public AbstractEvent {
protected:
	float move_speed; //速度
	float px; //x方向の移動量
	float py; //y方向の移動量
	float stop_x; //目的の座標
	float stop_y;
public:
	PlayerMoveEvent(EventManager* man, float x, float y, float speed, bool stop_player, bool stop_enemy); //コンストラクタ(移動量、速度、自機を止めるか、敵を止めるか)
	~PlayerMoveEvent(); //デストラクタ
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //更新
	void Draw(); //描画
};
