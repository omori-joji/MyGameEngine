#pragma once
#include "Engine/GameObject.h"

class Title;

//�����V�[�����Ǘ�����N���X
class Setumei : public GameObject
{

	int hModel_;
	int sceneMoveTime_;

	Title* pTitle;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Setumei(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};

