#pragma once
#include "ModeBase.h"
#include "..\single\Key.h"
#include "..\single\Sound.h"
#include "..\single\Image.h"
#include "..\single\Display.h"

struct KeySettingStruct{
	//設定の構造体
	int key_up;			//上のキー
	int key_down;		//下のキー
	int key_left;		//左のキー
	int key_right;		//右のキー
	int key_jump;		//ジャンプのキー
	int key_attack;		//攻撃のキー
	int key_plus;			//+ボタンのキー
	//int key_minus;			//-ボタンのキー
	int pad_up;			//上のボタン
	int pad_down;		//下のボタン
	int pad_left;		//左のボタン
	int pad_right;		//右のボタン
	int pad_jump;		//ジャンプのボタン
	int pad_attack;		//攻撃のボタン
	int pad_plus;			//+ボタン
	//int pad_minus;			//-ボタン
};

class KeyConfig : public ModeBase {
private:

	int message_font; //フォント情報

	std::map<int, char*> key_map; //キーの番号に対応する文字

	int key_cursor; //カーソルの位置(キーコンフィグ)
	int pad_cursor; //カーソルの位置(パッドコンフィグ)

	Key_Func button[BUTTON]; //対応するボタン
	char key_input[BUTTON]; //入力したキーの文字

	KeySettingStruct setting;

	void Reset(); //初期化
	void LoadSetting(); //設定の読み込み
	void SaveSetting(); //設定の保存

public:
	KeyConfig(ModeChanger* changer, Parameter& param); //コンストラクタ
	~KeyConfig(); //デストラクタ
	void Update(); //更新
	void Draw(); //描画
};