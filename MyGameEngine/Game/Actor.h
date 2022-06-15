#pragma once
#include "../Engine/GameObject.h"
#include "Stage.h"
#include <string>

//�N���X�̑O���錾
class Stage;

class Actor : public GameObject
{
	char meanTimeGimmickNumber_;		//�����Ă���Ԕ�������{�^����1�̈�
	char no1DoubleGimmickNumber_;		//�Е��̓��������{�^����1�̈�
	char no2DoubleGimmickNumber_;		//�����Е��̓��������{�^����1�̈�
	bool isPastMeanTimeButton_;			//1�t���[���O�ɓ����{�^���𓥂�ł��邩���Ȃ���
	bool isPastDoubleButton_[2];		//1�t���[���O�ɓ���ł���Ԕ�������{�^���𓥂�ł��邩���Ȃ���
	int buttonSE_;						//SE���i�[����ϐ�
	Stage* pStage_;						//Stage�N���X���i�[����|�C���^
public:
	void Initialize() override;		//������
	void Update() override;			//�X�V
	void Draw() override;			//�`��
	void Release() override;		//�J��
	Actor(GameObject* parent, const std::string& name);//�R���X�g���N�^

	//����ł���Ԕ�������{�^���𓥂񂾏u�Ԃ̏���
	//�����F�Ȃ�
	//�߂�l�F�Ȃ�
	void CommonMeanTimeButtonDown();

	//���������{�^���̕Е��𓥂񂾏u�Ԃ̏���
	//�����F�Ȃ�
	//�߂�l�F�Ȃ�
	void No1DoubleButtonDown();	

	//�����Е��̓��������{�^���𓥂񂾏u�Ԃ̏���
	//�����F�Ȃ�
	//�߂�l�F�Ȃ�
	void No2DoubleButtonDown();
};

