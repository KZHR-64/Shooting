#pragma once

class CharacterBase{
protected:

public:
	struct HitDataStruct
	{
		//当たり判定情報の構造体
		float x; //x座標
		float y; //y座標
		int size; //大きさ
	};
	struct HitStruct
	{
		//当たり判定の構造体
		float x; //x座標
		float y; //y座標
		float distance; //本体との直線距離
		float angle; //初期の角度
		float size; //大きさ
	};
	virtual ~CharacterBase(){}
	virtual void Draw() = 0; //描画
};