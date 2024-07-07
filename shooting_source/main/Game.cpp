#pragma once
#include "DxLib.h"
#include "Game.h"

using namespace std;

Game::Game(ModeChanger* changer, Parameter& param) : ModeBase(changer, param) {
	stage_num = param.GetStageNum();
	modechanger = changer;
	player = make_shared<Player>();
	map = make_shared<MapChipManager>(param);
	enemy = make_shared<EnemyManager>();
	bullet = make_shared<BulletManager>();
	effect = make_shared<EffectManager>();
	event = make_shared<EventManager>(param);

	Image::Get_Instance()->LoadCharaImage();
	Image::Get_Instance()->LoadMapchipImage();
	Image::Get_Instance()->LoadBulletImage();

	live = 2; //残機を設定
	pause_flag = false; //ポーズ画面は閉じている
	cursor = 0; //カーソルを初期化

	map->MakeMap(player, enemy, event);
}

Game::~Game(){

	Image::Get_Instance()->DeleteCharaImage();
	Image::Get_Instance()->DeleteMapchipImage();
	Image::Get_Instance()->DeleteBulletImage();
	//Sound::Get_Instance()->StopBgm();
}

//再開
void Game::Restart() {
	player->Reset();
	event->Reset();
	enemy->Reset();
	bullet->Reset();
	effect->Reset();

	map->MakeMap(player, enemy, event);
}

//ゲームの更新
void Game::GameUpdate() {

	bool player_stop = event->GetPlayerStop();
	bool enemy_stop = event->GetEnemyStop();

	//Display::Get_Instance()->SetScrollX(player->GetX());
	//Display::Get_Instance()->SetScrollY(player->GetY());
	
	if (!player_stop) {
		map->Update(player, enemy);
	}
	map->EventHitCheck(event, player->GetX(), player->GetY());
	event->Update(player, enemy, effect, map);

	player_stop = event->GetPlayerStop();
	enemy_stop = event->GetEnemyStop();

	if (!player_stop) {
		player->Update();
	}
	player->AdjustPosition(map, (player_stop || enemy_stop));
	if (!player_stop) {
		player->AttackCheck(bullet, effect);
	}
	if (!enemy_stop) {
		enemy->Update(map, bullet, player, effect);
	}
	bullet->Update(player, enemy, effect);

	effect->Update();

	player->InhaleCheck(map, enemy);
	bullet->HitCheckMap(map);
	enemy->HitCheckBullet(bullet, effect);
	enemy->HitCheckEnemy(effect);
	player->HitCheckEnemy(enemy);
	player->HitCheckBullet(bullet);

	enemy->SpawnCheck();

	//まだクリア判定が出ていない状態で、ボスを倒したなら
	if (!event->GetClearFlag() && enemy->GetBeatBoss()) {
		event->SetEvent(1); //クリア動作のイベントを開始
	}

	//ミスしたなら
	if (player->GetHp() <= 0 && !player_stop) {
		event->AllEventEnd();
		event->SetEvent(2); //ミス動作のイベントを開始
	}

	//+が押されているなら
	if (Key::Get_Instance()->KeyCheckOnce(Plus) && !player_stop) {
		Sound::Get_Instance()->PlaySoundEffect(1); //効果音を鳴らす
		pause_flag = true; //ポーズ画面を開く
	}
}

//ポーズ画面の更新
void Game::PauseUpdate() {
	//上か下が押されているなら
	if (Key::Get_Instance()->KeyCheckOnce(Up) || Key::Get_Instance()->KeyCheckOnce(Down)) {
		cursor = (cursor + 1) % 2; //カーソルを移動
	}

	//決定が押されているなら
	if (Key::Get_Instance()->KeyCheckOnce(Jump)) {
		switch (cursor)
		{
		case 0:
			pause_flag = false; //ポーズ画面を閉じる
			break;
		case 1:
			event->SetClearFlag(true); //ステージセレクトに戻るようにする
			break;
		default:
			break;
		}
	}

	//+が押されているなら
	if (Key::Get_Instance()->KeyCheckOnce(Plus)) {
		pause_flag = false; //ポーズ画面を閉じる
	}
}

//更新
void Game::Update(){
	Parameter param;

	//ポーズ状態なら
	if (pause_flag) {
		PauseUpdate(); //ポーズ画面の更新
	}
	//そうでなければ
	else {
		GameUpdate(); //ゲームの更新
	}

	//クリアしたなら
	if (event->GetClearFlag()) {
		param.SetStageNum(stage_num); //ステージ番号を送る
		modechanger->ChangeMode(Next_Back, param); //一つ前の画面に戻る
	}

	//やりなおすなら
	if (event->GetRestartFlag()) {
		live--; //残機を減らす
		//残機があるなら
		if (0 < live) {
			Restart(); //ミスしたマップから再開する
		}
		else
		{
			modechanger->ChangeMode(Next_Gameover, true); //モードをゲームオーバーに変更
		}
	}
}

//描画
void Game::Draw(){
	map->Draw();
	enemy->Draw();
	player->Draw();
	bullet->Draw();
	effect->Draw();
	event->Draw();
	//DrawFormatString(0, 0, GetColor(0, 0, 255), "ゲーム%d%d%d%d", stage_num, enemy->GetBeatBoss(), enemy->GetBossFlag(), event->GetPlayerStop());

	//ポーズ状態なら
	if (pause_flag) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); //描画モードを反映

		DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(0, 0, 0), true); //画面を暗くする

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //描画モードを戻す
		DrawFormatString(320, 240, GetColor(0, 0, 255), "ポーズ%d", cursor);
	}
}