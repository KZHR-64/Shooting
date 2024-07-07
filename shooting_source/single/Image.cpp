#pragma once
#include "Image.h"
#include "DxLib.h"
#include <iostream>

//�R���X�g���N�^
Image::Image() {
	LoadMapchipConvertData(); //�}�b�v�`�b�v�ԍ��ϊ�����ǂݍ���
	LoadMapchipData(); //�}�b�v�`�b�v����ǂݍ���
	LoadBackData(); //�w�i����ǂݍ���
	LoadCharaData(); //�L�����̉摜����ǂݍ���
	LoadEffectData(); //�G�t�F�N�g�̉摜����ǂݍ���
	LoadBulletData(); //�e�̉摜����ǂݍ���
}

//�f�X�g���N�^
Image::~Image() {
	image_hundle.clear();
	mapchip_convert.clear();
	enemy_graphic_data.clear();
	effect_graphic_data.clear();
	bullet_graphic_data.clear();
	mapchip_graphic_data.clear();
	back_data.clear();
	DeleteMapchipImage();
	DeleteBackImage();
	DeleteCharaImage();
	DeleteEffectImage();
	DeleteBulletImage();
}

//������
void Image::Reset() {
	image_hundle.clear();
	DeleteBackImage();
	DeleteCharaImage();
	DeleteEffectImage();
	DeleteBulletImage();
	LoadBackData(); //�w�i����ǂݍ���
	LoadCharaData(); //�L�����̉摜����ǂݍ���
	LoadEffectData(); //�G�t�F�N�g�̉摜����ǂݍ���
	LoadBulletData(); //�e�̉摜����ǂݍ���
}

//�}�b�v�`�b�v���̓ǂݍ���
void Image::LoadMapchipData() {
	FILE *fp;
	char buf[256];
	char *p;
	char *tp;
	char *ctx;
	int num;

	fopen_s(&fp, "data/graphic/mapchip/mapchip_graphic.csv", "r"); //�}�b�v�`�b�v�̏���ǂݍ���
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
		sprintf_s(mapchip_graphic_data[num].name, "%s%s", "data/graphic/mapchip/", tp); //�t�@�C�������i�[
		tp = strtok_s(NULL, ",", &ctx);
		mapchip_graphic_data[num].num_x = atoi(tp); //�摜�̖����i���j��ݒ�
		tp = strtok_s(NULL, ",", &ctx);
		mapchip_graphic_data[num].num_y = atoi(tp); //�摜�̖����i�c�j��ݒ�
		tp = strtok_s(NULL, ",", &ctx);
		mapchip_graphic_data[num].size_x = atoi(tp); //�摜�̑傫���i���j��ݒ�
		tp = strtok_s(NULL, ",", &ctx);
		mapchip_graphic_data[num].size_y = atoi(tp); //�摜�̑傫���i�c�j��ݒ�
	}

	fclose(fp);
}

//�}�b�v�`�b�v�ԍ��ϊ����̓ǂݍ���
void Image::LoadMapchipConvertData() {
	FILE *fp;
	char buf[256];
	char *p;
	char *tp;
	char *ctx;
	int num;

	fopen_s(&fp, "data/graphic/mapchip/mapchip_convert.csv", "r"); //�ϊ��̏���ǂݍ���
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
		mapchip_convert[num].key_num = atoi(tp); //�匳�̉摜�ԍ���ݒ�
		tp = strtok_s(NULL, ",", &ctx);
		mapchip_convert[num].image_num = atoi(tp); //�g�p����摜�ԍ���ݒ�
	}

	fclose(fp);
}

//�w�i���̓ǂݍ���
void Image::LoadBackData() {
	FILE *fp;
	char buf[256];
	char *p;
	char *tp;
	char *ctx;
	int num;

	fopen_s(&fp, "data/graphic/back/back_data.csv", "r"); //�w�i�̏���ǂݍ���
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
		sprintf_s(back_data[num].name, "%s%s", "data/graphic/back/", tp); //�t�@�C�������i�[
	}

	fclose(fp);
}

