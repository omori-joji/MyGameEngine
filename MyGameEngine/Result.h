#pragma once
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Audio.h"
//Result�V�[�����Ǘ�����N���X
class Result : public GameObject
{
	int hModel_;						//���f���ԍ����i�[����ϐ�
	const float BACK_GROUND_VERTICAL_;	//�w�i��Y���̍���
	const float BACK_GROUND_BESIDE_;	//�w�i��X���̍���
	const float BACK_GROUND_DEPTH_;		//�w�i�̉��s
	int resultBGM_;						//BGM���i�[����ϐ�
	const string FILE_PAS_;				//���U���g��ʂ̃��f���̃t�@�C���p�X
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Result(GameObject* parent);
	void Initialize() override;		//������
	void Update() override;			//�X�V
	void Draw() override;			//�`��
	void Release() override;		//�J��
};

