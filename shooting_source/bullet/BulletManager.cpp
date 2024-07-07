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

//������
void BulletManager::Reset(){
	bullet.clear();
}

//�e���̐ݒ�
void BulletManager::SetData() {
	FILE *fp;
	char buf[256];
	char *p;
	char *tp;
	char *ctx;
	int num;

	fopen_s(&fp, "data/bullet/bullet_data.csv", "rb");
	if (fp == NULL) DebugBreak(); //�Ȃ���ΏI��

	memset(buf, 0, sizeof(buf)); //buf��������

	//�t�@�C�������s�ǂ�
	while (fgets(buf, 256, fp) != NULL)
	{
		p = strchr(buf, (int)'\n'); //���s������
		//���s������ꍇ
		if (p != NULL) {
			*p = '\0'; //���s���폜
		}
		tp = strtok_s(buf, ",", &ctx);
		num = atoi(tp); //�ԍ����擾
		tp = strtok_s(NULL, ",", &ctx);
		bullet_data[num].type = atoi(tp); //��ނ��擾
		tp = strtok_s(NULL, ",", &ctx);
		bullet_data[num].image = atoi(tp); //�摜�̔ԍ����擾
		tp = strtok_s(NULL, ",", &ctx);
		tp = strtok_s(NULL, ",", &ctx);
		tp = strtok_s(NULL, ",", &ctx);
		tp = strtok_s(NULL, ",", &ctx);
		bullet_data[num].breakable = (1 == atoi(tp)); //�󂹂邩���擾
		tp = strtok_s(NULL, ",", &ctx);
		bullet_data[num].hit_player = (1 == atoi(tp)); //���@�ɓ����邩���擾
		tp = strtok_s(NULL, ",", &ctx);
		bullet_data[num].hit_enemy = (1 == atoi(tp)); //�G�ɓ����邩���擾
		tp = strtok_s(NULL, ",", &ctx);
		bullet_data[num].hit_map = (1 == atoi(tp)); //�}�b�v�`�b�v�ɓ����邩���擾
		tp = strtok_s(NULL, ",", &ctx);
		bullet_data[num].damage = atoi(tp); //�_���[�W�l���擾

	}

	fclose(fp);
}

//�����邩�m�F
void BulletManager::EraseCheck() {
	if (bullet.size() == 0) return;
	float left = (float)Display::Get_Instance()->GetScrollX(); //��ʍ��[
	float right = (float)(Display::Get_Instance()->GetScrollX() + WINDOW_X); //��ʉE�[
	float top = (float)Display::Get_Instance()->GetScrollY(); //��ʏ�
	float bottom = (float)(Display::Get_Instance()->GetScrollY() + +WINDOW_Y); //��ʒ�

	for (auto bul = bullet.begin(); bul != bullet.end();) {
		bool erase_flag; //������t���O
		float x = (*bul)->GetX();
		float y = (*bul)->GetY();
		int end_time = (*bul)->GetEndTime(); //������܂ł̎���
		
		//��ʊO�Ȃ����
		erase_flag = (x < left - 64.f || right + 64.f < x || y < top - 64.f || bottom + 64.f < y);

		//������܂ł̎��Ԃ�0���傫���Ȃ�
		if (0 < end_time) {
			end_time--; //���Ԃ����炷
			//���Ԃ�0�ɂȂ����������
			if (end_time <= 0) erase_flag = true;
			(*bul)->SetEndTime(end_time); //���Ԃ�ݒ�
		}

		//�����t���O��true�Ȃ����
		if ((*bul)->GetEndFlag() || erase_flag) {
			bul = bullet.erase(bul);
		}
		else {
			bul++;
		}
	}
}

//�e�̔z�u
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

	new_bullet->SetDamage(bullet_data[num].damage); //�_���[�W�l��ݒ�
	new_bullet->SetBreakable(bullet_data[num].breakable); //�󂹂邩�ݒ�
	new_bullet->SetHitPlayer(bullet_data[num].hit_player); //���@�ɓ����邩�ݒ�
	new_bullet->SetHitEnemy(bullet_data[num].hit_enemy); //�G�ɓ����邩�ݒ�
	new_bullet->SetHitMap(bullet_data[num].hit_map); //�}�b�v�`�b�v�ɓ����邩�ݒ�

	bullet.emplace_back(new_bullet);

	return new_bullet;
}

//�}�b�v�`�b�v�Ƃ̓����蔻��
void BulletManager::HitCheckMap(shared_ptr<MapChipManager> map) {
	if (bullet.size() == 0) return;
	for (auto bul : bullet) {
		bul->HitCheckMap(map);
	}
}

//�L�����N�^�[�Ƃ̓����蔻��
int BulletManager::HitCheckChara(float cx, float cy, float hit_size, bool check_player, bool check_enemy) {
	int damage = 0; //�_���[�W�l
	for (auto bul : bullet) {
		if (!((check_player && bul->GetHitPlayer()) || (check_enemy && bul->GetHitEnemy()))) continue;
		int bullet_damage = bul->HitCheckChara(cx, cy, hit_size); //�_���[�W�l
		//�_���[�W�l������A�O�̂��̂��傫���Ȃ�
		if (damage < bullet_damage) {
			damage = bullet_damage; //�_���[�W�l���X�V
		}
	}
	return damage;
}

//���@��x���W���擾
float BulletManager::GetPlayerX() {
	return px;
}

//���@��y���W���擾
float BulletManager::GetPlayerY() {
	return py;
}

//�X�V
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

	EraseCheck(); //�e���������m�F
}

//�`��
void BulletManager::Draw(){
	if (bullet.size() == 0) return;
	for (auto bul : bullet) {
		bul->Draw();
		bul->DrawHit();
	}
	//DrawFormatString(64, 96, GetColor(255, 255, 255), "%d", bullet.size());
}