#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
//#include "Game.h"
#include "AbstractEffect.h"
#include "../main/Parameter.h"
#include "../player/Player.h"
//#include "Effect.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include "../single/Sound.h"
#include <map>
#include <list>
#include <queue>
#include <memory>

class AbstractEffect;

class EffectManager : public CharacterBase{
private:
	std::list<std::shared_ptr<AbstractEffect>> effect; //エフェクト

public:
	EffectManager(); //コンストラクタ
	~EffectManager(); //デストラクタ
	void Reset(); //初期化
	std::shared_ptr<AbstractEffect> SetEffect(int num, float ini_x, float ini_y); //エフェクトの配置(データの番号、座標)

	void Update(); //更新
	void Draw(); //描画
};