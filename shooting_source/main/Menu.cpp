#pragma once
#include "DxLib.h"
#include "Menu.h"
#include <math.h>

Menu::Menu(ModeChanger* changer, Parameter& param) : ModeBase(changer, param) {

	Reset(); //初期化
	
	cursor_pos = 0; //cursorの位置を初期化
}

//デストラクタ
Menu::~Menu() {
	
}

//初期化
void Menu::Reset() {
	Sound::Get_Instance()->LoadBgm(0); //曲を再生
	Image::Get_Instance()->LoadBackImage(4);
	for (int i = 0; i < 4; i++)
	{
		choice[i].image = Image::Get_Instance()->GetEffectImage(0, i); //画像を設定
		choice[i].ex_rate = 1.f; //倍率を初期化
	}
	logo = Image::Get_Instance()->GetEffectImage(1, 0); //画像を設定

	count = 0;
	return_flag = false; //帰還フラグはfalse
}

//更新
void Menu::Update(){
	Parameter param;

	//帰還フラグが立っている場合
	if (return_flag) {
		Reset(); //初期化
	}
	if (Key::Get_Instance()->KeyCheckOnce(Up)){ //上キーが押されていたら
		Sound::Get_Instance()->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos += 3; //カーソルを上に移動
		count = 0; //カウンターを初期化
	}

	if (Key::Get_Instance()->KeyCheckOnce(Down)){ //下キーが押されていたら
		Sound::Get_Instance()->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos++; //カーソルを下に移動
		count = 0; //カウンターを初期化
	}

	cursor_pos %= 4; //カーソルを合わせる

	//選択肢の状態を更新
	for (int i = 0; i < 4; i++)
	{
		if (i == cursor_pos) {
			choice[i].ex_rate = 1.1f + (0.1f * sinf(PI * 2.f / 90.f * count)); //選択されている場合は拡大、縮小を繰り返す
		}
		else {
			choice[i].ex_rate = 1.f; //選択されていなければ等倍
		}
	}

	if (Key::Get_Instance()->KeyCheckOnce(Jump)){ //決定キーが押されていたら
		Sound::Get_Instance()->PlaySoundEffect(1); //効果音を鳴らす
		return_flag = true; //帰還フラグを立てる
		//カーソルの位置によって遷移先を変更
		switch (cursor_pos)
		{
		case 0:
			//modechanger->ChangeMode(Next_StageSelect); //モードをステージセレクトに変更
			param.SetStageNum(0); //ステージ番号を設定
			modechanger->ChangeMode(Next_Game); //モードをゲームに変更
			break;
		case 1:
			modechanger->ChangeMode(Next_Option); //モードをオプションに変更
			break;
		case 2:
			modechanger->ChangeMode(Next_Config); //モードをキーコンフィグに変更
			break;
		case 3:
			PostMessageA(GetMainWindowHandle(), WM_CLOSE, 0, 0);
			break;
		default:
			break;
		}
	}

	/*if (Key::Get_Instance()->KeyCheckOnce(Attack)){ //戻るボタンが押されていたら
		Sound::Get_Instance()->PlaySoundEffect(2); //効果音を鳴らす
		modechanger->ChangeMode(Next_Back); //オープニングに戻る
	}*/

	count = (count + 1) % 90;//カウンターを増加
}

//描画
void Menu::Draw(){
	
	int image = Image::Get_Instance()->GetEffectImage(7, 0); //画像を取得

	int back = Image::Get_Instance()->GetBackImage(4); //背景を取得
	Display::Get_Instance()->FixedDraw(320.f, 240.f, LEFT, 0.f, back); //背景を描画

	//Display::Get_Instance()->FixedDraw(320.f, 96.f, LEFT, 0.f, logo); //ロゴを描画

	for (int i = 0; i < 4; i++)
	{
		Display::Get_Instance()->FixedDraw(480.f, 212.f + (64.f * i), LEFT, 0.f, choice[i].image, choice[i].ex_rate); //選択肢を描画
	}

	//DrawFormatString(128, 0, GetColor(255, 255, 255), "%d", orb[0].trance);
}