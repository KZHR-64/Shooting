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

//������
void EnemyManager::Reset(){
	midboss_flag = false;
	boss_flag = false;
	enemy.clear();
	standby_enemy.clear();
}

//�G���̐ݒ�
void EnemyManager::SetData() {
	FILE *fp;
	char buf[256];
	char *p;
	char *tp;
	char *ctx;
	int num;

	fopen_s(&fp, "data/enemy/enemy_data.csv", "rb");
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
		enemy_data[num].type = atoi(tp); //��ނ��擾
		tp = strtok_s(NULL, ",", &ctx);
		enemy_data[num].hp = atoi(tp); //HP���擾
		tp = strtok_s(NULL, ",", &ctx);
		enemy_data[num].image = atoi(tp); //�摜�̔ԍ����擾
		tp = strtok_s(NULL, ",", &ctx);
		enemy_data[num].size_x = atoi(tp); //���̑傫�����擾
		tp = strtok_s(NULL, ",", &ctx);
		enemy_data[num].size_y = atoi(tp); //�c�̑傫�����擾
		tp = strtok_s(NULL, ",", &ctx);
		enemy_data[num].inhale = (1 == atoi(tp)); //�z�����߂邩���擾
		tp = strtok_s(NULL, ",", &ctx);
		enemy_data[num].rank = atoi(tp); //�i���擾

	}

	fclose(fp);
}

//�����邩�m�F
void EnemyManager::EraseCheck() {
	if (enemy.size() == 0) return;
	float left = (float)Display::Get_Instance()->GetScrollX() - 64.f; //���荶�[
	float right = (float)(Display::Get_Instance()->GetScrollX() + WINDOW_X) + 64.f; //����E�[
	float top = (float)Display::Get_Instance()->GetScrollY() - 64.f; //�����
	float bottom = (float)(Display::Get_Instance()->GetScrollY() + WINDOW_Y) + 64.f; //�����

	for (auto ene = enemy.begin(); ene != enemy.end();) {
		bool erase_flag; //������t���O
		float x = (*ene)->GetX();
		float y = (*ene)->GetY();
		float size_x = 128.f;// *(*ene)->GetSizeX();
		float size_y = 128.f;// *(*ene)->GetSizeY();

		//��ʊO�Ȃ����
		erase_flag = (x < left - size_x || right + size_x < x || y < top - size_y || bottom + size_y < y) && (*ene)->GetBase() == NULL && !(*ene)->GetBossFlag();

		//�����t���O��true�Ȃ����
		if (erase_flag) {
			(*ene)->SetEndFlag(true);
		}
		ene++;
	}

	for (auto ene = enemy.begin(); ene != enemy.end();) {
		//�����t���O��true�Ȃ����
		if ((*ene)->GetEndFlag()) {
			ene = enemy.erase(ene);
		}
		else {
			ene++;
		}
	}
}

//�G���}�b�v�ɔz�u
void EnemyManager::SetStandby(char* file_name) {
	FILE *fp;
	char buf[64];
	int c;
	int i = 0;
	int row = 0; //�s
	int col = 0; //��
	StandbyEnemyDataStruct sta;

	memset(buf, 0, sizeof(buf)); //buf��������
	
	fopen_s(&fp, file_name, "rb");
	if (fp == NULL) DebugBreak(); //�Ȃ���ΏI��

	while (1)
	{
		while (1)
		{
			c = fgetc(fp);
			//�ǂݎ�����������u,�v�����s�A���[�Ȃ�
			if (c == ',' || c == '\n' || c == EOF) {
				break; //���[�v���甲����

			}
			//����ȊO�Ȃ�
			else {
				strcat_s(buf, (const char*)&c); //�������Ȃ���
			}
		}
		//���[�������烋�[�v���甲����
		if (c == EOF){
			break;
		}

		//�ǂݍ��񂾐��l��-1�łȂ����
		if (atoi(buf) != -1) {
			sta.flag = false; //�t���O��false
			sta.num = atoi(buf); //�ԍ���ݒ�
			sta.x = col * 32.f + (enemy_data[sta.num].size_x * 4.f); //x���W��ݒ�
			sta.y = (row + 1) * 32.f - (enemy_data[sta.num].size_y * 4.f); //y���W��ݒ�
			standby_enemy.emplace_back(sta);
		}

		memset(buf, 0, sizeof(buf)); //buf��������

		col++; //�񐔂𑝂₷

		//���s��������񐔂����Z�b�g���čs���𑝂₷
		if (c == '\n') {
			col = 0;
			row++;
		}
	}
	fclose(fp);
}

//�G�̔z�u
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

	new_enemy->SetHp(enemy_data[num].hp); //HP��ݒ�
	new_enemy->SetInhale(enemy_data[num].inhale); //�z�����߂邩�ݒ�
	new_enemy->SetBase(base); //�{�̂�ݒ�
	new_enemy->SetBossFlag(enemy_data[num].rank); //�{�X����ݒ�

	//�i�ɂ���ăt���O�𗧂Ă�
	if (enemy_data[num].rank == 1) midboss_flag = true;
	if (2 <= enemy_data[num].rank){
		boss_flag = true;
		boss_battle = true;
	}

	enemy.emplace_back(new_enemy);

	return new_enemy;
}

