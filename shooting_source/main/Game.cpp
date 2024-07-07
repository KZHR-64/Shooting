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

	live = 2; //�c�@��ݒ�
	pause_flag = false; //�|�[�Y��ʂ͕��Ă���
	cursor = 0; //�J�[�\����������

	map->MakeMap(player, enemy, event);
}

Game::~Game(){

	Image::Get_Instance()->DeleteCharaImage();
	Image::Get_Instance()->DeleteMapchipImage();
	Image::Get_Instance()->DeleteBulletImage();
	//Sound::Get_Instance()->StopBgm();
}

//�ĊJ
void Game::Restart() {
	player->Reset();
	event->Reset();
	enemy->Reset();
	bullet->Reset();
	effect->Reset();

	map->MakeMap(player, enemy, event);
}

//�Q�[���̍X�V
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

	//�܂��N���A���肪�o�Ă��Ȃ���ԂŁA�{�X��|�����Ȃ�
	if (!event->GetClearFlag() && enemy->GetBeatBoss()) {
		event->SetEvent(1); //�N���A����̃C�x���g���J�n
	}

	//�~�X�����Ȃ�
	if (player->GetHp() <= 0 && !player_stop) {
		event->AllEventEnd();
		event->SetEvent(2); //�~�X����̃C�x���g���J�n
	}

	//+��������Ă���Ȃ�
	if (Key::Get_Instance()->KeyCheckOnce(Plus) && !player_stop) {
		Sound::Get_Instance()->PlaySoundEffect(1); //���ʉ���炷
		pause_flag = true; //�|�[�Y��ʂ��J��
	}
}

//�|�[�Y��ʂ̍X�V
void Game::PauseUpdate() {
	//�ォ����������Ă���Ȃ�
	if (Key::Get_Instance()->KeyCheckOnce(Up) || Key::Get_Instance()->KeyCheckOnce(Down)) {
		cursor = (cursor + 1) % 2; //�J�[�\�����ړ�
	}

	//���肪������Ă���Ȃ�
	if (Key::Get_Instance()->KeyCheckOnce(Jump)) {
		switch (cursor)
		{
		case 0:
			pause_flag = false; //�|�[�Y��ʂ����
			break;
		case 1:
			event->SetClearFlag(true); //�X�e�[�W�Z���N�g�ɖ߂�悤�ɂ���
			break;
		default:
			break;
		}
	}

	//+��������Ă���Ȃ�
	if (Key::Get_Instance()->KeyCheckOnce(Plus)) {
		pause_flag = false; //�|�[�Y��ʂ����
	}
}

//�X�V
void Game::Update(){
	Parameter param;

	//�|�[�Y��ԂȂ�
	if (pause_flag) {
		PauseUpdate(); //�|�[�Y��ʂ̍X�V
	}
	//�����łȂ����
	else {
		GameUpdate(); //�Q�[���̍X�V
	}

	//�N���A�����Ȃ�
	if (event->GetClearFlag()) {
		param.SetStageNum(stage_num); //�X�e�[�W�ԍ��𑗂�
		modechanger->ChangeMode(Next_Back, param); //��O�̉�ʂɖ߂�
	}

	//���Ȃ����Ȃ�
	if (event->GetRestartFlag()) {
		live--; //�c�@�����炷
		//�c�@������Ȃ�
		if (0 < live) {
			Restart(); //�~�X�����}�b�v����ĊJ����
		}
		else
		{
			modechanger->ChangeMode(Next_Gameover, true); //���[�h���Q�[���I�[�o�[�ɕύX
		}
	}
}

//�`��
void Game::Draw(){
	map->Draw();
	enemy->Draw();
	player->Draw();
	bullet->Draw();
	effect->Draw();
	event->Draw();
	//DrawFormatString(0, 0, GetColor(0, 0, 255), "�Q�[��%d%d%d%d", stage_num, enemy->GetBeatBoss(), enemy->GetBossFlag(), event->GetPlayerStop());

	//�|�[�Y��ԂȂ�
	if (pause_flag) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); //�`�惂�[�h�𔽉f

		DrawBox(0, 0, WINDOW_X, WINDOW_Y, GetColor(0, 0, 0), true); //��ʂ��Â�����

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //�`�惂�[�h��߂�
		DrawFormatString(320, 240, GetColor(0, 0, 255), "�|�[�Y%d", cursor);
	}
}