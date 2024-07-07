#pragma once
#include "../character/CharacterBase.h"
#include "EffectManager.h"
#include "../Define.h"
//#include "Game.h"
//#include "Map.h"
//#include "Bullet.h"
//#include "Enemy.h"
//#include "Effect.h"
#include "../single/Key.h"
#include "../single/Display.h"
#include "../single/Image.h"
#include <memory>

class EffectManager;

class AbstractEffect : public CharacterBase{
protected:
	EffectManager* manager;

	bool flag; //�\�����邩
	bool end_flag; //�������邩
	int image; //�\������摜
	int time; //�^�C�}�[
	float x; //x���W
	float y; //y���W(��ԏ����Ƃ���)
	float base_x; //���X��x���W
	float base_y; //���X��y���W
	float sx; //x�����̑��x
	float sy; //y�����̑��x
	float angle; //�p�x

public:
	AbstractEffect(EffectManager* man, int num, float ini_x, float ini_y); //�R���X�g���N�^(�摜�̔ԍ��A���W)
	~AbstractEffect(); //�f�X�g���N�^

	bool GetEndFlag(); //�������邩���擾
	void SetEndFlag(bool set_flag); //�������邩��ݒ�
	int GetTime(); //�G�t�F�N�g�̎��Ԃ�Ԃ�
	void SetTime(int set_time); //���Ԃ�ݒ�(����)
	float GetX(); //�G�t�F�N�g��x���W��Ԃ�
	void SetX(float set_x); //�G�t�F�N�g��x���W��ݒ�
	float GetY(); //�G�t�F�N�g��y���W��Ԃ�
	void SetY(float set_y); //�G�t�F�N�g��y���W��ݒ�
	float GetBaseX(); //�G�t�F�N�g�̌���x���W��Ԃ�
	void SetBaseX(float set_x); //�G�t�F�N�g�̌���x���W��ݒ�
	float GetBaseY(); //�G�t�F�N�g�̌���y���W��Ԃ�
	void SetBaseY(float set_y); //�G�t�F�N�g�̌���y���W��ݒ�
	float GetXSpeed(); //�G�t�F�N�g��x�����̑��x��Ԃ�
	void SetXSpeed(float set_x); //�G�t�F�N�g��x�����̑��x��ݒ�
	float GetYSpeed(); //�G�t�F�N�g��y�����̑��x��Ԃ�
	void SetYSpeed(float set_y); //�G�t�F�N�g��y�����̑��x��ݒ�
	float GetAngle(); //�p�x���擾
	void SetAngle(float set_angle); //�p�x��ݒ�(�p�x)
	float GetSpinSpeed(); //��]���x���擾
	void SetSpinSpeed(float set_angle); //��]���x��ݒ�(�p�x)

	virtual void Update() = 0;
};