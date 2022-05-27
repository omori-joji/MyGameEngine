#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
#include "Engine/Fbx.h"
#include "Stage.h"
#include <string>

class Stage;

class Basic : public GameObject
{
	char meanTimeGimmickNumber_;		//�����Ă���Ԕ�������{�^����1�̈�
	char no1DoubleGimmickNumber_;		//�Е��̓��������{�^����1�̈�
	char no2DoubleGimmickNumber_;		//�����Е��̓��������{�^����1�̈�
	bool isPastMeanTimeButton_;			//1�t���[���O�ɓ����{�^���𓥂�ł��邩���Ȃ���
	bool isPastDoubleButton_[2];		//1�t���[���O�ɓ���ł���Ԕ�������{�^���𓥂�ł��邩���Ȃ���
	Stage* pStage_;						//Stage�N���X���i�[����|�C���^
public:
	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
	Basic(GameObject* parent, const std::string& name);//�R���X�g���N�^
	void CommonMeanTimeButtonDown();			//����ł���Ԕ�������{�^���𓥂񂾏u�Ԃ̏���
	void No1DoubleButtonDown();					//���������{�^���̕Е��𓥂񂾏u�Ԃ̏���
	void No2DoubleButtonDown();					//�����Е��̓��������{�^���𓥂񂾏u�Ԃ̏���
};

