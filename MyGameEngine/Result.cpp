#include "Result.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
Result::Result(GameObject* parent)
	: GameObject(parent, "Result"), hModel_(-1)
{
}

//������
void Result::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load("Assets/StageBlock/Result.fbx");
	assert(hModel_ >= 0);
}

//�X�V
void Result::Update()
{
	if (Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TITLE2);
	}
}

//�`��
void Result::Draw()
{
	Transform trans;

	trans.position_.x = 28/2;
	trans.position_.y = 23/2;
	trans.position_.z = -21.4;

	trans.Calclation();

	Model::SetTransform(hModel_, trans);
	Model::Draw(hModel_);
}

//�J��
void Result::Release()
{
}