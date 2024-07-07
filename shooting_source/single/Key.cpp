#pragma once
#include "Key.h"
#include "DxLib.h"

Key::Key() {
	button[Jump].key = KEY_INPUT_Z; //ジャンプはzキー
	button[Jump].pad = PAD_INPUT_1; //ジャンプは1ボタン
	button[Attack].key = KEY_INPUT_X; //攻撃はxキー
	button[Attack].pad = PAD_INPUT_2; //攻撃は2ボタン
	button[Up].key = KEY_INPUT_UP; //上移動は上キー
	button[Up].pad = PAD_INPUT_UP; //上移動は上ボタン
	button[Down].key = KEY_INPUT_DOWN; //下移動は下キー
	button[Down].pad = PAD_INPUT_DOWN; //下移動は下ボタン
	button[Left].key = KEY_INPUT_LEFT; //左移動は左キー
	button[Left].pad = PAD_INPUT_LEFT; //左移動は左ボタン
	button[Right].key = KEY_INPUT_RIGHT; //右移動は右キー
	button[Right].pad = PAD_INPUT_RIGHT; //右移動は右ボタン
	button[Plus].key = KEY_INPUT_A; //Lボタンはaキー
	button[Plus].pad = PAD_INPUT_5; //Lボタンは3ボタン
	//button[Minus].key = KEY_INPUT_S; //Rボタンはsキー
	//button[Minus].pad = 7; //Rボタンは4ボタン

	pad = 0;
}

//更新
void Key::Update() {
	int i;
	for (i = 0; i < 256; i++) old_key_list[i] = key_list[i]; //一つ前の入力状態を得る
	old_pad = pad; //一つ前の入力状態を得る
	GetHitKeyStateAll(key_list); // 全てのキーの入力状態を得る
	pad = GetJoypadInputState(DX_INPUT_PAD1); // 全てのボタンの入力状態を得る
}

//操作に対応するキーを取得
void Key::GetKey(Key_Func* set_key) {
	for (int i = 0; i < BUTTON; i++)
	{
		set_key[i].key = button[i].key; //キーの設定
		set_key[i].pad = button[i].pad; //パッドの設定
	}
}

//操作に対応するキーを変更
void Key::SetKey(Key_Func* set_key) {
	for (int i = 0; i < BUTTON; i++)
	{
		button[i].key = set_key[i].key; //キーの設定
		button[i].pad = set_key[i].pad; //パッドの設定
	}
}

//キーが押されているか
bool Key::KeyCheck(int check) {
	if (key_list[button[check].key] != 0 || (pad & button[check].pad)) return true; //対応するキーかパッドのボタンが押されていたらtrueを
	else return false; //そうでなければfalseを返す
}

//キーが一度押されたか
bool Key::KeyCheckOnce(int check) {
	//対応するキーかパッドのボタンが押されていたら
	if (key_list[button[check].key] != 0 || (pad & button[check].pad)) {
		if (old_key_list[button[check].key] == 0 && !(old_pad & button[check].pad)) return true; //一つ前に押されていなければtrueを
		else return false; //そうでなければfalseを返す
	}
	else return false; //そうでなければfalseを返す
}

//キーが一度放されたか
bool Key::KeyCheckLetGo(int check) {
	//対応するキーかパッドのボタンが放されていたら
	if (key_list[button[check].key] == 0 && !(pad & button[check].pad)) {
		if (old_key_list[button[check].key] != 0 || (old_pad & button[check].pad)) return true; //一つ前に押されていればtrueを
		else return false; //そうでなければfalseを返す
	}
	else return false; //そうでなければfalseを返す
}

//押されたキーを一つ返す
int Key::GetKeyOnce() {
	for (int i = 0; i < 256; i++)
	{
		// 押されているキーがあった場合
		if (key_list[i] != 0) {
			if (old_key_list[i] == 0) return i; //一つ前に押されていなければiを返す
		}
	}
	return -1; //なければ-1を返す
}

//押されたボタンを一つ返す
int Key::GetPadOnce() {
	for (int i = 0; i < 28; i++) {
		// 押されているボタンがあった場合
		if (pad & (1 << i)) {
			if (!(old_pad & (1 << i))) return (int)pow(2, i); //一つ前に押されていなければiを返す
		}
	}
	return -1; //なければ-1を返す
}