#pragma once
#include "DxLib.h"
#include "Gameover.h"

Gameover::Gameover(ModeChanger* changer, Parameter& param) : ModeBase(changer, param) {

	Sound::Get_Instance()->LoadBgm(3); //曲を再生
	Image::Get_Instance()->LoadBackImage(4);

	//画像を設定
	for (int i = 0; i < 2; i++)
	{
		select_hundle[i] = Image::Get_Instance()->GetEffectImage(11, i);
	}

	cursor_pos = 0; //cursorの位置を初期化
}

//デストラクタ
Gameover::~Gameover() {
	
}

//初期化
void Gameover::Reset() {

}

//更新
void Gameover::Update(){

	if (Key::Get_Instance()->KeyCheckOnce(Down) || Key::Get_Instance()->KeyCheckOnce(Up)){ //下キーか上キーが押されていたら
		Sound::Get_Instance()->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos = (cursor_pos + 1) % 2; //カーソルを下に移動
	}
	if (Key::Get_Instance()->KeyCheckOnce(Jump)){ //決定キーが押されていたら
		Sound::Get_Instance()->PlaySoundEffect(1); //効果音を鳴らす
		//カーソルの位置によって遷移先を変更
		switch (cursor_pos)
		{
		case 0:
			modechanger->ChangeMode(Next_Game, true); //モードをゲーム画面に変更
			break;
		case 1:
			modechanger->ChangeMode(Next_Back); //モードをステージセレクトに変更
			break;
		default:
			break;
		}
	}
}

//描画
void Gameover::Draw(){
	int back = Image::Get_Instance()->GetBackImage(4); //背景を取得
	Display::Get_Instance()->FixedDraw(320.f, 240.f, LEFT, 0.f, back); //背景を描画

	int blend_mode; //表示方法
	int blend; //文字の明るさ

	//選択によって文字の明るさを変更
	for (int i = 0; i < 2; i++)
	{
		blend_mode = ((cursor_pos == i) ? DX_BLENDMODE_NOBLEND : DX_BLENDMODE_SUB);
		blend = ((cursor_pos == i) ? 1 : 64);
		Display::Get_Instance()->FixedDraw(480.f, 244.f + (96.f * i), LEFT, 0.f, select_hundle[i], 1.f, blend_mode, blend); //選択肢を描画
	}
}