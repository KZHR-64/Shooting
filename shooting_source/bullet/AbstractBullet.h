#pragma once
#include "../character/CharacterBase.h"
#include "BulletManager.h"
#include "../Define.h"
//#include "Game.h"
#include "../map/MapChipManager.h"
#include "../map/AbstractMapChip.h"
#include "../effect/EffectManager.h"
#include "../enemy/EnemyManager.h"
//#include "Bullet.h"
//#include "Enemy.h"
//#include "Bullet.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <vector>
#include <memory>

class BulletManager;
class EnemyManager;
class MapChipManager;
class EffectManager;
class AbstractMapChip;

class AbstractBullet : public CharacterBase{
protected:
	BulletManager* manager;
	std::vector<HitStruct> hit; //当たり判定

	bool live_flag; //動作するか
	bool end_flag; //消去するか
	int image; //表示する画像
	int time; //タイマー
	int end_time; //消滅までの時間
	int damage; //ダメージ値
	float x; //x座標
	float y; //y座標
	float base_x; //元々のx座標
	float base_y; //元々のy座標
	int size_x; //横の大きさ
	int size_y; //縦の大きさ
	float sx; //x方向の速度
	float sy; //y方向の速度
	float angle; //角度
	bool breakable; //壊せるか
	bool hit_player; //自機に当たるか
	bool hit_enemy; //敵に当たるか
	bool hit_map; //マップチップに当たるか

	void SetHit(float cx, float cy, float hit_size); //当たり判定の配置(x,y座標、当たり判定の大きさ)

public:
	AbstractBullet(BulletManager* man, int num, float ini_x, float ini_y, float ini_speed, float ini_angle); //コンストラクタ(画像の番号、座標、速度、角度)
	~AbstractBullet(); //デストラクタ

	bool GetEndFlag(); //消去するかを取得
	void SetEndFlag(bool flag); //消去するかを設定
	int GetTime(); //弾の時間を返す
	void SetTime(int set_time); //時間を設定(時間)
	int GetEndTime(); //消滅までの時間を返す
	void SetEndTime(int set_time); //消滅までの時間を設定(時間)
	int GetDamage(); //ダメージ値を返す
	void SetDamage(int set_damage); //ダメージ値を設定(ダメージ値)
	float GetX(); //弾のx座標を返す
	void SetX(float set_x); //弾のx座標を設定
	float GetY(); //弾のy座標を返す
	void SetY(float set_y); //弾のy座標を設定
	float GetBaseX(); //弾の元のx座標を返す
	void SetBaseX(float set_x); //弾の元のx座標を設定
	float GetBaseY(); //弾の元のy座標を返す
	void SetBaseY(float set_y); //弾の元のy座標を設定
	int GetSizeX(); //弾の横の大きさを返す
	void SetSizeX(int set_size); //弾の横の大きさを設定
	int GetSizeY(); //弾の縦の大きさを返す
	void SetSizeY(int set_size); //弾の縦の大きさを設定
	void SetSpeed(float speed); //角度を基に速度を設定
	float GetXSpeed(); //弾のx方向の速度を返す
	void SetXSpeed(float set_x); //弾のx方向の速度を設定
	float GetYSpeed(); //弾のy方向の速度を返す
	void SetYSpeed(float set_y); //弾のy方向の速度を設定
	float GetAngle(); //角度を取得
	void SetAngle(float set_angle); //角度を設定(角度)
	float GetSpinSpeed(); //回転速度を取得
	void SetSpinSpeed(float set_angle); //回転速度を設定(角度)
	bool GetBreakable(); //壊せるかを取得
	void SetBreakable(bool flag); //壊せるかを設定
	bool GetHitPlayer(); //自機に当たるかを取得
	void SetHitPlayer(bool flag); //自機に当たるかを設定
	bool GetHitEnemy(); //敵に当たるかを取得
	void SetHitEnemy(bool flag); //敵に当たるかを設定
	bool GetHitMap(); //マップチップに当たるかを取得
	void SetHitMap(bool flag); //マップチップに当たるかを設定

	void HitUpdate(); //当たり判定の更新
	void DrawHit(); //当たり判定の描画

	int HitCheckChara(float cx, float cy, float hit_size, bool check_inhale = false); //キャラクターとの当たり判定(キャラのx,y座標、当たり判定の大きさ、吸い込み判定か)
	void HitCheckMap(std::shared_ptr<MapChipManager> map); //マップチップとの当たり判定

	virtual void Update(std::shared_ptr<EnemyManager> enemy, std::shared_ptr<EffectManager> effect) = 0;
};