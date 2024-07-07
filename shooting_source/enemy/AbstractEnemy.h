#pragma once
#include "../character/CharacterBase.h"
#include "EnemyManager.h"
#include "../Define.h"
//#include "Game.h"
#include "../map/MapChipManager.h"
#include "../map/AbstractMapChip.h"
#include "../bullet/BulletManager.h"
#include "../effect/EffectManager.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <memory>

class EnemyManager;
class BulletManager;
class MapChipManager;
class EffectManager;
class AbstractMapChip;

class AbstractEnemy : public CharacterBase {
protected:
	EnemyManager* manager;

	std::vector<std::shared_ptr<AbstractEnemy>> parts; //パーツとして扱う敵
	AbstractEnemy* base_enemy; //本体
	std::vector<HitStruct> hit; //当たり判定

	bool live_flag; //表示するか
	bool end_flag; //消去するか
	bool boss_flag; //ボスキャラか
	bool hit_flag; //当たり判定
	int image; //表示する画像
	int trance; //透明度
	int time; //タイマー
	int hp; //HP
	float x; //x座標
	float y; //y座標
	float base_x; //元々のx座標
	float base_y; //元々のy座標
	float sx; //x方向の速度
	float sy; //y方向の速度
	float angle; //角度
	float spin_speed; //回転速度
	bool lr; //向き(0=左、1=右)
	int jump_time; //ジャンプしている時間
	bool jump_flag; //ジャンプしているか
	bool flying_flag; //飛んでいるか
	bool damaged; //ダメージを受けているか
	int damage_time; //ダメージ動作の時間
	bool inhale; //吸い込めるか
	bool hit_map; //マップチップに当たるか
	bool inhaled_flag; //吸い込まれているか

	void SetHit(float cx, float cy, float hit_size); //当たり判定の配置(x,y座標、当たり判定の大きさ)

public:
	AbstractEnemy(EnemyManager* man, int num, float ini_x, float ini_y); //コンストラクタ(画像の番号、座標)
	~AbstractEnemy(); //デストラクタ

	AbstractEnemy* GetBase(); //本体を取得
	void SetBase(AbstractEnemy* base); //本体を設定
	bool GetEndFlag(); //消去するかを取得
	void SetEndFlag(bool flag); //消去するかを設定
	bool GetBossFlag(); //ボスかを取得
	void SetBossFlag(int rank); //ボスかを設定(格)
	bool GetHitFlag(); //当たり判定を取得
	void SetHitFlag(bool flag); //当たり判定を設定
	void SetTrance(int set_trance); //透明度を設定
	int GetTime(); //敵の時間を返す
	void SetTime(int set_time); //時間を設定(時間)
	int GetHp(); //HPを返す
	void SetHp(int set_hp); //HPを設定(HP)
	float GetX(); //敵のx座標を返す
	void SetX(float set_x); //敵のx座標を設定
	float GetY(); //敵のy座標を返す
	void SetY(float set_y); //敵のy座標を設定
	float GetBaseX(); //敵の元のx座標を返す
	void SetBaseX(float set_x); //敵の元のx座標を設定
	float GetBaseY(); //敵の元のy座標を返す
	void SetBaseY(float set_y); //敵の元のy座標を設定
	void SetSpeed(float speed); //角度を基に速度を設定
	float GetXSpeed(); //敵のx方向の速度を返す
	void SetXSpeed(float set_x); //敵のx方向の速度を設定
	float GetYSpeed(); //敵のy方向の速度を返す
	void SetYSpeed(float set_y); //敵のy方向の速度を設定
	float GetAngle(); //角度を取得
	void SetAngle(float set_angle); //角度を設定(角度)
	float GetSpinSpeed(); //回転速度を取得
	void SetSpinSpeed(float set_angle); //回転速度を設定(角度)
	bool GetLr(); //向きを取得
	void SetLr(bool set_lr); //向きを設定(向き)
	bool GetFlying(); //飛んでいるかを取得
	void SetFlying(bool flag); //飛んでいるかを設定
	bool GetDamaged(); //ダメージを受けているかを取得
	bool GetInhale(); //吸い込めるかを取得
	void SetInhale(bool flag); //吸い込めるかを設定
	bool GetHitMap(); //マップチップに当たるかを取得
	void SetHitMap(bool flag); //マップチップに当たるかを設定
	bool GetInhaledFlag(); //吸い込まれているかを取得
	void SetInhaledFlag(bool flag); //吸い込まれているかを設定
	void Homing(float set_spin_speed, float speed, float set_x, float set_y); //目標に向けての速度を調整(回転速度、速度、目標の座標)
	void HomingSpin(float set_spin_speed, float set_x, float set_y, bool use_base = false); //目標に向けて回転(回転速度、目標の座標、基の座標を使うか)
	void Spin(float set_spin_speed, float spin_max, float spin_min); //回転させる(回転速度、上限、下限)

	bool HitDamage(int damage_num); //ダメージ処理(ダメージ値)
	void HitUpdate(); //当たり判定の更新
	void DrawHit(); //当たり判定の描画

	void AdjustPosition(std::shared_ptr<MapChipManager> map); //位置の調節
	void HitCheckBullet(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //弾に当たっているか
	void HitCheckEnemy(float cx, float cy, float hit_size, std::shared_ptr<EffectManager> effect); //敵に当たっているか
	bool HitCheckChara(float cx, float cy, float hit_size, bool check_hit = true); //キャラクターとの当たり判定(キャラのx,y座標、当たり判定の大きさ、当たり判定の有無を確認するか)
	void Timer(); //タイマー関連の更新

	virtual void AbsUpdate() = 0; //必ず行う更新
	virtual void Update(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect) = 0; //更新
};