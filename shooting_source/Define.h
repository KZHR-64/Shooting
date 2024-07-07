#pragma once
#include "DxLib.h"

typedef enum {
	//次の画面
	Next_None,			//変えない
	Next_Opening,		//オープニング画面
	Next_Menu,			//メニュー画面
	Next_StageSelect,	//ステージセレクト画面
	Next_Game,			//ゲーム画面
	Next_Gameover,		//ゲームオーバー画面
	Next_Option,		//オプション画面
	Next_Config,		//キーコンフィグ画面
	Next_Back,			//前に戻る
} NextMode;

typedef enum {
	//キャラの動作
	Move_Stand, //静止
	Move_Walk, //歩行
	Move_Jump, //ジャンプ
	//これ以降はキャラごとに設定
} MoveSet;

const static int WINDOW_X = 640; //画面の大きさ(横)
const static int WINDOW_Y = 480; //画面の大きさ(縦)

const static int BUTTON = 7; //ボタンの総数
const static int RECORD = 12; //保存する、ボタンを押した履歴数
const static int STAGE_MAX = 1; //ステージの総数

const static int VOLUME_MAX = 25; //音量の最大値
const static int VOLUME_SECTION = 10; //1目盛ごとの音量

const static bool LEFT = false; //左向きを表す
const static bool RIGHT = true; //右向きを表す

const static int HP_MAX = 6; //HPの最大値
const static int JUMP_TIME_MAX = 12; //ジャンプで上昇する時間
const static int DAMAGE_TIME_MAX = 10; //ダメージ動作の時間
const static int DAMAGE_INV_TIME = 60; //ダメージを受けたときの無敵時間
const static int CLEAR_MOVE_TIME_MAX = 300; //クリア時の動作時間
const static int WEAPON_MAX = 2; //武器の最大数

const static int MAPCHIP_MAX = 1024; //マップチップの最大数

const static int BACKGROUND_MAX = 2; //背景の最大数

const static int ENEMY_MAX = 32; //敵の最大数
const static int EFFECT_MAX = 64; //エフェクトの最大数

const static int BULLET_MAX = 64; //弾の最大数
const static int PLAYER_BULLET_MAX = 8; //自機の弾の最大数

const static float PI = 3.141592654f;	//円周率