#pragma once
#include "DxLib.h"
#include "Mode.h"
#include "Game.h"
#include "StageSelect.h"
#include "Option.h"
#include "KeyConfig.h"
#include "Opening.h"
#include "Menu.h"
#include "Gameover.h"

using namespace std;

Mode::Mode(){
	//Image::Get_Instance()->LoadEffectImage();
	next = Next_None;
	change = false;
	erase = false;
	full_screen = false;
	blackout_time = 0;
	blackout_flag = false; //暗転状態を初期化
	scene_stack.push(make_shared<Opening>(this, param));//(ModeBase*) new Opening(this)); //始めはオープニング画面
}

Mode::~Mode()
{
	//スタックを全開放
	while (!scene_stack.empty())
	{
		scene_stack.pop();
	}
}

//暗転
void Mode::Blackout() {
	//暗転直後の場合
	if (blackout_time == 0) {
		//Sound::Get_Instance()->StopBgm();
	}

	blackout_time++; //暗転時間を増加

	//暗転時間が一定に達した場合
	if (42 < blackout_time) {
		//ウィンドウサイズを変更する場合
		if (change) {
			SetWindowSizeExtendRate(1.0);
			SetWindowSizeChangeEnableFlag(full_screen); //設定を変更
			SetMainWindowText("テスト");
			SetDrawScreen(DX_SCREEN_BACK);
		}
		//現在のモードを消す場合
		if (erase) {
			scene_stack.pop();
		}
		//次に移る
		switch (next){
		case Next_Opening: //オープニングの場合
			scene_stack.push(make_shared<Opening>(this, param));
			break;
		case Next_Menu: //メニュー画面の場合
			scene_stack.push(make_shared<Menu>(this, param));
			break;
		case Next_StageSelect: //ステージセレクト画面の場合
			param.SetStageNum(0);
			scene_stack.push(make_shared<StageSelect>(this, param));
			break;
		case Next_Game: //ゲーム画面の場合
			scene_stack.push(make_shared<Game>(this, param));
			break;
		case Next_Gameover: //ゲームオーバー画面の場合
			scene_stack.push(make_shared<Gameover>(this, param));
			break;
		case Next_Option: //オプション画面の場合
			scene_stack.push(make_shared<Option>(this, param));
			break;
		case Next_Config: //キーコンフィグ画面の場合
			scene_stack.push(make_shared<KeyConfig>(this, param));
			break;
		case Next_Back: //戻る場合
			scene_stack.pop();
			break;
		default:
			break;
		}
		blackout_flag = false; //暗転フラグをfalseに
	}
}

//次のモードにする
void Mode::ChangeMode(NextMode nmode, bool erase_now, bool change_window, bool full){
	next = nmode; //次の場面を設定
	blackout_flag = true; //暗転
	blackout_time = 0; //暗転時間を初期化
	erase = erase_now; //今のモードを消すか
	change = change_window; //ウィンドウを変えるか
	full_screen = full; //フルスクリーンにするか
}

//次のモードにする
void Mode::ChangeMode(NextMode nmode, Parameter &parameter, bool erase_now){
	param.CopyParam(parameter);
	next = nmode; //次の場面を設定
	blackout_flag = true; //暗転
	blackout_time = 0; //暗転時間を初期化
	erase = erase_now; //今のモードを消すか
	change = false; //ウィンドウを変えるか
}

// 前のモードに戻る
void Mode::BackMode() {
	scene_stack.pop();
}

//更新
void Mode::Update(){
	Key::Get_Instance()->Update(); //キーを更新
	
	//暗転中の場合
	if (blackout_flag) {
		Blackout(); //暗転処理
	}
	else {
		scene_stack.top()->Update();
	}
}

//描画
void Mode::Draw(){
	scene_stack.top()->Draw();

	//暗転中の場合
	if (blackout_flag) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (256 / 42) * blackout_time); //描画モードを反映

		DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(0, 0, 0), true); //画面を暗くする

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //描画モードを戻す
	}
}