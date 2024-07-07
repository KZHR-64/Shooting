#pragma once
#include "../character/CharacterBase.h"
#include "MapChipManager.h"
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

class MapChipManager;

class AbstractMapChip : public CharacterBase{
protected:
	MapChipManager* manager;

	bool live_flag; //動作するか
	bool draw_flag; //描画するか
	int image; //表示する画像
	int time; //タイマー
	float x; //x座標
	float y; //y座標(一番上を基準とする)
	float base_x; //元々のx座標
	float base_y; //元々のy座標
	int size_x; //横の大きさ
	int size_y; //縦の大きさ
	float sx; //x方向の速度
	float sy; //y方向の速度
	float angle; //角度
	bool hit_flag; //当たり判定
	bool inhale; //吸い込めるか
	bool breakable; //壊せるか
	bool inhaled_flag; //吸い込まれているか

public:
	AbstractMapChip(MapChipManager* man, int num); //コンストラクタ(画像の番号)
	~AbstractMapChip(); //デストラクタ

	bool GetLiveFlag(); //動作するかを取得
	void SetLiveFlag(bool flag); //動作するかを設定
	bool GetDrawFlag(); //描画するかを取得
	void SetDrawFlag(bool flag); //描画するかを設定
	int GetTime(); //マップチップの時間を返す
	void SetTime(int set_time); //時間を設定(時間)
	float GetX(); //マップチップのx座標を返す
	void SetX(float set_x); //マップチップのx座標を設定
	float GetY(); //マップチップのy座標を返す
	void SetY(float set_y); //マップチップのy座標を設定
	float GetBaseX(); //マップチップの元のx座標を返す
	void SetBaseX(float set_x); //マップチップの元のx座標を設定
	float GetBaseY(); //マップチップの元のy座標を返す
	void SetBaseY(float set_y); //マップチップの元のy座標を設定
	int GetSizeX(); //マップチップの横の大きさを返す
	void SetSizeX(int set_size); //マップチップの横の大きさを設定
	int GetSizeY(); //マップチップの縦の大きさを返す
	void SetSizeY(int set_size); //マップチップの縦の大きさを設定
	float GetXSpeed(); //マップチップのx方向の速度を返す
	void SetXSpeed(float set_x); //マップチップのx方向の速度を設定
	float GetYSpeed(); //マップチップのy方向の速度を返す
	void SetYSpeed(float set_y); //マップチップのy方向の速度を設定
	float GetAngle(); //角度を取得
	void SetAngle(float set_angle); //角度を設定(角度)
	float GetSpinSpeed(); //回転速度を取得
	void SetSpinSpeed(float set_angle); //回転速度を設定(角度)
	bool GetHitFlag(); //当たり判定を取得
	void SetHitFlag(bool flag); //当たり判定を設定
	bool GetInhale(); //吸い込めるかを取得
	void SetInhale(bool flag); //吸い込めるかを設定
	bool GetBreakable(); //壊せるかを取得
	void SetBreakable(bool flag); //壊せるかを設定
	bool GetInhaledFlag(); //吸い込まれているかを取得
	void SetInhaledFlag(bool flag); //吸い込まれているかを設定

	virtual void Update() = 0;
};