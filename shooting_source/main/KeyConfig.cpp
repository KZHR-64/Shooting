#pragma once
#include "DxLib.h"
#include "KeyConfig.h"

KeyConfig::KeyConfig(ModeChanger* changer, Parameter& param) : ModeBase(changer, param) {

	Reset();

	LoadSetting();

	message_font = CreateFontToHandle("Meiryo UI", 24, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1); //フォント情報

	key_map[KEY_INPUT_BACK] = "BackSpace";	// バックスペースキー
	key_map[KEY_INPUT_TAB] = "Tab";	// タブキー
	key_map[KEY_INPUT_RETURN] = "Enter";	// エンターキー
	key_map[KEY_INPUT_LSHIFT] = "LShift";	// 左シフトキー
	key_map[KEY_INPUT_RSHIFT] = "Rshift";	// 右シフトキー
	key_map[KEY_INPUT_LCONTROL] = "LCtrl";	// 左コントロールキー
	key_map[KEY_INPUT_RCONTROL] = "Rctrl";	// 右コントロールキー
	key_map[KEY_INPUT_ESCAPE] = "Esc";	// エスケープキー
	key_map[KEY_INPUT_SPACE] = "Space";	// スペースキー
	key_map[KEY_INPUT_PGUP] = "PgUp";	// ＰａｇｅＵＰキー
	key_map[KEY_INPUT_PGDN] = "PgDn";	// ＰａｇｅＤｏｗｎキー
	key_map[KEY_INPUT_END] = "End";	// エンドキー
	key_map[KEY_INPUT_HOME] = "Home";	// ホームキー
	key_map[KEY_INPUT_LEFT] = "←";	// 左キー
	key_map[KEY_INPUT_UP] = "↑";	// 上キー
	key_map[KEY_INPUT_RIGHT] = "→";	// 右キー
	key_map[KEY_INPUT_DOWN] = "↓";	// 下キー
	key_map[KEY_INPUT_INSERT] = "Insert";	// インサートキー
	key_map[KEY_INPUT_DELETE] = "Delete";	// デリートキー
	key_map[KEY_INPUT_MINUS] = "-";	// －キー
	key_map[KEY_INPUT_YEN] = "\\";	// ￥キー
	key_map[KEY_INPUT_PREVTRACK] = "^";	// ＾キー
	key_map[KEY_INPUT_PERIOD] = ".";	// ．キー
	key_map[KEY_INPUT_SLASH] = "/";	// ／キー
	key_map[KEY_INPUT_LALT] = "LAlt";	// 左ＡＬＴキー
	key_map[KEY_INPUT_RALT] = "RAlt";	// 右ＡＬＴキー
	key_map[KEY_INPUT_SCROLL] = "ScrollLock";	// ScrollLockキー
	key_map[KEY_INPUT_SEMICOLON] = ";";	// ；キー
	key_map[KEY_INPUT_COLON] = ":";	// ：キー
	key_map[KEY_INPUT_LBRACKET] = "[";	// ［キー
	key_map[KEY_INPUT_RBRACKET] = "]";	// ］キー
	key_map[KEY_INPUT_AT] = "@";	// ＠キー
	key_map[KEY_INPUT_BACKSLASH] = "＼";	// ＼キー
	key_map[KEY_INPUT_COMMA] = ",";	// ，キー
	key_map[KEY_INPUT_CAPSLOCK] = "CapsLock";	// CaspLockキー
	key_map[KEY_INPUT_PAUSE] = "Pause";	// PauseBreakキー
	key_map[KEY_INPUT_NUMPAD0] = "0";	// テンキー０
	key_map[KEY_INPUT_NUMPAD1] = "1";	// テンキー１
	key_map[KEY_INPUT_NUMPAD2] = "2";	// テンキー２
	key_map[KEY_INPUT_NUMPAD3] = "3";	// テンキー３
	key_map[KEY_INPUT_NUMPAD4] = "4";	// テンキー４
	key_map[KEY_INPUT_NUMPAD5] = "5";	// テンキー５
	key_map[KEY_INPUT_NUMPAD6] = "6";	// テンキー６
	key_map[KEY_INPUT_NUMPAD7] = "7";	// テンキー７
	key_map[KEY_INPUT_NUMPAD8] = "8";	// テンキー８
	key_map[KEY_INPUT_NUMPAD9] = "9";	// テンキー９
	key_map[KEY_INPUT_MULTIPLY] = "*";	// テンキー＊キー
	key_map[KEY_INPUT_ADD] = "+";	// テンキー＋キー
	key_map[KEY_INPUT_SUBTRACT] = "-";	// テンキー－キー
	key_map[KEY_INPUT_DECIMAL] = ".";	// テンキー．キー
	key_map[KEY_INPUT_DIVIDE] = "/";	// テンキー／キー
	key_map[KEY_INPUT_NUMPADENTER] = "Enter";	// テンキーのエンターキー
	key_map[KEY_INPUT_F1] = "F1";	// Ｆ１キー
	key_map[KEY_INPUT_F2] = "F2";	// Ｆ２キー
	key_map[KEY_INPUT_F3] = "F3";	// Ｆ３キー
	key_map[KEY_INPUT_F4] = "F4";	// Ｆ４キー
	key_map[KEY_INPUT_F5] = "F5";	// Ｆ５キー
	key_map[KEY_INPUT_F6] = "F6";	// Ｆ６キー
	key_map[KEY_INPUT_F7] = "F7";	// Ｆ７キー
	key_map[KEY_INPUT_F8] = "F8";	// Ｆ８キー
	key_map[KEY_INPUT_F9] = "F9";	// Ｆ９キー
	key_map[KEY_INPUT_F10] = "F10";	// Ｆ１０キー
	key_map[KEY_INPUT_F11] = "F11";	// Ｆ１１キー
	key_map[KEY_INPUT_F12] = "F12";	// Ｆ１２キー
	key_map[KEY_INPUT_A] = "A";	// Ａキー
	key_map[KEY_INPUT_B] = "B";	// Ｂキー
	key_map[KEY_INPUT_C] = "C";	// Ｃキー
	key_map[KEY_INPUT_D] = "D";	// Ｄキー
	key_map[KEY_INPUT_E] = "E";	// Ｅキー
	key_map[KEY_INPUT_F] = "F";	// Ｆキー
	key_map[KEY_INPUT_G] = "G";	// Ｇキー
	key_map[KEY_INPUT_H] = "H";	// Ｈキー
	key_map[KEY_INPUT_I] = "I";	// Ｉキー
	key_map[KEY_INPUT_J] = "J";	// Ｊキー
	key_map[KEY_INPUT_K] = "K";	// Ｋキー
	key_map[KEY_INPUT_L] = "L";	// Ｌキー
	key_map[KEY_INPUT_M] = "M";	// Ｍキー
	key_map[KEY_INPUT_N] = "N";	// Ｎキー
	key_map[KEY_INPUT_O] = "O";	// Ｏキー
	key_map[KEY_INPUT_P] = "P";	// Ｐキー
	key_map[KEY_INPUT_Q] = "Q";	// Ｑキー
	key_map[KEY_INPUT_R] = "R";	// Ｒキー
	key_map[KEY_INPUT_S] = "S";	// Ｓキー
	key_map[KEY_INPUT_T] = "T";	// Ｔキー
	key_map[KEY_INPUT_U] = "U";	// Ｕキー
	key_map[KEY_INPUT_V] = "V";	// Ｖキー
	key_map[KEY_INPUT_W] = "W";	// Ｗキー
	key_map[KEY_INPUT_X] = "X";	// Ｘキー
	key_map[KEY_INPUT_Y] = "Y";	// Ｙキー
	key_map[KEY_INPUT_Z] = "Z";	// Ｚキー
	key_map[KEY_INPUT_0] = "0";	// ０キー
	key_map[KEY_INPUT_1] = "1";	// １キー
	key_map[KEY_INPUT_2] = "2";	// ２キー
	key_map[KEY_INPUT_3] = "3";	// ３キー
	key_map[KEY_INPUT_4] = "4";	// ４キー
	key_map[KEY_INPUT_5] = "5";	// ５キー
	key_map[KEY_INPUT_6] = "6";	// ６キー
	key_map[KEY_INPUT_7] = "7";	// ７キー
	key_map[KEY_INPUT_8] = "8";	// ８キー
	key_map[KEY_INPUT_9] = "9";	// ９キー
}