//�L�����摜���̓ǂݍ���
void Image::LoadCharaData() {
	FILE *fp;
	char buf[256];
	char *p;
	char *tp;
	char *ctx;
	int num;

	fopen_s(&fp, "data/graphic/character/character_graphic.csv", "r"); //�L�����摜�̏���ǂݍ���
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
		sprintf_s(enemy_graphic_data[num].name, "%s%s", "data/graphic/character/", tp); //�t�@�C�������i�[
		tp = strtok_s(NULL, ",", &ctx);
		enemy_graphic_data[num].num_x = atoi(tp); //�摜�̖����i���j��ݒ�
		tp = strtok_s(NULL, ",", &ctx);
		enemy_graphic_data[num].num_y = atoi(tp); //�摜�̖����i�c�j��ݒ�
		tp = strtok_s(NULL, ",", &ctx);
		enemy_graphic_data[num].size_x = atoi(tp); //�摜�̑傫���i���j��ݒ�
		tp = strtok_s(NULL, ",", &ctx);
		enemy_graphic_data[num].size_y = atoi(tp); //�摜�̑傫���i�c�j��ݒ�
	}

	fclose(fp);
}

//�G�t�F�N�g�摜���̓ǂݍ���
void Image::LoadEffectData() {
	FILE *fp;
	char buf[256];
	char *p;
	char *tp;
	char *ctx;
	int num;

	fopen_s(&fp, "data/graphic/effect/effect_graphic.csv", "r"); //�w�i�̏���ǂݍ���
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
		sprintf_s(effect_graphic_data[num].name, "%s%s", "data/graphic/effect/", tp); //�t�@�C�������i�[
		tp = strtok_s(NULL, ",", &ctx);
		effect_graphic_data[num].num_x = atoi(tp); //�摜�̖����i���j��ݒ�
		tp = strtok_s(NULL, ",", &ctx);
		effect_graphic_data[num].num_y = atoi(tp); //�摜�̖����i�c�j��ݒ�
		tp = strtok_s(NULL, ",", &ctx);
		effect_graphic_data[num].size_x = atoi(tp); //�摜�̑傫���i���j��ݒ�
		tp = strtok_s(NULL, ",", &ctx);
		effect_graphic_data[num].size_y = atoi(tp); //�摜�̑傫���i�c�j��ݒ�
	}

	fclose(fp);
}

//�e�摜���̓ǂݍ���
void Image::LoadBulletData() {
	FILE *fp;
	char buf[256];
	char *p;
	char *tp;
	char *ctx;
	int num;

	fopen_s(&fp, "data/graphic/bullet/bullet_graphic.csv", "r"); //�w�i�̏���ǂݍ���
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
		sprintf_s(bullet_graphic_data[num].name, "%s%s", "data/graphic/bullet/", tp); //�t�@�C�������i�[
		tp = strtok_s(NULL, ",", &ctx);
		bullet_graphic_data[num].num_x = atoi(tp); //�摜�̖����i���j��ݒ�
		tp = strtok_s(NULL, ",", &ctx);
		bullet_graphic_data[num].num_y = atoi(tp); //�摜�̖����i�c�j��ݒ�
		tp = strtok_s(NULL, ",", &ctx);
		bullet_graphic_data[num].size_x = atoi(tp); //�摜�̑傫���i���j��ݒ�
		tp = strtok_s(NULL, ",", &ctx);
		bullet_graphic_data[num].size_y = atoi(tp); //�摜�̑傫���i�c�j��ݒ�
	}

	fclose(fp);
}

//�}�b�v�`�b�v�̉摜�����[�h
void Image::LoadMapImage() {
	LoadDivGraph("data/graphic/mapchip/mapchip.png", 44, 22, 2, 32, 32, map_image); //�}�b�v�`�b�v�̉摜�����[�h

	warp_image = LoadGraph("data/graphic/mapchip/warp.png"); //���[�v�n�_�̉摜�����[�h
}

//�}�b�v�`�b�v�̉摜��Ԃ�(�摜�̔ԍ�)
int Image::GetMapImage(int num) {
	return map_image[num];
}

//���[�v�n�_�̉摜��Ԃ� 
int Image::GetWarpImage() {
	return warp_image;
}

//�}�b�v�`�b�v�̉摜���폜
void Image::DeleteMapImage() {
	int size = sizeof(map_image) / sizeof(int);
	for (int i = 0; i < size; i++)
	{
		DeleteGraph(map_image[i]);
	}
	DeleteGraph(warp_image);
}

