#pragma once

class CharacterBase{
protected:

public:
	struct HitDataStruct
	{
		//�����蔻����̍\����
		float x; //x���W
		float y; //y���W
		int size; //�傫��
	};
	struct HitStruct
	{
		//�����蔻��̍\����
		float x; //x���W
		float y; //y���W
		float distance; //�{�̂Ƃ̒�������
		float angle; //�����̊p�x
		float size; //�傫��
	};
	virtual ~CharacterBase(){}
	virtual void Draw() = 0; //�`��
};