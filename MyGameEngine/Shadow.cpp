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


	pPlayer_ = (Player*)Find("Player");
	pStage_ = (Stage*)Find("Stage");

	//transform_.position_ = pStage_->stertPos;
}

void Shadow::Update()
{
	int a = 1;

	//�L�^��
	if (isRecording_ == false)
	{
		//�ϒ��z��ɖ��t���[���v���C���[�̈ʒu���L�^����
		recordData_.push_back(pPlayer_->transform_.position_);
	}
	//�Đ���
	else if(frameCounter_<recordData_.size()-1 && isRecording_ == true)
	{
		transform_.position_ = recordData_[frameCounter_];
		frameCounter_++;
	}
	//�Đ����I������������x�Đ����n�߂�
	else if(frameCounter_>=recordData_.size()-1 && isRecording_ == true)
	{
		frameCounter_ = 0;
	}
	

	if (Input::IsKeyDown(DIK_LSHIFT) || Input::IsKeyDown(DIK_RSHIFT))
	{
		isRecording_ = true;
	}
}

void Shadow::Draw()
{
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