//�}�b�v�`�b�v�̉摜�����[�h
void Image::LoadMapchipImage() {
	// �L�����摜�̃��������m��
	for each (auto var in mapchip_graphic_data)
	{
		int image_num = var.second.num_x * var.second.num_y; //�摜�̑���
		int *eimage = new int[image_num]; //��U�摜������ϐ�

		LoadDivGraph(var.second.name, image_num, var.second.num_x, var.second.num_y, var.second.size_x, var.second.size_y, eimage); //�摜�����[�h

		for (int i = 0; i < image_num; i++)
		{
			mapchip_image[var.first].push_back(eimage[i]); //�摜������
		}
	}
}

//�}�b�v�`�b�v�̉摜��Ԃ�
int Image::GetMapchipImage(int image_num) {
	int key_num = mapchip_convert[image_num].key_num;
	int image = mapchip_convert[image_num].image_num;

	//�摜��T��
	auto einum = mapchip_image.find(key_num); //�摜������
	//�������ꍇ
	if (einum != mapchip_image.end()) {
		if ((unsigned)image < mapchip_image[key_num].size()) {
			return mapchip_image[key_num][image]; //�摜��Ԃ�
		}
	}
	return -1;
}

//�}�b�v�`�b�v�̉摜��Ԃ�
int Image::GetMapchipImage(int map_num, int image_num) {
	//�摜��T��
	auto einum = mapchip_image.find(map_num); //�摜������
	//�������ꍇ
	if (einum != mapchip_image.end()) {
		if ((unsigned)image_num < mapchip_image[map_num].size()) {
			return mapchip_image[map_num][image_num]; //�摜��Ԃ�
		}
	}
	return -1;
}

//�}�b�v�`�b�v�̉摜���폜
void Image::DeleteMapchipImage() {
	// �}�b�v�`�b�v�摜�̃����������
	for each (auto var in mapchip_image)
	{
		const int size = var.second.size();
		for (int i = 0; i < size; i++)
		{
			DeleteGraph(var.second[i]);
		}
		var.second.clear(); //�����������
	}
	mapchip_image.clear(); //�����������
}

//�w�i�̉摜�����[�h
void Image::LoadBackImage(int num) {
	// �ԍ����w�i�������̏ꍇ
	if ((unsigned)num < back_data.size()) {
		//�w�i��T��
		auto back_num = background.find(num); //�w�i������
		//�Ȃ������ꍇ
		if (back_num == background.end()) {
			background[num] = LoadGraph(back_data[num].name); //�w�i�����[�h
		}
	}
}

//�w�i�̉摜��Ԃ�(�摜�̔ԍ�)
int Image::GetBackImage(int num) {
	//�w�i��T��
	auto back_num = background.find(num); //�w�i������
	//�������ꍇ
	if (back_num != background.end()) {
		return background[num]; //�w�i��Ԃ�
	}
	return -1;
}

//�w�i�̉摜���폜
void Image::DeleteBackImage() {
	for each (auto var in background)
	{
		DeleteGraph(var.second);
	}
	background.clear(); //�����������
}

//�L�����̉摜�����[�h
void Image::LoadCharaImage() {
	// �L�����摜�̃��������m��
	for each (auto var in enemy_graphic_data)
	{
		int image_num = var.second.num_x * var.second.num_y; //�摜�̑���
		int *eimage = new int[image_num]; //��U�摜������ϐ�

		LoadDivGraph(var.second.name, image_num, var.second.num_x, var.second.num_y, var.second.size_x, var.second.size_y, eimage); //�摜�����[�h

		for (int i = 0; i < image_num; i++)
		{
			enemy_image[var.first].push_back(eimage[i]); //�摜������
		}
	}
}

//�L�����̉摜��Ԃ�(�L�����̔ԍ��A�摜�̔ԍ�)
int Image::GetCharaImage(int enemy_num, int image_num) {
	//�摜��T��
	auto einum = enemy_image.find(enemy_num); //�摜������
	//�������ꍇ
	if (einum != enemy_image.end()) {
		if ((unsigned)image_num < enemy_image[enemy_num].size()) {
			return enemy_image[enemy_num][image_num]; //�摜��Ԃ�
		}
	}
	return -1;
}

//�L�����̉摜���폜
void Image::DeleteCharaImage() {
	// �L�����摜�̃����������
	for each (auto var in enemy_image)
	{
		const int size = var.second.size();
		for (int i = 0; i < size; i++)
		{
			DeleteGraph(var.second[i]);
		}
		var.second.clear(); //�����������
	}
	enemy_image.clear(); //�����������
}

