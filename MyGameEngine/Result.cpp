#include "Result.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
Result::Result(GameObject* parent)
	: GameObject(parent, "Result"), 
	hModel_(-1),				//���f���ԍ����i�[����ϐ�
	BACK_GROUND_VERTICAL_(23),	//�w�i��Y���̍���
	BACK_GROUND_BESIDE_(28),	//�w�i��X���̍���
	BACK_GROUND_DEPTH_(-21.4f),	//�w�i�̉��s
	FILE_PAS_("Assets/Result/")	//���U���g��ʂ̃��f���̃t�@�C���p�X
{
}

//������
void Result::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_ = Model::Load(FILE_PAS_ + "Result.fbx");
}

//�X�V
void Result::Update()
{
	//SPACE�L�[����������^�C�g����ʂɈڍs
	if (Input::IsKeyDown(DIK_SPACE))
	{
		//SceneManager�N���X��T����
		SceneManager* pSceneManager = (SceneManager*)Find("SceneManager");

		//ChangeScene�ŃV�[����ς���
		pSceneManager->ChangeScene(SCENE_ID_TITLE);
	}
}

//�`��
void Result::Draw()
{
	//�w�i��`��
	Transform trans;

	//�ʒu����
	trans.position_.x = BACK_GROUND_BESIDE_ /2.0f;
	trans.position_.y = BACK_GROUND_VERTICAL_ /2.0f;
	trans.position_.z = BACK_GROUND_DEPTH_;

	//���[���h�s��
	trans.Calclation();

	//�`��J�n
	Model::SetTransform(hModel_, trans);
	Model::Draw(hModel_);
}

//�J��
void Result::Release()
{
}