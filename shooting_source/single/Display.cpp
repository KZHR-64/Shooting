#pragma once
#include "Display.h"
#include "DxLib.h"

Display::Display() {
	scroll_x = 0; //横方向のスクロールを初期化
	scroll_y = 0; //縦方向のスクロールを初期化
	scroll_x_max = 0; //スクロール上限を初期化
	scroll_y_max = 0; //スクロール上限を初期化
	scroll_x_min = 0; //スクロール下限を初期化
	scroll_y_min = 0; //スクロール下限を初期化
	back_x_max = 0; //スクロール上限を初期化
	back_y_max = 0; //スクロール上限を初期化
}

//スクロールを反映させた描画
void Display::Draw(float x, float y, bool lr, float angle, int image, int BlendMode, int Pal) {

	SetDrawBlendMode(BlendMode, Pal); //描画モードを反映

	DrawRotaGraph((int)x - scroll_x, (int)y - scroll_y, 1.0, angle, image, true, lr);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //描画モードを戻す
}

//背景の描画
void Display::BackDraw(float x, float y, int image, int BlendMode, int Pal) {
	//背景画像の大きさを取得
	int size_x;
	int size_y;
	GetGraphSize(image, &size_x, &size_y);

	// 実際に使うのは半分の大きさ
	size_x = size_x / 2;
	size_y = size_y / 2;

	SetDrawBlendMode(BlendMode, Pal); //描画モードを反映

	DrawRotaGraph((int)x + size_x, (int)y + size_y, 1.f, 0.f,image, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //描画モードを戻す
}

//スクロールを反映させない描画
void Display::FixedDraw(float x, float y, bool lr, float angle, int image, double ex_rate, int BlendMode, int Pal) {
	SetDrawBlendMode(BlendMode, Pal); //描画モードを反映

	DrawRotaGraph((int)x, (int)y, ex_rate, angle, image, true, lr);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //描画モードを戻す
}

//当たり判定の描画
void Display::HitDraw(float x, float y, float hit_size) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 192); //描画モードを反映

	DrawCircle((int)x - scroll_x, (int)y - scroll_y, (int)hit_size, GetColor(255, 96, 96));

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //描画モードを戻す
}

//横方向にどれだけスクロールしているか返す
int Display::GetScrollX() {
	return scroll_x;
}

//縦方向にどれだけスクロールしているか返す
int Display::GetScrollY() {
	return scroll_y;
}

//横方向にどれだけスクロールさせるか設定する
void Display::SetScrollX(float x) {
	scroll_x = (int)x;// -224;
	//最低値を下回った場合
	if (scroll_x < scroll_x_min) {
		scroll_x = scroll_x_min; //スクロールは最低値に
	}
	//はみ出した場合
	if (scroll_x_max < scroll_x) {
		scroll_x = scroll_x_max;
	}
}

//縦方向にどれだけスクロールさせるか設定する
void Display::SetScrollY(float y) {
	scroll_y = (int)y - 324;
	//マイナスになった場合
	if (scroll_y < scroll_y_min) {
		scroll_y = scroll_y_min; //スクロールは最低値に
	}

	//はみ出した場合
	if (scroll_y_max < scroll_y) {
		scroll_y = scroll_y_max;
	}
}

//横方向のスクロール下限を返す
int Display::GetScrollXMin() {
	return scroll_x_min;
}

//縦方向のスクロール下限を返す
int Display::GetScrollYMin() {
	return scroll_y_min;
}

//横方向のスクロール上限を返す
int Display::GetScrollXMax() {
	return scroll_x_max + WINDOW_X;
}

//縦方向のスクロール上限を返す
int Display::GetScrollYMax() {
	return scroll_y_max + WINDOW_Y;
}

//横方向のスクロール下限を設定する
void Display::SetScrollXMin(int x) {
	scroll_x_min = x;
}

//縦方向のスクロール下限を設定する
void Display::SetScrollYMin(int y) {
	scroll_y_min = y;
}

//横方向のスクロール上限を設定する
void Display::SetScrollXMax(int x) {
	back_x_max = scroll_x_max;
	scroll_x_max = x - WINDOW_X;
}

//縦方向のスクロール上限を設定する
void Display::SetScrollYMax(int y) {
	back_y_max = scroll_y_max;
	scroll_y_max = y - WINDOW_Y;
}

//横方向のスクロール上限を戻す
void Display::ReSetScrollXMax() {
	scroll_x_max = back_x_max;
}

//縦方向のスクロール上限を戻す
void Display::ReSetScrollYMax() {
	scroll_y_max = back_y_max;
}

//横方向にどれだけスクロールしたか返す
int Display::GetScrollDifX() {
	return scroll_dif_x;
}

//縦方向にどれだけスクロールしたか返す
int Display::GetScrollDifY() {
	return scroll_dif_y;
}