//�G�t�F�N�g�̉摜�����[�h
void Image::LoadEffectImage() {
	// �G�t�F�N�g�摜�̃��������m��
	for each (auto var in effect_graphic_data)
	{
		int image_num = var.second.num_x * var.second.num_y; //�摜�̑���
		int *eimage = new int[image_num]; //��U�摜������ϐ�

		LoadDivGraph(var.second.name, image_num, var.second.num_x, var.second.num_y, var.second.size_x, var.second.size_y, eimage); //�摜�����[�h

		for (int i = 0; i < image_num; i++)
		{
			effect_image[var.first].push_back(eimage[i]); //�摜������
		}
	}
}

//�G�t�F�N�g�̉摜��Ԃ�
int Image::GetEffectImage(int effect_num, int image_num) {
	//�摜��T��
	auto einum = effect_image.find(effect_num); //�摜������
	//�������ꍇ
	if (einum != effect_image.end()) {
		if ((unsigned)image_num < effect_image[effect_num].size()) {
			return effect_image[effect_num][image_num]; //�摜��Ԃ�
		}
	}
	return -1;
}

//�G�t�F�N�g�̉摜����Ԃ�
int Image::GetEffectSize(int effect_num) {
	//�摜��T��
	auto einum = effect_image.find(effect_num); //�摜������
	//�������ꍇ
	if (einum != effect_image.end()) {
		return effect_image[effect_num].size(); //�摜��Ԃ�
	}
	return 0;
}

//�G�t�F�N�g�̉摜���폜
void Image::DeleteEffectImage() {
	// �G�t�F�N�g�摜�̃����������
	for each (auto var in effect_image)
	{
		const int size = var.second.size();
		for (int i = 0; i < size; i++)
		{
			DeleteGraph(var.second[i]);
		}
		var.second.clear(); //�����������
	}
	effect_image.clear(); //�����������
}

//�e�̉摜�����[�h
void Image::LoadBulletImage() {
	// �G�t�F�N�g�摜�̃��������m��
	for each (auto var in bullet_graphic_data)
	{
		int image_num = var.second.num_x * var.second.num_y; //�摜�̑���
		int *bimage = new int[image_num]; //��U�摜������ϐ�

		LoadDivGraph(var.second.name, image_num, var.second.num_x, var.second.num_y, var.second.size_x, var.second.size_y, bimage); //�摜�����[�h

		for (int i = 0; i < image_num; i++)
		{
			bullet_image[var.first].push_back(bimage[i]); //�摜������
		}
	}
}

//�e�̉摜��Ԃ�
int Image::GetBulletImage(int bullet_num, int image_num) {
	//�摜��T��
	auto einum = bullet_image.find(bullet_num); //�摜������
	//�������ꍇ
	if (einum != bullet_image.end()) {
		if ((unsigned)image_num < bullet_image[bullet_num].size()) {
			return bullet_image[bullet_num][image_num]; //�摜��Ԃ�
		}
	}
	return -1;
}

//�e�̉摜���폜
void Image::DeleteBulletImage() {
	// �G�t�F�N�g�摜�̃����������
	for each (auto var in bullet_image)
	{
		const int size = var.second.size();
		for (int i = 0; i < size; i++)
		{
			DeleteGraph(var.second[i]);
		}
		var.second.clear(); //�����������
	}
	bullet_image.clear(); //�����������
}

//���������摜��ǂݍ���
int Image::LoadSingleImage(char file_name[64]) {
	int num = LoadGraph(file_name);
	image_hundle.push_back(num);
	return num;
}

//���������摜��ǂݍ���
void Image::LoadDividedImage(char *file_name, int num, int num_x, int num_y, int size_x, int size_y, int *hundle) {
	LoadDivGraph(file_name, num, num_x, num_y, size_x, size_y, hundle); //�摜�����[�h

	// �n���h�����Ǘ�
	for (int i = 0; i < num; i++)
	{
		image_hundle.push_back(hundle[i]);
	}
}

//�摜���폜
void Image::DeleteImage() {
	//�摜�̃����������
	const int size = image_hundle.size();
	for (int i = 0; i < size; i++)
	{
		DeleteGraph(image_hundle[i]);
	}
	image_hundle.clear();
}