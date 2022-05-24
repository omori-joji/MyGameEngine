#pragma once
#include "Engine/SceneManager.h"
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"


//Title�V�[�����Ǘ�����N���X
class Title : public GameObject
{
	int hModel_[3];
	int stageNumModel_[4];
	int se_[2];
	int stageNum_;
	int imageNum_;
	int chengeCount;

	bool iskeyDown_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Title(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

