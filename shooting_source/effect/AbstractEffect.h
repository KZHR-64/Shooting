#pragma once
#include "../character/CharacterBase.h"
#include "EffectManager.h"
#include "../Define.h"
//#include "Game.h"
//#include "Map.h"
//#include "Bullet.h"
//#include "Enemy.h"
//#include "Effect.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <memory>

class EffectManager;

class AbstractEffect : public CharacterBase{
protected:
	EffectManager* manager;

	bool flag; //表示するか
	bool end_flag; //消去するか
	int image; //表示する画像
	int time; //タイマー
	float x; //x座標
	float y; //y座標(一番上を基準とする)
	float base_x; //元々のx座標
	float base_y; //元々のy座標
	float sx; //x方向の速度
	float sy; //y方向の速度
	float angle; //角度

public:
	AbstractEffect(EffectManager* man, int num, float ini_x, float ini_y); //コンストラクタ(画像の番号、座標)
	~AbstractEffect(); //デストラクタ

	bool GetEndFlag(); //消去するかを取得
	void SetEndFlag(bool set_flag); //消去するかを設定
	int GetTime(); //エフェクトの時間を返す
	void SetTime(int set_time); //時間を設定(時間)
	float GetX(); //エフェクトのx座標を返す
	void SetX(float set_x); //エフェクトのx座標を設定
	float GetY(); //エフェクトのy座標を返す
	void SetY(float set_y); //エフェクトのy座標を設定
	float GetBaseX(); //エフェクトの元のx座標を返す
	void SetBaseX(float set_x); //エフェクトの元のx座標を設定
	float GetBaseY(); //エフェクトの元のy座標を返す
	void SetBaseY(float set_y); //エフェクトの元のy座標を設定
	float GetXSpeed(); //エフェクトのx方向の速度を返す
	void SetXSpeed(float set_x); //エフェクトのx方向の速度を設定
	float GetYSpeed(); //エフェクトのy方向の速度を返す
	void SetYSpeed(float set_y); //エフェクトのy方向の速度を設定
	float GetAngle(); //角度を取得
	void SetAngle(float set_angle); //角度を設定(角度)
	float GetSpinSpeed(); //回転速度を取得
	void SetSpinSpeed(float set_angle); //回転速度を設定(角度)

	virtual void Update() = 0;
};