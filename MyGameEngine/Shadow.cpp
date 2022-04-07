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
	isRecording_(false),//Playerの動きを記録しているか
	frameCounter_(0)
{

}

void Shadow::Initialize()
{
	hModel_ = Model::Load("Assets/Player.fbx");
}

void Shadow::Update()
{
	int a = 0;
	if (pPlayer_ == nullptr)
	{
		pPlayer_ = (Player*)Find("Player");
	}

	if (pStage_ == nullptr)
	{
		pStage_ = (Stage*)Find("Stage");
	}



	//記録中
	if (isRecording_ == false)
	{
		//可変長配列に毎フレームプレイヤーの位置を記録する
		recordData_.push_back(pPlayer_->transform_.position_);
	}
	//再生中
	else if(frameCounter_<recordData_.size()-1 && isRecording_ == true)
	{
		int a = 0;
		transform_.position_ = recordData_[frameCounter_];
		frameCounter_++;
	}
	//再生が終わったらもう一度再生し始める
	else if(frameCounter_>=recordData_.size()-1 && isRecording_ == true)
	{
		frameCounter_ = 0;
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

void Shadow::Flag()
{
	isRecording_ = true;
}