KeyConfig::~KeyConfig() {
	key_map.clear();
	DeleteFontToHandle(message_font);
}

//初期化
void KeyConfig::Reset() {
	Sound::Get_Instance()->LoadBgm(1); //曲を再生
	Image::Get_Instance()->LoadBackImage(2);

	//画像を設定

	key_cursor = 0; //カーソルの位置
	pad_cursor = 0; //カーソルの位置

	return_flag = false; //帰還フラグはfalse
}

//設定の読み込み
void KeyConfig::LoadSetting() {
	FILE *fp;
	char buf[256];

	fopen_s(&fp, "key_config.dat", "rb"); //設定を読み込む

	//なければデフォルト
	if (fp == NULL) {
		button[Jump].key = KEY_INPUT_Z; //ジャンプはzキー
		button[Attack].key = KEY_INPUT_X; //攻撃はxキー
		button[Up].key = KEY_INPUT_UP; //上移動は上キー
		button[Down].key = KEY_INPUT_DOWN; //下移動は下キー
		button[Left].key = KEY_INPUT_LEFT; //左移動は左キー
		button[Right].key = KEY_INPUT_RIGHT; //右移動は右キー
		button[Plus].key = KEY_INPUT_A; //Lボタンはaキー
		//button[Minus].key = KEY_INPUT_S; //Rボタンはsキー
		button[Jump].pad = PAD_INPUT_1; //ジャンプは1ボタン
		button[Attack].pad = PAD_INPUT_2; //攻撃は2ボタン
		button[Up].pad = PAD_INPUT_UP; //上移動は上ボタン
		button[Down].pad = PAD_INPUT_DOWN; //下移動は下ボタン
		button[Left].pad = PAD_INPUT_LEFT; //左移動は左ボタン
		button[Right].pad = PAD_INPUT_RIGHT; //右移動は右ボタン
		button[Plus].pad = PAD_INPUT_5; //Lボタンは5ボタン
		//button[Minus].pad = PAD_INPUT_4; //Rボタンは4ボタン
	}
	else {
		memset(buf, 0, sizeof(buf)); //メモリをセット

		fread(&setting, sizeof(setting), 1, fp);
		button[Jump].key = setting.key_jump;
		button[Attack].key = setting.key_attack;
		button[Up].key = setting.key_up;
		button[Down].key = setting.key_down;
		button[Left].key = setting.key_left;
		button[Right].key = setting.key_right;
		button[Plus].key = setting.key_plus;
		//button[Minus].key = setting.key_minus;
		button[Jump].pad = setting.pad_jump;
		button[Attack].pad = setting.pad_attack;
		button[Up].pad = setting.pad_up;
		button[Down].pad = setting.pad_down;
		button[Left].pad = setting.pad_left;
		button[Right].pad = setting.pad_right;
		button[Plus].pad = setting.pad_plus;
		//button[Minus].pad = setting.pad_minus;
		fclose(fp);
	}
}

