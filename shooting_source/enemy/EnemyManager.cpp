#pragma once
#include "DxLib.h"
#include "EnemyManager.h"
#include "enemylist/NoMove.h"
#include "enemylist/Raidrone.h"
#include "enemylist/Raidrone2.h"
#include "enemylist/Raidrone3.h"
#include "enemylist/Peckiller.h"
#include "enemylist/Peckiller2.h"
#include "enemylist/Missile.h"
#include "enemylist/JumboRaidrone.h"
#include "enemylist/Desdragud.h"
#include "enemylist/DesdragudArm.h"
#include <math.h>

using namespace std;

EnemyManager::EnemyManager(){
	midboss_flag = false;
	boss_flag = false;
	boss_battle = false;
	px = 0.f;
	py = 0.f;
	SetData();
}

EnemyManager::~EnemyManager(){
	enemy.clear();
	enemy_data.clear();
	standby_enemy.clear();
}

//初期化
void EnemyManager::Reset(){
	midboss_flag = false;
	boss_flag = false;
	enemy.clear();
	standby_enemy.clear();
}

//敵情報の設定
void EnemyManager::SetData() {
	FILE *fp;
	char buf[256];
	char *p;
	char *tp;
	char *ctx;
	int num;

	fopen_s(&fp, "data/enemy/enemy_data.csv", "rb");
	if (fp == NULL) DebugBreak(); //なければ終了

	memset(buf, 0, sizeof(buf)); //bufを初期化

	//ファイルから一行読み
	while (fgets(buf, 256, fp) != NULL)
	{
		p = strchr(buf, (int)'\n'); //改行を検索
		//改行がある場合
		if (p != NULL) {
			*p = '\0'; //改行を削除
		}
		tp = strtok_s(buf, ",", &ctx);
		num = atoi(tp); //番号を取得
		tp = strtok_s(NULL, ",", &ctx);
		enemy_data[num].type = atoi(tp); //種類を取得
		tp = strtok_s(NULL, ",", &ctx);
		enemy_data[num].hp = atoi(tp); //HPを取得
		tp = strtok_s(NULL, ",", &ctx);
		enemy_data[num].image = atoi(tp); //画像の番号を取得
		tp = strtok_s(NULL, ",", &ctx);
		enemy_data[num].size_x = atoi(tp); //横の大きさを取得
		tp = strtok_s(NULL, ",", &ctx);
		enemy_data[num].size_y = atoi(tp); //縦の大きさを取得
		tp = strtok_s(NULL, ",", &ctx);
		enemy_data[num].inhale = (1 == atoi(tp)); //吸い込めるかを取得
		tp = strtok_s(NULL, ",", &ctx);
		enemy_data[num].rank = atoi(tp); //格を取得

	}

	fclose(fp);
}

//消えるか確認
void EnemyManager::EraseCheck() {
	if (enemy.size() == 0) return;
	float left = (float)Display::Get_Instance()->GetScrollX() - 64.f; //判定左端
	float right = (float)(Display::Get_Instance()->GetScrollX() + WINDOW_X) + 64.f; //判定右端
	float top = (float)Display::Get_Instance()->GetScrollY() - 64.f; //判定上
	float bottom = (float)(Display::Get_Instance()->GetScrollY() + WINDOW_Y) + 64.f; //判定底

	for (auto ene = enemy.begin(); ene != enemy.end();) {
		bool erase_flag; //消えるフラグ
		float x = (*ene)->GetX();
		float y = (*ene)->GetY();
		float size_x = 128.f;// *(*ene)->GetSizeX();
		float size_y = 128.f;// *(*ene)->GetSizeY();

		//画面外なら消す
		erase_flag = (x < left - size_x || right + size_x < x || y < top - size_y || bottom + size_y < y) && (*ene)->GetBase() == NULL && !(*ene)->GetBossFlag();

		//消去フラグがtrueなら消去
		if (erase_flag) {
			(*ene)->SetEndFlag(true);
		}
		ene++;
	}

	for (auto ene = enemy.begin(); ene != enemy.end();) {
		//消去フラグがtrueなら消去
		if ((*ene)->GetEndFlag()) {
			ene = enemy.erase(ene);
		}
		else {
			ene++;
		}
	}
}

