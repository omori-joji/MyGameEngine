#include "../PlayScene.h"
#include "../Stage.h"
#include "../Result.h"
#include "../Title.h"
#include "sceneManager.h"
#include "Model.h"

//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager"),
	nextSceneID_(),
	currentSceneID_()
{
}

//������
void SceneManager::Initialize()
{
	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<Title>(this);
}

//�X�V
void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();

		//���[�h�����f�[�^��S�폜
		Model::AllRelease();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		   case SCENE_ID_STAGE1: Instantiate<Stage>(this); break;	//STAGE1
		   case SCENE_ID_STAGE2: Instantiate<Stage>(this); break;	//STAGE2
		   case SCENE_ID_STAGE3: Instantiate<Stage>(this); break;	//STAGE3
		   case SCENE_ID_STAGE4: Instantiate<Stage>(this); break;	//STAGE4
		   case SCENE_ID_TITLE: Instantiate<Title>(this); break;	//�^�C�g�����
		   case SCENE_ID_CLEAR: Instantiate<Result>(this); break;	//�N���A���
		   case SCENE_ID_DEBUG: Instantiate<Stage>(this); break;	//�f�o�b�O�p
		}
		//���̃V�[�������݂̃V�[���ɓ���ւ���
		currentSceneID_ = nextSceneID_;
	}
}

//�`��
void SceneManager::Draw()
{
}

//�J��
void SceneManager::Release()
{
}

//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}

//���̃V�[����o�^����֐�
SCENE_ID SceneManager::SetnextSceneID(SCENE_ID x)
{
	x = nextSceneID_;
	return x;
}
