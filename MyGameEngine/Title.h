#pragma once
#include "Engine/SceneManager.h"
#include "Engine/GameObject.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"

//Title�V�[�����Ǘ�����N���X
class Title : public GameObject
{
	const float BACK_GROUND_VERTICAL_;	//�w�i��Y���̒l
	const float BACK_GROUND_BESIDE_;	//�w�i��X���̒l
	const float DEPTH_;					//�w�i�̉��s
	const float STAGE_NUMBER_VERTICAL_;	//�X�e�[�W�ԍ�Y���̒l
	const float STAGE_NUMBER_BESIDE_;	//�X�e�[�W�ԍ�X���̒l
	const float SCALE_MAGNIFICATION_;	//�X�e�[�W�ԍ��̉��s
	const float DEPTH_DIFFERRENCE_;		//�w�i�Ƃ̉��s�̍�
	int stageNum_;						//�ڍs�������X�e�[�W�̃��f���ԍ�
	int imageNum_;						//�w�i�̃��f���ԍ�
	const string FILE_PAS_;				//Title�̃��f���f�[�^�̃t�@�C���p�X

	//�X�e�[�W�ԍ�
	enum
	{
		STAGE_NUMVER_1,	//�X�e�[�W�ԍ�1
		STAGE_NUMVER_2,	//�X�e�[�W�ԍ�2
		STAGE_NUMVER_3,	//�X�e�[�W�ԍ�3
		MODELE_NUMVER_4,	//�X�e�[�W�ԍ�4
		STAGE_NUMBER_MAX,
	};
	//�w�i�̃��f���ԍ�
	enum
	{
		BACKGROUND,
		BACKGROUND_NOWLOADING,
		MODELE_MAX,
	};
	//�T�E���h�ԍ�
	enum
	{
		SE_ARROW,			//���L�[���������Ƃ���SE
		SE_DECISION,		//����{�^����SE
		SE_MAX,
	};

	int se_[SE_MAX];							//SE���i�[����ϐ�
	int hModel_[MODELE_MAX];					//���f�����i�[����ϐ�
	int stageNum_Modele_[STAGE_NUMBER_MAX];		//�X�e�[�W�ԍ��̃��f�����i�[����ϐ�
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Title(GameObject* parent);
	void Initialize() override;		//������
	void Update() override;			//�X�V
	void Draw() override;			//�`��
	void Release() override;		//�J��
};