//�G���o���ł��邩�m�F
void EnemyManager::SpawnCheck() {
	if (standby_enemy.size() == 0) return;
	float left = (float)Display::Get_Instance()->GetScrollX() - 64.f; //���荶�[
	float right = (float)(Display::Get_Instance()->GetScrollX() + WINDOW_X) + 64.f; //����E�[
	float top = (float)Display::Get_Instance()->GetScrollY() - 64.f; //�����
	float bottom = (float)(Display::Get_Instance()->GetScrollY() + WINDOW_Y) + 64.f; //�����

	for (unsigned int i = 0; i < standby_enemy.size(); i++) {
		int num = standby_enemy[i].num;
		float x = 4.f * enemy_data[num].size_x; //����p
		float y = 4.f * enemy_data[num].size_y; //����p

		//�G���o�����Ă��Ȃ��Ĕ͈͓��ɂ���Ȃ�
		if (!standby_enemy[i].flag && (0 < standby_enemy[i].x - left && standby_enemy[i].x - right < 0 && 0 < standby_enemy[i].y - top && standby_enemy[i].y - bottom < 0)) {
			standby_enemy[i].flag = true; //�o���ς݂�
			SetEnemy(num, standby_enemy[i].x, standby_enemy[i].y); //�G���o��������
		}

		//�o���ς݂Ŕ͈͊O�ɂ���Ȃ�
		if (standby_enemy[i].flag && (4.f * x < left - standby_enemy[i].x || 4.f * x < standby_enemy[i].x - right || 4.f * y < top - standby_enemy[i].y || 4.f * y < standby_enemy[i].y - bottom)) {
			standby_enemy[i].flag = false; //�o�����Ă��Ȃ�������
		}
	}
}

//�L�����N�^�[�Ƃ̓����蔻��
bool EnemyManager::HitCheckChara(float cx, float cy, float hit_size) {
	for (auto ene : enemy) {
		if (ene->HitCheckChara(cx, cy, hit_size)) {
			return true;
		}
	}
	return false;
}

//�z�����ݔ���
shared_ptr<AbstractEnemy> EnemyManager::InhaleCheck(float cx, float cy, float hit_size, bool check_inhaled) {
	for (auto ene : enemy) {
		bool inh_flag = (ene->GetInhale() && !ene->GetInhaledFlag() && !check_inhaled) || (check_inhaled && ene->GetInhaledFlag());
		if (ene->HitCheckChara(cx, cy, hit_size, false) && inh_flag && ene->GetBase() == NULL) {
			return ene;
		}
	}
	return NULL;
}

//�e�ɓ������Ă��邩
void EnemyManager::HitCheckBullet(shared_ptr<BulletManager> bullet, std::shared_ptr<EffectManager> effect) {
	if (enemy.size() == 0) return;

	for (auto ene : enemy) {
		ene->HitCheckBullet(bullet, effect);
	}
}

//�G�ɓ������Ă��邩
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

//�{�X�풆���擾
bool EnemyManager::GetBossFlag() {
	return (boss_flag || midboss_flag);
}

//�{�X��|�������擾
bool EnemyManager::GetBeatBoss() {
	return (boss_battle && !boss_flag);
}

//���@��x���W���擾
float EnemyManager::GetPlayerX() {
	return px;
}

//���@��y���W���擾
float EnemyManager::GetPlayerY() {
	return py;
}

//�X�V
void EnemyManager::Update(shared_ptr<MapChipManager> map, shared_ptr<BulletManager> bullet, shared_ptr<Player> player, shared_ptr<EffectManager> effect) {
	px = player->GetX();
	py = player->GetY();
	if (enemy.size() == 0) {
		boss_flag = false;
		midboss_flag = false;
		return;
	}

	bool boss = false; //�{�X�����邩

	for (auto ene : enemy) {
		//���܂�Ă��Ȃ��Ȃ�
		if (!ene->GetInhaledFlag()) {
			ene->Update(bullet, effect); //���삷��
		}
		ene->AbsUpdate();
		ene->Timer();
		
		ene->AdjustPosition(map);
		
		if (ene->GetBossFlag()) boss = true; //�{�X������΃t���O��true
	}

	//�{�X�����Ȃ��Ȃ�{�X��t���O��false��
	if (!boss) {
		boss_flag = false;
		midboss_flag = false;
	}

	EraseCheck(); //�G���������m�F
}

//�`��
void EnemyManager::Draw(){
	//if (0 < standby_enemy.size()) DrawFormatString(320, 128, GetColor(255, 0, 0), "%d %d %f", boss_flag, midboss_flag, standby_enemy[0].y);

	if (enemy.size() == 0) return;
	for (auto ene : enemy) {
		//���G���Ԓ��͓_�ł���
		if (ene->GetDamaged()) {
			ene->SetTrance(192);
			
		} else {
			ene->SetTrance(256);
		}
		//�{�̂��Ȃ����̂̂ݕ`��(���͖{�̂ɔC����)
		if (ene->GetBase() == NULL) {
			ene->Draw();
		}
		//ene->DrawHit();
	}
}