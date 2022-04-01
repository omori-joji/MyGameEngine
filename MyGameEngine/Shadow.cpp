#include "Shadow.h"

#include "Stage.h"
#include "Engine/Model.h"

Shadow::Shadow(GameObject* parent)
	:GameObject(parent, "Shadow"),
	pPlayer_(nullptr),
     hModel_(-1)
{
}

void Shadow::Initialize()
{
	hModel_ = Model::Load("Assets/Player.fbx");

	if (pPlayer_ == nullptr)
	{
		pPlayer_ = (Player*)Find("Player");
	}

	transform_.position_ = pPlayer_->stertPos_;
}

void Shadow::Update()
{





}

void Shadow::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Shadow::Release()
{
}
