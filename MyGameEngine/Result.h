#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
//Result�V�[�����Ǘ�����N���X
class Result : public GameObject
{
	int hModel_;						//���f���ԍ����i�[����ϐ�
	const int BACK_GROUND_VERTICAL_;	//�w�i��Y���̍���
	const int BACK_GROUND_BESIDE_;		//�w�i��X���̍���
	const float BACK_GROUND_DEPTH_;		//�w�i�̉��s
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Result(GameObject* parent);
	void Initialize() override;		//������
	void Update() override;			//�X�V
	void Draw() override;			//�`��
	void Release() override;		//�J��
};