//敵をマップに配置
void EnemyManager::SetStandby(char* file_name) {
	FILE *fp;
	char buf[64];
	int c;
	int i = 0;
	int row = 0; //行
	int col = 0; //列
	StandbyEnemyDataStruct sta;

	memset(buf, 0, sizeof(buf)); //bufを初期化
	
	fopen_s(&fp, file_name, "rb");
	if (fp == NULL) DebugBreak(); //なければ終了

	while (1)
	{
		while (1)
		{
			c = fgetc(fp);
			//読み取った文字が「,」か改行、末端なら
			if (c == ',' || c == '\n' || c == EOF) {
				break; //ループから抜ける

			}
			//それ以外なら
			else {
				strcat_s(buf, (const char*)&c); //文字をつなげる
			}
		}
		//末端だったらループから抜ける
		if (c == EOF){
			break;
		}

		//読み込んだ数値が-1でなければ
		if (atoi(buf) != -1) {
			sta.flag = false; //フラグはfalse
			sta.num = atoi(buf); //番号を設定
			sta.x = col * 32.f + (enemy_data[sta.num].size_x * 4.f); //x座標を設定
			sta.y = (row + 1) * 32.f - (enemy_data[sta.num].size_y * 4.f); //y座標を設定
			standby_enemy.emplace_back(sta);
		}

		memset(buf, 0, sizeof(buf)); //bufを初期化

		col++; //列数を増やす

		//改行だったら列数をリセットして行数を増やす
		if (c == '\n') {
			col = 0;
			row++;
		}
	}
	fclose(fp);
}

//敵の配置
shared_ptr<AbstractEnemy> EnemyManager::SetEnemy(int num, float ini_x, float ini_y, AbstractEnemy* base) {
	shared_ptr<AbstractEnemy> new_enemy;

	switch (enemy_data[num].type)
	{
	case 0:
		new_enemy = make_shared<NoMove>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 1:
		new_enemy = make_shared <Raidrone>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 2:
		new_enemy = make_shared <Raidrone2>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 3:
		new_enemy = make_shared <Raidrone3>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 4:
		new_enemy = make_shared <Peckiller>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 5:
		new_enemy = make_shared <Peckiller2>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 6:
		new_enemy = make_shared <Missile>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 32:
		new_enemy = make_shared <JumboRaidrone>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 33:
		new_enemy = make_shared <Desdragud>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	case 34:
		new_enemy = make_shared <DesdragudArm>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	default:
		new_enemy = make_shared<NoMove>(this, enemy_data[num].image, ini_x, ini_y);
		break;
	}

	new_enemy->SetHp(enemy_data[num].hp); //HPを設定
	new_enemy->SetInhale(enemy_data[num].inhale); //吸い込めるか設定
	new_enemy->SetBase(base); //本体を設定
	new_enemy->SetBossFlag(enemy_data[num].rank); //ボスかを設定

	//格によってフラグを立てる
	if (enemy_data[num].rank == 1) midboss_flag = true;
	if (2 <= enemy_data[num].rank){
		boss_flag = true;
		boss_battle = true;
	}

	enemy.emplace_back(new_enemy);

	return new_enemy;
}

//敵が出現できるか確認
void EnemyManager::SpawnCheck() {
	if (standby_enemy.size() == 0) return;
	float left = (float)Display::Get_Instance()->GetScrollX() - 64.f; //判定左端
	float right = (float)(Display::Get_Instance()->GetScrollX() + WINDOW_X) + 64.f; //判定右端
	float top = (float)Display::Get_Instance()->GetScrollY() - 64.f; //判定上
	float bottom = (float)(Display::Get_Instance()->GetScrollY() + WINDOW_Y) + 64.f; //判定底

	for (unsigned int i = 0; i < standby_enemy.size(); i++) {
		int num = standby_enemy[i].num;
		float x = 4.f * enemy_data[num].size_x; //判定用
		float y = 4.f * enemy_data[num].size_y; //判定用

		//敵が出現していなくて範囲内にあるなら
		if (!standby_enemy[i].flag && (0 < standby_enemy[i].x - left && standby_enemy[i].x - right < 0 && 0 < standby_enemy[i].y - top && standby_enemy[i].y - bottom < 0)) {
			standby_enemy[i].flag = true; //出現済みに
			SetEnemy(num, standby_enemy[i].x, standby_enemy[i].y); //敵を出現させる
		}

		//出現済みで範囲外にあるなら
		if (standby_enemy[i].flag && (4.f * x < left - standby_enemy[i].x || 4.f * x < standby_enemy[i].x - right || 4.f * y < top - standby_enemy[i].y || 4.f * y < standby_enemy[i].y - bottom)) {
			standby_enemy[i].flag = false; //出現していない扱いに
		}
	}
}

