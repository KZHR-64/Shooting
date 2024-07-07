#pragma once
#include "DxLib.h"
#include "BulletManager.h"
#include "bulletlist/StraightShoot.h"
#include "bulletlist/PlayerShoot.h"
#include "bulletlist/SpreadShoot.h"
#include "bulletlist/DesdragudShoot.h"
#include "bulletlist/FallBomber.h"

using namespace std;

BulletManager::BulletManager(){
	SetData();

	px = 0.f;
	py = 0.f;
}

BulletManager::~BulletManager(){
	bullet.clear();
	bullet_data.clear();
}

//初期化
void BulletManager::Reset(){
	bullet.clear();
}

//弾情報の設定
void BulletManager::SetData() {
	FILE *fp;
	char buf[256];
	char *p;
	char *tp;
	char *ctx;
	int num;

	fopen_s(&fp, "data/bullet/bullet_data.csv", "rb");
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
		bullet_data[num].type = atoi(tp); //種類を取得
		tp = strtok_s(NULL, ",", &ctx);
		bullet_data[num].image = atoi(tp); //画像の番号を取得
		tp = strtok_s(NULL, ",", &ctx);
		tp = strtok_s(NULL, ",", &ctx);
		tp = strtok_s(NULL, ",", &ctx);
		tp = strtok_s(NULL, ",", &ctx);
		bullet_data[num].breakable = (1 == atoi(tp)); //壊せるかを取得
		tp = strtok_s(NULL, ",", &ctx);
		bullet_data[num].hit_player = (1 == atoi(tp)); //自機に当たるかを取得
		tp = strtok_s(NULL, ",", &ctx);
		bullet_data[num].hit_enemy = (1 == atoi(tp)); //敵に当たるかを取得
		tp = strtok_s(NULL, ",", &ctx);
		bullet_data[num].hit_map = (1 == atoi(tp)); //マップチップに当たるかを取得
		tp = strtok_s(NULL, ",", &ctx);
		bullet_data[num].damage = atoi(tp); //ダメージ値を取得

	}

	fclose(fp);
}

//消えるか確認
void BulletManager::EraseCheck() {
	if (bullet.size() == 0) return;
	float left = (float)Display::Get_Instance()->GetScrollX(); //画面左端
	float right = (float)(Display::Get_Instance()->GetScrollX() + WINDOW_X); //画面右端
	float top = (float)Display::Get_Instance()->GetScrollY(); //画面上
	float bottom = (float)(Display::Get_Instance()->GetScrollY() + +WINDOW_Y); //画面底

	for (auto bul = bullet.begin(); bul != bullet.end();) {
		bool erase_flag; //消えるフラグ
		float x = (*bul)->GetX();
		float y = (*bul)->GetY();
		int end_time = (*bul)->GetEndTime(); //消えるまでの時間
		
		//画面外なら消す
		erase_flag = (x < left - 64.f || right + 64.f < x || y < top - 64.f || bottom + 64.f < y);

		//消えるまでの時間が0より大きいなら
		if (0 < end_time) {
			end_time--; //時間を減らす
			//時間が0になったら消える
			if (end_time <= 0) erase_flag = true;
			(*bul)->SetEndTime(end_time); //時間を設定
		}

		//消去フラグがtrueなら消去
		if ((*bul)->GetEndFlag() || erase_flag) {
			bul = bullet.erase(bul);
		}
		else {
			bul++;
		}
	}
}

//弾の配置
shared_ptr<AbstractBullet> BulletManager::SetBullet(int num, float ini_x, float ini_y, float speed, float angle) {
	shared_ptr<AbstractBullet> new_bullet;

	switch (bullet_data[num].type)
	{
	case 0:
		new_bullet = make_shared<StraightShoot>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	case 1:
		new_bullet = make_shared<PlayerShoot>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	case 2:
		new_bullet = make_shared<SpreadShoot>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	case 3:
		new_bullet = make_shared<DesdragudShoot>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	default:
		new_bullet = make_shared<StraightShoot>(this, bullet_data[num].image, ini_x, ini_y, speed, angle);
		break;
	}

	new_bullet->SetDamage(bullet_data[num].damage); //ダメージ値を設定
	new_bullet->SetBreakable(bullet_data[num].breakable); //壊せるか設定
	new_bullet->SetHitPlayer(bullet_data[num].hit_player); //自機に当たるか設定
	new_bullet->SetHitEnemy(bullet_data[num].hit_enemy); //敵に当たるか設定
	new_bullet->SetHitMap(bullet_data[num].hit_map); //マップチップに当たるか設定

	bullet.emplace_back(new_bullet);

	return new_bullet;
}

//マップチップとの当たり判定
void BulletManager::HitCheckMap(shared_ptr<MapChipManager> map) {
	if (bullet.size() == 0) return;
	for (auto bul : bullet) {
		bul->HitCheckMap(map);
	}
}

//キャラクターとの当たり判定
int BulletManager::HitCheckChara(float cx, float cy, float hit_size, bool check_player, bool check_enemy) {
	int damage = 0; //ダメージ値
	for (auto bul : bullet) {
		if (!((check_player && bul->GetHitPlayer()) || (check_enemy && bul->GetHitEnemy()))) continue;
		int bullet_damage = bul->HitCheckChara(cx, cy, hit_size); //ダメージ値
		//ダメージ値があり、前のものより大きいなら
		if (damage < bullet_damage) {
			damage = bullet_damage; //ダメージ値を更新
		}
	}
	return damage;
}

//自機のx座標を取得
float BulletManager::GetPlayerX() {
	return px;
}

//自機のy座標を取得
float BulletManager::GetPlayerY() {
	return py;
}

//更新
void BulletManager::Update(shared_ptr<Player> player, shared_ptr<EnemyManager> enemy, shared_ptr<EffectManager> effect){
	px = player->GetX();
	py = player->GetY();
	if (bullet.size() == 0) return;
	for (auto bul : bullet) {
		
		bul->Update(enemy, effect);
		
		bul->SetX(bul->GetX() + bul->GetXSpeed());
		bul->SetY(bul->GetY() + bul->GetYSpeed());
		int time = bul->GetTime();
		time++;
		bul->SetTime(time);
		bul->HitUpdate();
	}

	EraseCheck(); //弾を消すか確認
}

//描画
void BulletManager::Draw(){
	if (bullet.size() == 0) return;
	for (auto bul : bullet) {
		bul->Draw();
		bul->DrawHit();
	}
	//DrawFormatString(64, 96, GetColor(255, 255, 255), "%d", bullet.size());
}