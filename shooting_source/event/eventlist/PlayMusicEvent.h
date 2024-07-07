#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <iostream>
#include <string>
#include <sstream>

//BGM再生イベント

class PlayMusicEvent : public AbstractEvent {
protected:
	int bgm_num; //BGM番号
public:
	PlayMusicEvent(EventManager* man, int num, bool stop_player, bool stop_enemy); //コンストラクタ(BGM番号、自機を止めるか、敵を止めるか)
	~PlayMusicEvent(); //デストラクタ
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //更新
	void Draw(); //描画
};
