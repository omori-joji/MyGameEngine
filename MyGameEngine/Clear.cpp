#include "Clear.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
Clear::Clear(GameObject* parent)
	: GameObject(parent, "Clear"), hModel_(-1)
{
}

//������
void Clear::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Assets/Clear.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Clear::Update()
{
	if (Input::IsKeyDown(DIK_1))
	{
		SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE2);
	}
}

//�`��
void Clear::Draw()
{
	Transform trans;

	trans.position_.x = 10;
	trans.position_.y = 15;
	trans.position_.z = 40;

	trans.Calclation();

	Model::SetTransform(hModel_, trans);
	Model::Draw(hModel_);
}

//�J��
void Clear::Release()
{
}