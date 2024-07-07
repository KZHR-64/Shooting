#pragma once
#include "../character/CharacterBase.h"
#include "../Define.h"
//#include "Game.h"
#include "../map/MapChipManager.h"
#include "../map/AbstractMapChip.h"
#include "../bullet/BulletManager.h"
#include "../enemy/EnemyManager.h"
#include "../effect/EffectManager.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <memory>

class MapChipManager;
class BulletManager;
class EnemyManager;
class EffectManager;
class AbstractMapChip;
class AbstractBullet;
class AbstractEnemy;
class AbstractEffect;

struct AttackStruct
{
	//攻撃の構造体
	bool flag; //攻撃しているか
	int push_time; //ボタンを押している時間
};

struct CatcherStruct
{
	//つかみビームの構造体
	bool flag; //出しているか
	bool catch_flag; //つかんでいるか
	float x; //座標
	float y;
};

struct PlayerPartsStruct
{
	//パーツの構造体
	float x; //座標
	float y;
	float angle; //角度
	float total_angle; //角度の合計
	float def_angle; //計算用の角度
	float def_distance; //計算用の距離
	float spin_angle; //回転の基準となる角度
	float spin_distance; //回転の基準となる距離
};

class Player : public CharacterBase{
private:
	void Control(); //自機の操作
	void DamageAction(); //ダメージ動作
	void Move(); //移動
	void SetGraphic(); //表示する画像を決定
	void SetKeyRecord(); //キーの履歴を更新
	bool RecordCheck(bool record[], int point = 0); //入力履歴の確認(渡す列、探し始める点)
	void SetParts(); //パーツをそろえる
	float PartsSpin(float parts_angle, float spin_speed, float spin_max, float spin_min); //パーツを回転させる(基の角度、回転速度、上限、下限)

	int hp; //HP
	float x, y; //座標
	float fx, fy; //次に行く予定の座標
	float sx, sy; //速度
	float angle; //角度
	float sangle; //回転速度
	bool lr; //向き(0=左、1=右)
	bool damaged; //ダメージを受けているか
	int damage_time; //ダメージ動作の時間
	int move_type; //行っている動作
	int move_time; //動作の時間
	int handle; //表示する画像の番号
	int inv_time; //無敵時間
	bool draw_flag; //描画するか
	const float move_speed = 6.f; //基となる移動速度
	const float hit_size = 16.f; //当たり判定の大きさ

	AttackStruct attack;
	CatcherStruct catch_arm;
	//std::shared_ptr<AbstractEnemy> catch_enemy; //つかんだ敵
	std::shared_ptr<AbstractEffect> catch_effect; //ビーム用のエフェクト

	PlayerPartsStruct body, left_thigh, left_leg, right_thigh, right_leg, left_shoulder, right_shoulder, left_arm, right_arm; //各パーツ
	
	bool commando[BUTTON][RECORD]; //入力したキーの履歴

public:
	Player(); //コンストラクタ
	~Player(); //デストラクタ
	void Reset(); //初期化
	void AdjustPosition(std::shared_ptr<MapChipManager> map, bool event_flag); //位置の調節
	void AttackCheck(std::shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect); //攻撃
	void InhaleCheck(std::shared_ptr<MapChipManager> map, std::shared_ptr<EnemyManager> enemy); //吸い込めるか確認
	void HitCheckEnemy(std::shared_ptr<EnemyManager> enemy); //敵に当たっているか
	void HitCheckBullet(std::shared_ptr<BulletManager> bullet); //弾に当たっているか
	int GetHp(); //HPを返す
	float GetX(); //x座標を返す
	float GetY(); //y座標を返す
	void SetX(float px); //x座標を設定
	void SetY(float py); //y座標を設定
	float GetXSpeed(); //横の速度を返す
	float GetYSpeed(); //縦の速度を返す
	void SetXSpeed(float speed_x); //横の速度を設定(速さ)
	void SetYSpeed(float speed_y); //縦の速度を設定(速さ)
	void SetDrawFlag(bool flag); //描画するか設定
	void Update(); //更新
	void Draw() override; //描画
};