//設定の保存
void KeyConfig::SaveSetting() {
	FILE *fp;

	//キーコンフィグを反映
	setting.key_up = button[Up].key;
	setting.key_down = button[Down].key;
	setting.key_left = button[Left].key;
	setting.key_right = button[Right].key;
	setting.key_jump = button[Jump].key;
	setting.key_attack = button[Attack].key;
	setting.key_plus = button[Plus].key;
	//setting.key_minus = button[Minus].key;
	setting.pad_up = button[Up].pad;
	setting.pad_down = button[Down].pad;
	setting.pad_left = button[Left].pad;
	setting.pad_right = button[Right].pad;
	setting.pad_jump = button[Jump].pad;
	setting.pad_attack = button[Attack].pad;
	setting.pad_plus = button[Plus].pad;
	//setting.pad_minus = button[Minus].pad;

	fopen_s(&fp, "key_config.dat", "wb"); //設定の入ったファイルを開く

	fwrite(&setting, sizeof(setting), 1, fp); //ファイルに設定を書き込む

	fclose(fp);
}

//更新
void KeyConfig::Update(){
	//帰還フラグが立っている場合
	if (return_flag) {
		Reset();
	}

	int key = Key::Get_Instance()->GetKeyOnce(); //押されているキーを取得
	int pad = Key::Get_Instance()->GetPadOnce(); //押されているボタンを取得
	int flag = false; //コンフィグ終了フラグ

	//押されているキーがある場合
	if (key != -1) {
		// 最後まで設定していない場合
		if (key_cursor < BUTTON) {
			//他のキーを確認
			for (int i = 0; i < BUTTON; i++)
			{
				if (i == key_cursor) continue; //iがカーソルと一致した場合はスルー
				//すでにキーが設定されている場合
				if (button[i].key == key) {
					button[i].key = button[key_cursor].key; //入れ替える
				}
			}
			button[key_cursor].key = key; //押されたキーを格納
			key_cursor++; //カーソルを一つ下に移動
		}
		// 最後まで設定している場合
		else {
			flag = true; //コンフィグ終了フラグを立てる
		}
		Sound::Get_Instance()->PlaySoundEffect(1); //効果音を鳴らす
	}

	//押されているボタンがある場合
	if (pad != -1) {
		// 最後まで設定していない場合
		if (pad_cursor < BUTTON) {
			//他のボタンを確認
			for (int i = 0; i < BUTTON; i++)
			{
				if (i == pad_cursor) continue; //iがカーソルと一致した場合はスルー
				//すでにボタンが設定されている場合
				if (button[i].pad == pad) {
					button[i].pad = button[pad_cursor].pad; //入れ替える
				}
			}
			button[pad_cursor].pad = pad; //押されたボタンを格納
			pad_cursor++; //カーソルを一つ下に移動
		}
		// 最後まで設定している場合
		else {
			flag = true; //コンフィグ終了フラグを立てる
		}
		Sound::Get_Instance()->PlaySoundEffect(1); //効果音を鳴らす
	}

	//コンフィグ終了フラグがtrueの場合
	if (flag) {
		Key::Get_Instance()->SetKey(button); //設定を確定する
		SaveSetting(); //設定を保存する
		modechanger->ChangeMode(Next_Back); //メニューに戻る
	}
}

