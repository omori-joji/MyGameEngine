#pragma once
#include "GameObject.h"
#include "Common.h"

//�Q�[���ɓo�ꂷ��V�[��
enum SCENE_ID
{
	SCENE_ID_STAGE1,//STAGE1
	SCENE_ID_STAGE2,//STAGE2
	SCENE_ID_STAGE3,//STAGE3
	SCENE_ID_STAGE4,//STAGE4
	SCENE_ID_CLEAR,//�N���A���
	SCENE_ID_TITLE,//��ԍŏ��̃^�C�g��
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
	void Initialize() override;				//������
	void Update() override;					//�X�V
	void Draw() override;					//�`��
	void Release() override;				//���

	//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
	//�����Fnext	���̃V�[����ID
	//�����ȂƂ��Ŏg���̂�public�ɂ��Ă���
	void ChangeScene(SCENE_ID next);
	SCENE_ID SetnextSceneID(SCENE_ID x);	//���̃V�[����o�^����֐�
	SCENE_ID nextSceneID_;					//���̃V�[��
private:
	SCENE_ID currentSceneID_;				//���݂̃V�[��
};