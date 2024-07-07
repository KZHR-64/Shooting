#pragma once
#include "DxLib.h"
#include "StageSelect.h"
#include "Parameter.h"

StageSelect::StageSelect(ModeChanger* changer, Parameter& param) : ModeBase(changer, param) {
	stage_num = param.GetStageNum();
	cursor_pos_x = 0;
	cursor_pos_y = 0;

	message_font = CreateFontToHandle("Meiryo UI", 32, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2); //フォント情報

	Reset();
}

//デストラクタ
StageSelect::~StageSelect() {
	DeleteFontToHandle(message_font);
}

//初期化
void StageSelect::Reset() {
	FILE *fp;
	char buf[512];
	char *p;
	char *tp;
	char *ctx;

	Sound::Get_Instance()->LoadBgm(2); //曲を再生
	Image::Get_Instance()->LoadBackImage(3);

	fopen_s(&fp, "data/subtitle.csv", "r");
	if (fp == NULL) DebugBreak(); //なければ終了

	//設定
	for (int i = 0; i < STAGE_MAX; i++) {
		subtitle[i].select_flag = true;
		subtitle[7].select_flag = false;
		subtitle[i].hundle = Image::Get_Instance()->GetEffectImage(10, 0); //サムネイルを取得

		//サブタイトルを取得
		fgets(buf, 512, fp);
		//選択可能なら
		if (subtitle[i].select_flag) {
			p = strchr(buf, (int)'\n'); //改行を検索
			//改行がある場合
			if (p != NULL) {
				*p = '\0'; //改行を削除
			}
			tp = strtok_s(buf, ",", &ctx);
			subtitle[i].str1 = (std::string)tp;
			tp = strtok_s(NULL, ",", &ctx);
			subtitle[i].str2 = (std::string)tp;
		}
		//選択不可なら
		else {
			subtitle[i].hundle = Image::Get_Instance()->GetEffectImage(10, 0);
			subtitle[i].str1 = "？"; 
			subtitle[i].str2 = "？";
		}
	}

	fclose(fp);

	return_flag = false; //帰還フラグはfalse
}

//情報の更新
void StageSelect::SetData() {

}

//更新
void StageSelect::Update() {
	Parameter param;
	//帰還フラグが立っている場合
	if (return_flag) {
		Reset();
	}

	//ステージ選択
	if (Key::Get_Instance()->KeyCheckOnce(Left)){ //左ボタンが押されていたら
		Sound::Get_Instance()->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos_x = (cursor_pos_x + 3) % 4; //カーソル番号を減らす
	}
	if (Key::Get_Instance()->KeyCheckOnce(Right)){ //右ボタンが押されていたら
		Sound::Get_Instance()->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos_x = (cursor_pos_x + 1) % 4; //カーソル番号を増やす
	}
	if (Key::Get_Instance()->KeyCheckOnce(Up)){ //下ボタンが押されていたら
		Sound::Get_Instance()->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos_y = (cursor_pos_y + 1) % 2; //カーソル番号を減らす
	}
	if (Key::Get_Instance()->KeyCheckOnce(Down)){ //下ボタンが押されていたら
		Sound::Get_Instance()->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos_y = (cursor_pos_y + 1) % 2; //カーソル番号を増やす
	}

	stage_num = (cursor_pos_y * 4) + cursor_pos_x; //ステージ番号を設定
	if (stage_num < 0) {
		stage_num = 0;//ステージ番号が0未満になった場合は0に
	}
	if (STAGE_MAX <= stage_num) {
		stage_num = STAGE_MAX - 1;//ステージ番号が最大を超えた場合は最大値に
		cursor_pos_x = (STAGE_MAX - 1) % 4;
		cursor_pos_y = STAGE_MAX / 4;
	}

	if (Key::Get_Instance()->KeyCheckOnce(Jump)){ //決定ボタンが押されていたら
		//ステージが選択可能なら
		if (subtitle[stage_num].select_flag) {
			Sound::Get_Instance()->PlaySoundEffect(1); //効果音を鳴らす
			return_flag = true; //帰還フラグを立てる
			param.SetStageNum(stage_num); //ステージ番号を設定
			modechanger->ChangeMode(Next_Game, param); //モードをゲームに変更
		}
		//そうでなければ
		else {
			Sound::Get_Instance()->PlaySoundEffect(3); //効果音を鳴らす
		}
	}
	if (Key::Get_Instance()->KeyCheckOnce(Attack)){ //戻るボタンが押されていたら
		Sound::Get_Instance()->PlaySoundEffect(2); //効果音を鳴らす
		modechanger->ChangeMode(Next_Back, param); //メニューに戻る
	}
}

//描画
void StageSelect::Draw() {

	int back = Image::Get_Instance()->GetBackImage(3); //背景を取得
	Display::Get_Instance()->FixedDraw(320.f, 240.f, LEFT, 0.f, back); //背景を描画

	//カーソルを表示
	int cursor_x = 43 + (cursor_pos_x * 136);
	int cursor_y = 68 + (cursor_pos_y * 136);
	DrawBox(cursor_x, cursor_y, cursor_x + 144, cursor_y + 144, GetColor(238, 131, 111), true);

	//サムネイルを表示
	for (int i = 0; i < STAGE_MAX; i++) {
		float x = 43.f + 72.f + ((i % 4) * 136.f);
		float y = 68.f + 72.f + ((i / 4) * 136.f);
		Display::Get_Instance()->FixedDraw(x, y, LEFT, 0.f, subtitle[i].hundle);
	}

	DrawFormatString(0, 30, GetColor(255, 255, 255), "%d", stage_num);
	
	DrawStringToHandle(60, 374, subtitle[stage_num].str1.c_str(), GetColor(236, 236, 236), message_font, GetColor(21, 169, 175));
	DrawStringToHandle(60, 416, subtitle[stage_num].str2.c_str(), GetColor(236, 236, 236), message_font, GetColor(21, 169, 175));
}