//描画
void KeyConfig::Draw(){
	int back = Image::Get_Instance()->GetBackImage(2); //背景を取得
	Display::Get_Instance()->FixedDraw(320.f, 240.f, LEFT, 0.f, back); //背景を描画

	//カーソルの大きさを指定
	int cursor_size_x = 188;
	int cursor_size_y = 40;

	//カーソルの位置を指定
	int key_cursor_x = 266;
	int key_cursor_y = 112 + (cursor_size_y * key_cursor);

	//カーソルの位置を指定
	int pad_cursor_x = key_cursor_x + cursor_size_x;
	int pad_cursor_y = 112 + (cursor_size_y * pad_cursor);

	//選択する位置以外は少し暗くする
	for (int i = 0; i <= BUTTON; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		if (i != key_cursor)DrawBox(key_cursor_x, 112 + (cursor_size_y * i), key_cursor_x + cursor_size_x, 112 + (cursor_size_y * i) + cursor_size_y, GetColor(128, 128, 128), true);
		if (i != pad_cursor) DrawBox(pad_cursor_x, 112 + (cursor_size_y * i), pad_cursor_x + cursor_size_x, 112 + (cursor_size_y * i) + cursor_size_y, GetColor(128, 128, 128), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	for (int i = 0; i < BUTTON; i++)
	{
		DrawFormatStringToHandle(key_cursor_x + 12, 112 + (cursor_size_y * i) + 8, GetColor(255, 255, 255), message_font, "%s", key_map[button[i].key]);
		int pad_num = (int)log2((double)(button[i].pad));
		DrawFormatStringToHandle(pad_cursor_x + 12, 112 + (cursor_size_y * i) + 8, GetColor(255, 255, 255), message_font, "%d", pad_num);
	}
}