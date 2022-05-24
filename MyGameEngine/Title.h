#pragma once
#include "Engine/SceneManager.h"
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"


//Title�V�[�����Ǘ�����N���X
class Title : public GameObject
{
	const int BACK_GROUND_VERTICAL_;
	const int BACK_GROUND_BESIDE_;
	const float DEPTH_;
	const float STAGE_NUMBER_VERTICAL_;
	const float STAGE_NUMBER_BESIDE_;
	const float SCALE_MAGNIFICATION_;

	int stageNum_;
	int imageNum_;
	int chengeCount_;
	enum
	{
		MODELE_NUMVER_1,
		MODELE_NUMVER_2,
		MODELE_NUMVER_3,
		MODELE_NUMVER_4,

		SE_NUMBER_1 = 0,
		SE_NUMBER_2,

		MAX_SE = 2,
		MAX_MODELE,
		MAX_STAGE_NUMBER,
	};
	int se_[MAX_SE];
	int hModel_[MAX_MODELE];
	int stageNum_Modele_[MAX_STAGE_NUMBER];

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