//キャラクターとの当たり判定
bool EnemyManager::HitCheckChara(float cx, float cy, float hit_size) {
	for (auto ene : enemy) {
		if (ene->HitCheckChara(cx, cy, hit_size)) {
			return true;
		}
	}
	return false;
}

//吸い込み判定
shared_ptr<AbstractEnemy> EnemyManager::InhaleCheck(float cx, float cy, float hit_size, bool check_inhaled) {
	for (auto ene : enemy) {
		bool inh_flag = (ene->GetInhale() && !ene->GetInhaledFlag() && !check_inhaled) || (check_inhaled && ene->GetInhaledFlag());
		if (ene->HitCheckChara(cx, cy, hit_size, false) && inh_flag && ene->GetBase() == NULL) {
			return ene;
		}
	}
	return NULL;
}

//弾に当たっているか
void EnemyManager::HitCheckBullet(shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect) {
	if (enemy.size() == 0) return;

	for (auto ene : enemy) {
		ene->HitCheckBullet(bullet, effect);
	}
}

//敵に当たっているか
void EnemyManager::HitCheckEnemy(std::shared_ptr<EffectManager> effect) {
	if (enemy.size() == 0) return;

	for (auto ene : enemy) {
		if (!ene->GetInhaledFlag()) continue;
		float x = ene->GetX();
		float y = ene->GetY();
		for (auto ene2 : enemy) {
			ene2->HitCheckEnemy(x, y, 32.f, effect);
		}
	}
}

//ボス戦中か取得
bool EnemyManager::GetBossFlag() {
	return (boss_flag || midboss_flag);
}

//ボスを倒したか取得
bool EnemyManager::GetBeatBoss() {
	return (boss_battle && !boss_flag);
}

//自機のx座標を取得
float EnemyManager::GetPlayerX() {
	return px;
}

//自機のy座標を取得
float EnemyManager::GetPlayerY() {
	return py;
}

//更新
void EnemyManager::Update(shared_ptr<MapChipManager> map, shared_ptr<BulletManager> bullet, shared_ptr<Player> player, shared_ptr<EffectManager> effect) {
	px = player->GetX();
	py = player->GetY();
	if (enemy.size() == 0) {
		boss_flag = false;
		midboss_flag = false;
		return;
	}

	bool boss = false; //ボスがいるか

	for (auto ene : enemy) {
		//つかまれていないなら
		if (!ene->GetInhaledFlag()) {
			ene->Update(bullet, effect); //動作する
		}
		ene->AbsUpdate();
		ene->Timer();
		
		ene->AdjustPosition(map);
		
		if (ene->GetBossFlag()) boss = true; //ボスがいればフラグはtrue
	}

	//ボスがいないならボス戦フラグをfalseに
	if (!boss) {
		boss_flag = false;
		midboss_flag = false;
	}

	EraseCheck(); //敵を消すか確認
}

//描画
void EnemyManager::Draw(){
	//if (0 < standby_enemy.size()) DrawFormatString(320, 128, GetColor(255, 0, 0), "%d %d %f", boss_flag, midboss_flag, standby_enemy[0].y);

	if (enemy.size() == 0) return;
	for (auto ene : enemy) {
		//無敵時間中は点滅する
		if (ene->GetDamaged()) {
			ene->SetTrance(192);
			
		} else {
			ene->SetTrance(256);
		}
		//本体がないもののみ描画(他は本体に任せる)
		if (ene->GetBase() == NULL) {
			ene->Draw();
		}
		//ene->DrawHit();
	}
}