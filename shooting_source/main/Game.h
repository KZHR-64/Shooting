#pragma once
#include "ModeBase.h"
#include "Parameter.h"
#include "..\player\Player.h"
#include "..\map\MapChipManager.h"
#include "..\enemy\EnemyManager.h"
#include "..\bullet\BulletManager.h"
#include "..\effect\EffectManager.h"
#include "..\event\EventManager.h"
#include "..\single\Key.h"
#include "..\single\Display.h"
#include "..\single\Sound.h"
#include "..\single\Image.h"
#include <memory>

class GameBase;
class Player;
class MapChipManager;
class EnemyManager;
class BulletManager;
class EffectManager;
class EventManager;
//class Parameter;

class Game : public ModeBase {
private:
	std::shared_ptr<Player> player;
	std::shared_ptr<MapChipManager> map;
	std::shared_ptr<EnemyManager> enemy;
	std::shared_ptr<BulletManager> bullet;
	std::shared_ptr<EffectManager> effect;
	std::shared_ptr<EventManager> event;
	Parameter parameter;
	int stage_num; //ステージ番号
	int live; //残機
	bool pause_flag; //ポーズ画面を開いているか
	int cursor; //ポーズ画面のカーソル
	
	void GameUpdate(); //ゲームの更新
	void PauseUpdate(); //ポーズ画面の更新

public:
	Game(ModeChanger *changer, Parameter &param); //コンストラクタ
	~Game(); //デストラクタ
	void Restart(); //再開
	void Update(); //更新
	void Draw(); //描画
};