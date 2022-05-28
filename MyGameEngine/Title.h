#pragma once
#include "Engine/SceneManager.h"
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"

//Title�V�[�����Ǘ�����N���X
class Title : public GameObject
{
	const int BACK_GROUND_VERTICAL_;	//�w�i��Y���̒l
	const int BACK_GROUND_BESIDE_;		//�w�i��X���̒l
	const float DEPTH_;					//�w�i�̉��s
	const float STAGE_NUMBER_VERTICAL_;	//�X�e�[�W�ԍ�Y���̒l
	const float STAGE_NUMBER_BESIDE_;	//�X�e�[�W�ԍ�X���̒l
	const float SCALE_MAGNIFICATION_;	//�X�e�[�W�ԍ��̉��s
	int stageNum_;//�ڍs�������X�e�[�W�̃��f���ԍ�
	int imageNum_;//�w�i�̃��f���ԍ�

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
	int se_[MAX_SE];							//SE���i�[����ϐ�
	int hModel_[MAX_MODELE];					//���f�����i�[����ϐ�
	int stageNum_Modele_[MAX_STAGE_NUMBER];		//�X�e�[�W�ԍ��̃��f�����i�[����ϐ�
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Title(GameObject* parent);
	void Initialize() override;		//������
	void Update() override;			//�X�V
	void Draw() override;			//�`��
	void Release() override;		//�J��
};

