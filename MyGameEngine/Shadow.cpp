#include "Shadow.h"
#include "Stage.h"
#include "Engine/Model.h"
#include "Player.h"
#include "Engine/Input.h"

Shadow::Shadow(GameObject* parent)
	:GameObject(parent, "Shadow"),
	pPlayer_(nullptr),
	pStage_(nullptr),
    hModel_(-1),
	isRecording_(false),//Player�̓������L�^���Ă��邩
	frameCounter_(0)
{

}

void Shadow::Initialize()
{
	hModel_ = Model::Load("Assets/Player.fbx");
}

void Shadow::Update()
{
	if (pPlayer_ == nullptr)
	{
		pPlayer_ = (Player*)Find("Player");
	}

	if (pStage_ == nullptr)
	{
		pStage_ = (Stage*)Find("Stage");
	}



	//�L�^��
	if (isRecording_ == false)
	{
		//�ϒ��z��ɖ��t���[���v���C���[�̈ʒu���L�^����
		recordData_.push_back(pPlayer_->transform_.position_);
	}
	//�Đ���
	else if(frameCounter_<recordData_.size()-1 && isRecording_ == true)
	{

		//���t���[���e��Positon���v���C���[��Position�ɂ��Ă�����
		transform_.position_ = recordData_[frameCounter_];

		//���̃t���[����
		frameCounter_++;
	}



	//�Đ����I�������
	if (frameCounter_ >= recordData_.size() - 1)
	{

		//��\��
		isRecording_ = false;

		//�t���[�����̃��Z�b�g
		frameCounter_ = 0;
	}
}

void Shadow::Draw()
{
	//�\���E��\��
	if (isRecording_)
	{
		Model::SetTransform(hModel_, transform_);
		Model::Draw(hModel_);
	}

}

void Shadow::Release()
{
}

void Shadow::Collision()
{
}

void Shadow::Flag()
{
	isRecording_ = true;
	frameCounter_ = 0;
}
