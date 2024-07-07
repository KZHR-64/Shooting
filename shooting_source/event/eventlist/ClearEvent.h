#pragma once
#include "../AbstractEvent.h"
#include "../Define.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"

//クリアイベント

class ClearEvent : public AbstractEvent {
protected:
	int wait_time; //待ち時間
public:
	ClearEvent(EventManager* man, int waiting, bool stop_player, bool stop_enemy); //コンストラクタ(待ち時間、自機を止めるか、敵を止めるか)
	~ClearEvent(); //デストラクタ
	void Update(std::shared_ptr<Player> player, std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect); //更新
	void Draw(); //描画
};
