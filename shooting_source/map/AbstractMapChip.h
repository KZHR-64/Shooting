#pragma once
#include "../character/CharacterBase.h"
#include "MapChipManager.h"
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

class MapChipManager;

class AbstractMapChip : public CharacterBase{
protected:
	MapChipManager* manager;

	bool live_flag; //���삷�邩
	bool draw_flag; //�`�悷�邩
	int image; //�\������摜
	int time; //�^�C�}�[
	float x; //x���W
	float y; //y���W(��ԏ����Ƃ���)
	float base_x; //���X��x���W
	float base_y; //���X��y���W
	int size_x; //���̑傫��
	int size_y; //�c�̑傫��
	float sx; //x�����̑��x
	float sy; //y�����̑��x
	float angle; //�p�x
	bool hit_flag; //�����蔻��
	bool inhale; //�z�����߂邩
	bool breakable; //�󂹂邩
	bool inhaled_flag; //�z�����܂�Ă��邩

public:
	AbstractMapChip(MapChipManager* man, int num); //�R���X�g���N�^(�摜�̔ԍ�)
	~AbstractMapChip(); //�f�X�g���N�^

	bool GetLiveFlag(); //���삷�邩���擾
	void SetLiveFlag(bool flag); //���삷�邩��ݒ�
	bool GetDrawFlag(); //�`�悷�邩���擾
	void SetDrawFlag(bool flag); //�`�悷�邩��ݒ�
	int GetTime(); //�}�b�v�`�b�v�̎��Ԃ�Ԃ�
	void SetTime(int set_time); //���Ԃ�ݒ�(����)
	float GetX(); //�}�b�v�`�b�v��x���W��Ԃ�
	void SetX(float set_x); //�}�b�v�`�b�v��x���W��ݒ�
	float GetY(); //�}�b�v�`�b�v��y���W��Ԃ�
	void SetY(float set_y); //�}�b�v�`�b�v��y���W��ݒ�
	float GetBaseX(); //�}�b�v�`�b�v�̌���x���W��Ԃ�
	void SetBaseX(float set_x); //�}�b�v�`�b�v�̌���x���W��ݒ�
	float GetBaseY(); //�}�b�v�`�b�v�̌���y���W��Ԃ�
	void SetBaseY(float set_y); //�}�b�v�`�b�v�̌���y���W��ݒ�
	int GetSizeX(); //�}�b�v�`�b�v�̉��̑傫����Ԃ�
	void SetSizeX(int set_size); //�}�b�v�`�b�v�̉��̑傫����ݒ�
	int GetSizeY(); //�}�b�v�`�b�v�̏c�̑傫����Ԃ�
	void SetSizeY(int set_size); //�}�b�v�`�b�v�̏c�̑傫����ݒ�
	float GetXSpeed(); //�}�b�v�`�b�v��x�����̑��x��Ԃ�
	void SetXSpeed(float set_x); //�}�b�v�`�b�v��x�����̑��x��ݒ�
	float GetYSpeed(); //�}�b�v�`�b�v��y�����̑��x��Ԃ�
	void SetYSpeed(float set_y); //�}�b�v�`�b�v��y�����̑��x��ݒ�
	float GetAngle(); //�p�x���擾
	void SetAngle(float set_angle); //�p�x��ݒ�(�p�x)
	float GetSpinSpeed(); //��]���x���擾
	void SetSpinSpeed(float set_angle); //��]���x��ݒ�(�p�x)
	bool GetHitFlag(); //�����蔻����擾
	void SetHitFlag(bool flag); //�����蔻���ݒ�
	bool GetInhale(); //�z�����߂邩���擾
	void SetInhale(bool flag); //�z�����߂邩��ݒ�
	bool GetBreakable(); //�󂹂邩���擾
	void SetBreakable(bool flag); //�󂹂邩��ݒ�
	bool GetInhaledFlag(); //�z�����܂�Ă��邩���擾
	void SetInhaledFlag(bool flag); //�z�����܂�Ă��邩��ݒ�

	virtual void Update() = 0;
};