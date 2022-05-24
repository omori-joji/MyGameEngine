#include "sceneManager.h"
#include "../PlayScene.h"
#include "Model.h"
#include "../Stage.h"
#include "../Result.h"
#include "../Title.h"

//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{

}

//������
void SceneManager::Initialize()
{
	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<Result>(this);
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
		   case SCENE_ID_STAGE1: Instantiate<Stage>(this); break;
		   case SCENE_ID_STAGE2: Instantiate<Stage>(this); break;
		   case SCENE_ID_STAGE3: Instantiate<Stage>(this); break;
		   case SCENE_ID_STAGE4: Instantiate<Stage>(this); break;
		   case SCENE_ID_CLEAR: Instantiate<Result>(this); break;
		   case SCENE_ID_TITLE2: Instantiate<Title>(this); break;
		}
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

SCENE_ID SceneManager::SetnextSceneID(SCENE_ID x)
{
	x = nextSceneID_;
	return x;
}
