#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
//#include "Game.h"
#include "AbstractEnemy.h"
#include "../main/Parameter.h"
#include "../player/Player.h"
#include "../map/MapChipManager.h"
#include "../effect/EffectManager.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include "../single/Sound.h"
#include <map>
#include <list>
#include <vector>
#include <memory>

class Player;
class AbstractEnemy;
class MapChipManager;
class EffectManager;

struct EnemyDataStruct
{
	//敵情報の構造体
	int type; //種類
	int image; //表示する画像
	int hp; //HP
	int size_x; //横の大きさ
	int size_y; //縦の大きさ
	bool inhale; //吸い込めるか
	int rank; //格(0=雑魚、1=中ボス、2以上=ボス)
};

struct StandbyEnemyDataStruct
{
	//マップに配置する敵の構造体
	bool flag; //出現したか
	int num; //種類
	float x; //座標
	float y;
};

class EnemyManager : public CharacterBase{
private:
	std::map<int, EnemyDataStruct> enemy_data; //弾情報
	std::list<std::shared_ptr<AbstractEnemy>> enemy; //敵
	std::vector<StandbyEnemyDataStruct> standby_enemy; //マップに配置する敵

	bool boss_battle; //ボス戦を行っているか
	bool boss_flag; //ボスが出ているか
	bool midboss_flag; //中ボスが出ているか
	float px; //自機の座標
	float py;

	void SetData(); //敵情報の設定

public:
	EnemyManager(); //コンストラクタ
	~EnemyManager(); //デストラクタ
	void Reset(); //初期化
	void EraseCheck(); //消えるか確認
	void SetStandby(char* file_name); //敵をマップに配置
	std::shared_ptr<AbstractEnemy> SetEnemy(int num, float ini_x, float ini_y, AbstractEnemy* base = NULL); //敵の配置(データの番号、座標、本体)
	void SpawnCheck(); //敵が出現できるか確認
	bool HitCheckChara(float cx, float cy, float hit_size); //キャラクターとの当たり判定(キャラのx,y座標、x,y方向の大きさ)
	std::shared_ptr<AbstractEnemy> InhaleCheck(float cx, float cy, float hit_size, bool check_inhaled); //吸い込み判定(キャラのx,y座標、当たり判定の大きさ、すでに吸い込まれているものを取得する)
	void HitCheckBullet(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //弾に当たっているか
	void HitCheckEnemy(std::shared_ptr<EffectManager> effect); //敵に当たっているか
	bool GetBossFlag(); //ボス戦中か取得
	bool GetBeatBoss(); //ボスを倒したか取得
	float GetPlayerX(); //自機のx座標を取得
	float GetPlayerY(); //自機のy座標を取得

	void Update(std::shared_ptr<MapChipManager> map, std::shared_ptr<BulletManager> bullet, std::shared_ptr<Player> player, std::shared_ptr<EffectManager> effect); //更新
	void Draw(); //描画
};