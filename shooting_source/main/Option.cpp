#pragma once
#include "DxLib.h"
#include "Option.h"

Option::Option(ModeChanger* changer, Parameter& param) : ModeBase(changer, param) {
	Reset();

	cursor_pos = 0; //cursorの位置を初期化

	LoadSetting();
}

Option::~Option() {
	
}

//初期化
void Option::Reset() {
	Sound::Get_Instance()->LoadBgm(1); //曲を再生
	Image::Get_Instance()->LoadBackImage(1);
	
	//画像を設定
	on_hundle = Image::Get_Instance()->GetEffectImage(3, 1);
	off_hundle = Image::Get_Instance()->GetEffectImage(3, 0);
	volume_hundle = Image::Get_Instance()->GetEffectImage(4, 0);
	graduation_hundle = Image::Get_Instance()->GetEffectImage(5, 0);
	
	return_flag = false; //帰還フラグはfalse
}

//設定の読み込み
void Option::LoadSetting() {
	FILE *fp;
	char buf[256];

	fopen_s(&fp, "config.dat", "rb"); //設定を読み込む

	//なければデフォルト
	if (fp == NULL) {
		setting.fps_flag = Fps::Get_Instance()->GetDrawFlag();
		setting.full_screen = true;
		setting.volume_bgm = Sound::Get_Instance()->GetBgmVolume();
		setting.volume_effect = Sound::Get_Instance()->GetSoundVolume();
	}
	else {
		memset(buf, 0, sizeof(buf)); //メモリをセット

		fread(&setting, sizeof(setting), 1, fp);
		fclose(fp);
	}

	initial_fullscreen = setting.full_screen; //画面開いた直後の設定
}

//設定の保存
void Option::SaveSetting() {
	FILE *fp;

	fopen_s(&fp, "config.dat", "wb"); //設定の入ったファイルを開く

	fwrite(&setting, sizeof(setting), 1, fp); //ファイルに設定を書き込む

	fclose(fp);
}

//更新
void Option::Update(){
	//帰還フラグが立っている場合
	if (return_flag) {
		Reset();
	}

	//上キーが押されていたら
	if (Key::Get_Instance()->KeyCheckOnce(Up)){
		Sound::Get_Instance()->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos = (cursor_pos - 1); //カーソルを上に移動
	}

	//下キーが押されていたら
	if (Key::Get_Instance()->KeyCheckOnce(Down)){
		Sound::Get_Instance()->PlaySoundEffect(0); //効果音を鳴らす
		cursor_pos = (cursor_pos + 1); //カーソルを下に移動
	}

	if (cursor_pos < 0) cursor_pos = 0;
	if (3 < cursor_pos) cursor_pos = 3;

	//左右の入力情報を取得
	bool left = Key::Get_Instance()->KeyCheckOnce(Left);
	bool right = Key::Get_Instance()->KeyCheckOnce(Right);

	if (left || right){
		//カーソル位置で処理を決定
		switch (cursor_pos)
		{
		case 0:
			//fps表示
			setting.fps_flag = !setting.fps_flag;
			Fps::Get_Instance()->SetDrawFlag(setting.fps_flag);
			break;
		case 1:
			//フルスクリーン表示
			setting.full_screen = !setting.full_screen;
			break;
		case 2:
			//BGM音量
			if (left) {
				setting.volume_bgm--;
			}
			else if (right) {
				setting.volume_bgm++;
			}
			//音量を調整
			if (setting.volume_bgm < 0) {
				setting.volume_bgm = 0;
			}
			if (VOLUME_MAX < setting.volume_bgm) {
				setting.volume_bgm = VOLUME_MAX;
			}
			Sound::Get_Instance()->SetBgmVolume(setting.volume_bgm); //音量を設定
			break;
		case 3:
			//効果音音量
			if (left) {
				setting.volume_effect--;
			}
			else if (right) {
				setting.volume_effect++;
			}
			//音量を調整
			if (setting.volume_effect < 0) {
				setting.volume_effect = 0;
			}
			if (VOLUME_MAX < setting.volume_effect) {
				setting.volume_effect = VOLUME_MAX;
			}
			Sound::Get_Instance()->SetSoundVolume(setting.volume_effect); //音量を設定
			break;
		default:
			break;
		}
		Sound::Get_Instance()->PlaySoundEffect(0); //効果音を鳴らす
	}

	//決定キーが押されていたら
	if (Key::Get_Instance()->KeyCheckOnce(Jump)){
		Sound::Get_Instance()->PlaySoundEffect(1); //効果音を鳴らす

		SaveSetting(); //設定を保存する
		return_flag = true; //帰還フラグを立てる

		bool change = (initial_fullscreen != setting.full_screen); //ウィンドウサイズを変えるか

		modechanger->ChangeMode(Next_Back, false, change, setting.full_screen); //メニューに戻る
	}
}

//描画
void Option::Draw(){
	int back = Image::Get_Instance()->GetBackImage(1); //背景を取得
	Display::Get_Instance()->FixedDraw(320.f, 240.f, LEFT, 0.f, back); //背景を描画

	int blend_mode; //表示方法
	int blend; //文字の明るさ

	//FPS
	//選択によって文字の明るさを変更
	blend_mode = (setting.fps_flag ? DX_BLENDMODE_SUB : DX_BLENDMODE_NOBLEND);
	blend = (setting.fps_flag ? 96 : 1);
	Display::Get_Instance()->FixedDraw(344.f, 144.f, LEFT, 0.f, off_hundle, 1.f, blend_mode, blend); //選択肢を描画
	blend_mode = (setting.fps_flag ? DX_BLENDMODE_NOBLEND : DX_BLENDMODE_SUB);
	blend = (setting.fps_flag ? 1 : 96);
	Display::Get_Instance()->FixedDraw(504.f, 144.f, LEFT, 0.f, on_hundle, 1.f, blend_mode, blend);

	//フルスクリーン
	//選択によって文字の明るさを変更
	blend_mode = (setting.full_screen ? DX_BLENDMODE_SUB : DX_BLENDMODE_NOBLEND);
	blend = (setting.full_screen ? 96 : 1);
	Display::Get_Instance()->FixedDraw(344.f, 208.f, LEFT, 0.f, off_hundle, 1.f, blend_mode, blend);
	blend_mode = (setting.full_screen ? DX_BLENDMODE_NOBLEND : DX_BLENDMODE_SUB);
	blend = (setting.full_screen ? 1 : 96);
	Display::Get_Instance()->FixedDraw(504.f, 208.f, LEFT, 0.f, on_hundle, 1.f, blend_mode, blend);

	//音量
	Display::Get_Instance()->FixedDraw(424.f, 272.f, LEFT, 0.f, volume_hundle);
	for (int i = 0; i < setting.volume_bgm; i++)
	{
		Display::Get_Instance()->FixedDraw(278.f + (12.f * i), 272.f, LEFT, 0.f, graduation_hundle);
	}

	Display::Get_Instance()->FixedDraw(424.f, 336.f, LEFT, 0.f, volume_hundle);
	for (int i = 0; i < setting.volume_effect; i++)
	{
		Display::Get_Instance()->FixedDraw(278.f + (12.f * i), 336.f, LEFT, 0.f, graduation_hundle);
	}

	//選択した位置以外は少し暗くする
	for (int i = 0; i < 4; i++)
	{
		if (i == cursor_pos) continue;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 112 + (64 * i), 640, 176 + (64 * i), GetColor(128, 128, 128), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}