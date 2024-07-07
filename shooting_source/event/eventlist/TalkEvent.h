#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <iostream>
#include <string>
#include <sstream>
#include <memory>

//会話イベント

class TalkEvent : public AbstractEvent {
protected:
	std::string chara_name; //キャラクター名
	std::string message; //文章
public:
	TalkEvent(EventManager* man, char* name, char *str, bool stop_player, bool stop_enemy); //コンストラクタ(キャラ名、文章、自機を止めるか、敵を止めるか)
	~TalkEvent(); //デストラクタ
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //更新
	void Draw(); //描画
};
