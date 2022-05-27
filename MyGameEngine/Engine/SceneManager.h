#pragma once
#include "GameObject.h"
#include "Common.h"



//�Q�[���ɓo�ꂷ��V�[��
enum SCENE_ID
{
	SCENE_ID_TEST = 0,
	SCENE_ID_STAGE1,
	SCENE_ID_STAGE2,
	SCENE_ID_STAGE3,
	SCENE_ID_STAGE4,
	SCENE_ID_CLEAR,
	SCENE_ID_CLEDIT,
	SCENE_ID_TITLE,
	SCENE_ID_TITLE2,
	SCENE_ID_SETUMEI,
	SCENE_ID_DEBUG,
};

//-----------------------------------------------------------
//�V�[���؂�ւ���S������I�u�W�F�N�g
//-----------------------------------------------------------
class SceneManager : public GameObject
{
public:

	//�R���X�g���N�^
	//�����Fparent	�e�I�u�W�F�N�g�i��{�I�ɃQ�[���}�l�[�W���[�j
	SceneManager(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
	//�����Fnext	���̃V�[����ID
	void ChangeScene(SCENE_ID next);

	SCENE_ID SetnextSceneID(SCENE_ID x);
	SCENE_ID nextSceneID_;		//���̃V�[��

private:
	SCENE_ID currentSceneID_;	//���݂̃V�[��

	
};